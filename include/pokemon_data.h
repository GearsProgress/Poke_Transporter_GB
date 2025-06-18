#ifndef POKEMON_DATA_H
#define POKEMON_DATA_H

#include <tonc.h>

#define med_fast_max (u32)1000000
// Slightly Fast goes unused
// Slightly Slow goes unused
#define med_slow_max (u32)1059860
#define fast_max (u32)800000
#define slow_max (u32)1250000
// Erractic is Gen 3+
// Fluctuating is Gen 3+

#define EXP_FAST 0
// Slightly Fast goes unused
// Slightly Slow goes unused
#define EXP_MED_SLOW 3
#define EXP_MED_FAST 4
#define EXP_SLOW 5
// Erractic is Gen 3+
// Fluctuating is Gen 3+

#define JPN_ID 1
#define ENG_ID 2
#define FRE_ID 3
#define ITA_ID 4
#define GER_ID 5
#define SPA_ID 7
#define KOR_ID 8

#define GREEN_ID 0
#define RED_ID 1
#define BLUE_ID 2
#define YELLOW_ID 3
#define GOLD_ID 4
#define SILVER_ID 5
#define CRYSTAL_ID 6

#define EVENT_MEW_JPN 0
#define EVENT_MEW_ENG 1
#define EVENT_MEW_FRE 2
#define EVENT_MEW_ITA 3
#define EVENT_MEW_GER 4
#define EVENT_MEW_SPA 5
#define EVENT_CELEBI 6


#define MAX_PKMN_IN_BOX 30
#define NUM_POKEMON 252
#define POKEMON_ARRAY_SIZE NUM_POKEMON + 1

// these arrays are too small to compress
extern const u32 EXP_MAXIMUMS[6];
extern const int GENDER_THRESHOLDS[2][8];
// the next arrays don't compress well at all. Not worth the decompression overhead.
extern const byte gen_1_index_array[191];
extern const u8 EVOLUTIONS[POKEMON_ARRAY_SIZE];

// Unfortunately we can't compress this 8 KB MOVESETS array.
// I mean, we physically can, but decompressing it means storing it in IWRAM,
// at a moment (during convert_to_gen_three()) at which we are using a LOT of IWRAM already.
// By keeping it uncompressed, it gets stored in EWRAM, where it won't hinder us.
// But it does mean that it still takes up 8 KB in the rom.
// Just for reference: when compressing it with ZX0 AND only storing the "changed" bits for PKMN
// evolutions in relation to their base forms, we could bring the size down to 4641 bytes.
// But alas, the IWRAM consumption at a critical point in time made this approach unviable.
// TODO: we might be able to load similar data from the game cartridges.
// However, it turns out the data is different between the R/S/E and FR/LG games.
// So we would have to store "patches"/differences if we go this route.
// It also means we'd have to figure out rom offsets for every single gen III game variant/localization.
extern const byte MOVESETS[POKEMON_ARRAY_SIZE][32];

/**
 * Okay, here's the thing: to reduce the rom size, we compressed a bunch of data with ZX0
 * Among this data are various data tables that were previously just stored as const arrays.
 * 
 * But, during the mystery_gift_builder/mystery_gift_injector execution,
 * these data tables are used intensely, because you're not using them for single pokémon, but rather for boxes of pokémon.
 * 
 * Decompression is not cheap, so we can't afford to decompress the tables again and again for every pokémon we deal with
 * during this flow.
 * 
 * This is where this class comes in. It is basically a holder of these tables. The idea is to pass it along with the mystery_gift_builder
 * and have it lazy decompress the tables AND charsets it needs. This way when we are dealing with multiple pokémon, we are not decompressing
 * the same data every time and thereby make performance suffer.
 * 
 * It DOES have a significant IWRAM cost though. The intention is to just allocate this struct on the stack.
 * As far as I can tell, our stack is not really restricted at all. It just fills up the IWRAM as needed. So we need to be careful not to 
 * overwrite/corrupt any code or data we specifically tagged to be stored in IWRAM.
 */
class PokemonTables
{
public:
    bool exp_groups_loaded;
    bool gender_ratios_loaded;
    bool num_abilities_loaded;
    bool first_moves_loaded;
    bool power_points_loaded;
    bool event_pkmn_loaded;
    bool types_loaded;
    // a number representing the unique combination of gen 1/2 and the specific language
    // 0 means not loaded
    u8 input_charset_type;
    // 0 means not loaded, 1=JPN, 2=Intern
    u8 gen3_charset_type;

    u8 EXP_GROUPS[POKEMON_ARRAY_SIZE];
    u8 GENDER_RATIO[POKEMON_ARRAY_SIZE];
    bool NUM_ABILITIES[POKEMON_ARRAY_SIZE];
    byte FIRST_MOVES[POKEMON_ARRAY_SIZE];
    u8 POWER_POINTS[252];
    byte EVENT_PKMN[8][80];
    u8 TYPES[POKEMON_ARRAY_SIZE][2];
    u16 input_charset[256];
    u16 gen3_charset[256];

    PokemonTables();

    void load_exp_groups();
    void load_gender_ratios();
    void load_num_abilities();
    void load_first_moves();
    void load_power_points();
    void load_event_pkmn();
    void load_types();
    void load_input_charset(byte gen, byte lang);
    void load_gen3_charset(byte lang);

    u32 get_max_exp(int index_num);
    u8 get_gender_threshold(int index_num, bool is_gen_3);
    bool get_num_abilities(int index_num);
    bool can_learn_move(int pkmn_index, int move_index);
    byte get_earliest_move(int index_num);
    byte get_gen_3_char(u16 input_char);
};

/**
 * Loads the charset for <gen> and <lang> into <output_char_array>
 */
void load_localized_charset(u16 *output_char_array, byte gen, byte lang);
byte get_char_from_charset(const u16 *charset, u16 input_char);
#endif