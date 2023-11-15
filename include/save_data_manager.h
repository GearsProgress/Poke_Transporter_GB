#ifndef SAVE_DATA_MANAGER_H
#define SAVE_DATA_MANAGER_H

#include <tonc.h>

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

void load_custom_save_data();
void write_custom_save_data();
bool is_caught(int dex_num);
void set_caught(int dex_num);
int get_def_lang();
void set_def_lang(int nLang);
int get_def_lang_num();
bool get_tutorial_flag();
void set_tutorial_flag(bool value);
void initalize_save_data();
#endif
