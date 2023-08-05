#ifndef RANDOM_H
#define RANDOM_H

void rand_set_seed(unsigned int init_seed);
void rand_next_frame();
unsigned int get_rand_u32();

unsigned int get_rand_range(unsigned int inc_min, unsigned int exc_max);

#endif