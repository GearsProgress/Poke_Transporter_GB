#ifndef POKEMON_H
#define POKEMON_H

#include <tonc.h>
#include "random.h"

class Pokemon
{
public:
    Pokemon();
    void load_data(int gen, int index, byte *party_data);
    void convert_to_gen_three(u32 random_32);
    void copy_from_to(byte *source, byte *destination, int size, bool reverse_endian);
    void alocate_data_chunks(byte *G, byte *A, byte *E, byte *M);
    void insert_data(byte *first, byte *second, byte *third, byte *fourth);
    byte get_gen_3_data(int index);
    byte* get_full_gen_3_array();
    byte get_unencrypted_data(int index);
    byte* convert_text(byte *text_array, int size, int gen);
    u32 generate_pid(byte pid_species_index, byte nature, byte *pid_ivs, u32 seed);
    byte rand_reverse_mod(byte modulo_divisor, byte target_mod, u32 seed);
    byte get_rand_gender_byte(byte index_num, byte attack_DVs, u32 seed);

private:
    byte gen;
    byte species_index;
    byte moves[4];
    byte trainer_id[2];
    byte exp[4];
    byte nickname[10];
    byte trainer_name[7];
    byte pokerus;
    byte caught_data[2];
    byte level;
    byte gen_3_pkmn[80];
    byte unencrypted_data[49]; // Contains the 48 GAEM bytes, along with the modulo int
    byte pid[4] = {0b00000001, 0b10101010, 0b11111111, 0b10011001}; //Little Endian, reverse of Bulbapedia
    byte blank_word[4] = {0};
    byte data_section_G[12];
    byte data_section_A[12];
    byte data_section_E[12];
    byte data_section_M[12];
    hword checksum;
    byte encryption_key[4];
    hword origin_info = 0;
    bool is_shiny = false;
    byte pp_values[4];
    byte pp_bonus;
    byte pure_pp_values[4];
    byte dvs[2];
    byte ivs[6];
    byte ribbons[4];
    u32 iv_egg_ability;
};

#endif