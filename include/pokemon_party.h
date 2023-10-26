#ifndef POKEMON_PARTY_H
#define POKEMON_PARTY_H

#include <tonc.h>
#include "pokemon.h"

class Pokemon_Party
{
public:
    Pokemon_Party();
    void start_link();
    int get_last_error();
    void load_pokemon();
    Pokemon* get_full_pokemon_array();

private:
    Pokemon party[6];
    byte party_data_array[GEN2_INT_SIZE + 4];
    int last_error;
    int party_size;
    int gen;
};

#endif