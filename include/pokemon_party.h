#ifndef POKEMON_PARTY_H
#define POKEMON_PARTY_H

#include <tonc.h>
#include "pokemon.h"

class Pokemon_Party{
    public:
    Pokemon_Party();
    int start_link();

    private:
    Pokemon party[6];
    byte party_data[444];
};

#endif