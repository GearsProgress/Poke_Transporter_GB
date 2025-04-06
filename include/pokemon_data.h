#ifndef POKEMON_DATA_H
#define POKEMON_DATA_H

#include <tonc.h>
#include <string>

#define erratic_max (u32)600000
#define fast_max (u32)800000
#define med_fast_max (u32)1000000
#define med_slow_max (u32)1059860
#define slow_max (u32)1250000
#define flux_max (u32)1640000

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

extern const u8 EXP_GROUPS[POKEMON_ARRAY_SIZE];
extern const u32 EXP_MAXIMUMS[6];
extern const int GENDER_THRESHOLDS[2][8];
extern const u8 GENDER_RATIO[POKEMON_ARRAY_SIZE];
extern const bool NUM_ABILITIES[POKEMON_ARRAY_SIZE];
extern const byte MOVESETS[POKEMON_ARRAY_SIZE][32];
extern const byte FIRST_MOVES[POKEMON_ARRAY_SIZE];
extern const char* NAMES[POKEMON_ARRAY_SIZE];
extern const u16 JPN_NAMES[POKEMON_ARRAY_SIZE][6];
extern const u8 EVOLUTIONS[POKEMON_ARRAY_SIZE];
extern const u8 POWER_POINTS[252];
extern const u8 MENU_SPRITE_PALS[POKEMON_ARRAY_SIZE + 26][2];
extern const byte gen_1_index_array[191];
extern const u16 gen_1_Jpn_char_array[256];
extern const u16 gen_1_Eng_char_array[256];
extern const u16 gen_1_FreGer_char_array[256];
extern const u16 gen_1_ItaSpa_char_array[256];
extern const u16 gen_2_Jpn_char_array[256];
extern const u16 gen_2_Eng_char_array[256];
extern const u16 gen_2_FreGer_char_array[256];
extern const u16 gen_2_ItaSpa_char_array[256];
extern const u16 gen_3_Jpn_char_array[256];
extern const u16 gen_3_Intern_char_array[256];
extern const byte EVENT_PKMN[8][80];
extern const u8 TYPES[POKEMON_ARRAY_SIZE][2];

u32 get_max_exp(int index_num);
u8 get_gender_threshold(int index_num, bool is_gen_3);
bool get_num_abilities(int index_num);
bool can_learn_move(int pkmn_index, int move_index);
byte get_earliest_move(int index_num);
byte get_gen_3_char(u16 input_char, bool is_jpn);

#endif