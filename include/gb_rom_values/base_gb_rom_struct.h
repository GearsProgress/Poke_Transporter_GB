#ifndef PAYLOAD_H
#define PAYLOAD_H

// Redefine these because C++ doesn't like TONC
typedef unsigned char  u8,  byte, uchar, echar;
typedef unsigned short u16, hword, ushort, eshort;
typedef unsigned int   u32, word, uint, eint;
typedef unsigned long long u64;

#define PAYLOAD_SIZE 637
#define NUM_PAYLOADS 1

#define GB_TILE_WIDTH 20

struct GB_ROM
{
public:
    int language;
    int version;
    byte payload_array[PAYLOAD_SIZE];

    hword print_string_start;
    hword stack_overwrite_location;
    byte short_pkmn_name; // The name of the Pokemon that moves us through RAM
    byte pointer_pkmn_name; // The name of the Pokemon that corrupts the stack
    byte custom_name[11];
    // This can be a few different places:
    // wSerialOtherGameboyRandomNumberListBlock:
    //      0xCD81 to 0xCD8A
    // wLinkEnemyTrainerName: 
    //      0xD887 to 0xDA2F
    // wSerialEnemyMonsPatchList:
    //      0xC5D0 to 0xC6E8
    byte enter_vector_destination;
    hword enter_vector_location;
    hword clearScreen;
    hword textBoarderUppLeft;
    byte textBoarderWidth;
    byte textBoarderHeight;
    hword CableClub_TextBoxBoarder;
    hword transferWaitString;
    hword transferStringLocation;
    hword placeString;
    hword hSerialConnectionStatus;
    hword wBoxDataStart;
    hword wBoxDataEnd;
    hword Serial_ExchangeBytes;
    hword garbageDataLocation;
    hword pkmnTransferArray;
    hword wRemoveMonFromBox;
    hword arrayCounter;
    hword wBoxCount;
    hword wWhichPokemon;
    hword _RemovePokemon;
    hword SaveSAVtoSRAM1;
    byte SaveSAVtoSRAM1_memBank;
    hword Bankswitch;
    hword SoftReset;
    byte transferString[30];
};

#endif