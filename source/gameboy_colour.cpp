#include <tonc.h>
#include <string>
#include "gameboy_colour.h"
#include "pokemon_trade.h"
#include "output.h"
#include "LinkGPIO.h"
#include "script_array.h"

#define BYTE_INCOMPLETE 0
#define BYTE_COMPLETE 1
#define TIMEOUT 2
#define TIMEOUT_ONE_LENGTH 1000000 // Maybe keep a 10:1 ratio between ONE and TWO?
#define TIMEOUT_TWO_LENGTH 100000

const int MODE = 1; // mode=0 will transfer pokemon data from pokemon.h
                    // mode=1 will copy pokemon party data being received

LinkGPIO *linkGPIO = new LinkGPIO();

uint8_t shift;
uint8_t in_data;
uint8_t out_data;
uint frame;

bool SC_state;

connection_state_t connection_state;
trade_centre_state_gen_II_t trade_centre_state_gen_II;
int counter;
int gen_1_room_counter = 0;

int gen;

int trade_pokemon;

unsigned long last_bit;

int FF_count;
int zero_count;

char hexArr[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

char output[2];

std::string outHexStr(vu8 inputNum)
{
  std::string out = "XX";
  out[0] = (inputNum)&0xF;
  out[1] = (inputNum >> 4) & 0xF;
  return out;
}

std::string out_array[10];

void print(std::string str)
{
  for (int i = 10; i > 0; i--)
  {
    out_array[i] = out_array[i - 1];
  }
  out_array[0] = std::to_string(frame) + ": " + str + "\n";
  tte_erase_screen();
  tte_set_pos(0, 0);
  for (int j = 0; j < 10; j++)
  {
    tte_write(out_array[j].c_str());
  }
}

void updateFrames()
{
  if (((connection_state > 1) && (frame - last_bit >= ((trade_centre_state_gen_II >= WAITING_TO_SEND_DATA) ? 10 : 1000))) /*|| connection_state == PRE_CONNECTED*/)
  {
    SC_state = !SC_state;
    linkGPIO->writePin(LinkGPIO::Pin::SC, SC_state);
    // print(SC_state ? "True" : "False");
    last_bit = frame;
  }
  frame++;
}

void setup()
{

  shift = 0;
  in_data = 0;
  out_data = 0;
  frame = 0;

  SC_state = 0;

  connection_state = PRE_CONNECT_ONE;
  trade_centre_state_gen_II = INIT;
  counter = 0;

  gen = 0;

  trade_pokemon = -1;

  FF_count = 0;
  zero_count = 0;

  // pinMode(SCLK_, INPUT);
  // pinMode(MISO_, INPUT);
  // pinMode(MOSI_, OUTPUT);

  linkGPIO->reset();

  linkGPIO->setMode(LinkGPIO::Pin::SC, LinkGPIO::Direction::INPUT);
  linkGPIO->setMode(LinkGPIO::Pin::SO, LinkGPIO::Direction::OUTPUT);
  linkGPIO->setMode(LinkGPIO::Pin::SI, LinkGPIO::Direction::INPUT);

  /*
  LINK_SPI_SET_LOW(REG_RCNT, 4);
  LINK_SPI_SET_LOW(REG_RCNT, 6);
  LINK_SPI_SET_HIGH(REG_RCNT, 7);

  LINK_SPI_SET_LOW(REG_RCNT, LINK_SPI_BIT_GENERAL_PURPOSE_LOW);
  LINK_SPI_SET_HIGH(REG_RCNT, LINK_SPI_BIT_GENERAL_PURPOSE_HIGH);
  */

  tte_erase_screen();
  tte_set_pos(0, 0);
  tte_write("FEED ME POKEMON, I HUNGER!\n");

  // digitalWrite(MOSI_, LOW);
  linkGPIO->writePin(LinkGPIO::Pin::SO, 0);
  out_data <<= 1;
}

byte handleIncomingByte(byte in)
{
  byte send = 0x00;

  if (trade_centre_state_gen_II < WAITING_TO_SEND_DATA)
  {
    switch (in)
    {
    case 0x00:
      FF_count = 0;
      zero_count++;
      break;

    case 0xFF:
      zero_count = 0;
      FF_count++;
      break;

    default:
      FF_count = 0;
      zero_count = 0;
      break;
    }
  }

  switch (connection_state)
  {
  case PRE_CONNECT_ONE:
    if (in == PKMN_MASTER)
    {
      connection_state = PRE_CONNECT_TWO;
    }
    send = PKMN_MASTER;
    break;

  case PRE_CONNECT_TWO:
    if (in == PKMN_MASTER)
    {
      connection_state = NOT_CONNECTED;
      linkGPIO->setMode(LinkGPIO::Pin::SC, LinkGPIO::Direction::OUTPUT);
      shift = shift + 1;
    }
    send = PKMN_MASTER;
    break;

  case NOT_CONNECTED:
    if (in == PKMN_SLAVE)
      send = PKMN_MASTER;
    else if (in == PKMN_BLANK)
    {
      send = PKMN_BLANK;
    }
    else if (in == PKMN_CONNECTED_I)
    {
      send = PKMN_CONNECTED_I;
      gen = 1;
      connection_state = CONNECTED;
    }
    else if (in == PKMN_CONNECTED_II)
    {
      send = PKMN_CONNECTED_II;
      gen = 2;
      connection_state = CONNECTED;
    }
    else if (in == 127)
    {
      shift++;
    }
    break;

  case CONNECTED:
    if (in == PKMN_CONNECTED_I)
    { // acknowledge connection
      send = PKMN_CONNECTED_I;
      gen_1_room_counter = 0;
    }
    else if (in == PKMN_CONNECTED_II)
    { // acknowledge connection
      send = PKMN_CONNECTED_II;
      gen_1_room_counter = 0;
    }
    else if (in == ITEM_1_HIGHLIGHTED)
    { // select gen 1 trade room automatically
      send = ITEM_1_SELECTED;
      if (gen_1_room_counter >= 3)
      {
        connection_state = TRADE_CENTRE;
      }
      gen_1_room_counter++;
    }
    else if (in == GEN_II_CABLE_TRADE_CENTER)
    { // acknowledge trade center selection
      connection_state = TRADE_CENTRE;
      send = GEN_II_CABLE_TRADE_CENTER;
    }
    else if (in == GEN_II_CABLE_CLUB_COLOSSEUM)
    { // acknowledge colosseum selection
      connection_state = COLOSSEUM;
      send = GEN_II_CABLE_CLUB_COLOSSEUM;
    }
    else
    {
      send = in;
    }
    break;

  case TRADE_CENTRE:
    if (trade_centre_state_gen_II == INIT && in == 0x00)
    {
      trade_centre_state_gen_II = READY_TO_GO;
      send = 0x00;
    }
    else if (trade_centre_state_gen_II == READY_TO_GO && in == 0xFD)
    {
      trade_centre_state_gen_II = SEEN_FIRST_WAIT;
      send = 0xFD;
    }
    else if (trade_centre_state_gen_II == SEEN_FIRST_WAIT && in != 0xFD)
    {
      // random data of slave is ignored.
      send = in;
      trade_centre_state_gen_II = SENDING_RANDOM_DATA;
    }
    else if (trade_centre_state_gen_II == SENDING_RANDOM_DATA && in == 0xFD)
    {
      trade_centre_state_gen_II = WAITING_TO_SEND_DATA;
      send = 0xFD;
    }
    else if (trade_centre_state_gen_II == WAITING_TO_SEND_DATA && in != 0xFD)
    {
      counter = 0;
      // send first byte
      switch (MODE)
      {
      case 0:
        send = DATA_BLOCK_GEN_II[counter];
        INPUT_BLOCK_GEN_II[counter] = in;
        break;
      case 1:
        send = in;
        break;
      default:
        send = in;
        break;
      }
      counter++;
      trade_centre_state_gen_II = SENDING_DATA;
    }
    else if (trade_centre_state_gen_II == SENDING_DATA)
    {
      switch (MODE)
      {
      case 0:
        send = DATA_BLOCK_GEN_II[counter];
        INPUT_BLOCK_GEN_II[counter] = in;
        break;
      case 1:
        send = in;
        break;
      default:
        send = in;
        break;
      }
      counter++;
      if (counter == PLAYER_LENGTH_GEN_II)
      {
        trade_centre_state_gen_II = SENDING_PATCH_DATA;
      }
    }
    else if (trade_centre_state_gen_II == SENDING_PATCH_DATA && in == 0xFD)
    {
      counter = 0;
      send = 0xFD;
    }
    else if (trade_centre_state_gen_II == SENDING_PATCH_DATA && in != 0xFD)
    {
      send = in;
      trade_centre_state_gen_II = MIMIC;
    }
    else if (trade_centre_state_gen_II == MIMIC)
    {
      send = in;
    }
    else if (trade_centre_state_gen_II == TRADE_PENDING && (in & 0x60) == 0x60)
    {
      if (in == 0x6f)
      {
        trade_centre_state_gen_II = READY_TO_GO;
        send = 0x6f;
      }
      else
      {
        send = 0x60; // first pokemon
        trade_pokemon = in - 0x60;
      }
    }
    else if (trade_centre_state_gen_II == TRADE_PENDING && in == 0x00)
    {
      send = 0;
      trade_centre_state_gen_II = TRADE_CONFIRMATION;
    }
    else if (trade_centre_state_gen_II == TRADE_CONFIRMATION && (in & 0x60) == 0x60)
    {
      send = in;
      if (in == 0x61)
      {
        trade_pokemon = -1;
        trade_centre_state_gen_II = TRADE_PENDING;
      }
      else
      {
        trade_centre_state_gen_II = DONE;
      }
    }
    else if (trade_centre_state_gen_II == DONE && in == 0x00)
    {
      send = 0;
      trade_centre_state_gen_II = INIT;
    }
    else
    {
      send = in;
    }
    break;

  default:
    send = in;
    break;
  }

  return send;
}

int transferBit(byte *party_data)
{
  int timeout = 0;
  int flag = BYTE_INCOMPLETE;
  in_data |= (linkGPIO->readPin(LinkGPIO::Pin::SI)) << (7 - shift); /*digitalRead(MISO_)*/
  if (++shift > 7)
  {
    shift = 0;
    out_data = handleIncomingByte(in_data); // in_data
    print(
        std::to_string(trade_centre_state_gen_II) + " " +
        std::to_string(connection_state) + " " +
        std::to_string(in_data) + " " +
        std::to_string(out_data) + "\n");
    if (trade_centre_state_gen_II == SENDING_DATA)
    {
      party_data[0] = in_data;
      flag = BYTE_COMPLETE;
    }
    in_data = 0;
  }
  while (!((connection_state >= 2) ? SC_state : linkGPIO->readPin(LinkGPIO::Pin::SC)))
  {
    updateFrames();
    timeout++;
    if (timeout > TIMEOUT_TWO_LENGTH)
    {
      timeout = 0;
      return TIMEOUT;
    }
    /*
    if (timeout % 100 == 0)
    {
      tte_set_pos(0, 0);
      tte_erase_line();
      tte_write(std::to_string(timeout).c_str());
    }*/
  } // no activity when clock is low //!digitalRead(SCLK_)
  // digitalWrite(MOSI_, out_data & 0x80 ? HIGH : LOW);

  linkGPIO->writePin(LinkGPIO::Pin::SO, (out_data >> 7));
  out_data <<= 1;
  return flag;
}

int loop(byte *party_data)
{
  int counter = 0;
  int timeout;
  int transfer_state = BYTE_INCOMPLETE;
  while (true)
  {
    last_bit = frame;
    while (((connection_state >= 2) ? SC_state : linkGPIO->readPin(LinkGPIO::Pin::SC))) /*digitalRead(SCLK_)*/
    {
      updateFrames();
      timeout++;
      if (timeout > TIMEOUT_ONE_LENGTH)
      {
        return COND_ERROR_TIMEOUT_ONE;
      }
    }
    timeout = 0;
    // updateFrames();
    transfer_state = transferBit(&party_data[counter]); // This statement will cause a loop. If that loop takes too long, then the transfer state will be TIMEOUT

    if (transfer_state == BYTE_COMPLETE)
    {
      counter++;
    }
    else if (
        transfer_state == TIMEOUT)
    {
      return COND_ERROR_TIMEOUT_TWO;
    }
    if (FF_count > 25)
    {
      return COND_ERROR_DISCONNECT;
    }
    if (zero_count > 25)
    {
      return COND_ERROR_COM_ENDED;
    }
    if (connection_state == COLOSSEUM)
    {
      return COND_ERROR_COLOSSEUM;
    }

    if (trade_centre_state_gen_II == SENDING_PATCH_DATA)
    {
      return 0;
    }
  }
}
