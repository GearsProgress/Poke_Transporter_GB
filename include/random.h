#ifndef RANDOM_H
#define RANDOM_H

class Poke_Random{
    public:
        Poke_Random(unsigned int init_seed);
        void next_frame();
        unsigned int get_rand();
    private:
        unsigned int rand;
};

unsigned int convert_random(unsigned int seed, unsigned int inc_min, unsigned int exc_max);

#endif