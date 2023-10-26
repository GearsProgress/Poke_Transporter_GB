#ifndef SAVE_DATA_MANAGER_H
#define SAVE_DATA_MANAGER_H

#include <tonc.h>

#define RUBY_ID 4282454      // AXV
#define SAPPHIRE_ID 4282448  // AXP
#define FIRERED_ID 4345938   // BPR
#define LEAFGREEN_ID 4345927 // BPG
#define EMERALD_ID 4345925   // BPE

#define VERS_1_0 0
#define VERS_1_1 1
#define VERS_1_2 2

#define NUM_GAME_PAIRS 3
#define NUM_VERSIONS 3

#define HALL_OF_FAME 0x01C000
#define HOF_SECTION 2032

// Data map:
// There are 1936 (0x790) unused bytes starting at 0x1D7F0

//                                | Offset  | Size  | Contents
//                                --------------------------
#define TUTORIAL_FLAG 0x01    //  | 0x1     | 1     | Has made it through the tutorial
#define CAUGHT_DATA 0x02      //  | 0x2     | 31    | Flags for each Pokemon species
#define DEFAULT_LANGUAGE 0x21 //  | 0x21    | 1     | Default international language
#define SAVE_DATA_SIZE 0x22

void load_gamecode();
void load_save_data();
void write_save_data();
bool is_caught(int dex_num);
void set_caught(int dex_num);
int get_def_lang();
void set_def_lang(int nLang);
int get_gamecode();
int get_version();

#endif
