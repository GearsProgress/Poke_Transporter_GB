#include <tonc.h>
#include "pokemon.h"

#define pkmn_size ((gen == 1) ? 44 : 48)
#define name_size 11

byte gen_one_pkmn_index[255] = {0};
byte gen_two_pkmn_index[255] = {0};

Pokemon::Pokemon(byte gen, int index, byte *party_data)
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
            copy_from_to(&party_data[party_offset + 0x02], &moves[0], 4);
            copy_from_to(&party_data[party_offset + 0x06], &trainer_id[0], 2);
            exp[3]; //??
            copy_from_to(&party_data[name_offset + 8], &nickname[0], 10);
            copy_from_to(&party_data[ot_offset + 0x00], &trainer_name[0], 11);
            pokerus = party_data[party_offset + 0x1C];
            copy_from_to(&party_data[party_offset + 0x1D], &caught_data[0], 2);
            level; //??
            break;
        }
    }

byte* Pokemon::convert_to_gen_three()
    {
        copy_from_to(&blank_word[0], &gen_3_pkmn[0], 4); // Personality Value
        copy_from_to(&blank_word[0], &gen_3_pkmn[4], 2); // SID
        copy_from_to(&trainer_id[0], &gen_3_pkmn[6], 2); // TID
        gen_3_pkmn[8] = 0xBB;
        gen_3_pkmn[9] = 0xFF; // Nickname
        gen_3_pkmn[18] = 2;// Language
        gen_3_pkmn[19] = 0b00000010; // Egg Name
        gen_3_pkmn[20] = 0xBB;
        gen_3_pkmn[21] = 0xFF;       // OT Name
        gen_3_pkmn[27] = 0b00000000; // Markings
        // ???
        // Data:
        data_section_G[0] = 0x01;
        data_section_G[1] = 0x9B; // Species Index
        data_section_G[4] = 0xFF; // EXP

        data_section_A[0] = moves[0]; // Move 1
        data_section_A[2] = moves[1]; // Move 2
        data_section_A[4] = moves[2]; // Move 3
        data_section_A[6] = moves[3]; // Move 4

        // Data section E is all zero

        data_section_M[0] = pokerus;

        // Checksum:
        checksum = 0x0000;
        for (int i = 0; i < 12; i = i + 2){
            checksum = checksum + ((data_section_G[i] << 8) | data_section_G[i + 1]);
            checksum = checksum + ((data_section_A[i] << 8) | data_section_A[i + 1]);
            checksum = checksum + ((data_section_E[i] << 8) | data_section_E[i + 1]);
            checksum = checksum + ((data_section_M[i] << 8) | data_section_M[i + 1]);
        }

        gen_3_pkmn[28] = (checksum & 0xFF00) >> 8;
        gen_3_pkmn[29] = checksum & 0xFF;

        for (int i = 0; i < 4; i++){
            encryption_key[i] = gen_3_pkmn[4 + i] ^ PID[i]; // XOR SID and TID with PID
        }

        for (int i = 0; i < 12; i++){
            data_section_G[i] ^= encryption_key[i % 4];
            data_section_A[i] ^= encryption_key[i % 4];
            data_section_E[i] ^= encryption_key[i % 4];
            data_section_M[i] ^= encryption_key[i % 4];
        }

        // TODO: FIX TO MODULO
        copy_from_to(&data_section_G[0], &gen_3_pkmn[32], 12);
        copy_from_to(&data_section_A[0], &gen_3_pkmn[44], 12);
        copy_from_to(&data_section_E[0], &gen_3_pkmn[56], 12);
        copy_from_to(&data_section_M[0], &gen_3_pkmn[68], 12);


        return gen_3_pkmn;
    }

void Pokemon::copy_from_to(byte *source, byte *destination, int size){
        for (int i = 0; i < size; i++){
            destination[i] = source[i];
        }
    }
