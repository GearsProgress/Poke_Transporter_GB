#ifndef RANDOM_H
#define RANDOM_H

#include <tonc.h>

void rand_set_seed(unsigned int init_seed);
unsigned int rand_get_seed();
void rand_next_frame();
u32 get_rand_u32();
u16 get_rand_u16();
u32 get_rev_rand_u32(u32 input);
u16 get_rev_rand_u16(u32 input);
void enable_auto_random();
void disable_auto_random();

unsigned int get_rand_range(unsigned int inc_min, unsigned int exc_max);

#endif