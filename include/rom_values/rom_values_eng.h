#ifndef ROM_VALUES_ENG_H
#define ROM_VALUES_ENG_H

#include "rom_values/base_rom_struct.h"

const struct ROM_DATA ENG_RUBY_v0 = {
    .is_valid = true,

    .gamecode = RUBY_ID,
    .version = VERS_1_0,
    .language = LANG_ENG,

    .loc_copyMonToPC = 0x0803D998, // Known as "SendMonToPC"
    .loc_gSpecialVar_0x8000 = 0x0202E8C4,
    .loc_gSaveBlock1 = 0x02025734,
    .loc_getSetPokedexFlag = 0x08090D90,
    .loc_gSaveDataBuffer = 0x02000000, // Known as "gSharedMem" in RS
    .loc_readFlashSector = 0x08125BF8, // Known as "DoReadFlashWholeSection" in RS

    // The following should be consistant across languages and revisions.
    .offset_ramscript = 0x3690, // Ramscript offset as found within the SaveBlock1 struct in global.h
    .offset_flags = 0x1220,     // Flag offset as found within the SaveBlock1 struct in global.h
    .offset_script = 0x0810,
    .text_region = TEXT_HOENN,

    // PKHeX's list of flags is useful for making sure the detection is accurate: https://github.com/kwsch/PKHeX/blob/78a557c3cdaa6f48b42cc96df8ccb4d20b897937/PKHeX.Core/Resources/text/other/flags_rs.txt
    .e4_flag = 0x800 + 0x04,   // The flag that is set when you become champion. Often listed as "GAME_CLEAR"
    .mg_flag = 0x800 + 0x4C,   // The flag that is set when you enable Mystery Gift. Known as "EXDATA_ENABLE" in RS
    .unused_flag_start = 0x21, // The start of the unused flags and must have 31 open flags in a row

    .map_bank = 20,
    .map_id = 2,
    .npc_id = 1,

    .def_map_bank = 8,
    .def_map_id = 1,
    .def_npc_id = 1,

    .test_map_bank = 2,
    .test_map_id = 2,
    .test_npc_id = 3,
};
const struct ROM_DATA ENG_SAPPHIRE_v0 = {
    .is_valid = true,

    .gamecode = SAPPHIRE_ID,
    .version = VERS_1_0,
    .language = LANG_ENG,

    .loc_copyMonToPC = 0x0803D998, // Known as "SendMonToPC"
    .loc_gSpecialVar_0x8000 = 0x0202E8C4,
    .loc_gSaveBlock1 = 0x02025734,
    .loc_getSetPokedexFlag = 0x08090D90,
    .loc_gSaveDataBuffer = 0x02000000, // Known as "gSharedMem" in RS
    .loc_readFlashSector = 0x08125BF8, // Known as "DoReadFlashWholeSection" in RS

    // The following should be consistant across languages and revisions.
    .offset_ramscript = 0x3690, // Ramscript offset as found within the SaveBlock1 struct in global.h
    .offset_flags = 0x1220,     // Flag offset as found within the SaveBlock1 struct in global.h
    .offset_script = 0x0810,
    .text_region = TEXT_HOENN,

    // PKHeX's list of flags is useful for making sure the detection is accurate: https://github.com/kwsch/PKHeX/blob/78a557c3cdaa6f48b42cc96df8ccb4d20b897937/PKHeX.Core/Resources/text/other/flags_rs.txt
    .e4_flag = 0x800 + 0x04,   // The flag that is set when you become champion. Often listed as "GAME_CLEAR"
    .mg_flag = 0x800 + 0x4C,   // The flag that is set when you enable Mystery Gift. Known as "EXDATA_ENABLE" in RS
    .unused_flag_start = 0x21, // The start of the unused flags and must have 31 open flags in a row

    .map_bank = 20,
    .map_id = 2,
    .npc_id = 1,

    .def_map_bank = 8,
    .def_map_id = 1,
    .def_npc_id = 1,

    .test_map_bank = 2,
    .test_map_id = 2,
    .test_npc_id = 3,
};
const struct ROM_DATA ENG_RUBY_v1 = {
    .is_valid = true,

    .gamecode = RUBY_ID,
    .version = VERS_1_1,
    .language = LANG_ENG,

    .loc_copyMonToPC = 0x0803D998, // Known as "SendMonToPC"
    .loc_gSpecialVar_0x8000 = 0x0202E8C4,
    .loc_gSaveBlock1 = 0x02025734,
    .loc_getSetPokedexFlag = 0x08090D90,
    .loc_gSaveDataBuffer = 0x02000000, // Known as "gSharedMem" in RS
    .loc_readFlashSector = 0x08125BF8, // Known as "DoReadFlashWholeSection" in RS

    // The following should be consistant across languages and revisions.
    .offset_ramscript = 0x3690, // Ramscript offset as found within the SaveBlock1 struct in global.h
    .offset_flags = 0x1220,     // Flag offset as found within the SaveBlock1 struct in global.h
    .offset_script = 0x0810,
    .text_region = TEXT_HOENN,

    // PKHeX's list of flags is useful for making sure the detection is accurate: https://github.com/kwsch/PKHeX/blob/78a557c3cdaa6f48b42cc96df8ccb4d20b897937/PKHeX.Core/Resources/text/other/flags_rs.txt
    .e4_flag = 0x800 + 0x04,   // The flag that is set when you become champion. Often listed as "GAME_CLEAR"
    .mg_flag = 0x800 + 0x4C,   // The flag that is set when you enable Mystery Gift. Known as "EXDATA_ENABLE" in RS
    .unused_flag_start = 0x21, // The start of the unused flags and must have 31 open flags in a row

    .map_bank = 20,
    .map_id = 2,
    .npc_id = 1,

    .def_map_bank = 8,
    .def_map_id = 1,
    .def_npc_id = 1,

    .test_map_bank = 2,
    .test_map_id = 2,
    .test_npc_id = 3,
};
const struct ROM_DATA ENG_SAPPHIRE_v1 = {0};
const struct ROM_DATA ENG_RUBY_v2 = {0};
const struct ROM_DATA ENG_SAPPHIRE_v2 = {0};
const struct ROM_DATA ENG_FIRERED_v0 = {
    .is_valid = true,

    .gamecode = FIRERED_ID,
    .version = VERS_1_0,
    .language = LANG_ENG,

    .loc_copyMonToPC = 0x08040B90, // Known as "SendMonToPC"
    .loc_gSpecialVar_0x8000 = 0x020370B8,
    .loc_gSaveBlock1PTR = 0x03005008,
    .loc_getSetPokedexFlag = 0x08088E8C,
    .loc_gSaveDataBuffer = 0x02039A38, // The location of the saveDataBuffer
    .loc_readFlashSector = 0x080DA190,

    // The following should be consistant across languages and revisions.
    .offset_ramscript = 0x361C, // Ramscript offset as found within the SaveBlock1 struct in global.h
    .offset_flags = 0x0EE0,     // Flag offset as found within the SaveBlock1 struct in global.h
    .offset_wondercard = 0x0460,
    .offset_script = 0x079C,
    .text_region = TEXT_KANTO,

    // PKHeX's list of flags is useful for making sure the detection is accurate: https://github.com/kwsch/PKHeX/blob/78a557c3cdaa6f48b42cc96df8ccb4d20b897937/PKHeX.Core/Resources/text/other/flags_rs.txt
    .e4_flag = 0x860 + 0x04,   // The flag that is set when you become champion. Often listed as "GAME_CLEAR"
    .mg_flag = 0x860 + 0x7B,   // The flag that is set when you enable Mystery Gift. Known as "EXDATA_ENABLE" in RS
    .unused_flag_start = 0x20, // The start of the unused flags and must have 31 open flags in a row

    .map_bank = 30,
    .map_id = 0,
    .npc_id = 1,

    .def_map_bank = 0xFF,
    .def_map_id = 0xFF,
    .def_npc_id = 0xFF,

    .test_map_bank = 7,
    .test_map_id = 3,
    .test_npc_id = 2,
};
const struct ROM_DATA ENG_LEAFGREEN_v0 = {
    .is_valid = true,

    .gamecode = LEAFGREEN_ID,
    .version = VERS_1_0,
    .language = LANG_ENG,

    .loc_copyMonToPC = 0x08040B90,
    .loc_gSpecialVar_0x8000 = 0x020370B8,
    .loc_gSaveBlock1PTR = 0x03005008,
    .loc_getSetPokedexFlag = 0x08088E48,
    .loc_gSaveDataBuffer = 0x02039A38, // The location of the saveDataBuffer
    .loc_readFlashSector = 0x080DA164,

    // The following should be consistant across languages and revisions.
    .offset_ramscript = 0x361C, // Ramscript offset as found within the SaveBlock1 struct in global.h
    .offset_flags = 0x0EE0,     // Flag offset as found within the SaveBlock1 struct in global.h
    .offset_wondercard = 0x0460,
    .offset_script = 0x079C,
    .text_region = TEXT_KANTO,

    // PKHeX's list of flags is useful for making sure the detection is accurate: https://github.com/kwsch/PKHeX/blob/78a557c3cdaa6f48b42cc96df8ccb4d20b897937/PKHeX.Core/Resources/text/other/flags_rs.txt
    .e4_flag = 0x860 + 0x04,   // The flag that is set when you become champion. Often listed as "GAME_CLEAR"
    .mg_flag = 0x860 + 0x7B,   // The flag that is set when you enable Mystery Gift. Known as "EXDATA_ENABLE" in RS
    .unused_flag_start = 0x20, // The start of the unused flags and must have 31 open flags in a row

    .map_bank = 30,
    .map_id = 0,
    .npc_id = 1,

    .def_map_bank = 0xFF,
    .def_map_id = 0xFF,
    .def_npc_id = 0xFF,

    .test_map_bank = 7,
    .test_map_id = 3,
    .test_npc_id = 2,
};
const struct ROM_DATA ENG_FIRERED_v1 = {
    .is_valid = true,

    .gamecode = FIRERED_ID,
    .version = VERS_1_1,
    .language = LANG_ENG,

    .loc_copyMonToPC = 0x08040BA4,
    .loc_gSpecialVar_0x8000 = 0x020370B8,
    .loc_gSaveBlock1PTR = 0x03005008,
    .loc_getSetPokedexFlag = 0x08088E88,
    .loc_gSaveDataBuffer = 0x02039A38, // The location of the saveDataBuffer
    .loc_readFlashSector = 0x080DA1A4,

    // The following should be consistant across languages and revisions.
    .offset_ramscript = 0x361C, // Ramscript offset as found within the SaveBlock1 struct in global.h
    .offset_flags = 0x0EE0,     // Flag offset as found within the SaveBlock1 struct in global.h
    .offset_wondercard = 0x0460,
    .offset_script = 0x079C,
    .text_region = TEXT_KANTO,

    // PKHeX's list of flags is useful for making sure the detection is accurate: https://github.com/kwsch/PKHeX/blob/78a557c3cdaa6f48b42cc96df8ccb4d20b897937/PKHeX.Core/Resources/text/other/flags_rs.txt
    .e4_flag = 0x860 + 0x04,   // The flag that is set when you become champion. Often listed as "GAME_CLEAR"
    .mg_flag = 0x860 + 0x7B,   // The flag that is set when you enable Mystery Gift. Known as "EXDATA_ENABLE" in RS
    .unused_flag_start = 0x20, // The start of the unused flags and must have 31 open flags in a row

    .map_bank = 30,
    .map_id = 0,
    .npc_id = 1,

    .def_map_bank = 0xFF,
    .def_map_id = 0xFF,
    .def_npc_id = 0xFF,

    .test_map_bank = 7,
    .test_map_id = 3,
    .test_npc_id = 2,
};
const struct ROM_DATA ENG_LEAFGREEN_v1 = {
    .is_valid = true,

    .gamecode = LEAFGREEN_ID,
    .version = VERS_1_1,
    .language = LANG_ENG,

    .loc_copyMonToPC = 0x08040BA4,
    .loc_gSpecialVar_0x8000 = 0x020370B8,
    .loc_gSaveBlock1PTR = 0x03005008,
    .loc_getSetPokedexFlag = 0x08088E74,
    .loc_gSaveDataBuffer = 0x02039A38, // The location of the saveDataBuffer
    .loc_readFlashSector = 0x080DA178,

    // The following should be consistant across languages and revisions.
    .offset_ramscript = 0x361C, // Ramscript offset as found within the SaveBlock1 struct in global.h
    .offset_flags = 0x0EE0,     // Flag offset as found within the SaveBlock1 struct in global.h
    .offset_wondercard = 0x0460,
    .offset_script = 0x079C,
    .text_region = TEXT_KANTO,

    // PKHeX's list of flags is useful for making sure the detection is accurate: https://github.com/kwsch/PKHeX/blob/78a557c3cdaa6f48b42cc96df8ccb4d20b897937/PKHeX.Core/Resources/text/other/flags_rs.txt
    .e4_flag = 0x860 + 0x04,   // The flag that is set when you become champion. Often listed as "GAME_CLEAR"
    .mg_flag = 0x860 + 0x7B,   // The flag that is set when you enable Mystery Gift. Known as "EXDATA_ENABLE" in RS
    .unused_flag_start = 0x20, // The start of the unused flags and must have 31 open flags in a row

    .map_bank = 30,
    .map_id = 0,
    .npc_id = 1,

    .def_map_bank = 0xFF,
    .def_map_id = 0xFF,
    .def_npc_id = 0xFF,

    .test_map_bank = 7,
    .test_map_id = 3,
    .test_npc_id = 2,
};
const struct ROM_DATA ENG_EMERALD_v0 = {
    .is_valid = true,

    .gamecode = EMERALD_ID,
    .version = VERS_1_0,
    .language = LANG_ENG,

    .loc_copyMonToPC = 0x0806B490,
    .loc_gSpecialVar_0x8000 = 0x020375D8,
    .loc_gSaveBlock1PTR = 0x03005D8C,
    .loc_getSetPokedexFlag = 0x080C0664,
    .loc_gSaveDataBuffer = 0x0203ABBC, // The location of the saveDataBuffer
    .loc_readFlashSector = 0x0815314C,

    // The following should be consistant across languages and revisions.
    .offset_ramscript = 0x3728, // Ramscript offset as found within the SaveBlock1 struct in global.h
    .offset_flags = 0x1270,     // Flag offset as found within the SaveBlock1 struct in global.h
    .offset_wondercard = 0x056C,
    .offset_script = 0x08A8,
    .text_region = TEXT_HOENN,

    // PKHeX's list of flags is useful for making sure the detection is accurate: https://github.com/kwsch/PKHeX/blob/78a557c3cdaa6f48b42cc96df8ccb4d20b897937/PKHeX.Core/Resources/text/other/flags_rs.txt
    .e4_flag = 0x860 + 0x04,   // The flag that is set when you become champion. Often listed as "GAME_CLEAR"
    .mg_flag = 0x860 + 0x7B,   // The flag that is set when you enable Mystery Gift. Known as "EXDATA_ENABLE" in RS
    .unused_flag_start = 0x20, // The start of the unused flags and must have 31 open flags in a row

    .map_bank = 20,
    .map_id = 2,
    .npc_id = 1,

    .def_map_bank = 0xFF,
    .def_map_id = 0xFF,
    .def_npc_id = 0xFF,

    .test_map_bank = 5,
    .test_map_id = 4,
    .test_npc_id = 2,
};

#endif