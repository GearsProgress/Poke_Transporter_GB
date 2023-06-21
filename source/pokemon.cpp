#include <tonc.h>
#include "pokemon.h"

#define pkmn_size ((gen == 1) ? 44 : 48)
#define name_size 11

byte gen_one_pkmn_index[255] = {0};
byte gen_two_pkmn_index[255] = {0};

class Pokemon
{
public:
    Pokemon(byte gen, int index, byte party_data[441])
    {
        int party_offset = 20 + (index * 48);
        int ot_offset = 20 + (6 * pkmn_size) + (index * name_size);
        int name_offset = 20 + (6 * pkmn_size) + (6 * name_size) + (index * name_size);

        switch (gen)
        {
        case 1:

            break;
        case 2:
            species_index = gen_one_pkmn_index[party_data[party_offset + 0x00]];
            copy(party_data[party_offset + 0x02], party_data[party_offset + 0x06], moves[0]);
            //std::copy(party_data[party_offset + 0x06], party_data[party_offset + 0x08], trainer_id[0]);
            exp[3]; //??
            //std::copy(party_data[name_offset + 0x00], party_data[name_offset + 0x0A], nickname[0]);
            //std::copy(party_data[ot_offset + 0x00], party_data[name_offset + 0x0A], trainer_name[11]);
            pokerus = party_data[party_offset + 0x1C];
            //std::copy(party_data[party_offset + 0x1D], party_data[party_offset + 0x1F], caught_data[0]);
            level; //??
            break;
        }
    }

    void convert_to_gen_three()
    {
        //std::copy(gen_3_pkmn[0], gen_3_pkmn[3], blank_word[0]); // Personality Value
        //std::copy(gen_3_pkmn[4], gen_3_pkmn[5], blank_word[0]); // SID
        //std::copy(gen_3_pkmn[6], gen_3_pkmn[7], blank_word[0]); // TID
        gen_3_pkmn[8] = 0xBB;
        gen_3_pkmn[9] = 0xFF; // Nickname
        // Language
        gen_3_pkmn[19] = 0b00000010; // Egg Name
        gen_3_pkmn[20] = 0xBB;
        gen_3_pkmn[21] = 0xFF;       // OT Name
        gen_3_pkmn[27] = 0b00000000; // Markings
        // Checksum
        // ???
        // Data
    }

    void copy(int start, int stop, byte *array){
        for (int i = 0; i < (stop - start); i++){
            gen_3_pkmn[i + start] = array[i];
        }
    }

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
    byte blank_word[4] = {0};
};
