#ifndef POKEMON_H
#define POKEMON_H

#include <tonc.h>

class Pokemon
{
public:
    Pokemon(byte gen, int index, byte *party_data);
    byte* convert_to_gen_three();
    void copy_from_to(byte *source, byte *destination, int size);

private:
    byte gen;
    byte species_index;
    byte moves[4];
    byte trainer_id[2];
    byte exp[3];
    byte nickname[11];
    byte trainer_name[11];
    byte pokerus;
    byte caught_data[2];
    byte level;
    byte gen_3_pkmn[80];
    byte PID[4] = {0};
    byte blank_word[4] = {0};
    byte data_section_G[12];
    byte data_section_A[12];
    byte data_section_E[12];
    byte data_section_M[12];
    hword checksum;
    byte encryption_key[4];
};

#endif