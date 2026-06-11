#ifndef LINK_HANDLER_H_
#define LINK_HANDLER_H_

#include <tonc.h>
#include "libraries/gba-link-connection/LinkSPI.hpp"
#include "pokemon_party.h"
#include "GB_Payloads.h"

#define SPI_TEXT_OUT_ARRAY_ELEMENT_SIZE 64

enum GameBoyROM
{
    RED_JP_v0,
    RED_JP_v1,
    RED_EN,
    RED_FR,
    RED_IT,
    RED_DE,
    RED_SP,
    GREEN_JP_v0,
    GREEN_JP_v1,
    BLUE_JP,
    BLUE_EN,
    BLUE_FR,
    BLUE_IT,
    BLUE_DE,
    BLUE_SP,
    YELLOW_JP_v0,
    YELLOW_JP_v1,
    YELLOW_JP_v2,
    YELLOW_JP_v3,
    YELLOW_EN,
    YELLOW_FR,
    YELLOW_IT,
    YELLOW_DE,
    YELLOW_SP,
    GOLD_JP_v0,
    GOLD_JP_v1,
    GOLD_EN,
    GOLD_FR,
    GOLD_IT,
    GOLD_DE,
    GOLD_SP,
    GOLD_KOR,
    SILVER_JP_v0,
    SILVER_JP_v1,
    SILVER_EN,
    SILVER_FR,
    SILVER_IT,
    SILVER_DE,
    SILVER_SP,
    SILVER_KOR,
    CRYSTAL_JP,
    CRYSTAL_EN,
    CRYSTAL_FR,
    CRYSTAL_IT,
    CRYSTAL_DE,
    CRYSTAL_SP,

    NO_GB_ROM,
    GB_ROM_ERROR,
};

// This table has the 3 checksums, followed by the enum value
const u8 GameBoyROMChecksumTable[][4]{
    {0x32, 0xA2, 0xC1, RED_JP_v0},
    {0x31, 0xB8, 0x66, RED_JP_v1},
    {0x20, 0x91, 0xE6, RED_EN},
    {0x18, 0x7A, 0xFC, RED_FR},
    {0x18, 0x89, 0xD2, RED_IT},
    {0x18, 0x5C, 0xDC, RED_DE},
    {0x18, 0x38, 0x4A, RED_SP},
    {0x9C, 0xDD, 0xD5, GREEN_JP_v0},
    {0x9B, 0xF5, 0x47, GREEN_JP_v1},
    {0xE5, 0xDC, 0x36, BLUE_JP},
    {0xD3, 0x9D, 0x0A, BLUE_EN},
    {0xCB, 0x56, 0xA4, BLUE_FR},
    {0xCB, 0x5E, 0x9C, BLUE_IT},
    {0xCB, 0x2E, 0xBC, BLUE_DE},
    {0xCB, 0x14, 0xD7, BLUE_SP},
    {0x20, 0x9C, 0x29, YELLOW_JP_v0},
    {0x1F, 0x88, 0x58, YELLOW_JP_v1},
    {0x1E, 0xED, 0xD9, YELLOW_JP_v2},
    {0x1D, 0xD9, 0x84, YELLOW_JP_v3},
    {0x97, 0x04, 0x7C, YELLOW_EN},
    {0x61, 0x66, 0xFB, YELLOW_FR},
    {0x5C, 0x4E, 0x8F, YELLOW_IT},
    {0x5F, 0xB7, 0xC1, YELLOW_DE},
    {0x52, 0x56, 0x37, YELLOW_SP},
    {0x48, 0x8A, 0x70, GOLD_JP_v0},
    {0x47, 0x84, 0x60, GOLD_JP_v1},
    {0x4B, 0x68, 0x2D, GOLD_EN},
    {0x4A, 0x6F, 0xC6, GOLD_FR},
    {0x47, 0xCE, 0x0C, GOLD_IT},
    {0x4C, 0xDC, 0x97, GOLD_DE},
    {0x3D, 0x93, 0x53, GOLD_SP},
    {0x08, 0x77, 0x8A, GOLD_KOR},
    {0x27, 0x76, 0x91, SILVER_JP_v0},
    {0x26, 0x1D, 0x34, SILVER_JP_v1},
    {0x2A, 0x0D, 0xAE, SILVER_EN},
    {0x29, 0xFB, 0x8C, SILVER_FR},
    {0x26, 0x73, 0x50, SILVER_IT},
    {0x2B, 0xCD, 0x6E, SILVER_DE},
    {0x1C, 0x06, 0x4B, SILVER_SP},
    {0xE7, 0x98, 0x5B, SILVER_KOR},
    {0x22, 0x9A, 0x40, CRYSTAL_JP},
    {0x26, 0x18, 0xD2, CRYSTAL_EN},
    {0x26, 0xF2, 0xE2, CRYSTAL_FR},
    {0x23, 0xDB, 0xBA, CRYSTAL_IT},
    {0x28, 0x49, 0x82, CRYSTAL_DE},
    {0x19, 0x42, 0xF4, CRYSTAL_SP},
};

enum LinkState
{
    INITIAL_CONNECTION = 0x00,
    CLOCK,
    SAVE_SUCCESS,
    MENU_OPEN,
    MENU_SUCCESS,
    WAIT_FOR_TRADE,
    TRADE_PREAMBLE,
    TRADE,
    MAIL,
    WAIT_FOR_CHECKSUM_PAYLOAD,
    GET_CHECKSUM,
    WAIT_FOR_SECOND_PAYLOAD,
    SEND_SPECIFIC_PAYLOAD,
    SOFT_RESET,

    PACKET_EXCHANGE = 0x10,
    BYTE_EXCHANGE,
    PRINT_LAST_PACKET,

    END = 0xFF,
};

enum LinkConnectionError
{
    NO_ERROR,
    PACKET_TIMED_OUT,
    CHECKSUM_MISMATCH,
};

enum PayloadCommand
{
    CMD_ReloadCurrentBox,    // no arguments used. Reloads the current box from SRAM. Use this as the first command byte before performing other commands.
    CMD_TransferPokemon,     // 1st argument = secondary payload size, 2nd argument = box that should be transferred from. This command uses a secondary payload. The size of this secondary payload needs to be declared beforehand. Prior to requesting a secondary payload, the program will use the second argument to load a specific box from SRAM. Box numbers are 0-indexed and range from 0x00 (box 1) to 0x0B(box 12). This load procedure currently cannot be skipped. Once the secondary payload arrives, the program will verify its integrity and align the payload. Afterwards, it will use the information within this payload to remove pokémon from the current box. Once all transferred pokémon have been removed, the program will save the current box.
    CMD_SoftReset,           // no arguments used. Instantly soft resets the game.
    CMD_OpenSRAM,            // 1st argument = SRAM bank to be opened. Opens access to SRAM and switches to the SRAM bank determined by the 1st argument. SRAM will remain open afterwards.
    CMD_CloseSRAM,           // no arguments used. Instantly closes access to SRAM.
    CMD_RunSecondaryPayload, // 1st argument = secondary payload size. This command uses a secondary payload. The size of this secondary payload needs to be declared beforehand. Once the secondary payload arrives, the program will verify its integrity and align the payload. Afterwards, it will jump to the secondary payload and execute it. IMPORTANT: if you want to report an error when executing this secondary payload, return with carry flag set. IMPORTANT: if you want to report that the payload was executed safely, return with carry flag reset.*/
    CMD_ReadDataRequest,     // a request to read data starting from the address defined by the 16-bit pointer.
};

#define OUTP_PREAMBLE_INDEX 0
#define OUTP_COUNTER_INDEX 1
#define OUTP_COMMAND_INDEX 2
#define OUTP_ARGS_INDEX 3
#define OUTP_POINTER_INDEX 5
#define OUTP_FILLER_INDEX 7
#define OUTP_LENGTH 13

#define INP_COUNTER_INDEX (0 + INP_DELAY_FROM_OUTP)
#define INP_LSB_INDEX (1 + INP_DELAY_FROM_OUTP)
#define INP_CHECKSUM_INDEX (3 + INP_DELAY_FROM_OUTP)
#define INP_DATA_INDEX (4 + INP_DELAY_FROM_OUTP)
#define INP_LENGTH (12 + INP_DELAY_FROM_OUTP)

#define INP_DELAY_FROM_OUTP 3
#define TOTAL_PACKET_LENGTH (OUTP_LENGTH + INP_DELAY_FROM_OUTP)

struct LinkPacket
{
    // Out packet parameters
    PayloadCommand command;
    byte argument[2] = {0x00, 0x00};
    u16 pointer;

    // Incoming data
    LinkConnectionError latestError = NO_ERROR;
    byte recievedData[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
};

class LinkConnection
{
public:
    LinkState enterState;
    LinkState exitState;
    bool subStateChanged = false;

    LinkConnectionError lastError = NO_ERROR;

    uint8_t inData;
    uint8_t outData;
    uint8_t nextOutData;

    int globalStateCounter = 0; // The counter for the total number of bytes sent
    int subStateCounter = 0; // The counter for the total number of bytes sent in this substate

    int gen = 0;                    // The generation we are trading with
    GameBoyROM currROM = NO_GB_ROM; // The GameBoy ROM we're communicating with

    int FF_count = 0;   // The number of 0xFF bytes that have been in a row
    int zero_count = 0; // The number of 0x00 bytes that have been in a row

    byte payloadBuffer[0x2A0];
    int curr_payload_size = 0;
    byte dataOutBuffer[16];
    int dataOutBufferCurrIndex = 0;

    LinkPacket *currLinkPacketArr;
    int currLinkPacketArrTotalCount = 0;
    int currLinkPacketArrFilledCount = 0;
    int currLinkPacketArrIndex = 0;

    bool pauseOnByte = false;   // Used for pausing and sending one byte at a time
    bool pauseOnPacket = false; // Used for pausing and sending one packet at a time
    bool skipPrint = false;     // Skips printing to the screen
    bool newPacket = false;

    void setup(const u16 *debug_charset);
    void startConnection(LinkState startState);
    bool earlyExit();
    void exchangeBytes();
    void printData();
    void writeData();
    void handleStateLogic();
    void prepareForNextCycle();
    // Some operations are too long to be done within the IRQ.
    // So we need to handle them in the main loop instead to avoid data corruption.
    void handleCartIO();

private:
    void load_payload(GB_PayloadsFiles payload);
    void loadCurrGameFromChecksum();
    bool processPacket();

    // Used for debug features
#define LINE_WIDTH 24
#define NUM_LINES 8
    char stuff[NUM_LINES][LINE_WIDTH];
    char line[LINE_WIDTH] = "OUT";
    unsigned link_cable_memory_section_index;
    unsigned link_cable_array_index;
    const u16 *debug_charset;
    unsigned writeBufferOffset;
};

extern LinkConnection globalLinkCable;
void linkCableIRQ();

#endif /* LINK_HANDLER_H_ */
