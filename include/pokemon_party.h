#ifndef POKEMON_PARTY_H
#define POKEMON_PARTY_H

#include <tonc.h>
#include "pccs/PokeBox.h"
#include "gb_rom_values/base_gb_rom_struct.h"
class Pokemon_Party
{
public:
    Pokemon_Party();
    PokemonTables table;
    void start_link();
    void continue_link(bool cancel_connection);
    int get_last_error();
    bool load_gb_rom(Language lang, Game game);
    bool get_has_new_pkmn();
    void set_game(int nGame);
    void set_lang(int nLang);
    int get_lang();
    bool load_gb_rom();
    GB_ROM curr_gb_rom;
    void show_sprites();
    bool get_contains_mythical();
    void set_mythic_stabilization(bool stabilize);
    int get_game_gen();
    int get_num_pkmn();
    bool get_contains_invalid();
    bool get_contains_missingno();
    PokeBox box;
    byte box_data_array[0x462];

private:
    void init_payload();

    u8 current_payload[PAYLOAD_SIZE];
    int last_error;
    bool stabilize_mythic = false;
    int game;
    char lang;
};

#endif