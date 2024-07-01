#include "rom_data.h"
#include "mystery_gift_builder.h"
#include "pokemon_party.h"
#include "pokemon_data.h"
#include "gba_rom_values/eng_gba_rom_values.h"

extern rom_data curr_rom;

rom_data::rom_data() {}
bool rom_data::load_rom()
{
    const ROM_DATA *list_of_roms[NUM_ROMS] = {
        &ENG_RUBY_v0,
        &ENG_SAPPHIRE_v0,
        &ENG_RUBY_v1,
        &ENG_SAPPHIRE_v1,
        &ENG_RUBY_v2,
        &ENG_SAPPHIRE_v2,
        &ENG_FIRERED_v0,
        &ENG_LEAFGREEN_v0,
        &ENG_FIRERED_v1,
        &ENG_LEAFGREEN_v1,
        &ENG_EMERALD_v0,
    };

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

    for (int i = 0; i < NUM_ROMS; i++)
    {
        if (gamecode == list_of_roms[i]->gamecode &&
            language == list_of_roms[i]->language &&
            version == list_of_roms[i]->version)
        {
            fill_values(list_of_roms[i]);
            rom_loaded = true;
            return true;
        }
    }
    return false;
}

void rom_data::fill_values(const ROM_DATA *rom_values)
{
    loc_sendMonToPC = rom_values->loc_copyMonToPC;
    loc_gSpecialVar_0x8000 = rom_values->loc_gSpecialVar_0x8000;
    loc_gSaveBlock1 = rom_values->loc_gSaveBlock1;
    loc_setPokedexFlag = rom_values->loc_getSetPokedexFlag;
    loc_gSaveDataBuffer = rom_values->loc_gSaveDataBuffer;
    loc_readFlashSector = rom_values->loc_readFlashSector;
    loc_loadSaveSection30 = rom_values->loc_loadSaveSection30;
    loc_m4aMPlayStop = rom_values->loc_m4aMPlayStop;
    loc_gMPlayInfo_BGM = rom_values->loc_gMPlayInfo_BGM;
    loc_gMPlayInfo_SE2 = rom_values->loc_gMPlayInfo_SE2;
    loc_MPlayStart = rom_values->loc_MPlayStart;
    loc_CreateFanfareTask = rom_values->loc_CreateFanfareTask;
    loc_sFanfareCounter = rom_values->loc_sFanfareCounter;
    loc_gPlttBufferFaded = rom_values->loc_gPlttBufferFaded;
    loc_gSprites = rom_values->loc_gSprites;
    loc_voicegroup = rom_values->loc_voicegroup;
    loc_sPicTable_NPC = rom_values->loc_sPicTable_NPC;

    offset_ramscript = rom_values->offset_ramscript;
    offset_flags = rom_values->offset_flags;
    offset_wondercard = rom_values->offset_wondercard;
    offset_script = rom_values->offset_script;
    text_region = rom_values->text_region;
    special_DrawWholeMapView = rom_values->special_DrawWholeMapView;

    e4_flag = rom_values->e4_flag;                                 // The flag that is set when you become champion. Often listed as "GAME_CLEAR"
    mg_flag = rom_values->mg_flag;                                 // The flag that is set when you enable Mystery Gift. Known as "EXDATA_ENABLE" in RS
    unused_flag_start = rom_values->unused_flag_start;             // The start of the unused flags and must have 31 open flags in a row
    all_collected_flag = rom_values->unused_flag_start;            // The flag for if everything has been collected
    pkmn_collected_flag_start = rom_values->unused_flag_start + 1; // The beginning of the flags for each of the Pokemon

    map_bank = (ENABLE_OLD_EVENT ? rom_values->old_map_bank : rom_values->map_bank);
    map_id = (ENABLE_OLD_EVENT ? rom_values->old_map_id : rom_values->map_id);
    npc_id = (ENABLE_OLD_EVENT ? rom_values->old_npc_id : rom_values->npc_id);
    npc_palette = rom_values->npc_palette;

    def_map_bank = rom_values->def_map_bank;
    def_map_id = rom_values->def_map_id;
    def_npc_id = rom_values->def_npc_id;

    loc_gSaveBlock1PTR = rom_values->loc_gSaveBlock1PTR; // TODO: Only used for old script, can be removed later

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

bool rom_data::verify_rom()
{
    return !rom_loaded ||
           IGNORE_GAME_PAK ||
           ((gamecode == ((*(vu8 *)(0x80000AC)) << 0x10 | (*(vu8 *)(0x80000AD)) << 0x08 | (*(vu8 *)(0x80000AE)) << 0x00)) &&
            (language == (*(vu8 *)(0x80000AF))) &&
            (version == (*(vu8 *)(0x80000BC))));
}