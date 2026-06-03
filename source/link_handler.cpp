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

    if (g_debug_options.print_link_data)
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

  linkSPI->activate(LinkSPI::Mode::MASTER_256KBPS);
  linkSPI->setWaitModeActive(false);

  this->debug_charset = debug_charset;

  if (g_debug_options.print_link_data == true)
  {
    create_textbox(0, 0, 138, 128, false);
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
    //REG_TM3D = -0x4000 / 2;
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
  inData = linkSPI->transfer(outData);
}

void LinkConnection::printData()
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

void LinkConnection::writeData()
{
  global_memory_buffer[link_cable_array_index + 0] = compState;
  global_memory_buffer[link_cable_array_index + 1] = (compStateCounter >> 8) & 0xFF;
  global_memory_buffer[link_cable_array_index + 2] = (compStateCounter >> 0) & 0xFF;
  global_memory_buffer[link_cable_array_index + 3] = subState;
  global_memory_buffer[link_cable_array_index + 4] = (subStateCounter >> 8) & 0xFF;
  global_memory_buffer[link_cable_array_index + 5] = (subStateCounter >> 0) & 0xFF;
  global_memory_buffer[link_cable_array_index + 6] = inData;
  global_memory_buffer[link_cable_array_index + 7] = outData;
  link_cable_array_index += 8;

  if (link_cable_array_index >= 0x1000 || nextSubState == END)
  {
    copy_ram_to_save(&global_memory_buffer[0], 0x1000 * link_cable_memory_section_index, 0x1000);
    link_cable_memory_section_index++;
    link_cable_array_index = link_cable_array_index % 0x1000;
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
  if (g_debug_options.print_link_data && key_hit(KEY_LEFT))
  {
    globalLinkCable.paused = true;
  }
  else if (g_debug_options.print_link_data && key_hit(KEY_RIGHT))
  {
    globalLinkCable.paused = false;
  }

  if (globalLinkCable.paused && g_debug_options.print_link_data)
  {
    if (key_hit(KEY_A))
    {
      return false; // Even if paused, run once
    }
  }
  return globalLinkCable.paused;
}

void LinkConnection::logicState_initConnection()
{
  switch (subState)
  {
  case CLOCK:
    if (inData == 0xFE)
    {
      nextSubState = SAVE_SUCCESS;
      outData = 0x00;
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
    else
    {
      outData = 0x00;
    }
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
      outData = 0x00;
    }
    else
    {
      outData = inData;
    }
    break;

  case TRADE_PREAMBLE:
    if (subStateCounter < 2)
    {
      outData = 0x00;
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
    outData = 0x00;
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
      LoadCurrGameFromChecksum();
      load_payload(GB_PayloadsFiles::SPECIFICPAYLOADGEN1_RB_EN);
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
    outData = 0x00;
    break;

  case SEND_SPECIFIC_PAYLOAD:
    if (subStateCounter > 200) // The 200 comes from the Universal Payload
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

    /*
  case SEND_PACKET:

    // Output the payload followed by 0xFF while waiting
    if (subStateCounter > 12)
    {
      nextSubState = RECIEVE_PACKET;
    }
    outData = payloadBuffer[subStateCounter];
    break;

  case WAIT_FOR_RESPONSE:
    if (inData != 0xFD)
    {
      nextSubState = RECIEVE_PACKET;
    }
    else if (subStateCounter >= 256)
    {
      lastError = PACKET_TIMED_OUT;
      nextSubState = END;
    }
    outData = 0xFF;
    break;

  case RECIEVE_PACKET:
    // See if we've already begun recieving the response
    if (dataOutBufferCurrIndex > 0)
    {
      // Are we at the end of the response?
      if (dataOutBufferCurrIndex >= 13)
      {
        nextSubState = END;
      }
      else
      {
        dataOutBuffer[dataOutBufferCurrIndex] = inData;
        dataOutBufferCurrIndex++;
      }
    }
    // We haven't... see if this is the first byte in the response

    // Let's also make sure that we haven't been sitting here for a long time

    break;
*/

  case BYTE_EXCHANGE:

    if (subStateCounter < OUT_PACKET_LENGTH)
    {
      // Start with OUT_PACKET_LENGTH of bytes of prep to make sure things are set to go
      outData = 0xFF;
    }
    else
    {
      switch (subStateCounter % OUT_PACKET_LENGTH)
      {
      case 0:
        outData = 0xFD;
        break;
      case 1:
        outData = currLinkPacketArr[currLinkPacketArrIndex].command;
        break;
      case 2:
        outData = currLinkPacketArr[currLinkPacketArrIndex].argument[0];
        break;
      case 3:
        outData = currLinkPacketArr[currLinkPacketArrIndex].argument[1];
        break;
      case 4:
        outData = currLinkPacketArr[currLinkPacketArrIndex].pointer >> 8;
        break;
      case 5:
        outData = currLinkPacketArr[currLinkPacketArrIndex].pointer >> 0;
        break;
      case OUT_PACKET_LENGTH - 1:
        currLinkPacketArrIndex++;
      default:
        outData = 0xFF;
        break;
      }
      if (currLinkPacketArrIndex >= currLinkPacketArrNum)
      {
        nextSubState = END;
      }

      if (subStateCounter % OUT_PACKET_LENGTH + 2 == 0)
      {
        // Process packet
      }
      dataOutBuffer[subStateCounter % OUT_PACKET_LENGTH + 2] = inData;
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

void LinkConnection::LoadCurrGameFromChecksum()
{
  if (((dataOutBuffer[0] + dataOutBuffer[1]) & 0x7F) != dataOutBuffer[3])
  {
    currROM = GB_ROM_ERROR;
  };

  int start = 0;
  int end = 0;

  if (gen == 1)
  {
    start = RED_JP_v0;
    end = GOLD_JP_v0;
  }
  else if (gen == 2)
  {
    start = GOLD_JP_v0;
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