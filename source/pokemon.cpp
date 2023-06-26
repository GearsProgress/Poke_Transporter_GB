#include <tonc.h>
#include "pokemon.h"
//#include "mirror.h"

#define pkmn_size ((gen == 1) ? 44 : 48)
#define name_size 11

byte gen_one_pkmn_index[255] = {0};

byte gen_two_char_index[255] = {};

Pokemon::Pokemon(byte gen, int index, byte *party_data)
    {
        int party_offset = 21 + (index * 48);
        int ot_offset = 21 + (6 * pkmn_size) + (index * name_size);
        int name_offset = 21 + (6 * pkmn_size) + (6 * name_size) + (index * name_size);

        switch (gen)
        {
        case 1:

            break;
        case 2:
            species_index = party_data[party_offset + 0x00];
            copy_from_to(&party_data[party_offset + 0x02], &moves[0], 4, false);
            copy_from_to(&party_data[party_offset + 0x06], &trainer_id[0], 2, false);
            exp[3]; //??
            copy_from_to(&party_data[name_offset + 8], &nickname[0], 10, false);
            copy_from_to(&party_data[ot_offset + 0x00], &trainer_name[0], 7, false);
            pokerus = party_data[party_offset + 0x1C];
            copy_from_to(&party_data[party_offset + 0x1D], &caught_data[0], 2, false);
            level; //??
            break;
        }
    }

void Pokemon::convert_to_gen_three()
    {
        
        copy_from_to(&pid[0], &gen_3_pkmn[0], 4, false); // Personality Value
        copy_from_to(&trainer_id[0], &gen_3_pkmn[4], 2, true); // TID
        copy_from_to(&blank_word[0], &gen_3_pkmn[6], 2, false); // SID
        copy_from_to(&nickname[0], &gen_3_pkmn[8], 10, false); // Nickname
        gen_3_pkmn[18] = 2; // Language, set to English
        gen_3_pkmn[19] = 0b00000010; // Egg Name
        copy_from_to(&trainer_name[0], &gen_3_pkmn[20], 7, false);// OT Name
        gen_3_pkmn[27] = 0b00000000; // Markings
        // ???
        // Data:
        data_section_G[0] = species_index;
        data_section_G[1] = 0x00; // Species Index, the largest byte will always be zero since there are only up to 251 Pokemon in gen 2
        copy_from_to(&exp[0], &data_section_G[4], 4, false);

        data_section_A[0] = moves[0]; // Move 1
        data_section_A[2] = moves[1]; // Move 2
        data_section_A[4] = moves[2]; // Move 3
        data_section_A[6] = moves[3]; // Move 4

        // Data section E is all zero

        //data_section_M[0] = pokerus;
        data_section_M[3] = 0x20;

        // Checksum:
        checksum = 0x0000;
        for (int i = 0; i < 12; i = i + 2){
            checksum = checksum + ((data_section_G[i + 1] << 8) | data_section_G[i]);
            checksum = checksum + ((data_section_A[i + 1] << 8) | data_section_A[i]);
            checksum = checksum + ((data_section_E[i + 1] << 8) | data_section_E[i]);
            checksum = checksum + ((data_section_M[i + 1] << 8) | data_section_M[i]);
        }

        gen_3_pkmn[28] = checksum & 0xFF;
        gen_3_pkmn[29] = (checksum & 0xFF00) >> 8;

        for (int i = 0; i < 4; i++){
            encryption_key[i] = gen_3_pkmn[4 + i] ^ pid[i]; // XOR SID and TID with PID
        }

        for (int i = 0; i < 12; i++){
            unencrypted_data[i] = data_section_G[i];
            data_section_G[i] ^= encryption_key[i % 4];
            unencrypted_data[12 + i] = data_section_A[i];
            data_section_A[i] ^= encryption_key[i % 4];
            unencrypted_data[24 + i] = data_section_E[i];
            data_section_E[i] ^= encryption_key[i % 4];
            unencrypted_data[36 + i] = data_section_M[i];
            data_section_M[i] ^= encryption_key[i % 4];
        }

        // Puts the four data chunks into their correct locations based on the PID
        alocate_data_chunks(data_section_G, data_section_A, data_section_E, data_section_M);
    }

void Pokemon::copy_from_to(byte *source, byte *destination, int size, bool reverse_endian){
    if(reverse_endian){
        for (int i = 0; i < size; i++){
            destination[(size - 1) - i] = source[i];
        }
    } else {
        for (int i = 0; i < size; i++){
            destination[i] = source[i];
        }
    }
}

void Pokemon::alocate_data_chunks(byte *G, byte *A, byte *E, byte *M){
    //reverse_endian(pid, 4); // This PERMANENTLY reverses the PID which is 'okay' because it is not used again. Bad practice though...
    word full_pid = (pid[3] << 24 | pid[2] << 16 | pid[1] << 8 | pid[0]);
    byte mod_pid = full_pid % 24;
    unencrypted_data[48] = mod_pid;
    // This is such a stupid way to do this, but I can't for the life of me find a formula for the permutation table.
    switch (mod_pid){
        case  0: insert_data(G, A, E, M); break;
        case  1: insert_data(G, A, M, E); break;
        case  2: insert_data(G, E, A, M); break;
        case  3: insert_data(G, E, M, A); break;
        case  4: insert_data(G, M, A, E); break;
        case  5: insert_data(G, M, E, A); break;
        case  6: insert_data(A, G, E, M); break;
        case  7: insert_data(A, G, M, E); break;
        case  8: insert_data(A, E, G, M); break;
        case  9: insert_data(A, E, M, G); break;
        case 10: insert_data(A, M, G, E); break;
        case 11: insert_data(A, M, E, G); break;
        case 12: insert_data(E, G, A, M); break;
        case 13: insert_data(E, G, M, A); break;
        case 14: insert_data(E, A, G, M); break;
        case 15: insert_data(E, A, M, G); break;
        case 16: insert_data(E, M, G, A); break;
        case 17: insert_data(E, M, A, G); break;
        case 18: insert_data(M, G, A, E); break;
        case 19: insert_data(M, G, E, A); break;
        case 20: insert_data(M, A, G, E); break;
        case 21: insert_data(M, A, E, G); break;
        case 22: insert_data(M, E, G, A); break;
        case 23: insert_data(M, E, A, G); break;
    }
}

void Pokemon::insert_data(byte *first, byte *second, byte *third, byte *fourth){
    copy_from_to(&first[0], &gen_3_pkmn[32], 12, false);
    copy_from_to(&second[0], &gen_3_pkmn[44], 12, false);
    copy_from_to(&third[0], &gen_3_pkmn[56], 12, false);
    copy_from_to(&fourth[0], &gen_3_pkmn[68], 12, false);
}

byte Pokemon::get_gen_3_data(int index){
    return gen_3_pkmn[index];
}

byte* Pokemon::get_full_gen_3_array(){
    return gen_3_pkmn;
}

byte Pokemon::get_unencrypted_data(int index){
    return unencrypted_data[index];
}