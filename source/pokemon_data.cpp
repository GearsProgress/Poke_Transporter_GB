#include "pokemon_data.h"
#include "zx0_decompressor.h"
#include "EXP_GROUPS_zx0_bin.h"
#include "GENDER_RATIO_zx0_bin.h"
#include "NUM_ABILITIES_zx0_bin.h"
#include "FIRST_MOVES_zx0_bin.h"
#include "EVOLUTIONS_zx0_bin.h"
#include "POWER_POINTS_zx0_bin.h"
#include "gen_1_index_array_zx0_bin.h"
#include "EVENT_PKMN_zx0_bin.h"
#include "TYPES_zx0_bin.h"
#include "MOVESETS_zx0_bin.h"
#include "gen_1_Jpn_char_array_zx0_bin.h"
#include "gen_1_Eng_char_array_zx0_bin.h"
#include "gen_1_FreGer_char_array_zx0_bin.h"
#include "gen_1_ItaSpa_char_array_zx0_bin.h"
#include "gen_2_Jpn_char_array_zx0_bin.h"
#include "gen_2_Eng_char_array_zx0_bin.h"
#include "gen_2_FreGer_char_array_zx0_bin.h"
#include "gen_2_ItaSpa_char_array_zx0_bin.h"
#include "gen_3_Jpn_char_array_zx0_bin.h"
#include "gen_3_Intern_char_array_zx0_bin.h"
#include <tonc.h>

// Indexes found here: https://bulbapedia.bulbagarden.net/wiki/Experience#In_the_core_series
const u32 EXP_MAXIMUMS[6] = {
    med_fast_max,
    erratic_max,
    flux_max,
    med_slow_max,
    fast_max,
    slow_max};

const int GENDER_THRESHOLDS[2][8]{
    {-1, 2, 4, 8, 12, 14, -1, -1},
    {-1, 31, 63, 127, 191, 225, -1, -1}};

static void load_table(u8 *table, const u8* source, bool &loadedBool)
{
    if(loadedBool)
    {
        return;
    }
    zx0_decompressor_start(table, source);
    zx0_decompressor_read(zx0_decompressor_get_decompressed_size());
    loadedBool = true;
}

PokemonTables::PokemonTables()
    : exp_groups_loaded(false)
    , gender_ratios_loaded(false)
    , num_abilities_loaded(false)
    , power_points_loaded(false)
    , gen_1_index_array_loaded(false)
    , event_pkmn_loaded(false)
    , types_loaded(false)
    , input_charset_type(0)
    , gen3_charset_type(0)
    , movesets_loaded(false)
{
}

void PokemonTables::load_exp_groups()
{
    load_table(EXP_GROUPS, EXP_GROUPS_zx0_bin, exp_groups_loaded);
}

void PokemonTables::load_gender_ratios()
{
    load_table(GENDER_RATIO, GENDER_RATIO_zx0_bin, gender_ratios_loaded);
}

void PokemonTables::load_num_abilities()
{
    load_table((uint8_t*)NUM_ABILITIES, NUM_ABILITIES_zx0_bin, num_abilities_loaded);
}

void PokemonTables::load_first_moves()
{
    load_table(FIRST_MOVES, FIRST_MOVES_zx0_bin, first_moves_loaded);
}

void PokemonTables::load_evolutions()
{
    load_table(EVOLUTIONS, EVOLUTIONS_zx0_bin, evolutions_loaded);
}

void PokemonTables::load_power_points()
{
    load_table(POWER_POINTS, POWER_POINTS_zx0_bin, power_points_loaded);
}

void PokemonTables::load_gen1_index_array()
{
    load_table(gen_1_index_array, gen_1_index_array_zx0_bin, gen_1_index_array_loaded);
}

void PokemonTables::load_event_pkmn()
{
    load_table((uint8_t*)EVENT_PKMN, EVENT_PKMN_zx0_bin, event_pkmn_loaded);
}

void PokemonTables::load_types()
{
    load_table((uint8_t*)TYPES, TYPES_zx0_bin, types_loaded);
}

void PokemonTables::load_input_charset(byte gen, byte lang)
{
    const u8 desired_charset = (gen << 4) | (lang);
    if(input_charset_type == desired_charset)
    {
        return;
    }
    load_localized_charset(input_charset, gen, lang);
    input_charset_type = desired_charset;
}

void PokemonTables::load_gen3_charset(byte lang)
{
    // transform lang into the value that would get stored in gen3_charset_index
    if(lang == KOR_ID)
    {
        lang = JPN_ID;
    }
    else if(lang != JPN_ID)
    {
        lang = ENG_ID;
    }

    if(gen3_charset_type == lang)
    {
        return;
    }

    load_localized_charset(gen3_charset, 3, lang);
    gen3_charset_type = lang;
}

void PokemonTables::load_movesets()
{
    load_table((uint8_t*)MOVESETS, MOVESETS_zx0_bin, movesets_loaded);
}

u32 PokemonTables::get_max_exp(int index_num)
{
    load_exp_groups();
    int exp_group = EXP_GROUPS[index_num];
    u32 exp_max = EXP_MAXIMUMS[exp_group];
    u32 test = exp_max;
    return test;
}

u8 PokemonTables::get_gender_threshold(int index_num, bool is_gen_3)
{
    load_gender_ratios();
    return GENDER_THRESHOLDS[is_gen_3][GENDER_RATIO[index_num]];
}

// If the Pokemon has two abilities it returns a 1, since ability 1 is valid. Otherwise it returns 0
bool PokemonTables::get_num_abilities(int index_num)
{
    load_num_abilities();
    return NUM_ABILITIES[index_num];
}

bool PokemonTables::can_learn_move(int pkmn_index, int move_index)
{
    load_movesets();
    load_evolutions();
    byte data_byte = MOVESETS[pkmn_index][move_index / 8];
    data_byte |= MOVESETS[EVOLUTIONS[pkmn_index]][move_index / 8];             // add in the previous evolution's moves (if they exist)
    data_byte |= MOVESETS[EVOLUTIONS[EVOLUTIONS[pkmn_index]]][move_index / 8]; // add in the first evolution's moves (if they exist)
    return (data_byte >> (7 - (move_index % 8))) & 0x1;
}

byte PokemonTables::get_earliest_move(int index_num)
{
    load_first_moves();
    return FIRST_MOVES[index_num];
}

byte PokemonTables::get_gen_3_char(u16 input_char)
{
    return get_char_from_charset(gen3_charset, input_char);
}

static const u8 *localization_charset_files[]
{
    gen_1_Jpn_char_array_zx0_bin,
    gen_1_Eng_char_array_zx0_bin,
    gen_1_FreGer_char_array_zx0_bin,
    gen_1_FreGer_char_array_zx0_bin,
    gen_1_ItaSpa_char_array_zx0_bin,
    gen_1_ItaSpa_char_array_zx0_bin,
    0,
    gen_2_Jpn_char_array_zx0_bin,
    gen_2_Eng_char_array_zx0_bin,
    gen_2_FreGer_char_array_zx0_bin,
    gen_2_FreGer_char_array_zx0_bin,
    gen_2_ItaSpa_char_array_zx0_bin,
    gen_2_ItaSpa_char_array_zx0_bin,
    0,
    gen_3_Jpn_char_array_zx0_bin,
    gen_3_Intern_char_array_zx0_bin,
    gen_3_Intern_char_array_zx0_bin,
    gen_3_Intern_char_array_zx0_bin,
    gen_3_Intern_char_array_zx0_bin,
    gen_3_Intern_char_array_zx0_bin,
    gen_3_Jpn_char_array_zx0_bin
};

void load_localized_charset(u16 *output_char_array, byte gen, byte lang)
{
    // in the localization_charset_files list,
    // gen 1 starts first and every gen has 7 entries (1 per language)
    // however, the language values are 1-based, so we need to convert to 0-based
    const u8 *input_buffer = localization_charset_files[(gen - 1) * 7 + (lang - 1)];
    zx0_decompressor_start((u8*)output_char_array, input_buffer);
    zx0_decompressor_read(sizeof(u16) * 256);
}

byte get_char_from_charset(const u16 *charset, u16 input_char)
{
    u16 i = 0;
    while(i < 256)
    {
        if (charset[i] == input_char)
        {
            return i;
        }
        ++i;
    }
    return 0;
}