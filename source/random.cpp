#include "random.h"

unsigned int rand;

Poke_Random::Poke_Random(unsigned int init_seed){
    rand = init_seed;
}

void Poke_Random::next_frame(){
    rand =  0x41C64E6D * rand + 0x00006073; // This is the randomization method used in Gen 3
}

unsigned int Poke_Random::get_rand(){
    return rand;
}

unsigned int convert_random(unsigned int seed, unsigned int inc_min, unsigned int exc_max){
    return ((double)((seed / (double)0x100000000) * (exc_max - inc_min)) + inc_min);
}