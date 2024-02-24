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
    int get_num_pkmn();
    int get_dex_num(int index);


private:
    byte box_data_array[0x462];
    int last_error;
    int num_pokemon;
    bool has_new_pkmn;
    int game;
    char lang;
};

#endif