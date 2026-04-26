// Loosely based on code created by StevenChaulk
// Source: https://github.com/stevenchaulk/arduino-poke-gen2

#ifndef LINK_HANDLER_H_
#define LINK_HANDLER_H_

#include <tonc.h>
#include "libraries/gba-link-connection/LinkSPI.hpp"
#include "pokemon_party.h"

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

#define SPI_TEXT_OUT_ARRAY_ELEMENT_SIZE 64

enum ConnectionState
{
    CLOCK,
    MENU,
    WAIT_FOR_TRADE,
    TRADE_PREAMBLE,
    TRADE,
    PARTY_PREAMBLE,
    COLOSSEUM,
    CANCEL,
    TRADE_DATA,
    BOX_PREAMBLE,
    BOX_DATA,
    END1,
    REBOOT,
    REMOVE_ARRAY_PREAMBLE,
    SEND_REMOVE_ARRAY,
    END2,
};

struct LinkState
{
    ConnectionState conState = CLOCK;

    uint8_t in_data;
    uint8_t out_data;

    int section_data_counter = 0; // The counter for the number of bytes we have sent in this section
    int global_data_counter = 0; // the counter for the total number of bytes sent
    int gen = 0;          // The generation we are trading with

    int FF_count = 0;   // The number of 0xFF bytes that have been in a row
    int zero_count = 0; // The number of 0x00 bytes that have been in a row

    int mosi_delay = 4;      // inital delay, speeds up once sending
    int received_offset = 0; // The offset contained in the last packet
    int next_offset = 0;     // The offset we are sending in the next packet
    int packet_index = 0;    // The index of the current packet

    bool failed_packet = false; // Flags if a packet failed
    bool init_packet = true;    // Flags if a packet is the inital one
    bool end_of_data = false;   // Flags if we are at the end of the data
    bool test_packet_fail = false; // ???

    byte data_packet[PACKET_SIZE];

    bool irq_enabled = true; // Stores if the IRQ is currently enabled, used for pausing and sending one byte at a time

    // This is info that was passed in via handleIncomingByte
    byte *box_data_storage;
    byte *curr_payload;
    GB_ROM *curr_gb_rom;
    PokeBox *box;
    const u16 *debug_charset;
    bool cancel_connection;
};

void setup(byte *box_data_storage, byte *curr_payload, GB_ROM *curr_rom, PokeBox *box, const u16 *debug_charset, bool cancel_connection);
byte handleIncomingByte();
int loop(byte *box_data_storage, byte *curr_payload, GB_ROM *curr_rom, PokeBox *box, const u16 *debug_charset, bool cancel_connection);
byte exchange_parties(byte curr_in, byte *curr_payload);
byte exchange_boxes(byte curr_in, byte *party_data, GB_ROM *curr_gb_rom, const u16 *debug_charset);
byte exchange_remove_array(byte curr_in, PokeBox *box, bool cancel_connection);
void handshake();

#endif /* LINK_HANDLER_H_ */
