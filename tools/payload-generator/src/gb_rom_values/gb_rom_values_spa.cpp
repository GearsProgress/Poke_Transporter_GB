#include "gb_rom_values/gb_rom_values.h"

const struct GB_ROM gb_rom_values_spa[] = {
    {// SPA_RED
        .language = SPA_ID,
        .version = RED_ID,
        .generation = 1,
        .method = METHOD_NEWLINE,
        .payload_size = 637,
        .box_data_size = 0x462,

        .print_string_start = 0xC456,
        .stack_overwrite_location = 0xDFDD,
        .short_pkmn_name = 0xE3,
        .pointer_pkmn_name = 0xFC,
        .padding_1 = 0,

        .clearScreen = 0x00190F,
        .CableClub_TextBoxBorder = 0x005B00,
        .placeString = 0x001955,
        .Serial_ExchangeBytes = 0x00216E,
        ._RemovePokemon = 0x007BBB,
        .SaveSAVtoSRAM1 = 0x1C77D0,
        .SaveSAVtoSRAM2 = 0x1C77FD,
        .OpenSRAM = 0,
        .SaveBox = 0,
        .Bankswitch = 0x0035F5,
        .SoftReset = 0x001F48,
        .CloseSRAM = 0,
        .garbageDataLocation = 0x00217F,

        .wRemoveMonFromBox = 0xCF9A,
        .wBoxCount = 0xDA85,
        .wWhichPokemon = 0x00CF97,
        .wBoxDataStart = 0xDA85,
        .wBoxDataEnd = 0xDEE7,
        .wSerialEnemyDataBlock = 0xD898,
        .wEnemyMonSpecies = 0xCFEA,

        .wSerialEnemyMonsPatchList = 0xC5D0,
        .wSerialOtherGameboyRandomNumberListBlock = 0xCD81,
        .hSerialConnectionStatus = 0xFFAA,

        .transferStringLocation = 0xC444,
        .textBorderUppLeft = 0xC42F,
        .textBorderWidth = 12,
        .textBorderHeight = 1,
        .padding_2 = 0},
    {// SPA_BLUE
        .language = SPA_ID,
        .version = BLUE_ID,
        .generation = 1,
        .method = METHOD_NEWLINE,
        .payload_size = 637,
        .box_data_size = 0x462,

        .print_string_start = 0xC456,
        .stack_overwrite_location = 0xDFDD,
        .short_pkmn_name = 0xE3,
        .pointer_pkmn_name = 0xFC,
        .padding_1 = 0,

        .clearScreen = 0x00190F,
        .CableClub_TextBoxBorder = 0x005B00,
        .placeString = 0x001955,
        .Serial_ExchangeBytes = 0x00216E,
        ._RemovePokemon = 0x007BBB,
        .SaveSAVtoSRAM1 = 0x1C77D0,
        .SaveSAVtoSRAM2 = 0x1C77FD,
        .OpenSRAM = 0,
        .SaveBox = 0,
        .Bankswitch = 0x0035F5,
        .SoftReset = 0x001F48,
        .CloseSRAM = 0,
        .garbageDataLocation = 0x00217F,

        .wRemoveMonFromBox = 0xCF9A,
        .wBoxCount = 0xDA85,
        .wWhichPokemon = 0x00CF97,
        .wBoxDataStart = 0xDA85,
        .wBoxDataEnd = 0xDEE7,
        .wSerialEnemyDataBlock = 0xD898,
        .wEnemyMonSpecies = 0xCFEA,

        .wSerialEnemyMonsPatchList = 0xC5D0,
        .wSerialOtherGameboyRandomNumberListBlock = 0xCD81,
        .hSerialConnectionStatus = 0xFFAA,

        .transferStringLocation = 0xC444,
        .textBorderUppLeft = 0xC42F,
        .textBorderWidth = 12,
        .textBorderHeight = 1,
        .padding_2 = 0},
    {// SPA_YELLOW
        .language = SPA_ID,
        .version = YELLOW_ID,
        .generation = 1,
        .method = METHOD_MEW,
        .payload_size = 637,
        .box_data_size = 0x462,

        .print_string_start = 0xC456,
        .stack_overwrite_location = 0xDFDD,
        .short_pkmn_name = 0x15,
        .pointer_pkmn_name = 0xE3,
        .padding_1 = 0,

        .clearScreen = 0x0016DD,
        .CableClub_TextBoxBorder =
            0x0016F0, // TextBoxBoarder, since the Cable Club isn't loaded
        .placeString = 0x1723,
        .Serial_ExchangeBytes = 0x001FCA,
        ._RemovePokemon = 0x017A43,
        .SaveSAVtoSRAM1 = 0x1C7B22,
        .SaveSAVtoSRAM2 = 0x1C7B46,
        .LoadCurrentBoxData = 0x1C79EC,
        .OpenSRAM = 0x003E9E,
        .SaveBox = 0,
        .Bankswitch = 0x003E89, // BankswitchCommon
        .SoftReset = 0x001D04,
        .CloseSRAM = 0x003EAE,
        .garbageDataLocation = 0x0161,

        .wRemoveMonFromBox = 0xCF99,
        .wBoxCount = 0xDA84,
        .wWhichPokemon = 0xCF96,
        .wBoxDataStart = 0xDA84,
        .wBoxDataEnd = 0xDEE6,
        .wSerialEnemyDataBlock = 0x00D897,
        .wEnemyMonSpecies = 0xCFE9,

        .wSerialEnemyMonsPatchList = 0xC5D0,
        .wSerialOtherGameboyRandomNumberListBlock = 0xCD81,
        .hSerialConnectionStatus = 0xFFAA,

        .transferStringLocation = 0xC444,
        .textBorderUppLeft = 0xC42F,
        .textBorderWidth = 12,
        .textBorderHeight = 1,
        .padding_2 = 0},
    {// SPA_GOLD
        .language = SPA_ID,
        .version = GOLD_ID,
        .generation = 2,
        .method = METHOD_GEN2,
        .payload_size = 672,
        .box_data_size = 0x44E,

        .print_string_start = 0xC442,
        .stack_overwrite_location =
            0xDFCB, // Found by seeing where 772C is stored in the stack, 772C
                    // is the code that calls PlaceString
        .short_pkmn_name = 0x4E,
        .pointer_pkmn_name = 0,
        .padding_1 = 0,

        .clearScreen = 0x000EE2,
        .CableClub_TextBoxBorder = 0x0A4DF2, // LinkTextboxAtHL
        .placeString = 0x000F74,
        .Serial_ExchangeBytes = 0x0710,
        ._RemovePokemon = 0x036040, // RemoveMonFromPartyOrBox
        .SaveSAVtoSRAM1 = 0,
        .SaveSAVtoSRAM2 = 0,
        .OpenSRAM = 0x003105,
        .SaveBox = 0x054E05,
        .Bankswitch = 0,
        .SoftReset = 0x05B0,
        .CloseSRAM = 0,
        .garbageDataLocation = 0x0654,

        .wRemoveMonFromBox = 0x01D008,   // wPokemonWithdrawDepositParameter
        .wBoxCount = 0x01AD6C,           // sBoxCount
        .wWhichPokemon = 0x01D005,       // wCurPartyMon
        .wBoxDataStart = 0xAD6C,         // sBoxStart
        .wBoxDataEnd = 0xB1BA,           // sBoxEnd
        .wSerialEnemyDataBlock = 0xDD40, // wOTPartyData
        .wEnemyMonSpecies = 0x01D0EF,

        .wSerialEnemyMonsPatchList = 0xC5D0, // wOTPatchLists
        .wSerialOtherGameboyRandomNumberListBlock =
            0xD0EF, // wOTLinkBattleRNData
        .hSerialConnectionStatus = 0xFFCD,

        .transferStringLocation = 0xC444,
        .textBorderUppLeft = 0xC42F,
        .textBorderWidth = 12,
        .textBorderHeight = 1,
        .padding_2 = 0},
    {// SPA_SILVER
        .language = SPA_ID,
        .version = SILVER_ID,
        .generation = 2,
        .method = METHOD_GEN2,
        .payload_size = 672,
        .box_data_size = 0x44E,

        .print_string_start = 0xC442,
        .stack_overwrite_location =
            0xDFCB, // Found by seeing where 772C is stored in the stack, 772C
                    // is the code that calls PlaceString
        .short_pkmn_name = 0x4E,
        .pointer_pkmn_name = 0,
        .padding_1 = 0,

        .clearScreen = 0x000EE2,
        .CableClub_TextBoxBorder = 0x0A4DF2, // LinkTextboxAtHL
        .placeString = 0x000F74,
        .Serial_ExchangeBytes = 0x0710,
        ._RemovePokemon = 0x03603E, // RemoveMonFromPartyOrBox
        .SaveSAVtoSRAM1 = 0,
        .SaveSAVtoSRAM2 = 0,
        .OpenSRAM = 0x003105,
        .SaveBox = 0x054E05,
        .Bankswitch = 0,
        .SoftReset = 0x05B0,
        .CloseSRAM = 0,
        .garbageDataLocation = 0x0654,

        .wRemoveMonFromBox = 0x01D008,   // wPokemonWithdrawDepositParameter
        .wBoxCount = 0x01AD6C,           // sBoxCount
        .wWhichPokemon = 0x01D005,       // wCurPartyMon
        .wBoxDataStart = 0xAD6C,         // sBoxStart
        .wBoxDataEnd = 0xB1BA,           // sBoxEnd
        .wSerialEnemyDataBlock = 0xDD40, // wOTPartyData
        .wEnemyMonSpecies = 0x01D0EF,

        .wSerialEnemyMonsPatchList = 0xC5D0, // wOTPatchLists
        .wSerialOtherGameboyRandomNumberListBlock =
            0xD0EF, // wOTLinkBattleRNData
        .hSerialConnectionStatus = 0xFFCD,

        .transferStringLocation = 0xC444,
        .textBorderUppLeft = 0xC42F,
        .textBorderWidth = 12,
        .textBorderHeight = 1,
        .padding_2 = 0},
    {// SPA_CRYSTAL
        .language = SPA_ID,
        .version = CRYSTAL_ID,
        .generation = 2,
        .method = METHOD_GEN2,
        .payload_size = 672,
        .box_data_size = 0x44E,

        .print_string_start = 0xC544,
        .stack_overwrite_location =
            0xE0BB, // Found by seeing where 7622 is stored in the stack, 7622
                    // is the code that calls PlaceString
                    // (PlaceTradePartnerNamesAndParty)
        .short_pkmn_name = 0x4E,
        .pointer_pkmn_name = 0,
        .padding_1 = 0,

        .clearScreen = 0x000FDB,
        .CableClub_TextBoxBorder = 0x0A4EF6, // LinkTextboxAtHL
        .placeString = 0x00106E,
        .Serial_ExchangeBytes = 0x075F,
        ._RemovePokemon = 0x036009, // RemoveMonFromPartyOrBox
        .SaveSAVtoSRAM1 = 0,
        .SaveSAVtoSRAM2 = 0,
        .OpenSRAM = 0x002FB5,
        .SaveBox = 0x054E0C,
        .Bankswitch = 0,
        .SoftReset = 0x0150, // Reset
        .CloseSRAM = 0,
        .garbageDataLocation = 0x0770,

        .wRemoveMonFromBox = 0x01D10B,   // wPokemonWithdrawDepositParameter
        .wBoxCount = 0x01AD10,           // sBoxCount
        .wWhichPokemon = 0x01D109,       // wCurPartyMon
        .wBoxDataStart = 0x01AD10,       // sBox
        .wBoxDataEnd = 0x01B15E,         // sBoxEnd
        .wSerialEnemyDataBlock = 0xD26B, // wOTPartyData
        .wEnemyMonSpecies = 0x01D206,

        .wSerialEnemyMonsPatchList = 0xC6D0, // wOTPatchLists
        .wSerialOtherGameboyRandomNumberListBlock =
            0xD206, // wOTLinkBattleRNData
        .hSerialConnectionStatus = 0xFFCB,

        .transferStringLocation = 0xC544,
        .textBorderUppLeft = 0xC52F,
        .textBorderWidth = 12,
        .textBorderHeight = 1,
        .padding_2 = 0}};

const u16 gb_rom_values_spa_size =
    static_cast<u16>(sizeof(gb_rom_values_spa) / sizeof(struct GB_ROM));
