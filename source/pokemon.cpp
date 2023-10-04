#include <tonc.h>
#include "pokemon.h"
#include "pokemon_data.h"
#include "random.h"

#define name_size 11

Pokemon::Pokemon(){};

void Pokemon::load_data(int index, byte *party_data)
{
    int pkmn_size;
    int ot_and_party;
    if (party_data[418] == 0xFD && party_data[419] == 0xFD && party_data[420] == 0xFD && party_data[421] == 0xFD){
        gen = 1;
        pkmn_size = 44;
        ot_and_party = 19;
    } else {
        gen = 2;
        pkmn_size = 48;
        ot_and_party = 21;
    }
    int party_offset = ot_and_party + (index * pkmn_size);
    int ot_offset = ot_and_party + (6 * pkmn_size) + (index * name_size);
    int name_offset = ot_and_party + (6 * pkmn_size) + (6 * name_size) + (index * name_size);

    switch (gen)
    {
    case 1:
        species_index = gen_1_index_array[party_data[party_offset + 0x00]];
        copy_from_to(&party_data[party_offset + 0x08], &moves[0], 4, false);
        copy_from_to(&party_data[party_offset + 0x0C], &trainer_id[0], 2, false);
        copy_from_to(&party_data[party_offset + 0x0E], &exp[0], 3, true);
        copy_from_to(&party_data[name_offset], &nickname[0], 10, false);
        copy_from_to(&party_data[ot_offset + 0x00], &trainer_name[0], 7, false);
        copy_from_to(&party_data[party_offset + 0x1B], &dvs[0], 2, false);
        copy_from_to(&party_data[party_offset + 0x1D], &pp_values[0], 4, false);
        pokerus = 0x00;
        caught_data[0] = 0x00;
        caught_data[1] = 0x00;
        level = party_data[party_offset + 0x21];
        break;
    case 2:
        species_index = party_data[party_offset + 0x00];
        copy_from_to(&party_data[party_offset + 0x02], &moves[0], 4, false);
        copy_from_to(&party_data[party_offset + 0x06], &trainer_id[0], 2, false);
        copy_from_to(&party_data[party_offset + 0x08], &exp[0], 3, true);
        copy_from_to(&party_data[name_offset], &nickname[0], 10, false);
        copy_from_to(&party_data[ot_offset + 0x00], &trainer_name[0], 7, false);
        copy_from_to(&party_data[party_offset + 0x15], &dvs[0], 2, false);
        copy_from_to(&party_data[party_offset + 0x17], &pp_values[0], 4, false);
        pokerus = party_data[party_offset + 0x1C];
        copy_from_to(&party_data[party_offset + 0x1D], &caught_data[0], 2, false);
        level = party_data[party_offset + 0x1F];
        break;
    }
}

void Pokemon::convert_to_gen_three()
{
    // Generate PID
    u32 n_pid = generate_pid(species_index, *(vu32 *)exp % 25, &dvs[0]);
    for (int i = 0; i < 4; i++)
    {
        pid[i] = (n_pid >> (i * 8)) & 0xFF;
    }

    // Make sure Level is not over 100 based on EXP
    if (*(vu32 *)exp > get_max_exp(species_index))
    {
        *(vu32 *)exp = get_max_exp(species_index);
    }

    // Separate the PP Up values from the Move PP values
    for (int i = 0; i < 4; i++)
    {
        pure_pp_values[i] = (pp_values[i] & 0b00111111);
        pp_bonus |= (pp_values[i] & 0b11000000) >> (6 - i * 2);
    }

    // Check that the moves are valid
    for (int i = 0; i < 4; i++){
        if((!can_learn_move(species_index, moves[i])) && (moves[i] != 0)){
            moves[i] = 12;
        }
    }

    // Make sure it has at least one move
    if (moves[0] + moves[1] + moves[2] + moves[3] == 0){
        moves[0] = get_earliest_move(species_index);
    }

    // Bubble valid moves to the top
    int i, j;
    bool swapped;
    for (i = 0; i < 3; i++) {
        swapped = false;
        for (j = 0; j < 3 - i; j++) {
            if ((moves[j] < moves[j + 1]) && moves[j] == 0) {
                moves[j] = moves[j + 1];
                moves[j + 1] = 0;
                swapped = true;
            }
        }
  
        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }

    // Convert and set IVs
    int hp_iv = 0;
    for (int i = 0; i < 4; i++)
    {
        ivs[i + 1] = (dvs[i / 2] >> (((i + 1) % 2) * 4)) & 0b1111;
        hp_iv |= ((ivs[i + 1] & 0x1) << i);
    };
    ivs[0] = hp_iv;
    ivs[5] = ivs[4];

    for (int i = 0; i < 6; i++)
    {
        ivs[i] = (ivs[i] * 2) + 1;
        iv_egg_ability |= ((ivs[i] & 0b11111) << (i * 5));
    }

    // Determine and set Ability
    iv_egg_ability |= ((pid[0] & 0x1) ? get_num_abilities(species_index) : 0) << 31;

    // Origin info
    origin_info |= ((caught_data[0] & 0b10000000) << 8); // OT gender - We would shift left 15 bits, but the bit is already shifted over 7
    origin_info |= (4 << 11);                            // Ball
    origin_info |= (((gen == 1) ? 4 : 7) << 7);          // Game
    origin_info |= level;                                // Level met

    // Ribbons and Obedience
    ribbons[2] |= 0b00000100;                         // Artist Ribbon
    if (species_index == 151 || species_index == 251) // Checks for Mew or Celebi
        ribbons[3] |= 0x10000000;                     // Fateful Encounter flag

    // Personality Value
    copy_from_to(&pid[0], &gen_3_pkmn[0], 4, false);
    // Trainer ID
    copy_from_to(&trainer_id[0], &gen_3_pkmn[4], 2, true);

    // Check if the Pokemon is shiny
    if (                                                                   // Is shiny
        (dvs[1] == 0b10101010) &&                                          // Checks if the Speed and Special DVs equal 10
        ((dvs[0] & 0xF) == 0b1010) &&                                      // Checks if the Defense DVs equal 10
        (((dvs[0] & 0b11000000) >> 6) | (((dvs[0] & 0b00110000) >> 2) > 7))) // Reorganizes the Attack DV bits so that they will be >7 if the Pokemon is shiny
    {
        secret_id[0] = trainer_id[0] ^ pid[0] ^ pid[2] ^ 0xFF;
        secret_id[1] = trainer_id[1] ^ pid[1] ^ pid[3] ^ 0xFF;
        // Randomly shift by 16 (maybe)
    }
    else // Not shiny, make sure it isn't
    {
        if (((trainer_id[0] ^ secret_id[0] ^ pid[0] ^ pid[2]) == 0) &&
            ((trainer_id[1] ^ secret_id[1] ^ pid[1] ^ pid[3]) > 7))
        {
            secret_id[0] = 0xFF;
            secret_id[1] = 0xFF;
        }
    }
    copy_from_to(&secret_id[0], &gen_3_pkmn[6], 2, false); // Set SID

    copy_from_to(convert_text(&nickname[0], 10, 2), &gen_3_pkmn[8], 10, false);    // Nickname
    gen_3_pkmn[18] = 2;                                                            // Language, set to English
    gen_3_pkmn[19] = 0b00000010;                                                   // Egg Name
    copy_from_to(convert_text(&trainer_name[0], 7, 2), &gen_3_pkmn[20], 7, false); // OT Name
    gen_3_pkmn[27] = 0b00000000;                                                   // Markings
    // ???

    // Data:
    data_section_G[0] = species_index;
    data_section_G[1] = 0x00; // Species Index, check for glitch Pokemon
    copy_from_to(&exp[0], &data_section_G[4], 3, false);
    data_section_G[8] = pp_bonus;

    data_section_A[0] = moves[0];                                   // Move 1
    data_section_A[2] = moves[1];                                   // Move 2
    data_section_A[4] = moves[2];                                   // Move 3
    data_section_A[6] = moves[3];                                   // Move 4
    copy_from_to(&pure_pp_values[0], &data_section_A[8], 4, false); // PP Values

    // Data section E is all zero (EVs and Contest Stats)

    data_section_M[0] = pokerus;
    data_section_M[1] = 0xFF;                      // Met location - set to Fateful Encounter (separate from flag), cannot be seen by player and is replaced by Pal Park in gen 4
    data_section_M[2] = origin_info & 0x00FF;      // Lower origins info
    data_section_M[3] = (origin_info >> 8) & 0xFF; // Upper origins info
    for (int i = 0; i < 4; i++)
    {
        data_section_M[i + 4] = (iv_egg_ability >> (i * 8) & 0xFF); // Set IVs, Egg, and Ability
    }
    copy_from_to(&ribbons[0], &data_section_M[8], 4, false); // Ribbons and Fateful Encounter

    // Checksum:
    checksum = 0x0000;
    for (int i = 0; i < 12; i = i + 2)
    {
        checksum = checksum + ((data_section_G[i + 1] << 8) | data_section_G[i]);
        checksum = checksum + ((data_section_A[i + 1] << 8) | data_section_A[i]);
        checksum = checksum + ((data_section_E[i + 1] << 8) | data_section_E[i]);
        checksum = checksum + ((data_section_M[i + 1] << 8) | data_section_M[i]);
    }

    gen_3_pkmn[28] = checksum & 0xFF;
    gen_3_pkmn[29] = (checksum & 0xFF00) >> 8;

    for (int i = 0; i < 4; i++)
    {
        encryption_key[i] = gen_3_pkmn[4 + i] ^ pid[i]; // XOR SID and TID with PID
    }

    for (int i = 0; i < 12; i++)
    {
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

void Pokemon::copy_from_to(byte *source, byte *destination, int size, bool reverse_endian)
{
    if (reverse_endian)
    {
        for (int i = 0; i < size; i++)
        {
            destination[(size - 1) - i] = source[i];
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            destination[i] = source[i];
        }
    }
}

void Pokemon::alocate_data_chunks(byte *G, byte *A, byte *E, byte *M)
{
    // reverse_endian(pid, 4); // This PERMANENTLY reverses the PID which is 'okay' because it is not used again. Bad practice though...
    word full_pid = (pid[3] << 24 | pid[2] << 16 | pid[1] << 8 | pid[0]);
    byte mod_pid = full_pid % 24;
    unencrypted_data[48] = mod_pid;
    // This is such a stupid way to do this, but I can't for the life of me find a formula for the permutation table.
    switch (mod_pid)
    {
    case 0:
        insert_data(G, A, E, M);
        break;
    case 1:
        insert_data(G, A, M, E);
        break;
    case 2:
        insert_data(G, E, A, M);
        break;
    case 3:
        insert_data(G, E, M, A);
        break;
    case 4:
        insert_data(G, M, A, E);
        break;
    case 5:
        insert_data(G, M, E, A);
        break;
    case 6:
        insert_data(A, G, E, M);
        break;
    case 7:
        insert_data(A, G, M, E);
        break;
    case 8:
        insert_data(A, E, G, M);
        break;
    case 9:
        insert_data(A, E, M, G);
        break;
    case 10:
        insert_data(A, M, G, E);
        break;
    case 11:
        insert_data(A, M, E, G);
        break;
    case 12:
        insert_data(E, G, A, M);
        break;
    case 13:
        insert_data(E, G, M, A);
        break;
    case 14:
        insert_data(E, A, G, M);
        break;
    case 15:
        insert_data(E, A, M, G);
        break;
    case 16:
        insert_data(E, M, G, A);
        break;
    case 17:
        insert_data(E, M, A, G);
        break;
    case 18:
        insert_data(M, G, A, E);
        break;
    case 19:
        insert_data(M, G, E, A);
        break;
    case 20:
        insert_data(M, A, G, E);
        break;
    case 21:
        insert_data(M, A, E, G);
        break;
    case 22:
        insert_data(M, E, G, A);
        break;
    case 23:
        insert_data(M, E, A, G);
        break;
    }
}

void Pokemon::insert_data(byte *first, byte *second, byte *third, byte *fourth)
{
    copy_from_to(&first[0], &gen_3_pkmn[32], 12, false);
    copy_from_to(&second[0], &gen_3_pkmn[44], 12, false);
    copy_from_to(&third[0], &gen_3_pkmn[56], 12, false);
    copy_from_to(&fourth[0], &gen_3_pkmn[68], 12, false);
}

byte Pokemon::get_gen_3_data(int index)
{
    return gen_3_pkmn[index];
}

byte *Pokemon::get_full_gen_3_array()
{
    return gen_3_pkmn;
}

byte Pokemon::get_unencrypted_data(int index)
{
    return unencrypted_data[index];
}

byte *Pokemon::convert_text(byte *text_array, int size, int gen)
{
    switch (gen)
    {
    case 1:
        for (int i = 0; i < size; i++)
        {
            if (text_array[i] == 0x50)
            {
                text_array[i] = 0xFF;
            }
            else if (text_array[i] >= 0x80)
            {
                text_array[i] = gen_1_char_array[text_array[i] - 0x80];
            }
            else
            {
                text_array[i] = 0x00;
            }
        }
        break;

    case 2:
        for (int i = 0; i < size; i++)
        {
            if (text_array[i] == 0x50)
            {
                text_array[i] = 0xFF;
            }
            else if (text_array[i] >= 0x80)
            {
                text_array[i] = gen_2_char_array[text_array[i] - 0x80];
            }
            else
            {
                text_array[i] = 0x00;
            }
        }
        break;
    }
    return text_array;
}

u32 Pokemon::generate_pid(byte pid_species_index, byte nature, byte *pid_dvs)
{
    // Set Unown Letter
    u32 new_pid = 0;
    byte letter = 0;
    if (pid_species_index == 0xC9) // Checks if the Pokemon is Unown
    {
        letter |= ((pid_dvs[0] >> 5) & 0b11) << 6;
        letter |= ((pid_dvs[0] >> 1) & 0b11) << 4;
        letter |= ((pid_dvs[1] >> 5) & 0b11) << 2;
        letter |= ((pid_dvs[1] >> 1) & 0b11);
        letter = letter / 10;

        byte letter_mod = rand_reverse_mod(28, letter);
        for (int i = 0; i < 4; i++)
        {
            new_pid |= ((letter_mod >> (i * 2)) & 0b11) << (8 * i);
        }

        // Randomize rest of PID
        new_pid |= get_rand_u32() & 0xFCFCFCFC;

        // Set Nature
        while ((new_pid % 25) != nature)
        {
            new_pid = (new_pid & 0xFFFFFF00) | ((new_pid & 0xFF) + 4);
        }
        return new_pid;
    }
    else
    {
        // Set the correct gender for the Pokemon
        new_pid |= get_rand_gender_byte(pid_species_index, ((pid_dvs[0] >> 4) & 0b1111));

        // Randomize rest of PID
        new_pid |= get_rand_u32() & 0xFFFFFF00;

        while (new_pid % 25 != nature)
        {
            new_pid = new_pid + 256;
        }
        return new_pid;
    }
}

byte Pokemon::rand_reverse_mod(byte modulo_divisor, byte target_mod)
{
    return (modulo_divisor * get_rand_range(0, (255 - target_mod) / modulo_divisor)) + target_mod;
}

byte Pokemon::get_rand_gender_byte(byte index_num, byte attack_DVs)
{
    byte gen2_threshold = get_gender_threshold(index_num, false);
    byte gen3_threshold = get_gender_threshold(index_num, true);
    if (gen2_threshold == -1) // Is one gender or is genderless
    {
        return get_rand_range(0, 256);
    }
    else if (attack_DVs < gen2_threshold) // Is Female
    {
        return get_rand_range(0, gen3_threshold);
    }
    else // Is Male
    {
        return get_rand_range(gen3_threshold, 256);
    }
}
