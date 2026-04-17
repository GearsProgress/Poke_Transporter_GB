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
#include "text_data_table.h"
#include "libraries/Pokemon-Gen3-to-Gen-X/include/save.h"
#include "flash_mem.h"

LinkSPI linkSPIInstance;
LinkSPI *linkSPI = &linkSPIInstance;
LinkState *currLinkState;

// Here's a compilation check to ensure that the size of these structs match our expectations.
// Just update it if you changed the struct members. The data-generator process prints their actual sizes.
static_assert(sizeof(struct GB_ROM) == 136);
static_assert(sizeof(struct ROM_DATA) == 160);

int link_cable_array_index = 0;
int link_cable_memory_section_index = 0;

void print(const char *format, ...)
{
  // I don't think this function is called anymore...
  va_list args;
  va_start(args, format);

  // 10 elements of 64 bytes, zero-initialized.
  char spi_text_out_array[10][SPI_TEXT_OUT_ARRAY_ELEMENT_SIZE] = {
      {0},
      {0},
      {0},
      {0},
      {0},
      {0},
      {0},
      {0},
      {0},
      {0}};

  for (int i = 10; i > 0; i--)
  {
    strncpy(spi_text_out_array[i], spi_text_out_array[i - 1], SPI_TEXT_OUT_ARRAY_ELEMENT_SIZE);
  }

  npf_vsnprintf(spi_text_out_array[0], SPI_TEXT_OUT_ARRAY_ELEMENT_SIZE, format, args);
  va_end(args);

  tte_erase_rect(0, 0, H_MAX, V_MAX);

  for (int j = 0; j < 10; j++)
  {
    tte_erase_rect(0, 0, H_MAX, V_MAX);
    tte_set_pos(0, 0);
    ptgb_write_simple(reinterpret_cast<const byte *>("#{cx:0xE000}"), true);
    ptgb_write_simple((byte *)(spi_text_out_array[j]), true);
  }
}

void setup(const u16 *debug_charset)
{
  interrupt_init();
  interrupt_set_handler(INTR_SERIAL, LINK_SPI_ISR_SERIAL);
  interrupt_enable(INTR_SERIAL);

  linkSPI->activate(LinkSPI::Mode::MASTER_256KBPS);
  linkSPI->setWaitModeActive(false);

  currLinkState = new LinkState;

  {
    u8 general_text_table_buffer[2048];
    text_data_table general_text(general_text_table_buffer);

    general_text.decompress(get_compressed_text_table(GENERAL_INDEX));
    ptgb_write_textbox(general_text.get_text_entry(GENERAL_connecting), true, false,
                       GENERAL_INDEX, GENERAL_connecting, false);
  }
}

byte handleIncomingByte(byte in, byte *box_data_storage, byte *curr_payload, GB_ROM *curr_gb_rom, PokeBox *box, const u16 *debug_charset, bool cancel_connection)
{
  switch (currLinkState->conState)
  {
  case HS:
    currLinkState->mosi_delay = 4;
    if (curr_gb_rom->generation == 2)
    {
      currLinkState->conState = ACK;
      return 0x00;
    }
    if (in == 0x00)
    {
      currLinkState->conState = ACK;
      return 0x01;
    }
    break;

  case ACK:
    if (curr_gb_rom->generation == 2)
    {
      if (in == 0x61)
      {
        currLinkState->conState = MENU;
        return 0x61;
      }
      return 0x01;
    }
    else
    {
      if (in == 0x00)
      {
        currLinkState->conState = MENU;
        return 0x00;
      }
      else if (in == 0x02)
      {
        currLinkState->conState = HS;
        return 0x02;
      }
    }
    break;

  case MENU:
    if (in == 0x60 || in == 0x61)
    {
      {
        u8 general_text_table_buffer[2048];
        text_data_table general_text(general_text_table_buffer);

        general_text.decompress(get_compressed_text_table(GENERAL_INDEX));
        ptgb_write_textbox(general_text.get_text_entry(GENERAL_link_success), true, false,
                           GENERAL_INDEX, GENERAL_link_success, false);
      }

      link_animation_state(STATE_NO_ANIM);
      currLinkState->conState = PRETRADE;
      currLinkState->data_counter = 0;
      return in;
    }
    else if (in == 0x02)
    {
      currLinkState->conState = HS;
      return 0x02;
    }
    else
    {
      return in;
    }
    break;

  case PRETRADE:
    if (currLinkState->data_counter == 16)
    {
      currLinkState->data_counter = 0;
      currLinkState->conState = TRADE;
    }
    currLinkState->data_counter++;
    if (curr_gb_rom->generation == 2)
    {
      return 0x61;
    }
    else if (curr_gb_rom->generation == 1 && curr_gb_rom->version == YELLOW_ID)
    {
      return 0xD5;
    }
    else
    {
      return 0xD4;
    }
    break;
  case TRADE:
    if (in == 0xfd)
    {
      {
        u8 general_text_table_buffer[2048];
        text_data_table general_text(general_text_table_buffer);

        general_text.decompress(get_compressed_text_table(GENERAL_INDEX));
        ptgb_write_textbox(general_text.get_text_entry(GENERAL_transferring), true, false,
                           GENERAL_INDEX, GENERAL_transferring, false);
      }

      link_animation_state(STATE_TRANSFER);
      currLinkState->mosi_delay = 1;
      currLinkState->conState = PARTY_PREAMBLE;
    }
    return in;
    break;
  case PARTY_PREAMBLE:
    if (in != 0xfd)
    {
      currLinkState->conState = TRADE_DATA;
      return exchange_parties(in, curr_payload);
    }
    return in;
    break;
  case TRADE_DATA:
    if (currLinkState->data_counter >= curr_gb_rom->payload_size)
    {
      if (in == 0xFD)
      {
        currLinkState->conState = BOX_PREAMBLE;
        currLinkState->init_packet = true;
      }
      else
      {
        return 0x00;
      }
    }
    return exchange_parties(in, curr_payload);
    break;
  case BOX_PREAMBLE:
    if (in != 0xFD)
    {
      currLinkState->conState = BOX_DATA;
      return exchange_boxes(in, box_data_storage, curr_gb_rom, debug_charset);
    }
    return in;
    break;
  case BOX_DATA:
    return exchange_boxes(in, box_data_storage, curr_gb_rom, debug_charset);
    break;
  case REBOOT:
    currLinkState->data_counter = 0;
    currLinkState->conState = REMOVE_ARRAY_PREAMBLE;
    return 0xFD;
    break;

  case REMOVE_ARRAY_PREAMBLE:
    if (in != 0xFD)
    {
      currLinkState->conState = SEND_REMOVE_ARRAY;
      return exchange_remove_array(in, box, cancel_connection);
    }
    return in;
    break;

  case SEND_REMOVE_ARRAY:
    if (currLinkState->data_counter >= 29) // This assumes the preamble does not count towards the number of bytes sent over the cable
    {
      currLinkState->conState = END2;
    }
    currLinkState->data_counter++;
    return exchange_remove_array(in, box, cancel_connection);
    break;

  default:
    return in;
    break;
  }

  return 0; // This should never hit
}

int loop(byte *box_data_storage, byte *curr_payload, GB_ROM *curr_gb_rom, PokeBox *box, const u16 *debug_charset, bool cancel_connection)
{
#define LINE_WIDTH 21
#define NUM_LINES 8
  int counter = 0;
  char stuff[NUM_LINES][LINE_WIDTH];
  while (true)
  {
    if (g_debug_options.print_link_data && key_held(KEY_L))
    {
      while (!key_hit(KEY_R))
      {
        VBlankIntrWait();
      }
      VBlankIntrWait();
    }
    // TODO: Restore Errors
    currLinkState->in_data = linkSPI->transfer(currLinkState->out_data);

    if (g_debug_options.print_link_data && !key_held(KEY_DOWN))
    {
      for (int i = 0; i < NUM_LINES; i++)
      {
        for (int j = 0; j < LINE_WIDTH; j++)
        {
          stuff[i][j] = stuff[i + 1][j];
        }
        stuff[i][20] = '\n';
      }
      n2hexstr(&stuff[NUM_LINES - 1][0], counter & 0xFFFFFF, 6);
      stuff[NUM_LINES - 1][6] = ':';
      n2hexstr(&stuff[NUM_LINES - 1][7], currLinkState->data_counter & 0xFFFF, 4);
      stuff[NUM_LINES - 1][11] = '|';
      n2hexstr(&stuff[NUM_LINES - 1][12], currLinkState->conState & 0xFF, 2);
      stuff[NUM_LINES - 1][14] = '|';
      n2hexstr(&stuff[NUM_LINES - 1][15], currLinkState->in_data & 0xFF, 2);
      stuff[NUM_LINES - 1][17] = '|';
      n2hexstr(&stuff[NUM_LINES - 1][18], currLinkState->out_data & 0xFF, 2);
      stuff[NUM_LINES - 1][20] = '\0';

      create_textbox(0, 0, 125, 128, false);
      ptgb_write_debug(debug_charset, *stuff, true);
    }
    else if (g_debug_options.write_cable_data_to_save)
    {
      global_memory_buffer[link_cable_array_index] = currLinkState->in_data;
      link_cable_array_index++;
      global_memory_buffer[link_cable_array_index] = currLinkState->out_data;
      link_cable_array_index++;
      if (link_cable_array_index >= 0x1000)
      {
        copy_ram_to_save(&global_memory_buffer[0], 0x1000 * link_cable_memory_section_index, 0x1000);
        link_cable_memory_section_index++;
        link_cable_array_index = link_cable_array_index % 0x1000;
      }
    }

    currLinkState->out_data = handleIncomingByte(currLinkState->in_data, box_data_storage, curr_payload, curr_gb_rom, box, debug_charset, cancel_connection);

    if (currLinkState->FF_count > (15 * 60))
    {
      return COND_ERROR_DISCONNECT;
    }
    if (currLinkState->zero_count > (5 * 60))
    {
      // return COND_ERROR_COM_ENDED;
    }
    if (currLinkState->conState == COLOSSEUM)
    {
      return COND_ERROR_COLOSSEUM;
    }

    if (currLinkState->conState == END1)
    {
      currLinkState->conState = REBOOT;
      if (g_debug_options.write_cable_data_to_save)
      {
        for (int i = 0; i < 16; i++)
        {
          global_memory_buffer[(link_cable_array_index + i) % 0x1000] = 0xAA;
        }
        copy_ram_to_save(&global_memory_buffer[0], 0x1000 * link_cable_memory_section_index, 0x1000);
      }
      return 0;
    }

    if (currLinkState->conState == END2)
    {
      return 0;
    }

    if (key_held(KEY_SELECT)) // Forces a disconnect... not sure why it would need to be locked behind debug mode
    {
      return COND_ERROR_DISCONNECT;
    }

    if (currLinkState->conState != BOX_DATA)
    {
      currLinkState->FF_count = (currLinkState->in_data == 0xFF ? currLinkState->FF_count + currLinkState->mosi_delay : 0);
      currLinkState->zero_count = (currLinkState->in_data == 0x00 ? currLinkState->zero_count + currLinkState->mosi_delay : 0);
    }

    counter++;
    for (int i = 0; i < currLinkState->mosi_delay; i++)
    {
      VBlankIntrWait();
    }
  }
};

byte exchange_parties(byte curr_in, byte *curr_payload)
{
  int ret = curr_payload[currLinkState->data_counter];
  currLinkState->data_counter += 1;
  return ret;
};

byte exchange_boxes(byte curr_in, byte *box_data_storage, GB_ROM *curr_gb_rom, const u16 *debug_charset)
{
  currLinkState->data_packet[currLinkState->packet_index] = curr_in;
  if (currLinkState->packet_index == PACKET_SIZE - 1)
  {
    byte checksum = 0;
    for (int i = 0; i < DATA_PER_PACKET; i++)
    {
      if (currLinkState->data_packet[PACKET_FLAG_AT(i)] == 1)
      {
        currLinkState->data_packet[PACKET_DATA_AT(i)] = 0xFE;
      }
      checksum += currLinkState->data_packet[PACKET_DATA_AT(i)];
    }
    checksum &= 0b01111111; // Reset the top bit so it matches the recieved range
    if (!currLinkState->init_packet)
    {
      currLinkState->received_offset = (currLinkState->data_packet[PACKET_LOCATION_LOWER] | (currLinkState->data_packet[PACKET_LOCATION_UPPER] << 8)) - ((curr_gb_rom->wBoxDataStart & 0xFFFF) + DATA_PER_PACKET);
    }

    if (checksum == currLinkState->data_packet[PACKET_CHECKSUM] && !currLinkState->init_packet && !(currLinkState->test_packet_fail && currLinkState->received_offset == 128)) // Verify if the data matches the checksum
    {
      for (int i = 0; i < DATA_PER_PACKET; i++)
      {
        if (currLinkState->received_offset + i <= curr_gb_rom->box_data_size && currLinkState->received_offset + i >= 0)
        {
          box_data_storage[currLinkState->received_offset + i] = currLinkState->data_packet[PACKET_DATA_AT(i)];
        }
      }
    }
    else if (!currLinkState->init_packet)
    {
      currLinkState->failed_packet = true;
      if (currLinkState->test_packet_fail)
      {
        currLinkState->test_packet_fail = false;
      }
    }

    if (currLinkState->end_of_data)
    {
      currLinkState->conState = END1;
    }
    else
    {
      currLinkState->conState = BOX_PREAMBLE;
    }

    if (currLinkState->received_offset > curr_gb_rom->box_data_size + DATA_PER_PACKET)
    {
      currLinkState->end_of_data = true;
    }

    if (!currLinkState->init_packet)
    {
      if (currLinkState->failed_packet)
      {
        currLinkState->next_offset -= DATA_PER_PACKET;
        if (currLinkState->next_offset < 0)
        {
          currLinkState->next_offset = 0;
        }
        currLinkState->failed_packet = false;
      }
      else
      {
        currLinkState->next_offset += DATA_PER_PACKET;
      }
    }
    if (((currLinkState->next_offset + curr_gb_rom->wBoxDataStart) & 0xFF) == 0xFE)
    {
      currLinkState->next_offset -= 1; // Set back the offset if the byte sent would be 0xFE, since that would break the system
    }

#define ROW_LENGTH 22
#define COLUMN_LENGTH 3 + DATA_PER_PACKET
    if (SHOW_DATA_PACKETS)
    {
      char outArr[COLUMN_LENGTH][ROW_LENGTH];
      for (int col = 0; col < COLUMN_LENGTH; col++)
      {
        for (int row = 0; row < ROW_LENGTH; row++)
        {
          if (row == ROW_LENGTH - 1 && col == COLUMN_LENGTH - 1)
          {
            outArr[col][row] = '\0';
          }
          else if (row == ROW_LENGTH - 1)
          {
            outArr[col][row] = '\n';
          }
          else
          {
            outArr[col][row] = ' ';
          }
        }
      }
      int currRow = 0;

      strcpy(&outArr[currRow][0], "Checksum: ");
      outArr[currRow][10] = ' ';
      n2hexstr(&outArr[currRow][11], checksum, 2);
      strcpy(&outArr[currRow][13], " = ");
      n2hexstr(&outArr[currRow][16], currLinkState->data_packet[PACKET_CHECKSUM], 2);
      outArr[currRow][18] = ' ';
      currRow += 1;

      for (int i = 0; i < DATA_PER_PACKET; i++)
      {
        outArr[currRow][0] = 'P';
        n2hexstr(&outArr[currRow][1], i, 1);
        strcpy(&outArr[currRow][2], ": ");
        n2hexstr(&outArr[currRow][4], currLinkState->data_packet[PACKET_DATA_AT(i)], 2);
        strcpy(&outArr[currRow][6], " (");
        n2hexstr(&outArr[currRow][8], currLinkState->data_packet[PACKET_FLAG_AT(i)], 2);
        outArr[currRow][10] = ')';
        currRow += 1;
      }

      strcpy(&outArr[currRow][0], "RO: ");
      n2hexstr(&outArr[currRow][4], currLinkState->received_offset, 4);
      strcpy(&outArr[currRow][8], "  FP: ");
      n2hexstr(&outArr[currRow][14], currLinkState->failed_packet, 2);
      outArr[currRow][16] = ' ';
      currRow += 1;

      strcpy(&outArr[currRow][0], "NO: ");
      n2hexstr(&outArr[currRow][4], currLinkState->next_offset, 4);
      strcpy(&outArr[currRow][8], "  IP: ");
      n2hexstr(&outArr[currRow][14], currLinkState->init_packet, 2);
      outArr[currRow][16] = ' ';

      // create_textbox(0, 0, 125, 110, false);
      link_animation_state(0);
      ptgb_write_debug(debug_charset, *outArr, true);

      while (!key_held(KEY_A))
      {
        VBlankIntrWait();
      }
      VBlankIntrWait();
    }
    currLinkState->packet_index = 0;
    currLinkState->init_packet = false;
  }
  currLinkState->packet_index += 1;
  switch (currLinkState->packet_index)
  {
  case 3:
    if (currLinkState->end_of_data)
    {
      return 0xFF;
    }
    return (curr_gb_rom->wBoxDataStart + currLinkState->next_offset) >> 8;
  case 2:
    return (curr_gb_rom->wBoxDataStart + currLinkState->next_offset) >> 0;
  default:
    return 0;
  }
};

byte exchange_remove_array(byte curr_in, PokeBox *box, bool cancel_connection)
{
  for (int i = 29; i >= 0; i--)
  {
    if (box->getGen3Pokemon(i)->isValid && !cancel_connection)
    {
      box->removePokemon(i);
      if (!(DONT_TRANSFER_POKEMON_AT_INDEX_X && i == POKEMON_INDEX_TO_SKIP))
      {
        return i;
      }
    }
  }
  return 0xFF;
}