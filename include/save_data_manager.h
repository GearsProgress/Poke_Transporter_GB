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
#define TRANSFERED_FLAGS    33          //| 0x21    | 6     | Flags for if a Pokemon has been transfered in by the player
#define PKMN1_DATA          39          //| 0x27    | 100   | Data for Pokemon #1
#define PKMN2_DATA          139         //| 0x8B    | 100   | Data for Pokemon #2
#define PKMN3_DATA          239         //| 0x8F    | 100   | Data for Pokemon #3
#define PKMN4_DATA          339         //| 0x153   | 100   | Data for Pokemon #4
#define PKMN5_DATA          439         //| 0x1B7   | 100   | Data for Pokemon #5
#define PKMN6_DATA          539         //| 0x21B   | 100   | Data for Pokemon #6

void load_save_data();
void write_save_data();
bool is_caught(int dex_num);
void set_caught(int dex_num);

#endif
