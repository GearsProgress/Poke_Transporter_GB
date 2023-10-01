#ifndef SAVE_DATA_MANAGER_H
#define SAVE_DATA_MANAGER_H

#include <tonc.h>

#define HALL_OF_FAME 0x01C000
#define HOF_SECTION 2032

// Data map:
//There are 1936 (0x790) unused bytes starting at 0x1D7F0

                                        //| Offset  | Size  | Contents
                                        //--------------------------
#define TUTORIAL_FLAG       1           //| 0x1     | 1     | Has made it through the tutorial
#define CAUGHT_DATA         2           //| 0x2     | 31    | Flags for each Pokemon species


void load_save_data();
void write_save_data();
bool is_caught(int dex_num);
void set_caught(int dex_num);

#endif
