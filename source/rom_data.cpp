#include "rom_data.h"
#include "mystery_gift_builder.h"
#include "pokemon_party.h"
#include "pokemon_data.h"

rom_data::rom_data() {}
bool rom_data::load_rom()
{
    if (IGNORE_GAME_PAK)
    {
        gamecode = DEBUG_GAME;
        version = DEBUG_VERS;
        language = DEBUG_LANG;
    }
    else
    {
        gamecode = (*(vu8 *)(0x80000AC)) << 0x10 |
                   (*(vu8 *)(0x80000AD)) << 0x08 |
                   (*(vu8 *)(0x80000AE)) << 0x00;
        language = (*(vu8 *)(0x80000AF));
        version = (*(vu8 *)(0x80000BC));
    }

    // This section will need to be updated when more languages are added. It wil likely have to be a 3D array
    if (language != LANG_ENG)
    {
        return false;
    }

    switch (gamecode)
    {
    case (RUBY_ID):
    case (SAPPHIRE_ID):

        map_bank = 0; // Testing girl is 0-10-1, lanette is 20-2-1
        map_id = 10;
        npc_id = 1;

        def_map_bank = 8;
        def_map_id = 1;
        def_npc_id = 1;

        text_region = TEXT_HOENN;
        offset_wondercard = 0;
        offset_script = 0x0810;

        e4_flag = 0x800 + 0x04;
        mg_flag = 0x800 + 0x4C;

        switch (version)
        {
        case (VERS_1_0):
            loc_sendMonToPC = 0x0803D998;
            loc_gSpecialVar_0x8000 = 0x0202E8C4;
            loc_gSaveBlock1 = 0x02025734;
            loc_setPokedexFlag = 0x08090D90;
            offset_ramscript = 0x3690;
            offset_flags = 0x1220;
            return true;
        case (VERS_1_1):
            loc_sendMonToPC = 0x0803D998;
            loc_gSpecialVar_0x8000 = 0x0202E8C4;
            loc_gSaveBlock1 = 0x02025734;
            loc_setPokedexFlag = 0x08090DB0;
            offset_ramscript = 0x3690;
            offset_flags = 0x1220;
            return true;
        case (VERS_1_2):
            loc_sendMonToPC = 0x0803D998;
            loc_gSpecialVar_0x8000 = 0x0202E8C4;
            loc_gSaveBlock1 = 0x02025734;
            loc_setPokedexFlag = 0x08090DB0;
            offset_ramscript = 0x3690;
            offset_flags = 0x1220;
            return true;
        }
        break;
    case (FIRERED_ID):
    case (LEAFGREEN_ID):

        map_bank = 30;
        map_id = 0;
        npc_id = 1;

        def_map_bank = 0xFF;
        def_map_id = 0xFF;
        def_npc_id = 0xFF;

        text_region = TEXT_KANTO;
        offset_wondercard = 0x0460;
        offset_script = 0x079C;

        e4_flag = 0x800 + 0x2C;
        mg_flag = 0x800 + 0x39;

        switch (version)
        {
        case (VERS_1_0):
            loc_sendMonToPC = 0x08040B90;
            loc_gSpecialVar_0x8000 = 0x020370B8;
            loc_gSaveBlock1PTR = 0x03005008;
            loc_setPokedexFlag = 0x08088E74;
            offset_ramscript = 0x361C;
            offset_flags = 0x0EE0;
            return true;
        case (VERS_1_1):
            loc_sendMonToPC = 0x08040BA4;
            loc_gSpecialVar_0x8000 = 0x020370B8;
            loc_gSaveBlock1PTR = 0x03005008;
            loc_setPokedexFlag = 0x08088E5C;
            offset_ramscript = 0x361C;
            offset_flags = 0x0EE0;
            return true;
        }
        break;
    case (EMERALD_ID):

        map_bank = 20;
        map_id = 2;
        npc_id = 1;

        def_map_bank = 0xFF;
        def_map_id = 0xFF;
        def_npc_id = 0xFF;

        text_region = TEXT_HOENN;
        offset_wondercard = 0x056C;
        offset_script = 0x08A8;

        e4_flag = 0x860 + 0x04;
        mg_flag = 0x860 + 0x7B;

        loc_sendMonToPC = 0x0806B490;
        loc_gSpecialVar_0x8000 = 0x020375D8;
        loc_gSaveBlock1PTR = 0x03005D8C;
        loc_setPokedexFlag = 0x080C0664;
        offset_ramscript = 0x3728;
        offset_flags = 0x1270;
        return true;
    }
    return false;
}

bool rom_data::is_hoenn()
{
    return (gamecode == RUBY_ID || gamecode == SAPPHIRE_ID || gamecode == EMERALD_ID);
}

bool rom_data::is_ruby_sapphire()
{
    return (gamecode == RUBY_ID || gamecode == SAPPHIRE_ID);
}

void rom_data::print_rom_info()
{
    std::string out;
    switch (gamecode)
    {
    case (RUBY_ID):
        out += "R";
        break;
    case (SAPPHIRE_ID):
        out += "S";
        break;
    case (FIRERED_ID):
        out += "F";
        break;
    case (LEAFGREEN_ID):
        out += "L";
        break;
    case (EMERALD_ID):
        out += "E";
        break;
    }
    out += "-";
    out += std::to_string(version);
    out += "-";
    out += char(language);
    tte_set_pos(0, 8);
    tte_write(out.c_str());
}