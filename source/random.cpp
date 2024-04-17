#include "random.h"
#include <tonc.h>

unsigned int u32_rand;

void rand_set_seed(unsigned int init_seed){
    u32_rand = init_seed;
}

unsigned int rand_get_seed(){
    return u32_rand;
}


void rand_next_frame(){
    u32_rand =  (0x41C64E6D * u32_rand) + 0x6073; // This is the randomization method used in Gen 3
}

u32 get_rand_u32(){
    rand_next_frame();
    return u32_rand;
}

u16 get_rand_u16(){
    rand_next_frame();
    return (u32_rand >> 16);
}

unsigned int get_rand_range(unsigned int inc_min, unsigned int exc_max){
    return ((double)((get_rand_u32() / (double)0x100000000) * (exc_max - inc_min)) + inc_min);
}