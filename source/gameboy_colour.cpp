// Loosely based on code created by StevenChaulk
// Source: https://github.com/stevenchaulk/arduino-poke-gen2

#include <tonc.h>
#include <stdarg.h>
#include <inttypes.h>
#include "libraries/nanoprintf/nanoprintf.h"
#include "libstd_replacements.h"
#include "gameboy_colour.h"
#include "pokemon_trade.h"
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
#include "libraries/gba-link-connection/LinkSPI.hpp"

#define DATA_PER_PACKET 8
#define PACKET_DATA_START 2
#define PACKET_DATA_AT(i) (PACKET_DATA_START + (i * 2))
#define PACKET_FLAG_AT(i) (PACKET_DATA_START + (i * 2) + 1)
#define PACKET_CHECKSUM (PACKET_DATA_START + (2 * DATA_PER_PACKET))
#define PACKET_LOCATION_UPPER (PACKET_CHECKSUM + 1)
#define PACKET_LOCATION_LOWER (PACKET_CHECKSUM + 2)

// 0xFD, 0x00, data bytes per packet, flag bytes per packet, the checksum, and two location bytes
#define PACKET_SIZE (1 + 1 + (2 * DATA_PER_PACKET) + 1 + 2) // Originally 13

#define TIMEOUT 2
#define TIMEOUT_ONE_LENGTH 1000000 // Maybe keep a 10:1 ratio between ONE and TWO?
#define TIMEOUT_TWO_LENGTH 100000

#define hs 0
#define ack 1
#define menu 2
#define pretrade 3
#define trade 4
#define party_preamble 5
#define colosseum 6
#define cancel 7
#define trade_data 8
#define box_preamble 9
#define box_data 10
#define end1 11
#define reboot 12
#define remove_array_preamble 13
#define send_remove_array 14
#define end2 15

const int MODE = 1; // mode=0 will transfer pokemon data from pokemon.h
                    // mode=1 will copy pokemon party data being received
LinkSPI linkSPIInstance;
LinkSPI *linkSPI = &linkSPIInstance;

uint8_t in_data;
uint8_t out_data;
uint frame;

connection_state_t connection_state;

int counter;
int data_counter = 0;
int gen_1_room_counter = 0;
int gen;
int trade_pokemon;

int FF_count;
int zero_count;

int state;
int mosi_delay = 4; // inital delay, speeds up once sending PKMN
int received_offset = 0;
int next_offset = 0;
int packet_index = 0;

bool failed_packet;
bool init_packet;

bool test_packet_fail = false;

bool end_of_data;

byte data_packet[PACKET_SIZE];

#define SPI_TEXT_OUT_ARRAY_ELEMENT_SIZE 64

// Here's a compilation check to ensure that the size of these structs match our expectations.
// Just update it if you changed the struct members. The data-generator process prints their actual sizes.
static_assert(sizeof(struct GB_ROM) == 136);
static_assert(sizeof(struct ROM_DATA) == 160);

int link_cable_array_index = 0;
int link_cable_memory_section_index = 0;

__attribute__((section(".link_debug")))
volatile LinkSPI_Debug link_debug;
volatile LinkSPI_Debug *linkSPIDebug = &link_debug;

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

  // This is for the emulation debug:
  linkSPI->setDebug(true);
  linkSPI->activate(LinkSPI::Mode::MASTER_256KBPS);
  linkSPI->setWaitModeActive(false);

  state = hs;

  in_data = 0;
  out_data = 0;
  frame = 0;

  connection_state = NOT_CONNECTED;
  counter = 0;

  gen = 0;

  trade_pokemon = -1;

  FF_count = 0;
  zero_count = 0;
  next_offset = 0;
  received_offset = 0;
  packet_index = 0;

  failed_packet = false;
  init_packet = true;
  end_of_data = false;
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
  // TODO: Change to a switch statement
  if (state == hs)
  {
    mosi_delay = 4;
    if (curr_gb_rom->generation == 2)
    {
      state = ack;
      return 0x00;
    }
    if (in == 0x00)
    {
      state = ack;
      return 0x01;
    }
  }

  else if (state == ack)
  {
    if (curr_gb_rom->generation == 2)
    {
      if (in == 0x61)
      {
        state = menu;
        return 0x61;
      }
      return 0x01;
    }
    else
    {
      if (in == 0x00)
      {
        state = menu;
        return 0x00;
      }
      else if (in == 0x02)
      {
        state = hs;
        return 0x02;
      }
    }
  }

  else if (state == menu)
  {
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
      state = pretrade;
      data_counter = 0;
      return in;
    }
    else if (in == 0x02)
    {
      state = hs;
      return 0x02;
    }
    else
    {
      return in;
    }
  }

  else if (state == pretrade)
  {
    if (data_counter == 16)
    {
      data_counter = 0;
      state = trade;
    }
    data_counter++;
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
  }

  else if (state == trade)
  {
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
      mosi_delay = 1;
      state = party_preamble;
    }
    return in;
  }

  else if (state == party_preamble)
  {
    if (in != 0xfd)
    {
      state = trade_data;
      return exchange_parties(in, curr_payload);
    }
    return in;
  }

  else if (state == trade_data)
  {
    if (data_counter >= curr_gb_rom->payload_size)
    {
      if (in == 0xFD)
      {
        state = box_preamble;
        init_packet = true;
      }
      else
      {
        return 0x00;
      }
    }
    return exchange_parties(in, curr_payload);
  }

  else if (state == box_preamble)
  {
    if (in != 0xFD)
    {
      state = box_data;
      return exchange_boxes(in, box_data_storage, curr_gb_rom, debug_charset);
    }
    return in;
  }

  else if (state == box_data)
  {
    return exchange_boxes(in, box_data_storage, curr_gb_rom, debug_charset);
  }

  else if (state == reboot)
  {
    data_counter = 0;
    state = remove_array_preamble;
    return 0xFD;
  }

  else if (state == remove_array_preamble)
  {
    if (in != 0xFD)
    {
      state = send_remove_array;
      return exchange_remove_array(in, box, cancel_connection);
    }
    return in;
  }

  else if (state == send_remove_array)
  {
    if (data_counter >= 29) // This assumes the preamble does not count towards the number of bytes sent over the cable
    {
      state = end2;
    }
    data_counter++;
    return exchange_remove_array(in, box, cancel_connection);
  }

  return in;
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
        global_next_frame();
      }
      global_next_frame();
    }
    // TODO: Restore Errors
    in_data = linkSPI->transfer(out_data);

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
      n2hexstr(&stuff[NUM_LINES - 1][7], data_counter & 0xFFFF, 4);
      stuff[NUM_LINES - 1][11] = '|';
      n2hexstr(&stuff[NUM_LINES - 1][12], state & 0xFF, 2);
      stuff[NUM_LINES - 1][14] = '|';
      n2hexstr(&stuff[NUM_LINES - 1][15], in_data & 0xFF, 2);
      stuff[NUM_LINES - 1][17] = '|';
      n2hexstr(&stuff[NUM_LINES - 1][18], out_data & 0xFF, 2);
      stuff[NUM_LINES - 1][20] = '\0';

      create_textbox(0, 0, 125, 128, false);
      ptgb_write_debug(debug_charset, *stuff, true);
    }
    else if (g_debug_options.write_cable_data_to_save)
    {
      global_memory_buffer[link_cable_array_index] = in_data;
      link_cable_array_index++;
      global_memory_buffer[link_cable_array_index] = out_data;
      link_cable_array_index++;
      if (link_cable_array_index >= 0x1000)
      {
        copy_ram_to_save(&global_memory_buffer[0], 0x1000 * link_cable_memory_section_index, 0x1000);
        link_cable_memory_section_index++;
        link_cable_array_index = link_cable_array_index % 0x1000;
      }
    }

    out_data = handleIncomingByte(in_data, box_data_storage, curr_payload, curr_gb_rom, box, debug_charset, cancel_connection);

    if (FF_count > (15 * 60))
    {
      return COND_ERROR_DISCONNECT;
    }
    if (zero_count > (5 * 60))
    {
      // return COND_ERROR_COM_ENDED;
    }
    if (connection_state == COLOSSEUM)
    {
      return COND_ERROR_COLOSSEUM;
    }

    if (state == end1)
    {
      state = reboot;
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

    if (state == end2)
    {
      return 0;
    }

    if (key_held(KEY_SELECT)) // Forces a disconnect... not sure why it would need to be locked behind debug mode
    {
      return COND_ERROR_DISCONNECT;
    }

    if (state != box_data)
    {
      FF_count = (in_data == 0xFF ? FF_count + mosi_delay : 0);
      zero_count = (in_data == 0x00 ? zero_count + mosi_delay : 0);
    }

    counter++;
    for (int i = 0; i < mosi_delay; i++)
    {
      global_next_frame();
    }
  }
};

byte exchange_parties(byte curr_in, byte *curr_payload)
{
  int ret = curr_payload[data_counter];
  data_counter += 1;
  return ret;
};

byte exchange_boxes(byte curr_in, byte *box_data_storage, GB_ROM *curr_gb_rom, const u16 *debug_charset)
{
  data_packet[packet_index] = curr_in;
  if (packet_index == PACKET_SIZE - 1)
  {
    byte checksum = 0;
    for (int i = 0; i < DATA_PER_PACKET; i++)
    {
      if (data_packet[PACKET_FLAG_AT(i)] == 1)
      {
        data_packet[PACKET_DATA_AT(i)] = 0xFE;
      }
      checksum += data_packet[PACKET_DATA_AT(i)];
    }
    checksum &= 0b01111111; // Reset the top bit so it matches the recieved range
    if (!init_packet)
    {
      received_offset = (data_packet[PACKET_LOCATION_LOWER] | (data_packet[PACKET_LOCATION_UPPER] << 8)) - ((curr_gb_rom->wBoxDataStart & 0xFFFF) + DATA_PER_PACKET);
    }

    if (checksum == data_packet[PACKET_CHECKSUM] && !init_packet && !(test_packet_fail && received_offset == 128)) // Verify if the data matches the checksum
    {
      for (int i = 0; i < DATA_PER_PACKET; i++)
      {
        if (received_offset + i <= curr_gb_rom->box_data_size && received_offset + i >= 0)
        {
          box_data_storage[received_offset + i] = data_packet[PACKET_DATA_AT(i)];
        }
      }
    }
    else if (!init_packet)
    {
      failed_packet = true;
      if (test_packet_fail)
      {
        test_packet_fail = false;
      }
    }

    if (end_of_data)
    {
      state = end1;
    }
    else
    {
      state = box_preamble;
    }

    if (received_offset > curr_gb_rom->box_data_size + DATA_PER_PACKET)
    {
      end_of_data = true;
    }

    if (!init_packet)
    {
      if (failed_packet)
      {
        next_offset -= DATA_PER_PACKET;
        if (next_offset < 0)
        {
          next_offset = 0;
        }
        failed_packet = false;
      }
      else
      {
        next_offset += DATA_PER_PACKET;
      }
    }
    if (((next_offset + curr_gb_rom->wBoxDataStart) & 0xFF) == 0xFE)
    {
      next_offset -= 1; // Set back the offset if the byte sent would be 0xFE, since that would break the system
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
      n2hexstr(&outArr[currRow][16], data_packet[PACKET_CHECKSUM], 2);
      outArr[currRow][18] = ' ';
      currRow += 1;

      for (int i = 0; i < DATA_PER_PACKET; i++)
      {
        outArr[currRow][0] = 'P';
        n2hexstr(&outArr[currRow][1], i, 1);
        strcpy(&outArr[currRow][2], ": ");
        n2hexstr(&outArr[currRow][4], data_packet[PACKET_DATA_AT(i)], 2);
        strcpy(&outArr[currRow][6], " (");
        n2hexstr(&outArr[currRow][8], data_packet[PACKET_FLAG_AT(i)], 2);
        outArr[currRow][10] = ')';
        currRow += 1;
      }

      strcpy(&outArr[currRow][0], "RO: ");
      n2hexstr(&outArr[currRow][4], received_offset, 4);
      strcpy(&outArr[currRow][8], "  FP: ");
      n2hexstr(&outArr[currRow][14], failed_packet, 2);
      outArr[currRow][16] = ' ';
      currRow += 1;

      strcpy(&outArr[currRow][0], "NO: ");
      n2hexstr(&outArr[currRow][4], next_offset, 4);
      strcpy(&outArr[currRow][8], "  IP: ");
      n2hexstr(&outArr[currRow][14], init_packet, 2);
      outArr[currRow][16] = ' ';

      // create_textbox(0, 0, 125, 110, false);
      link_animation_state(0);
      ptgb_write_debug(debug_charset, *outArr, true);

      while (!key_held(KEY_A))
      {
        global_next_frame();
      }
      global_next_frame();
    }
    packet_index = 0;
    init_packet = false;
  }
  packet_index += 1;
  switch (packet_index)
  {
  case 3:
    if (end_of_data)
    {
      return 0xFF;
    }
    return (curr_gb_rom->wBoxDataStart + next_offset) >> 8;
  case 2:
    return (curr_gb_rom->wBoxDataStart + next_offset) >> 0;
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