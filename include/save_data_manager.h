#ifndef SAVE_DATA_MANAGER_H
#define SAVE_DATA_MANAGER_H

#include <tonc.h>

#define RUBY_ID 0x415856    // AXV
#define SAPPHIRE_ID 0x415850  // AXP
#define FIRERED_ID 0x425052   // BPR
#define LEAFGREEN_ID 0x425047 // BPG
#define EMERALD_ID 0x425045   // BPE

#define VERS_1_0 0
#define VERS_1_1 1
#define VERS_1_2 2

#define LANG_JPN 'J'
#define LANG_ENG 'E'
#define LANG_FRE 'F'
#define LANG_GER 'D'
#define LANG_ITA 'I'
#define LANG_SPA 'S'

#define NUM_GAME_PAIRS 3
#define NUM_VERSIONS 3

#define HALL_OF_FAME 0x01C000
#define HOF_SECTION 2032

// Data map:
// There are 1936 (0x790) unused bytes starting at 0x1D7F0

//                                | Offset  | Size  | Contents
//                                --------------------------
#define CAUGHT_DATA 0x00      //  | 0x0     | 32    | Flags for each Pokemon species
#define TUTORIAL_FLAG 0x20    //  | 0x1     | 1     | Has made it through the tutorial
#define DEFAULT_LANGUAGE 0x21 //  | 0x22    | 1     | Default international language
#define SAVE_DATA_SIZE 0x22

void load_gamecode();
void load_custom_save_data();
void write_custom_save_data();
bool is_caught(int dex_num);
void set_caught(int dex_num);
int get_def_lang();
void set_def_lang(int nLang);
int get_gamecode();
int get_version();
int get_language();

#endif
