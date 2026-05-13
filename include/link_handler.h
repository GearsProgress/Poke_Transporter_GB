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

enum CompositeState
{
    NO_COMPOSITE_STATE,
    INITIAL_CONNECTION
};

enum SubstateState
{
    NO_SUBSTATE,
    // INITIAL_CONNECTION
    CLOCK,
    SAVE_SUCCESS,
    MENU_OPEN,
    MENU_SUCCESS,
    WAIT_FOR_TRADE,
    TRADE_PREAMBLE,
    TRADE,
    EXTRA_BYTE,
    MAIL,
    END,
};

class LinkConnection
{
public:
    LinkConnection *globalPtr;

    CompositeState compState = NO_COMPOSITE_STATE;
    SubstateState subState = NO_SUBSTATE;

    CompositeState prevCompState = NO_COMPOSITE_STATE;
    SubstateState prevSubState = NO_SUBSTATE;

    uint8_t inData;
    uint8_t outData;

    int compStateCounter = 0; // the counter for the total number of bytes sent compstate
    int subStateCounter = 0;  // The counter for the total number of bytes sent in this substate
    int gen = 0;              // The generation we are trading with

    int FF_count = 0;   // The number of 0xFF bytes that have been in a row
    int zero_count = 0; // The number of 0x00 bytes that have been in a row

    int mosi_delay = 4;      // inital delay, speeds up once sending
    int received_offset = 0; // The offset contained in the last packet
    int next_offset = 0;     // The offset we are sending in the next packet
    int packet_index = 0;    // The index of the current packet

    bool failed_packet = false;    // Flags if a packet failed
    bool init_packet = true;       // Flags if a packet is the inital one
    bool end_of_data = false;      // Flags if we are at the end of the data
    bool test_packet_fail = false; // ???

    byte data_packet[PACKET_SIZE];
    byte curr_payload[0x2A0];
    int curr_payload_size = 0;

    bool paused = false; // Used for pausing and sending one byte at a time

    void setup(const u16 *debug_charset);
    void startConnection(CompositeState startState);
    bool earlyExit();
    void exchangeBytes();
    void printData();
    void writeData();
    void handleStateLogic();

private:
    void load_universal_payload();
    void logicState_initConnection();

    // Used for debug features
#define LINE_WIDTH 24
#define NUM_LINES 8
    char stuff[NUM_LINES][LINE_WIDTH];
    char line[LINE_WIDTH] = "OUT";
    int link_cable_array_index = 0;
    int link_cable_memory_section_index = 0;
    const u16 *debug_charset;
};

extern LinkConnection globalLinkCable;
void linkCableIRQ();

#endif /* LINK_HANDLER_H_ */
