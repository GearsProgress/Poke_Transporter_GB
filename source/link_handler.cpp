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

  if (!globalLinkCable.earlyExit())
  {

    globalLinkCable.exchangeBytes();

    if (g_debug_options.print_link_data || g_debug_options.print_link_packets)
    {
      globalLinkCable.printData();
    }

    if (g_debug_options.write_cable_data_to_save)
    {
      globalLinkCable.writeData();
    }

    globalLinkCable.handleStateLogic();
  }
}

void LinkConnection::setup(const u16 *debug_charset)
{
  link_cable_memory_section_index = 0;
  link_cable_array_index = 0;

  linkSPI->activate(LinkSPI::Mode::MASTER_256KBPS);
  linkSPI->setWaitModeActive(false);

  this->debug_charset = debug_charset;

  if (g_debug_options.print_link_data == true)
  {
    create_textbox(0, 0, 138, 128, false);
  }

  if(g_debug_options.write_cable_data_to_save == WRITE_CABLE_DATA_MODE_SRAM)
  {
    // if we're writing the cable data to SRAM, we should clear the SRAM first to make sure there's no leftover data from previous transfers
    volatile u8 *cur = SRAM_PTR;
    volatile u8 *end = SRAM_PTR + 0x10000;
    while(cur < end)
    {
      (*cur) = 0;
      ++cur;
    }
  }

  if(g_debug_options.load_cable_data_from_save == WRITE_CABLE_DATA_MODE_CART)
  {
    // if we're loading the cable data from the cart save, we should make sure to load our first section here.
    copy_save_to_ram(0x1000 * link_cable_memory_section_index, &global_memory_buffer[0], 0x1000);
  }
}

void LinkConnection::startConnection(CompositeState startState)
{
  switch (startState)
  {
  case INITIAL_CONNECTION:
    subState = CLOCK;
    REG_TM3D = -0x4000 / 60;
    REG_TM3CNT = TM_FREQ_1024 | TM_ENABLE;
    break;
  case PACKET_EXCHANGE:
    subState = BYTE_EXCHANGE;
    REG_TM3D = -0x0040;
    // REG_TM3D = -0x4000 / 2;
    REG_TM3CNT = TM_FREQ_1024 | TM_ENABLE;
    break;
  default:
    break;
  }

  nextSubState = subState;
  nextCompState = startState;
  lastError = NO_ERROR;
  irq_enable(II_TIMER3);
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
  switch(g_debug_options.load_cable_data_from_save)
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

      inData = global_memory_buffer[link_cable_array_index];
      ++link_cable_array_index;
      outData = global_memory_buffer[link_cable_array_index];
      ++link_cable_array_index;

      // we reached the end of our global_memory_buffer, we need to load the next data section from the cart save
      if(link_cable_array_index >= 0x1000)
      {
        ++link_cable_memory_section_index;
        link_cable_array_index = 0;
        copy_save_to_ram(0x1000 * link_cable_memory_section_index, &global_memory_buffer[0], 0x1000);
      }
      break;
    }
  }
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
      n2hexstr(&line[0], compState & 0xFF, 2);
      line[2] = ':';
      n2hexstr(&line[3], compStateCounter & 0xFFFF, 4);
      line[7] = '|';
      n2hexstr(&line[8], subState & 0xFF, 2);
      line[10] = ':';
      n2hexstr(&line[11], subStateCounter & 0xFFFF, 4);
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
        LinkPacket &currLinkPacket = currLinkPacketArr[packetIndex];

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
  switch(g_debug_options.write_cable_data_to_save)
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
      global_memory_buffer[link_cable_array_index + 0] = compState;
      global_memory_buffer[link_cable_array_index + 1] = (compStateCounter >> 8) & 0xFF;
      global_memory_buffer[link_cable_array_index + 2] = (compStateCounter >> 0) & 0xFF;
      global_memory_buffer[link_cable_array_index + 3] = subState;
      global_memory_buffer[link_cable_array_index + 4] = (subStateCounter >> 8) & 0xFF;
      global_memory_buffer[link_cable_array_index + 5] = (subStateCounter >> 0) & 0xFF;

      // actual data bytes start here.
      global_memory_buffer[link_cable_array_index + 6] = inData;
      global_memory_buffer[link_cable_array_index + 7] = outData;

      link_cable_array_index += 8;

      // If the buffer is full or we reached nextSubState == END, we save the buffer to the cartridge save
      if (link_cable_array_index >= 0x1000 || nextSubState == END)
      {
        erase_sector(0x1000 * link_cable_memory_section_index);
        copy_ram_to_save(&global_memory_buffer[0], 0x1000 * link_cable_memory_section_index, 0x1000);
        ++link_cable_memory_section_index;
        link_cable_array_index = 0;
      }
      break;
    }
  }
}

void LinkConnection::handleStateLogic()
{
  subState = nextSubState;
  compState = nextCompState;

  switch (compState)
  {
  case INITIAL_CONNECTION:
    logicState_initConnection();
    break;
  case PACKET_EXCHANGE:
    logicState_packetExchange();
    break;
  default:
    break;
  }

  if (nextSubState != subState)
  {
    subStateCounter = 0;
    subStateChanged = true;
  }
  else
  {
    subStateCounter++;
    subStateChanged = false;
  }

  if (nextCompState != compState)
  {
    compStateCounter = 0;
    compStateChanged = true;
  }
  else
  {
    compStateCounter++;
    compStateChanged = false;
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

void LinkConnection::logicState_initConnection()
{
  outData = 0x00;
  switch (subState)
  {
  case CLOCK:
    if (inData == 0xFE)
    {
      nextSubState = SAVE_SUCCESS;
      // outData defaults to 0x00
    }
    else
    {
      outData = 0x01;
    }
    break;

  case SAVE_SUCCESS:
    if (inData == 0x60 || inData == 0x61)
    {
      nextSubState = MENU_OPEN;
      outData = inData;
    }
    // outData defaults to 0x00
    break;

  case MENU_OPEN:
    if (inData == 0xD0 || inData == 0x61)
    {
      if (inData == 0xD0)
      {
        gen = 1;
        load_payload(GB_PayloadsFiles::UNIVERSALPAYLOADGEN1);
        outData = 0xD4;
      }
      else if (inData == 0x61)
      {
        gen = 2;
        load_payload(GB_PayloadsFiles::UNIVERSALPAYLOADGEN2);
        outData = 0x61;
      }
      nextSubState = MENU_SUCCESS;
    }
    break;

  case MENU_SUCCESS:
    if (inData == 0xFE)
    {
      nextSubState = WAIT_FOR_TRADE;
    }
    outData = inData;
    break;

  case WAIT_FOR_TRADE:
    if (inData == 0xFD)
    {
      REG_TM3D = -0x0040;
      nextSubState = TRADE_PREAMBLE;
      // outData defaults to 0x00
    }
    else
    {
      outData = inData;
    }
    break;

  case TRADE_PREAMBLE:
    if (subStateCounter < 2)
    {
      // outData defaults to 0x00
    }
    else if (subStateCounter < 9)
    {
      outData = 0xFD;
    }
    else
    {
      nextSubState = TRADE;
      outData = 0xFD;
    };
    break;

  case TRADE:
    if (subStateCounter > curr_payload_size)
    {
      if (this->gen == 2)
      {
        nextSubState = MAIL;
      }
      else
      {
        nextSubState = WAIT_FOR_CHECKSUM_PAYLOAD;
      }
    }
    outData = payloadBuffer[subStateCounter];
    break;

  case MAIL:
    if (subStateCounter > 0x186)
    {
      nextSubState = WAIT_FOR_CHECKSUM_PAYLOAD;
    }
    outData = 0x00;
    break;

  case WAIT_FOR_CHECKSUM_PAYLOAD:
    if (inData == 0xFD)
    {
      nextSubState = GET_CHECKSUM;
    }
    // outData defaults to 0x00
    break;

  case GET_CHECKSUM:
    if (inData != 0xFD)
    {
      dataOutBuffer[dataOutBufferCurrIndex] = inData;
      dataOutBufferCurrIndex++;
      outData = 0x01;
    }
    else if (inData == 0xFD && dataOutBufferCurrIndex > 0)
    {
      loadCurrGameFromChecksum();
      load_payload(GB_PayloadsFiles::SPECIFICPAYLOADGEN1_EN_R);
      nextSubState = SEND_SPECIFIC_PAYLOAD;
    }
    else
    {
      outData = 0xFD;
    }
    break;

  case WAIT_FOR_SECOND_PAYLOAD:
    if (inData == 0xFD)
    {
      nextSubState = SEND_SPECIFIC_PAYLOAD;
    }
    // outData defaults to 0x00
    break;

  case SEND_SPECIFIC_PAYLOAD:
    if (subStateCounter > 255) // The 255 comes from the Universal Payload
    {
      nextSubState = END;
    }
    if (subStateCounter < curr_payload_size)
    {
      outData = payloadBuffer[subStateCounter];
    }
    else
    {
      outData = 0x01;
    }
    break;

  case END:
    irq_disable(II_TIMER3);
    break;

  default:
    outData = inData;
    break;
  }
}

void LinkConnection::logicState_packetExchange()
{
  switch (subState)
  {
  case BYTE_EXCHANGE:

    if (subStateCounter < TOTAL_PACKET_LENGTH)
    {
      // Start with OUT_PACKET_LENGTH of bytes of prep to make sure things are set to go
      outData = 0xFF;
    }
    else
    {
      switch (subStateCounter % TOTAL_PACKET_LENGTH)
      {
      case 0:
        outData = 0xFD;
        break;
      case 1:
        outData = currLinkPacketArrIndex;
        break;
      case 2:
        outData = currLinkPacketArr[currLinkPacketArrIndex].command;
        break;
      case 3:
        outData = currLinkPacketArr[currLinkPacketArrIndex].argument[0];
        break;
      case 4:
        outData = currLinkPacketArr[currLinkPacketArrIndex].argument[1];
        break;
      case 5:
        outData = currLinkPacketArr[currLinkPacketArrIndex].pointer >> 0;
        break;
      case 6:
        outData = currLinkPacketArr[currLinkPacketArrIndex].pointer >> 8;
        break;
      case TOTAL_PACKET_LENGTH - 1:
        currLinkPacketArrIndex++;
      default:
        outData = 0xFF;
        break;
      }
      if (currLinkPacketArrIndex >= currLinkPacketArrNum)
      {
        nextSubState = END;
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

  case END:
    irq_disable(II_TIMER3);
    break;

  default:
    outData = inData;
    break;
  }
}

void LinkConnection::load_payload(GB_PayloadsFiles payload)
{
  u32 fileSize;
  u8 decompressionBuffer[0x1000];
  const u8 *chunkList[] = {(const u8 *)GB_Payloads_chunk0_lz10_bin};
  FileContainerReader reader(chunkList, 1);
  const u32 fileIndex = (u32)payload;

  reader.init(decompressionBuffer, sizeof(decompressionBuffer));
  fileSize = reader.getFileSize(fileIndex);
  reader.seekToFile(fileIndex);
  reader.read(this->payloadBuffer, fileSize);

  this->curr_payload_size = fileSize;
}

void LinkConnection::loadCurrGameFromChecksum()
{
  if (((dataOutBuffer[0] + dataOutBuffer[1]) & 0x7F) != dataOutBuffer[2])
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

bool LinkConnection::processPacket()
{
  int checksum = 0;
  LinkPacket &currPacket = currLinkPacketArr[dataOutBuffer[INP_COUNTER_INDEX]];
  for (int i = INP_DELAY_FROM_OUTP; i < INP_LENGTH; i++)
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

  if (checksum != dataOutBuffer[INP_CHECKSUM_INDEX])
  {
    currPacket.latestError = CHECKSUM_MISMATCH;
    return false;
  }
  return true;
}