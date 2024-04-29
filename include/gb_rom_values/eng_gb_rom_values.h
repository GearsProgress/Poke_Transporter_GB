#ifndef ENG_GB_ROM_VALUES_H
#define ENG_GB_ROM_VALUES_H

// These are redefined because C++ doesn't like compiling TONC
#define JPN_ID 1
#define ENG_ID 2
#define FRE_ID 3
#define ITA_ID 4
#define GER_ID 5
#define SPA_ID 7
#define KOR_ID 8

#define RED_GREEN_ID 0
#define RED_BLUE_ID 1
#define BLUE_ID 2
#define YELLOW_ID 3
#define GOLD_SILVER_ID 4
#define CRYSTAL_ID 5

#define METHOD_NEWLINE 0
#define METHOD_MEW 1
#define METHOD_GEN2 2

#include "gb_rom_values/base_gb_rom_struct.h"

const struct GB_ROM ENG_RED_BLUE = {
    .language = ENG_ID,
    .version = RED_BLUE_ID,
    .generation = 1,
    .method = METHOD_NEWLINE,
    .payload_size = 637,
    .box_data_size = 0x462,

    .print_string_start = 0xC456,
    .stack_overwrite_location = 0xDFDD,
    .short_pkmn_name = 0xE3,
    .pointer_pkmn_name = 0xFC,

    .enter_vector_destination = 0x05,
    .enter_vector_location = 0xC5D6,

    .clearScreen = 0x190F,
    .CableClub_TextBoxBoarder = 0x5AB3,
    .placeString = 0x1955,
    .hSerialConnectionStatus = 0xFFAA,
    .wBoxDataStart = 0xDA80,
    .wBoxDataEnd = 0xDEE2,
    .Serial_ExchangeBytes = 0x216F,
    .wRemoveMonFromBox = 0xCF95,
    .wBoxCount = 0xDA80,
    .wWhichPokemon = 0xCF92,
    ._RemovePokemon = 0x7B68,
    .SaveSAVtoSRAM1 = 0x77E2,
    .SaveSAVtoSRAM1_memBank = 0x1C,
    .Bankswitch = 0x35D6,
    .SoftReset = 0x1F49,
    .garbageDataLocation = 0x0316, // Starts with 0xFD

    .transferWaitString = 0xC67A, // Enter vector + A4
    .pkmnTransferArray = 0xC651,  // Enter vector + 7B
    .arrayCounter = 0xC650,       // Enter vector + 7A
    .transferString = {           // TRANSFERRING..\n
                       //  PLEASE WAIT!
                       0x93, 0x91, 0x80, 0x8D, 0x92, 0x85, 0x84, 0x91, 0x91, 0x88, 0x8D, 0x86, 0xF2, 0xF2, 0x4E,
                       0x7F, 0x8F, 0x8B, 0x84, 0x80, 0x92, 0x84, 0x7F, 0x96, 0x80, 0x88, 0x93, 0xE7, 0x7F, 0x50},
    .custom_name = {0x85, 0x84, 0x8D, 0x8D, 0x84, 0x8B, 0x50, 0x50, 0x50, 0x50, 0x50},

    .transferStringLocation = 0xC443,
    .textBoarderUppLeft = 0xC42E,
    .textBoarderWidth = 3,
    .textBoarderHeight = 14,
};

const struct GB_ROM ENG_YELLOW = {
    .language = ENG_ID,
    .version = YELLOW_ID,
    .generation = 1,
    .method = METHOD_MEW,
    .payload_size = 637,
    .box_data_size = 0x462,

    .print_string_start = 0xC456,
    .stack_overwrite_location = 0xDFDD,
    .short_pkmn_name = 0x15,
    .pointer_pkmn_name = 0xE3,

    //.enter_vector_destination = 0x05,
    //.enter_vector_location = 0xC5D6,

    .clearScreen = 0x16DD,
    .CableClub_TextBoxBoarder = 0x5B67,
    .placeString = 0x1723,
    .hSerialConnectionStatus = 0xFFAA,
    .wBoxDataStart = 0xDA7F,
    .wBoxDataEnd = 0xDEE1,
    .Serial_ExchangeBytes = 0x1FCB,
    .wRemoveMonFromBox = 0xCF94,
    .wBoxCount = 0xDA7F,
    .wWhichPokemon = 0xCF91,
    ._RemovePokemon = 0x7A0F,
    .SaveSAVtoSRAM1 = 0x1B32,
    .SaveSAVtoSRAM1_memBank = 0x1C,
    .Bankswitch = 0x3E84,
    .SoftReset = 0x1D05,
    .garbageDataLocation = 0x0161, // Starts with 0xFD

    .transferWaitString = 0xC67A, // Enter vector + A4
    .pkmnTransferArray = 0xC651,  // Enter vector + 7B
    .arrayCounter = 0xC650,       // Enter vector + 7A
    .transferString = {           // TRANSFERRING..\n
                       //  PLEASE WAIT!
                       0x93, 0x91, 0x80, 0x8D, 0x92, 0x85, 0x84, 0x91, 0x91, 0x88, 0x8D, 0x86, 0xF2, 0xF2, 0x4E,
                       0x7F, 0x8F, 0x8B, 0x84, 0x80, 0x92, 0x84, 0x7F, 0x96, 0x80, 0x88, 0x93, 0xE7, 0x7F, 0x50},
    .custom_name = {0x85, 0x84, 0x8D, 0x8D, 0x84, 0x8B, 0x50, 0x50, 0x50, 0x50, 0x50},

    .transferStringLocation = 0xC443,
    .textBoarderUppLeft = 0xC42E,
    .textBoarderWidth = 3,
    .textBoarderHeight = 14,
};


const struct GB_ROM ENG_GOLD_SILVER = {
    .language = ENG_ID,
    .version = GOLD_SILVER_ID,
    .generation = 2,
    .method = METHOD_GEN2,
    .payload_size = 672,
    .box_data_size = 0x44E,

    /**/
    .print_string_start = 0xC442,
    .stack_overwrite_location = 0xDFCB, // Found by seeing where 772C is stored in the stack, 772C is the code that calls PlaceString
    .short_pkmn_name = 0x4E,
    //.pointer_pkmn_name = 0xFC,

    //.enter_vector_destination = 0x05,
    .enter_vector_location = 0xC5D6,

    .clearScreen = 0x000EE2,
    .CableClub_TextBoxBoarder = 0x0A4D88, // LinkTextboxAtHL
    .placeString = 0x000F74,
    .hSerialConnectionStatus = 0xFFCD,
    .wBoxDataStart = 0xAD6C, // sBoxStart
    .wBoxDataEnd = 0xB1BA,   // sBoxEnd
    .Serial_ExchangeBytes = 0x0710,
    .wRemoveMonFromBox = 0x01D008, // wPokemonWithdrawDepositParameter, bank 1
    .wBoxCount = 0x01AD6C, // sBoxCount, bank 1
    .wWhichPokemon = 0x01D005,  // wCurPartyMon, bank 1
    ._RemovePokemon = 0x03603F - 2, // RemoveMonFromPartyOrBox, bank 3
    .SaveSAVtoSRAM1 = 0x0577E2, // ? 0x4DF6
    .SaveSAVtoSRAM1_memBank = 0x5,
    //.Bankswitch = 0x0010,
    .SoftReset = 0x05B0,           // ?
    .garbageDataLocation = 0x0654, // ? Starts with 0xFD

    .transferWaitString = 0xC67A, // Enter vector +
    .pkmnTransferArray = 0xC651,  // Enter vector +
    .arrayCounter = 0xC650,       // Enter vector +
    .transferString = {           // TRANSFERRING..\n
                       //  PLEASE WAIT!
                       0x93, 0x91, 0x80, 0x8D, 0x92, 0x85, 0x84, 0x91, 0x91, 0x88, 0x8D, 0x86, 0xF2, 0xF2, 0x4E,
                       0x7F, 0x8F, 0x8B, 0x84, 0x80, 0x92, 0x84, 0x7F, 0x96, 0x80, 0x88, 0x93, 0xE7, 0x7F, 0x50},
    .custom_name = {0x85, 0x84, 0x8D, 0x8D, 0x84, 0x8B, 0x50, 0x50, 0x50, 0x50, 0x50},

    .transferStringLocation = 0xC443, // ?
    .textBoarderUppLeft = 0xC42E,     // ?
    .textBoarderWidth = 3,            // ?
    .textBoarderHeight = 14,          // ?
};

#endif