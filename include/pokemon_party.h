#ifndef POKEMON_PARTY_H
#define POKEMON_PARTY_H

#include <tonc.h>
#include "pokemon.h"

#define BOX_DATA_ARRAY_SIZE 0x462

class Pokemon_Party
{
public:
    Pokemon_Party();
    void start_link();
    int get_last_error();
    Pokemon get_converted_pkmn(int index);
    bool get_has_new_pkmn();
    void set_game(int nGame);
    void set_lang(int nLang);
    int get_lang();

private:
    byte box_data_array[0x462];
    int last_error;
    bool has_new_pkmn;
    int game;
    char lang;
};

#endif