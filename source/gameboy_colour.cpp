// Original code created by StevenChaulk https://github.com/stevenchaulk/arduino-poke-gen2

#include <tonc.h>
#include <string>
#include "gameboy_colour.h"
#include "pokemon_trade.h"
#include "output.h"
#include "script_array.h"
#include "debug_mode.h"
#include "payload.h"
#include "interrupt.h"
#include "text_engine.h"

#define TIMEOUT 2
#define TIMEOUT_ONE_LENGTH 1000000 // Maybe keep a 10:1 ratio between ONE and TWO?
#define TIMEOUT_TWO_LENGTH 100000

#define hs 0
#define ack 1
#define menu 2
#define trade 3
#define preamble 4
#define colosseum 5
#define cancel 6
#define trade_data 7

const int MODE = 1; // mode=0 will transfer pokemon data from pokemon.h
                    // mode=1 will copy pokemon party data being received

LinkSPI *linkSPI = new LinkSPI();

uint8_t in_data;
uint8_t out_data;
uint frame;

connection_state_t connection_state;
trade_centre_state_gen_II_t trade_centre_state_gen_II;

int counter;
int data_counter = 0;
int gen_1_room_counter = 0;
int gen;
int trade_pokemon;

int FF_count;
int zero_count;

int state;

std::string out_array[10];

byte data[637] = {0, 0, 0, 0, 0, 0xCD, 0x87, 0xD8, 184, 165, 253, 253, 253, 253, 253, 253, 253, 253, 248, 0, 54, 253, 1, 62, 88, 197, 195, 214, 197, 6, 21, 21, 21, 21, 21, 21, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 252, 227, 227, 255, 33, 160, 195, 1, 136, 1, 62, 0, 205, 224, 54, 17, 24, 218, 33, 89, 196, 205, 85, 25, 195, 21, 218, 139, 142, 128, 131, 136, 141, 134, 232, 232, 232, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 64, 0, 0, 253, 253, 253, 253, 253, 255, 255, 62, 99, 245, 33, 160, 195, 1, 136, 1, 205, 224, 54, 17, 255, 197, 33, 87, 196, 205, 85, 25, 118, 118, 118, 118, 118, 118, 118, 241, 60, 14, 108, 185, 194, 216, 197, 62, 99, 195, 216, 197, 127, 135, 132, 139, 139, 142, 127, 150, 142, 145, 139, 131, 231, 127, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/*
byte data[638] = {
    // Seed
    182, 147, 113, 81, 51, 23, 228, 205, 184, 165,
    // Preamble
    253, 253, 253, 253, 253, 253, 253, 253,
    // Party
    248, 0, 54, 253, 1, 62, 88, 197, 195, 0xd6, 0xc5, 8, 21, 21, 22, 21, 22, 21, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227,
    227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 206, 227, 227, 255, 33, 160, 195, 1, 136, 1, 62, 0, 205, 224, 54, 17, 24, 218, 33, 89, 196, 205, 85, 25, 195, 21, 218, 139, 142, 128, 131, 136, 141, 134, 232, 232, 232, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 64, 0, 0,
    // Preamble
    253, 253, 253, 253, 255, 255,
    // Patch list
    0x3E, 0x63, 0xF5, 0x21, 0xA0, 0xC3, 0x01, 0x88,
    0x01, 0xCD, 0xE0, 0x36, 0x11, 0xFF, 0xC5, 0x21,
    0x57, 0xC4, 0xCD, 0x55, 0x19, 0x76, 0x76, 0x76,
    0x76, 0x76, 0x76, 0x76, 0xF1, 0x3C, 0x0E, 0x6C,
    0xB9, 0xC2, 0xD8, 0xC5, 0x3E, 0x63, 0xC3, 0xD8,
    0xC5, 0x7F, 0x87, 0x84, 0x8B, 0x8B, 0x8E, 0x7F,
    0x96, 0x8E, 0x91, 0x8B, 0x83, 0xE7, 0x7F, 0x50,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};
*/
void print(std::string str)
{
  for (int i = 10; i > 0; i--)
  {
    out_array[i] = out_array[i - 1];
  }
  out_array[0] = str + "\n";

  tte_erase_rect(LEFT, TOP, RIGHT, BOTTOM);
  tte_set_pos(LEFT, 0);
  for (int j = 0; j < 10; j++)
  {
    tte_write("#{cx:0xE000}");
    tte_write(out_array[j].c_str());
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
  trade_centre_state_gen_II = INIT;
  counter = 0;

  gen = 0;

  trade_pokemon = -1;

  FF_count = 0;
  zero_count = 0;

  if (DEBUG_MODE)
  {
    tte_erase_rect(LEFT, TOP, RIGHT, BOTTOM);
    tte_set_pos(0, 0);
    tte_write("FEED ME POKEMON, I HUNGER!\n");
  }
}

byte handleIncomingByte(byte in)
{
  if (state == hs)
  {
    if (in == 0x00)
    {
      state = ack;
      return 0x01;
    }
  }

  else if (state == ack)
  {
    if (in == 0x00)
    {
      state = menu;
      return 0x00;
    }
  }

  else if (state == menu)
  {
    if (in == 0xd4)
    {
      state = trade;
      return in;
    }
    else
    {
      return in;
    }
  }

  else if (state == trade)
  {
    if (in == 0xfd)
    {
      state = preamble;
    }
    return in;
  }

  else if (state == preamble)
  {
    if (in != 0xfd)
    {
      state = trade_data;
      return exchange_parties(in);
    }
    return in;
  }

  else if (state == trade_data)
  {
    return exchange_parties(in);
  }

  return in;
}

int loop(byte *party_data)
{
  int counter = 0;
  while (true)
  {
    in_data = linkSPI->transfer(out_data);

    print(
        std::to_string(counter) + ": [" +
        std::to_string(data_counter) + "][" +
        std::to_string(state) + "][" +
        std::to_string(in_data) + "][" +
        std::to_string(out_data) + "]\n");

    out_data = handleIncomingByte(in_data);
    party_data[counter] = in_data;

    if (FF_count > 25)
    {
      // return COND_ERROR_DISCONNECT;
    }
    if (zero_count > 25)
    {
      // return COND_ERROR_COM_ENDED;
    }
    if (connection_state == COLOSSEUM)
    {
      return COND_ERROR_COLOSSEUM;
    }

    if (trade_centre_state_gen_II == MIMIC)
    {
      return 0;
    }
    counter++;
    for (int i = 0; i < 3; i++)
    {
      VBlankIntrWait();
    }
  }
};

byte exchange_parties(byte curr_in)
{
  int ret = data[data_counter];
  data_counter += 1;
  // return curr_in;
  return ret;
};
