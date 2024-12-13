// Loosely based on code created by StevenChaulk
// Source: https://github.com/stevenchaulk/arduino-poke-gen2

#include <tonc.h>
#include <string>
#include "gameboy_colour.h"
#include "pokemon_trade.h"
#include "script_array.h"
#include "debug_mode.h"
#include "interrupt.h"
#include "text_engine.h"
#include "global_frame_controller.h"
#include "gb_rom_values/eng_gb_rom_values.h"
#include "background_engine.h"
#include "sprite_data.h"
#include "payload_builder.h"

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

LinkSPI *linkSPI = new LinkSPI();

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

std::string spi_text_out_array[10];

void print(std::string str)
{
  for (int i = 10; i > 0; i--)
  {
    spi_text_out_array[i] = spi_text_out_array[i - 1];
  }
  spi_text_out_array[0] = str + "\n";

  tte_erase_rect(LEFT, TOP, RIGHT, BOTTOM);
  tte_set_pos(LEFT, 0);
  for (int j = 0; j < 10; j++)
  {
    tte_write("#{cx:0xE000}");
    tte_write(spi_text_out_array[j].c_str());
  }
}

void setup()
{
  interrupt_init();
  interrupt_set_handler(INTR_SERIAL, LINK_SPI_ISR_SERIAL);
  interrupt_enable(INTR_SERIAL);

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

  if (DEBUG_MODE && false)
  {
    tte_erase_rect(LEFT, TOP, RIGHT, BOTTOM);
    tte_set_pos(0, 0);
    tte_write("FEED ME POKEMON, I HUNGER!\n");
  }
  set_textbox_large();
  tte_erase_screen();
  tte_set_pos(40, 24);
  tte_write("\n\n\n   Connecting to\n      GameBoy");
}

byte handleIncomingByte(byte in, byte *box_data_storage, byte *curr_payload, GB_ROM *curr_gb_rom, Simplified_Pokemon *curr_simple_array, bool cancel_connection)
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
      tte_erase_screen();
      tte_set_pos(40, 24);
      tte_write("\n\n\nLink was successful!\n\n  Waiting for trade");
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
      tte_erase_screen();
      tte_set_pos(40, 24);
      tte_write("\n\n\nTransferring data...\n    please wait!");
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
      return exchange_boxes(in, box_data_storage, curr_gb_rom);
    }
    return in;
  }

  else if (state == box_data)
  {
    return exchange_boxes(in, box_data_storage, curr_gb_rom);
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
      return exchange_remove_array(in, curr_simple_array, cancel_connection);
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
    return exchange_remove_array(in, curr_simple_array, cancel_connection);
  }

  return in;
}

int loop(byte *box_data_storage, byte *curr_payload, GB_ROM *curr_gb_rom, Simplified_Pokemon *curr_simple_array, bool cancel_connection)
{
  int counter = 0;
  while (true)
  {
    // TODO: Restore Errors
    in_data = linkSPI->transfer(out_data);

    if (DEBUG_MODE && false)
    {
      tte_set_margins(0, 0, H_MAX, V_MAX);
      print(
          std::to_string(counter) + ": [" +
          std::to_string(data_counter) + "][" +
          std::to_string(state) + "][" +
          std::to_string(in_data) + "][" +
          std::to_string(out_data) + "]\n");
    }
    out_data = handleIncomingByte(in_data, box_data_storage, curr_payload, curr_gb_rom, curr_simple_array, cancel_connection);

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
      return 0;
    }

    if (state == end2)
    {
      return 0;
    }

    if (DEBUG_MODE && key_hit(KEY_SELECT))
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

byte exchange_boxes(byte curr_in, byte *box_data_storage, GB_ROM *curr_gb_rom)
{
  if (SHOW_DATA_PACKETS)
  {
    tte_erase_rect(0, 0, H_MAX, V_MAX);
    tte_set_pos(8, 8);
  }
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
    if (SHOW_DATA_PACKETS)
    {
        tte_write("P: ");
        tte_write(std::to_string(data_packet[0]).c_str());
        tte_write("\n");
      for (int i = 0; i < DATA_PER_PACKET; i++)
      {
        tte_write(std::to_string(i).c_str());
        tte_write(": ");
        tte_write(std::to_string(data_packet[PACKET_DATA_AT(i)]).c_str());
        tte_write(" [");
        tte_write(std::to_string(data_packet[PACKET_FLAG_AT(i)]).c_str());
        tte_write("]\n");
      }
      tte_write(std::to_string(checksum).c_str());
      tte_write(" = ");
      tte_write(std::to_string(data_packet[PACKET_CHECKSUM]).c_str());
    }

    if (checksum == data_packet[PACKET_CHECKSUM] && !init_packet && !(test_packet_fail && received_offset == 128)) // Verify if the data matches the checksum
    {
      for (int i = 0; i < DATA_PER_PACKET; i++)
      {
        if (received_offset + i <= curr_gb_rom->box_data_size)
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

    if (SHOW_DATA_PACKETS)
    {
      tte_write("\nNO: ");
      tte_write(std::to_string(next_offset).c_str());
      tte_write("\nFP: ");
      tte_write(std::to_string(failed_packet).c_str());
    }

    if (!init_packet)
    {
      if (failed_packet)
      {
        next_offset -= DATA_PER_PACKET;
        failed_packet = false;
      }
      else
      {
        next_offset += DATA_PER_PACKET;
      }
    }

    if (SHOW_DATA_PACKETS)
    {
      tte_write("\nRO: ");
      tte_write(std::to_string(received_offset).c_str());
      tte_write("\nIP: ");
      tte_write(std::to_string(init_packet).c_str());

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

byte exchange_remove_array(byte curr_in, Simplified_Pokemon *curr_simple_array, bool cancel_connection)
{
  for (int i = 29; i >= 0; i--)
  {
    if (curr_simple_array[i].is_valid && !curr_simple_array[i].is_transferred && !cancel_connection)
    {
      curr_simple_array[i].is_transferred = true;
      return i;
    }
  }
  return 0xFF;
}