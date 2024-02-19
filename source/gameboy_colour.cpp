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
  int ret = gen1_eng_payload[data_counter];
  data_counter += 1;
  // return curr_in;
  return ret;
};
