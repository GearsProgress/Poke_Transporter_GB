#ifndef PAYLOAD_H
#define PAYLOAD_H

// Redefine these because C++ doesn't like TONC
typedef unsigned char u8, byte, uchar, echar;
typedef unsigned short u16, hword, ushort, eshort;
typedef unsigned int u32, word, uint, eint;
typedef unsigned long long u64;

#define PAYLOAD_SIZE 672
#define NUM_PAYLOADS 1

#define GB_TILE_WIDTH 20

struct GB_ROM
{
public:
    int language;
    int version;
    int generation;
    int method;
    int payload_size;
    int box_data_size;

    hword print_string_start;       // Start of where text is written in VRAM
    hword stack_overwrite_location; // The part of the stack that we're overwriting
    byte short_pkmn_name;           // The name of the Pokemon that moves us through RAM
    byte pointer_pkmn_name;         // The name of the Pokemon that overwrites the stack
    hword enter_vector_location;    // Where we should jump to from the enter vector
                                    // This can be a few different places:
                                    // wSerialOtherGameboyRandomNumberListBlock:
                                    //      0xCD81 to 0xCD8A
                                    // wLinkEnemyTrainerName:
                                    //      0xD887 to 0xDA2F
                                    // wSerialEnemyMonsPatchList:
                                    //      0xC5D0 to 0xC6E8

    word clearScreen;             // location of the clearScreen function in the ROM
    word CableClub_TextBoxBorder; // location of the CableClub_TextBoxBorder function in the ROM
    word placeString;             // location of the placeString function in the ROM
    word Serial_ExchangeBytes;    // location of the Serial_ExchangeBytes function in the ROM
    word _RemovePokemon;          // location of the _RemovePokemon function in the ROM
    word SaveSAVtoSRAM1;          // location of the SaveSAVtoSRAM1 function in the ROM
    word SaveSAVtoSRAM2;          // location of the SaveSAVtoSRAM2 function in the ROM
    word OpenSRAM;                // location of the OpenSRAM function in the ROM
    word SaveBox;                 // location of the SaveBox function in the ROM
    word Bankswitch;              // location of the Bankswitch function in the ROM
    word SoftReset;               // location of the SoftReset function in the ROM
    word garbageDataLocation;     // location of random data starting with 0xFD in the ROM

    word wRemoveMonFromBox;       // location of wRemoveMonFromBox in RAM
    word wBoxCount;               // location of wBoxCount in RAM
    word wWhichPokemon;           // location of wWhichPokemon in RAM
    word hSerialConnectionStatus; // location of hSerialConnectionStatus in RAM
    word wBoxDataStart;           // location of wBoxDataStart in RAM
    word wBoxDataEnd;             // location of wBoxDataEnd in RAM

    word transferWaitString; // location of the transferWaitString in RAM
    word pkmnTransferArray;  // location of the pkmnTransferArray in RAM
    word arrayCounter;       // location of the arrayCounter in RAM

    byte transferString[30]; // the custom transfer string
    byte custom_name[11];    // the custom name string

    hword transferStringLocation; // location in VRAM to start writing the transfer string to
    hword textBorderUppLeft;      // location in VRAM to put the upper left corner of the border
    byte textBorderWidth;         // the width of the text box border
    byte textBorderHeight;        // the height of the text box border
};

#endif