#ifndef SAVE_DATA_MANAGER_H
#define SAVE_DATA_MANAGER_H

#include <tonc.h>

#define HALL_OF_FAME 0x01C000
#define MYSTERY_GIFT 0x01E000
#define HOF_SECTION 2032

void load_save_data();
void write_save_data();
bool is_caught(int dex_num);
void set_caught(int dex_num);

#endif
