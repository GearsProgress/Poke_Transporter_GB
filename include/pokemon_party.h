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

private:
    Pokemon party[6];
    byte party_data_array[444];
    int last_error;
};

#endif