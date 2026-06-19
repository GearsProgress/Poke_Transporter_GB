#include <tonc.h>
#include <stdarg.h>
#include <inttypes.h>
#include "libraries/nanoprintf/nanoprintf.h"
#include "libstd_replacements.h"
#include "link_handler.h"
#include "script_array.h"
#include "dbg/debug_mode.h"
#include "interrupt.h"
#include "text_engine.h"
#include "global_frame_controller.h"
#include "background_engine.h"
#include "sprite_data.h"
#include "libraries/Pokemon-Gen3-to-Gen-X/include/save.h"
#include "flash_mem.h"
#include "FileContainerReader.h"
#include "text_tables.h"
#include "translated_text.h"

#include "GB_Payloads_chunk0_lz10_bin.h"
#include "GB_Payloads_chunk1_lz10_bin.h"
#include "GB_Payloads_chunk2_lz10_bin.h"
#include "GB_Payloads_chunk3_lz10_bin.h"
#include "GB_Payloads.h"

LinkSPI linkSPIInstance;
LinkSPI *linkSPI = &linkSPIInstance;

// Here's a compilation check to ensure that the size of these structs match our expectations.
// Just update it if you changed the struct members. The data-generator process prints their actual sizes.
static_assert(sizeof(struct GB_ROM) == 136);
static_assert(sizeof(struct ROM_DATA) == 160);

LinkConnection globalLinkCable;

void linkCableIRQ()
{
  /*
  ----------------
  This handshake process can be a bit weird, so let's break it down:

  First we exchange the bytes via handshake. inData will be set to the recieved byte, and the byte we send out will be outData.

  Then we determining what byte we will be sending out next, based on enterState and inByte in handleStateLogic().
  This will set exitState and nextOutByte.

  Then we print our information in the following format: globalCounter enterState:stateCounter:exitState inData outData

  We then prepare for the next cycle. Counters are incremented (or reset), enterState is set to exitState, and outByte is set to nextOutByte.
  ----------------
  */
  if (!globalLinkCable.earlyExit())
  {
    globalLinkCable.exchangeBytes();

    globalLinkCable.handleStateLogic();

    if (g_debug_options.print_link_data || g_debug_options.print_link_packets)
    {
      globalLinkCable.printData();
    }

    if (g_debug_options.write_cable_data_to_save)
    {
      globalLinkCable.writeData();
    }

    globalLinkCable.prepareForNextCycle();
  }
}

void LinkConnection::setup(const u16 *debug_charset)
{
  link_cable_memory_section_index = 0;
  link_cable_array_index = 0;
  writeBufferOffset = 0;

  linkSPI->activate(LinkSPI::Mode::MASTER_256KBPS);
  linkSPI->setWaitModeActive(false);

  this->debug_charset = debug_charset;

  lastError = NO_ERROR;

  if (g_debug_options.print_link_data == true)
  {
    create_textbox(0, 0, 138, 128, false);
  }

  if (g_debug_options.write_cable_data_to_save == WRITE_CABLE_DATA_MODE_SRAM)
  {
    // if we're writing the cable data to SRAM, we should clear the SRAM first to make sure there's no leftover data from previous transfers
    volatile u8 *cur = SRAM_PTR;
    volatile u8 *end = SRAM_PTR + 0x10000;
    while (cur < end)
    {
      (*cur) = 0;
      ++cur;
    }
  }
  else if (g_debug_options.write_cable_data_to_save == WRITE_CABLE_DATA_MODE_CART)
  {
    // before each write, we need to erase the sector.
    // so, let's do that for the first one before we start writing anything.
    erase_sector(0);
  }
}

void LinkConnection::loadPayload(GB_PayloadsFiles payload)
{
  u32 fileSize;
  u8 decompressionBuffer[0x1000];
  const u8 *chunkList[] = {
      (const u8 *)GB_Payloads_chunk0_lz10_bin,
      (const u8 *)GB_Payloads_chunk1_lz10_bin,
      (const u8 *)GB_Payloads_chunk2_lz10_bin,
      (const u8 *)GB_Payloads_chunk3_lz10_bin,
  };
  FileContainerReader reader(chunkList, 4);
  const u32 fileIndex = (u32)payload;

  reader.init(decompressionBuffer, sizeof(decompressionBuffer));
  fileSize = reader.getFileSize(fileIndex);
  reader.seekToFile(fileIndex);
  reader.read(this->payloadBuffer, fileSize);

  this->curr_payload_size = fileSize;
}

void LinkConnection::loadPayloadByROM(GameBoyROM rom)
{
  loadPayload(GameBoyROMPayloads[rom]);
  lang = GameBoyROMLanguages[rom];
}

void LinkConnection::loadCurrGameFromChecksum()
{
  if (((dataOutBuffer[0] + dataOutBuffer[1]) & 0x7F) != dataOutBuffer[3])
  {
    currROM = GB_ROM_ERROR;
  };

  int start = RED_JP_v0;
  int end = GOLD_JP_v0;

  if (gen == 2)
  {
    start = end;
    end = NO_GB_ROM;
  }

  for (int i = start; i < end; i++)
  {
    if (dataOutBuffer[0] == GameBoyROMChecksumTable[i][1] && dataOutBuffer[1] == GameBoyROMChecksumTable[i][2])
    {
      currROM = (GameBoyROM)GameBoyROMChecksumTable[i][3];
      return;
    }
  }
  currROM = GB_ROM_ERROR;
  return;
}

void LinkConnection::exchangeBytes()
{
  /*
  int timeout_frames = 10;
  inData = linkSPI->transfer(outData, [&timeout_frames]()
                             {
      // In the mGBA Lua bridge, replies arrive via emulator callbacks between frames.
      // Waiting here prevents valid bytes from being reported as timeouts.
      global_next_frame();
      return --timeout_frames <= 0; });
  */
  switch (g_debug_options.load_cable_data_from_save)
  {
  case WRITE_CABLE_DATA_MODE_OFF:
    // Normal transfer :-)
    inData = linkSPI->transfer(outData);
    break;
  case WRITE_CABLE_DATA_MODE_SRAM:
    // Pretend transfer, by loading the bytes from SRAM (where we stored them with writeData() in a previous transfer)
    inData = (*(SRAM_PTR + link_cable_array_index));
    ++link_cable_array_index;
    outData = (*(SRAM_PTR + link_cable_array_index));
    ++link_cable_array_index;
    break;
  case WRITE_CABLE_DATA_MODE_CART:
  {
    // Pretend transfer, by loading the bytes from the cartridge save. (where we stored them with writeData() in a previous transfer)
    // skip the first 6 bytes, which are for human consumption
    link_cable_array_index += 6;

    inData = read_byte_save((0x1000 * link_cable_memory_section_index) + link_cable_array_index);
    ++link_cable_array_index;
    outData = read_byte_save((0x1000 * link_cable_memory_section_index) + link_cable_array_index);
    ++link_cable_array_index;

    if (link_cable_array_index >= 0x1000)
    {
      // if we reached the end of the section, we need to load the next section (if there is one)
      ++link_cable_memory_section_index;
      link_cable_array_index = 0;
    }
    break;
  }
  }
}

void LinkConnection::startConnection(LinkState startState)
{
  switch (startState)
  {
  case INITIAL_CONNECTION:
    REG_TM3D = -0x4000 / 60;
    REG_TM3CNT = TM_FREQ_1024 | TM_ENABLE;
    break;
  case PACKET_EXCHANGE:
    REG_TM3D = -0x0040;
    // REG_TM3D = -0x4000 / 2;
    REG_TM3CNT = TM_FREQ_1024 | TM_ENABLE;
    break;
  default:
    break;
  }

  enterState = startState;
  irq_enable(II_TIMER3);
}

void LinkConnection::printData()
{
  if (globalLinkCable.skipPrint)
  {
    tte_erase_rect(0, 0, H_MAX, V_MAX);
  }
  else
  {
    if (g_debug_options.print_link_data)
    {
      n2hexstr(&line[0], globalStateCounter & 0xFFFF, 4);
      line[4] = '|';
      n2hexstr(&line[5], enterState & 0xFF, 2);
      line[7] = ':';
      n2hexstr(&line[8], subStateCounter & 0xFFFF, 4);
      line[12] = ':';
      n2hexstr(&line[13], exitState & 0xFF, 2);
      line[15] = '|';
      line[16] = 'i';
      n2hexstr(&line[17], inData & 0xFF, 2);
      line[19] = '|';
      line[20] = 'o';
      n2hexstr(&line[21], outData & 0xFF, 2);
      line[23] = '\0';
      scroll_text(true, tte_get_context(), false, 8, 8, 138, 135);
      ptgb_write_debug(this->debug_charset, line, true);
    }

    // TODO: This is pretty rough, but it's the best we can do until the text engine rewrite.
    if (g_debug_options.print_link_packets)
    {
      tte_erase_rect(160, 16, H_MAX, V_MAX);
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          n2hexstr(&line[3 * j], dataOutBuffer[(4 * i) + j], 2);
          line[(3 * j) + 2] = ' ';
        }
        line[12] = '\0';
        tte_set_pos(160, 16 * i);
        ptgb_write_debug(this->debug_charset, line, true);
      }

      for (int i = 0; i < 4; i++)
      {
        byte tempBuffer[16];
        int packetIndex = dataOutBuffer[INP_COUNTER_INDEX];
        LinkPacket &currLinkPacket = linkPacketArr[packetIndex];

        tempBuffer[0] = packetIndex;
        tempBuffer[1] = currLinkPacket.command;
        tempBuffer[2] = currLinkPacket.pointer >> 0;
        tempBuffer[3] = currLinkPacket.pointer >> 8;
        memcpy(&tempBuffer[4], currLinkPacket.argument, 2);
        tempBuffer[6] = currLinkPacket.latestError;
        tempBuffer[7] = 0x00;
        memcpy(&tempBuffer[8], currLinkPacket.recievedData, 8);

        for (int j = 0; j < 4; j++)
        {
          n2hexstr(&line[3 * j], tempBuffer[(4 * i) + j], 2);
          line[(3 * j) + 2] = ' ';
        }
        line[12] = '\0';
        tte_set_pos(160, (16 * 5) + (16 * i));
        ptgb_write_debug(this->debug_charset, line, true);
      }
    }
  }
}

void LinkConnection::writeData()
{
  switch (g_debug_options.write_cable_data_to_save)
  {
  case WRITE_CABLE_DATA_MODE_OFF:
    break;
  case WRITE_CABLE_DATA_MODE_SRAM:
  {
    (*(SRAM_PTR + link_cable_array_index)) = inData;
    ++link_cable_array_index;

    (*(SRAM_PTR + link_cable_array_index)) = outData;
    ++link_cable_array_index;
    break;
  }
  case WRITE_CABLE_DATA_MODE_CART:
  {
    // save the data to the cartridge in chunks of 4 KB
    // WARNING: If you want to add or remove fields here,
    // make sure to keep the number of bytes a clean divider of 4096 (global_memory_buffer_size)

    // the next 6 bytes are for human consumption when viewed in a hex editor.
    // they can be useful to correlate the current LinkConnection state with the data that was sent over the cable.
    // but they're not needed for reconstructing the conversation with load_cable_data_from_save
    global_memory_buffer[writeBufferOffset + 0] = (u8)(globalStateCounter >> 8) & 0xFF;
    global_memory_buffer[writeBufferOffset + 1] = (u8)(globalStateCounter >> 0) & 0xFF;
    global_memory_buffer[writeBufferOffset + 2] = (u8)enterState;
    global_memory_buffer[writeBufferOffset + 3] = (u8)(subStateCounter >> 8) & 0xFF;
    global_memory_buffer[writeBufferOffset + 4] = (u8)(subStateCounter >> 0) & 0xFF;
    global_memory_buffer[writeBufferOffset + 5] = (u8)exitState;

    // actual data bytes start here.
    global_memory_buffer[writeBufferOffset + 6] = inData;
    global_memory_buffer[writeBufferOffset + 7] = outData;

    writeBufferOffset += 8;

    break;
  }
  }
}

void LinkConnection::handleStateLogic()
{
  switch (enterState)
  {
  case INITIAL_CONNECTION:
    nextOutData = 0xFF;
    exitState = CLOCK;
    break;

  case CLOCK:
    if (inData == 0xFE)
    {
      exitState = SAVE_SUCCESS;
      nextOutData = 0x00;
    }
    else
    {
      nextOutData = 0x01;
    }
    break;

  case SAVE_SUCCESS:
    if (inData == 0x60 || inData == 0x61)
    {
      exitState = MENU_OPEN;
      nextOutData = inData;
    }
    // nextOutData defaults to 0x00
    break;

  case MENU_OPEN:
    if (inData == 0xD0 || inData == 0x61)
    {
      if (inData == 0xD0)
      {
        gen = 1;
        loadPayload(GB_PayloadsFiles::UNIVERSALPAYLOADGEN1);
        nextOutData = 0xD4;
      }
      else if (inData == 0x61)
      {
        gen = 2;
        loadPayload(GB_PayloadsFiles::UNIVERSALPAYLOADGEN2);
        nextOutData = 0x61;
      }
      exitState = MENU_SUCCESS;
    }
    break;

  case MENU_SUCCESS:
    if (inData == 0xFE)
    {
      exitState = WAIT_FOR_TRADE;
    }
    nextOutData = inData;
    break;

  case WAIT_FOR_TRADE:
    if (inData == 0xFD)
    {
      REG_TM3D = -0x0040;
      exitState = TRADE_PREAMBLE;
      // nextOutData defaults to 0x00
    }
    else
    {
      nextOutData = inData;
    }
    break;

  case TRADE_PREAMBLE:
    if (subStateCounter < 2)
    {
      // nextOutData defaults to 0x00
    }
    else if (subStateCounter < 9)
    {
      nextOutData = 0xFD;
    }
    else
    {
      exitState = TRADE;
      nextOutData = 0xFD;
    };
    break;

  case TRADE:
    if (subStateCounter > curr_payload_size)
    {
      if (this->gen == 2)
      {
        exitState = MAIL;
      }
      else
      {
        exitState = WAIT_FOR_CHECKSUM_PAYLOAD;
      }
    }
    nextOutData = payloadBuffer[subStateCounter];
    break;

  case MAIL:
    if (subStateCounter > 0x186)
    {
      exitState = WAIT_FOR_CHECKSUM_PAYLOAD;
    }
    nextOutData = 0x00;
    break;

  case WAIT_FOR_CHECKSUM_PAYLOAD:
    if (inData == 0xFD)
    {
      exitState = GET_CHECKSUM;
    }
    // nextOutData defaults to 0x00
    break;

  case GET_CHECKSUM:
    if (inData != 0xFD)
    {
      dataOutBuffer[dataOutBufferCurrIndex] = inData;
      dataOutBufferCurrIndex++;
      nextOutData = 0x01;
    }
    else if (inData == 0xFD && dataOutBufferCurrIndex > 0)
    {
      loadCurrGameFromChecksum();
      loadPayloadByROM(currROM);
      exitState = SEND_SPECIFIC_PAYLOAD;
    }
    else
    {
      nextOutData = 0xFD;
    }
    break;

  case WAIT_FOR_SECOND_PAYLOAD:
    if (inData == 0xFD)
    {
      exitState = SEND_SPECIFIC_PAYLOAD;
    }
    // nextOutData defaults to 0x00
    break;

  case SEND_SPECIFIC_PAYLOAD:
    if (subStateCounter > 255) // The 255 comes from the Universal Payload
    {
      exitState = END;
    }
    if (subStateCounter < curr_payload_size)
    {
      nextOutData = payloadBuffer[subStateCounter];
    }
    else
    {
      nextOutData = 0x01;
    }
    break;

  case PACKET_EXCHANGE:
    nextOutData = 0xFF;
    exitState = BYTE_EXCHANGE;
    break;

  case BYTE_EXCHANGE:
  {
    switch (subStateCounter % TOTAL_PACKET_LENGTH)
    {
    case 0:
      nextOutData = 0xFD;
      break;
    case 1:
      nextOutData = linkPacketArrIndex;
      linkPacketArr[linkPacketArrIndex % LINK_PACKET_ARRAY_SIZE].packetID = linkPacketArrIndex;
      break;
    case 2:
      nextOutData = linkPacketArr[linkPacketArrIndex % LINK_PACKET_ARRAY_SIZE].command;
      break;
    case 3:
      nextOutData = linkPacketArr[linkPacketArrIndex % LINK_PACKET_ARRAY_SIZE].argument[0];
      break;
    case 4:
      nextOutData = linkPacketArr[linkPacketArrIndex % LINK_PACKET_ARRAY_SIZE].argument[1];
      break;
    case 5:
      nextOutData = linkPacketArr[linkPacketArrIndex % LINK_PACKET_ARRAY_SIZE].pointer >> 0;
      break;
    case 6:
      nextOutData = linkPacketArr[linkPacketArrIndex % LINK_PACKET_ARRAY_SIZE].pointer >> 8;
      break;
    case TOTAL_PACKET_LENGTH - 1:
      linkPacketArrIndex = (linkPacketArrIndex + 1) & 0x7F;
    default:
      nextOutData = 0xFF;
      break;
    }

    if (allPacketsProcessed())
    {
      exitState = PRINT_LAST_PACKET;
    }

    if (subStateCounter % TOTAL_PACKET_LENGTH == 0)
    {
      newPacket = true;
      processPacket();
    }
    else
    {
      newPacket = false;
    }

    dataOutBuffer[subStateCounter % TOTAL_PACKET_LENGTH] = inData;
  }
  break;

  case PRINT_LAST_PACKET:
    nextOutData = 0xFF;
    exitState = END;
    break;

  case END:
    irq_disable(II_TIMER3);
    break;

  default:
    nextOutData = inData;
    break;
  }
}

void LinkConnection::prepareForNextCycle()
{
  if (exitState != enterState)
  {
    subStateCounter = 0;
    subStateChanged = true;
  }
  else
  {
    subStateCounter++;
    subStateChanged = false;
  }

  if (newPacket)
  {
    loadNextPacket();
  }

  globalStateCounter++;
  enterState = exitState;
  outData = nextOutData;
}

/*
 * So, dealing with writing to the cartridge in the IRQ handler was a no-go.
 * It just caused too many issues with data corruption, probably because the write and erase_sector
 * operation was taking too long.
 *
 * So, I moved it to the main loop through this function.
 * However, we need to be aware that this function can get interrupted by the IRQ handler at any time.
 *
 * We also need to take care to not have global_memory_buffer overflow as the IRQ handler just keeps adding to it.
 */
void LinkConnection::handleCartIO()
{
  u8 writeBuffer[0x1000];
  unsigned curBufDepth = writeBufferOffset;

  // first copy the current data to a local buffer. Note: the IRQ handler could append new data to global_memory_buffer during this call!
  memcpy(writeBuffer, global_memory_buffer, curBufDepth);
  // by updating the writeBufferOffset already, we allow the IRQ handler to start writing at the new right position
  // immediately.
  writeBufferOffset -= curBufDepth;
  // now move any data received during the memcpy to before writeBufferOffset, so it will be included in the next batch.
  // Note: keep in mind, here too the IRQ handler may be appending new data to global_memory_buffer and increase writeBufferOffset.
  // but it's harmless.
  memmove(global_memory_buffer, global_memory_buffer + curBufDepth, writeBufferOffset);

  u8 *curWriteBuf = writeBuffer;
  const u8 *const endWriteBuf = writeBuffer + curBufDepth;

  while (curWriteBuf < endWriteBuf)
  {
    // make sure not to write beyond the current flash sector's boundaries. We'll need an erase_sector() call before
    // we write to the next sector.
    const unsigned bytesRemainingInSector = 0x1000 - link_cable_array_index;
    const unsigned bytesToWrite = (curBufDepth < bytesRemainingInSector) ? curBufDepth : bytesRemainingInSector;

    copy_ram_to_save(curWriteBuf, (0x1000 * link_cable_memory_section_index) + link_cable_array_index, bytesToWrite);
    curWriteBuf += bytesToWrite;
    curBufDepth -= bytesToWrite;
    link_cable_array_index += bytesToWrite;

    if (link_cable_array_index >= 0x1000)
    {
      // we have reached the end of our current sector. Let's erase the next one.
      link_cable_array_index = 0;
      ++link_cable_memory_section_index;
      erase_sector(0x1000 * link_cable_memory_section_index);
    }
  }
}

bool LinkConnection::earlyExit()
{
  if (g_debug_options.print_link_data && !skipPrint && key_held(KEY_LEFT))
  {
    pauseOnByte = true;
    pauseOnPacket = false;
  }
  else if (g_debug_options.print_link_packets && !skipPrint && key_held(KEY_RIGHT))
  {
    pauseOnPacket = true;
    pauseOnByte = false;
  }
  else if (g_debug_options.print_link_data && !skipPrint && key_held(KEY_SELECT))
  {
    pauseOnByte = false;
  }
  else if (g_debug_options.print_link_packets && !skipPrint && key_held(KEY_START))
  {
    pauseOnPacket = false;
  }
  else if ((g_debug_options.print_link_data || g_debug_options.print_link_packets) && key_held(KEY_UP))
  {
    skipPrint = true;
    pauseOnPacket = false;
    pauseOnByte = false;
  }
  else if ((g_debug_options.print_link_data || g_debug_options.print_link_packets) && key_held(KEY_DOWN))
  {
    skipPrint = false;
  }

  if (pauseOnByte && g_debug_options.print_link_data)
  {
    if (key_hit(KEY_B))
    {
      return false; // Even if paused, run once
    }
  }

  if (pauseOnPacket && newPacket && g_debug_options.print_link_packets)
  {
    if (key_hit(KEY_A))
    {
      return false; // Even if paused, run once
    }
  }

  return pauseOnByte || (pauseOnPacket && newPacket);
}

bool LinkConnection::processPacket()
{
  int checksum = 0;
  LinkPacket &currPacket = linkPacketArr[dataOutBuffer[INP_COUNTER_INDEX] % LINK_PACKET_ARRAY_SIZE];
  if (currPacket.packetID != dataOutBuffer[INP_COUNTER_INDEX])
  {
    // This packet is not the correct ID for the response, ignore it
    return false;
  }

  for (int i = INP_COUNTER_INDEX; i < INP_LENGTH; i++)
  {
    if (i != INP_CHECKSUM_INDEX)
    {
      checksum += dataOutBuffer[i];
    }
  }
  // Add the read pointer
  checksum += ((currPacket.pointer + 8) >> 0) & 0xFF;
  checksum += ((currPacket.pointer + 8) >> 8) & 0xFF;

  checksum &= 0x7F;

  byte lsbByte = dataOutBuffer[INP_LSB_INDEX] | dataOutBuffer[INP_LSB_INDEX + 1];
  for (int i = 0; i < 8; i++)
  {
    currPacket.recievedData[i] =
        (dataOutBuffer[INP_DATA_INDEX + i] << 1) | ((lsbByte >> (7 - i)) & 0b1);
  }

  // The soft reset command has no response, don't expect one.
  if (currPacket.command == CMD_SoftReset)
  {
    // If this is a soft reset packet, that means that we don't care what we recieve from the final packet.
    softResetActivated = true;
  }
  else if (checksum != dataOutBuffer[INP_CHECKSUM_INDEX])
  {
    // The checksum has to match in order for it to be valid, if we've made it this far down the line.
    currPacket.latestError = CHECKSUM_MISMATCH;
    return false;
  }

  currPacket.latestError = PACKET_SUCCESS;
  return true;
}

void LinkConnection::loadNextPacket()
{
  /*
  ----------------
  For this part, the LinkConnection has an array of 4 packets that it will send.
  The current packet will be sent and a response will be recieved at the same time. If the recieved packet is
  successful, the data will be moved to the outArray and the packet will be replaced by a packet asking for the next data section.
  If the packet was not successful it will stay in the list and be ran again down the line. If packets have been sent for all the
  data sections, a completed packet will be replaced with an empty packet. Once the array is full of empty packets, the data
  has all been read and we are finished.
  ----------------
*/
  LinkPacket &currPacket = linkPacketArr[dataOutBuffer[INP_COUNTER_INDEX] & (LINK_PACKET_ARRAY_SIZE - 1)];
  if (currPacket.latestError == PACKET_SUCCESS)
  {
    // Packet was successful, Find which packet sent it and mark it.
    // If this was data, then save the data and replace it with the next one in line

    currPacket.latestError = PACKET_READ;
    if (((currPacket.command == CMD_ReadDataRequest) && (currPacket.pointer - linkPacketDataStart) < linkPacketDataSize))
    {
      memcpy(&outDataArrayPtr[currPacket.pointer - linkPacketDataStart], &currPacket.recievedData[0], 8);
      currPacket = LinkPacket(CMD_ReadDataRequest, 0x00, 0x00, linkPacketDataAddr);
      linkPacketDataAddr += 8;
    }
  }
  else
  {
    // Packet failed, don't remove it.
  }
}

bool LinkConnection::allPacketsProcessed()
{
  if (softResetActivated)
  {
    // This counts as processed, return true.
    return true;
  }
  for (int i = 0; i < LINK_PACKET_ARRAY_SIZE; i++)
  {
    if (linkPacketArr[i].inUse && linkPacketArr[i].latestError != PACKET_READ)
    {
      return false;
    }
  }
  return true;
}

void LinkConnection::resetLinkPackets()
{
  for (int i = 0; i < LINK_PACKET_ARRAY_SIZE; i++)
  {
    linkPacketArr[i] = LinkPacket();
  }
}

void LinkConnection::waitForEnd()
{
  while (enterState != END)
  {
    handleCartIO();
    VBlankIntrWait();
  }
}

bool LinkConnection::LinkCommand_InitalizeConnection(bool waitForCompletion)
{
  globalLinkCable.startConnection(INITIAL_CONNECTION);

  if (waitForCompletion)
  {
    waitForEnd();
  }
  return true;
}

bool LinkConnection::LinkCommand_ReloadCurrentBox(bool waitForCompletion)
{
  resetLinkPackets();

  linkPacketArr[0] = LinkPacket(CMD_ReloadCurrentBox, 0x00, 0x00, 0x0000);

  globalLinkCable.startConnection(PACKET_EXCHANGE);
  if (waitForCompletion)
  {
    waitForEnd();
  }
  return true;
};

bool LinkConnection::LinkCommand_TransferPokemon(bool waitForCompletion)
{
  // Check that box number is correct
  resetLinkPackets();

  linkPacketArr[0] = LinkPacket(CMD_ReloadCurrentBox, 0x00, 0x00, 0x0000);

  globalLinkCable.startConnection(PACKET_EXCHANGE);
  if (waitForCompletion)
  {
    waitForEnd();
  }
  return true;
};

bool LinkConnection::LinkCommand_SoftReset(bool waitForCompletion)
{
  resetLinkPackets();

  linkPacketArr[0] = LinkPacket(CMD_SoftReset, 0x00, 0x00, 0x0000);

  globalLinkCable.startConnection(PACKET_EXCHANGE);
  if (waitForCompletion)
  {
    waitForEnd();
  }
  return true;
};

bool LinkConnection::LinkCommand_ModifySRAMAccess(bool enableSRAM, byte SRAMbank, bool waitForCompletion)
{
  if (SRAMbank > 3)
  {
    return false;
  }
  resetLinkPackets();

  if (enableSRAM)
  {
    linkPacketArr[0] = LinkPacket(CMD_ModifySRAMAccess, 0x0A, SRAMbank, 0x0000);
  }
  else
  {
    linkPacketArr[0] = LinkPacket(CMD_ModifySRAMAccess, 0x00, 0x00, 0x0000);
  }

  globalLinkCable.startConnection(PACKET_EXCHANGE);
  if (waitForCompletion)
  {
    waitForEnd();
  }
  return true;
};

bool LinkConnection::LinkCommand_RunSecondaryPayload(bool waitForCompletion)
{
  resetLinkPackets();

  linkPacketArr[0] = LinkPacket(CMD_ReloadCurrentBox, 0x00, 0x00, 0x0000);

  globalLinkCable.startConnection(PACKET_EXCHANGE);
  if (waitForCompletion)
  {
    waitForEnd();
  }
  return true;
};

bool LinkConnection::LinkCommand_ReadMemorySection(u16 dataPointer, byte outArray[], int outArraySize, bool waitForCompletion)
{
  linkPacketDataStart = dataPointer;
  linkPacketDataSize = outArraySize;
  linkPacketDataAddr = dataPointer;
  outDataArrayPtr = outArray;

  for (int i = 0; i < LINK_PACKET_ARRAY_SIZE; i++)
  {
    linkPacketArr[i] = LinkPacket(CMD_ReadDataRequest, 0x00, 0x00, linkPacketDataAddr);
    linkPacketDataAddr += 8;
  }

  globalLinkCable.startConnection(PACKET_EXCHANGE);
  if (waitForCompletion)
  {
    waitForEnd();
  }
  return true;
}