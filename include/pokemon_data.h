#ifndef POKEMON_DATA_H
#define POKEMON_DATA_H

#include <tonc.h>

#define erratic_max      600000
#define fast_max         800000
#define med_fast_max    1000000
#define med_slow_max    1059860
#define slow_max        1250000
#define flux_max        1640000



extern const u8 EXP_MAX[251];
extern const u32 EXP_TYPES[6];

u32 get_max_exp(int index_num);

#endif