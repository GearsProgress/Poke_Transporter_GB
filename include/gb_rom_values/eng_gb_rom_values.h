#ifndef ENG_GB_ROM_VALUES_H
#define ENG_GB_ROM_VALUES_H

#include "base_gb_rom_struct.h"

const struct GB_ROM ENG_RED = {
    .language = ENG_ID,
    .version = RED_ID,
    .generation = 1,
    .method = METHOD_NEWLINE,
    .payload_size = 637,
    .box_data_size = 0x462,

    .print_string_start = 0xC456,
    .stack_overwrite_location = 0xDFDD,
    .short_pkmn_name = 0xE3,
    .pointer_pkmn_name = 0xFC,

    .clearScreen = 0x190F,
    .CableClub_TextBoxBorder = 0x5AB3,
    .placeString = 0x1955,
    .Serial_ExchangeBytes = 0x216F,
    ._RemovePokemon = 0x7B68,
    .SaveSAVtoSRAM1 = 0x1C77E2,
    .SaveSAVtoSRAM2 = 0x1C780F,
    .Bankswitch = 0x35D6,
    .SoftReset = 0x1F49,
    .garbageDataLocation = 0x0316,

    .wRemoveMonFromBox = 0xCF95,
    .wBoxCount = 0xDA80,
    .wWhichPokemon = 0xCF92,
    .wBoxDataStart = 0xDA80,
    .wBoxDataEnd = 0xDEE2,
    .wSerialEnemyDataBlock = 0xD893,
    .wEnemyMonSpecies = 0xCFE5,

    .wSerialEnemyMonsPatchList = 0xC5D0,
    .wSerialOtherGameboyRandomNumberListBlock = 0xCD81,
    .hSerialConnectionStatus = 0xFFAA,

    .transferStringLocation = 0xC444,
    .textBorderUppLeft = 0xC42F,
    .textBorderWidth = 12,
    .textBorderHeight = 1,
};
const struct GB_ROM ENG_BLUE = {
    .language = ENG_ID,
    .version = BLUE_ID,
    .generation = 1,
    .method = METHOD_NEWLINE,
    .payload_size = 637,
    .box_data_size = 0x462,

    .print_string_start = 0xC456,
    .stack_overwrite_location = 0xDFDD,
    .short_pkmn_name = 0xE3,
    .pointer_pkmn_name = 0xFC,

    .clearScreen = 0x190F,
    .CableClub_TextBoxBorder = 0x5AB3,
    .placeString = 0x1955,
    .Serial_ExchangeBytes = 0x216F,
    ._RemovePokemon = 0x7B68,
    .SaveSAVtoSRAM1 = 0x1C77E2,
    .SaveSAVtoSRAM2 = 0x1C780F,
    .Bankswitch = 0x35D6,
    .SoftReset = 0x1F49,
    .garbageDataLocation = 0x0316,

    .wRemoveMonFromBox = 0xCF95,
    .wBoxCount = 0xDA80,
    .wWhichPokemon = 0xCF92,
    .wBoxDataStart = 0xDA80,
    .wBoxDataEnd = 0xDEE2,
    .wSerialEnemyDataBlock = 0xD893,
    .wEnemyMonSpecies = 0xCFE5,

    .wSerialEnemyMonsPatchList = 0xC5D0,
    .wSerialOtherGameboyRandomNumberListBlock = 0xCD81,
    .hSerialConnectionStatus = 0xFFAA,

    .transferStringLocation = 0xC444,
    .textBorderUppLeft = 0xC42F,
    .textBorderWidth = 12,
    .textBorderHeight = 1,
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

    .clearScreen = 0x16DD,
    .CableClub_TextBoxBorder = 0x16F0, // TextBoxBoarder, since the Cable Club isn't loaded
    .placeString = 0x1723,
    .Serial_ExchangeBytes = 0x1FCB,
    ._RemovePokemon = 0x7A0F,
    .SaveSAVtoSRAM1 = 0x1C7B32,
    .SaveSAVtoSRAM2 = 0x1C7B56,
    .OpenSRAM = 0x3E99,
    .Bankswitch = 0x3E7E, // BankswitchCommon
    .SoftReset = 0x1D05,
    .CloseSRAM = 0x3EA9,
    .garbageDataLocation = 0x0161,

    .wRemoveMonFromBox = 0xCF94,
    .wBoxCount = 0xDA7F,
    .wWhichPokemon = 0xCF91,
    .wBoxDataStart = 0xDA7F,
    .wBoxDataEnd = 0xDEE1,
    .wSerialEnemyDataBlock = 0xD892,
    .wEnemyMonSpecies = 0xCFE4,

    .wSerialEnemyMonsPatchList = 0xC5D0,
    .wSerialOtherGameboyRandomNumberListBlock = 0xCD81,
    .hSerialConnectionStatus = 0xFFAA,

    .transferStringLocation = 0xC444,
    .textBorderUppLeft = 0xC42F,
    .textBorderWidth = 12,
    .textBorderHeight = 1,
};
const struct GB_ROM ENG_GOLD = {
    .language = ENG_ID,
    .version = GOLD_ID,
    .generation = 2,
    .method = METHOD_GEN2,
    .payload_size = 672,
    .box_data_size = 0x44E,

    .print_string_start = 0xC442,
    .stack_overwrite_location = 0xDFCB, // Found by seeing where 772C is stored in the stack, 772C is the code that calls PlaceString
    .short_pkmn_name = 0x4E,

    .clearScreen = 0x000EE2,
    .CableClub_TextBoxBorder = 0x0A4D88, // LinkTextboxAtHL
    .placeString = 0x000F74,
    .Serial_ExchangeBytes = 0x0710,
    ._RemovePokemon = 0x03603F, // RemoveMonFromPartyOrBox
    .OpenSRAM = 0x0030E1,
    .SaveBox = 0x054DF6,
    .SoftReset = 0x05B0,
    .garbageDataLocation = 0x0654,

    .wRemoveMonFromBox = 0x01D008,   // wPokemonWithdrawDepositParameter
    .wBoxCount = 0x01AD6C,           // sBoxCount
    .wWhichPokemon = 0x01D005,       // wCurPartyMon
    .wBoxDataStart = 0xAD6C,         // sBoxStart
    .wBoxDataEnd = 0xB1BA,           // sBoxEnd
    .wSerialEnemyDataBlock = 0xDD40, // wOTPartyData
    .wEnemyMonSpecies = 0x01D0EF,

    .wSerialEnemyMonsPatchList = 0xC5D0,                // wOTPatchLists
    .wSerialOtherGameboyRandomNumberListBlock = 0xD0EF, // wOTLinkBattleRNData
    .hSerialConnectionStatus = 0xFFCD,

    .transferStringLocation = 0xC444,
    .textBorderUppLeft = 0xC42F,
    .textBorderWidth = 12,
    .textBorderHeight = 1,
};
const struct GB_ROM ENG_SILVER = {
    .language = ENG_ID,
    .version = SILVER_ID,
    .generation = 2,
    .method = METHOD_GEN2,
    .payload_size = 672,
    .box_data_size = 0x44E,

    .print_string_start = 0xC442,
    .stack_overwrite_location = 0xDFCB, // Found by seeing where 772C is stored in the stack, 772C is the code that calls PlaceString
    .short_pkmn_name = 0x4E,

    .clearScreen = 0x000EE2,
    .CableClub_TextBoxBorder = 0x0A4D88, // LinkTextboxAtHL
    .placeString = 0x000F74,
    .Serial_ExchangeBytes = 0x0710,
    ._RemovePokemon = 0x03603D, // RemoveMonFromPartyOrBox
    .OpenSRAM = 0x0030E1,
    .SaveBox = 0x054DF6,
    .SoftReset = 0x05B0,
    .garbageDataLocation = 0x0654,

    .wRemoveMonFromBox = 0x01D008,   // wPokemonWithdrawDepositParameter
    .wBoxCount = 0x01AD6C,           // sBoxCount
    .wWhichPokemon = 0x01D005,       // wCurPartyMon
    .wBoxDataStart = 0xAD6C,         // sBoxStart
    .wBoxDataEnd = 0xB1BA,           // sBoxEnd
    .wSerialEnemyDataBlock = 0xDD40, // wOTPartyData
    .wEnemyMonSpecies = 0x01D0EF,

    .wSerialEnemyMonsPatchList = 0xC5D0,                // wOTPatchLists
    .wSerialOtherGameboyRandomNumberListBlock = 0xD0EF, // wOTLinkBattleRNData
    .hSerialConnectionStatus = 0xFFCD,

    .transferStringLocation = 0xC444,
    .textBorderUppLeft = 0xC42F,
    .textBorderWidth = 12,
    .textBorderHeight = 1,
};
const struct GB_ROM ENG_CRYSTAL = {
    .language = ENG_ID,
    .version = CRYSTAL_ID,
    .generation = 2,
    .method = METHOD_GEN2,
    .payload_size = 672,
    .box_data_size = 0x44E,

    .print_string_start = 0xC544,
    .stack_overwrite_location = 0xE0BB, // Found by seeing where 7622 is stored in the stack, 7622 is the code that calls PlaceString (PlaceTradePartnerNamesAndParty)
    .short_pkmn_name = 0x4E,

    .clearScreen = 0x000FDB,
    .CableClub_TextBoxBorder = 0x0A4EEF, // LinkTextboxAtHL
    .placeString = 0x001078,
    .Serial_ExchangeBytes = 0x075F,
    ._RemovePokemon = 0x036039, // RemoveMonFromPartyOrBox
    .OpenSRAM = 0x002FCB,
    .SaveBox = 0x054E0C,
    .SoftReset = 0x0150, // Reset
    .garbageDataLocation = 0x0770,

    .wRemoveMonFromBox = 0x01D10B,   // wPokemonWithdrawDepositParameter
    .wBoxCount = 0x01AD10,           // sBoxCount
    .wWhichPokemon = 0x01D109,       // wCurPartyMon
    .wBoxDataStart = 0x01AD10,       // sBox
    .wBoxDataEnd = 0x01B15E,         // sBoxEnd
    .wSerialEnemyDataBlock = 0xD26B, // wOTPartyData
    .wEnemyMonSpecies = 0x01D206,

    .wSerialEnemyMonsPatchList = 0xC6D0,                // wOTPatchLists
    .wSerialOtherGameboyRandomNumberListBlock = 0xD206, // wOTLinkBattleRNData
    .hSerialConnectionStatus = 0xFFCB,

    .transferStringLocation = 0xC544,
    .textBorderUppLeft = 0xC52F,
    .textBorderWidth = 12,
    .textBorderHeight = 1,
};

#endif