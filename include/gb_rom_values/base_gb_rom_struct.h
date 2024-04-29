#ifndef PAYLOAD_H
#define PAYLOAD_H

// Redefine these because C++ doesn't like TONC
typedef unsigned char u8, byte, uchar, echar;
typedef unsigned short u16, hword, ushort, eshort;
typedef unsigned int u32, word, uint, eint;
typedef unsigned long long u64;

#define PAYLOAD_SIZE 672
#define NUM_PAYLOADS 3

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
    byte enter_vector_destination;  // The location within the payload array where the jump should start
    hword enter_vector_location;    // Where we should jump to from the enter vector
                                    // This can be a few different places:
                                    // wSerialOtherGameboyRandomNumberListBlock:
                                    //      0xCD81 to 0xCD8A
                                    // wLinkEnemyTrainerName:
                                    //      0xD887 to 0xDA2F
                                    // wSerialEnemyMonsPatchList:
                                    //      0xC5D0 to 0xC6E8

    word clearScreen;
    word CableClub_TextBoxBoarder;
    hword placeString;
    hword hSerialConnectionStatus;
    hword wBoxDataStart;
    hword wBoxDataEnd;
    hword Serial_ExchangeBytes;
    word wRemoveMonFromBox;
    word wBoxCount;
    word wWhichPokemon;
    word _RemovePokemon;
    word SaveSAVtoSRAM1;
    byte SaveSAVtoSRAM1_memBank;
    hword Bankswitch;
    hword SoftReset;
    hword garbageDataLocation;

    hword transferWaitString;
    hword pkmnTransferArray;
    hword arrayCounter;
    byte transferString[30];
    byte custom_name[11];

    hword transferStringLocation;
    hword textBoarderUppLeft;
    byte textBoarderWidth;
    byte textBoarderHeight;
};

#endif