//Created by StevenChaulk https://github.com/stevenchaulk/arduino-poke-gen2

#ifndef GAMEBOY_COLOUR_H_
#define GAMEBOY_COLOUR_H_

#include <tonc.h>
#include <string>
#include "libraries/gba-link-connection/LinkSPI.hpp"
#include "pokemon_party.h"

/*
#define LINK_SPI_NO_DATA 0xffffffff
#define LINK_SPI_SIOCNT_NORMAL 0
#define LINK_SPI_BIT_CLOCK 0
#define LINK_SPI_BIT_CLOCK_SPEED 1
#define LINK_SPI_BIT_SI 2
#define LINK_SPI_BIT_SO 3
#define LINK_SPI_BIT_START 7
#define LINK_SPI_BIT_LENGTH 12
#define LINK_SPI_BIT_IRQ 14
#define LINK_SPI_BIT_GENERAL_PURPOSE_LOW 14
#define LINK_SPI_BIT_GENERAL_PURPOSE_HIGH 15
#define LINK_SPI_SET_HIGH(REG, BIT) REG |= 1 << BIT
#define LINK_SPI_SET_LOW(REG, BIT) REG &= ~(1 << BIT)

#define LINK_SPI_SET(REG, BIT, VALUE) VALUE ? LINK_SPI_SET_HIGH(REG, BIT) : LINK_SPI_SET_LOW(REG, BIT)
*/


// The number of frames(?) between changing the clock signals
#define FAST_SPEED 10
#define SLOW_SPEED 1000

void setup();
byte handleIncomingByte(byte in, byte *box_data_storage, PAYLOAD *curr_payload, Simplified_Pokemon *curr_simple_array);
int loop(byte *box_data_storage, PAYLOAD *curr_payload, Simplified_Pokemon *curr_simple_array);
byte exchange_parties(byte curr_in, PAYLOAD *curr_payload);
byte exchange_boxes(byte curr_in, byte *party_data);
byte exchange_remove_array(byte curr_in, Simplified_Pokemon *curr_simple_array);

#endif /* GAMEBOY_COLOUR_H_ */
