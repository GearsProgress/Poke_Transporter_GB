#ifndef POKEMON_PARTY_H
#define POKEMON_PARTY_H

#include <tonc.h>
#include "PokeBox.h"
#include "gb_rom_values/base_gb_rom_struct.h"

class Pokemon_Party
{
public:
    Pokemon_Party();
    PokemonTables table;
    bool get_has_new_pkmn();
    void set_lang(int nLang);
    int get_lang();
    GB_ROM curr_gb_rom;
    bool get_contains_mythical();
    void set_mythic_stabilization(bool stabilize);
    int get_num_pkmn();
    bool get_contains_invalid();
    bool get_contains_missingno();
    PokeBox box;
    byte box_data_array[0x462];

private:
    int last_error;
    bool stabilize_mythic = false;
    char lang;
};

#endif