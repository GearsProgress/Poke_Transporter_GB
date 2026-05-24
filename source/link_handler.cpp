// Loosely based on code created by StevenChaulk
// Source: https://github.com/stevenchaulk/arduino-poke-gen2

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

  {
    u8 general_text_table_buffer[2048];
    u8 lineBuffer[1024]; // text_helper/main.py restricts the lines to 1024 bytes.
    const u8 **chunkList;
    u32 numChunks;
    u32 chunkSize;

    get_text_table_chunks(GENERAL_INDEX, &chunkList, &numChunks, &chunkSize);

    FileContainerReader general_text_reader(chunkList, numChunks, chunkSize);
    general_text_reader.init(general_text_table_buffer, sizeof(general_text_table_buffer));
    general_text_reader.readFile(GENERAL_connecting, lineBuffer);
    ptgb_write_textbox(lineBuffer, true, false, GENERAL_INDEX, GENERAL_connecting, false);
  }

  create_textbox(0, 0, 138, 128, false);
}

void LinkConnection::startConnection(CompositeState startState)
{
  compState = startState;
  switch (startState)
  {
  case INITIAL_CONNECTION:
    subState = CLOCK;
    REG_TM3D = -0x4000 / 60;
    REG_TM3CNT = TM_FREQ_1024 | TM_ENABLE;
    irq_enable(II_TIMER3);
    break;
  default:
    break;
  }
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
  global_memory_buffer[link_cable_array_index] = inData;
  link_cable_array_index++;
  global_memory_buffer[link_cable_array_index] = outData;
  link_cable_array_index++;
  if (link_cable_array_index >= 0x1000)
  {
    copy_ram_to_save(&global_memory_buffer[0], 0x1000 * link_cable_memory_section_index, 0x1000);
    link_cable_memory_section_index++;
    link_cable_array_index = link_cable_array_index % 0x1000;
  }
}

void LinkConnection::handleStateLogic()
{
  prevCompState = compState;
  prevSubState = subState;
  switch (compState)
  {
  case INITIAL_CONNECTION:
    logicState_initConnection();
    break;
  default:
    break;
  }

  if (prevSubState != subState)
  {
    subStateCounter = 0;
  }
  else
  {
    subStateCounter++;
  }

  if (prevCompState != compState)
  {
    compStateCounter = 0;
  }
  else
  {
    compStateCounter++;
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
      subState = SAVE_SUCCESS;
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
      subState = MENU_OPEN;
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
        outData = 0xD4;
      }
      else if (inData == 0x61)
      {
        gen = 2;
        outData = 0x61;
      }
      load_universal_payload();
      subState = MENU_SUCCESS;
    }
    break;

  case MENU_SUCCESS:
    if (inData == 0xFE)
    {
      subState = WAIT_FOR_TRADE;
    }
    outData = inData;
    break;

  case WAIT_FOR_TRADE:
    if (inData == 0xFD)
    {
      REG_TM3D = -0x0040;
      subState = TRADE_PREAMBLE;
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
      subState = TRADE;
      outData = 0xFD;
    };
    break;

  case TRADE:
    if (subStateCounter > curr_payload_size)
    {
      if (this->gen == 2)
      {
        subState = MAIL;
      }
      else
      {
        subState = WAIT_FOR_PAYLOAD;
      }
    }
    outData = curr_payload[subStateCounter];
    break;

  case MAIL:
    if (subStateCounter >= 0x186)
    {
      subState = WAIT_FOR_PAYLOAD;
    }
    break;

  case WAIT_FOR_PAYLOAD:
    if (inData == 0xFD)
    {
      subState = GET_CHECKSUM;
      g_debug_options.print_link_data = true;
      paused = true;
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
      subState = END;
    }
    else
    {
      outData = 0xFD;
    }
    break;

  case END:
    irq_delete(II_TIMER3);
    break;

  default:
    outData = inData;
    break;
  }
}

void LinkConnection::load_universal_payload()
{
  u32 fileSize;
  u8 decompressionBuffer[0x1000];
  const u8 *chunkList[] = {(const u8 *)GB_Payloads_chunk0_lz10_bin};
  FileContainerReader reader(chunkList, 1);
  const u32 fileIndex = (this->gen == 1) ? (u32)GB_PayloadsFiles::UNIVERSALPAYLOADGEN1 : (u32)GB_PayloadsFiles::UNIVERSALPAYLOADGEN2;

  reader.init(decompressionBuffer, sizeof(decompressionBuffer));
  fileSize = reader.getFileSize(fileIndex);
  reader.seekToFile(fileIndex);
  reader.read(this->curr_payload, fileSize);

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