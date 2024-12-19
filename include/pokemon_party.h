#ifndef POKEMON_PARTY_H
#define POKEMON_PARTY_H

#include <tonc.h>
#include "pokemon.h"
#include "gb_rom_values/eng_gb_rom_values.h"

class Pokemon_Party
{
public:
    Pokemon_Party();
    void start_link();
    void continue_link(bool cancel_connection);
    int get_last_error();
    Pokemon get_converted_pkmn(int index);
    bool get_has_new_pkmn();
    void set_game(int nGame);
    void set_lang(int nLang);
    int get_lang();
    bool load_gb_rom();
    GB_ROM curr_gb_rom;
    void show_sprites();
    Pokemon pkmn_array[30];
    bool fill_simple_pkmn_array();
    bool get_contains_mythical();
    void set_mythic_stabilization(bool stabilize);
    bool contains_valid = false;
    bool contains_invalid = false;
    int get_game_gen();
    int get_num_pkmn();
    bool get_contains_invalid();
    bool get_contains_missingno();
    byte box_data_array[0x462];

private:
    int last_error;
    bool has_new_pkmn = false;
    bool contains_mythical = false;
    bool stabilize_mythic = false;
    bool contains_missingno = false;
    int game;
    char lang;
};

#endif