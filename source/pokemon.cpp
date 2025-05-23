#include <tonc.h>
#include "pokemon.h"
#include "pokemon_data.h"
#include "random.h"
#include "save_data_manager.h"
#include "debug_mode.h"
#include "text_engine.h"

Pokemon::Pokemon() {};

// TODO: Rewrite this with two different classes/structs that have arrays as input/output
// GBpkmn and GBApkmn
// A lot of the event Pokemon script is reused. Really should be split into many different functions
// Endian-ness too is all over the place... :/

void Pokemon::load_data(int index, const byte *party_data, int game, int lang)
{
    language = lang;
    if (lang == JPN_ID)
    {
        switch (game)
        {
        case GREEN_ID:
        case RED_ID:
        case BLUE_ID:
        case YELLOW_ID:
            gen = 1;
            pkmn_size = 44;
            ot_size = 6;
            nickname_size = 6;
            box_size = 30;
            break;
        case GOLD_ID:
        case SILVER_ID:
        case CRYSTAL_ID:
            gen = 2;
            pkmn_size = 32;
            ot_size = 6;
            nickname_size = 6;
            box_size = 30;
            break;
        }
    }
    else
    {
        switch (game)
        {
        case RED_ID:
        case BLUE_ID:
        case YELLOW_ID:
            gen = 1;
            pkmn_size = 33;
            ot_size = 11;
            nickname_size = 11;
            box_size = 20;
            break;
        case GOLD_ID:
        case SILVER_ID:
        case CRYSTAL_ID:
            gen = 2;
            pkmn_size = 32;
            ot_size = 11;
            nickname_size = 11;
            box_size = 20;
            break;
        }
    }
    int party_species_offset =
        1 +          // the num pkmn byte
        (1 * index); // the pkmn index we're looking for

    int box_struct_offset =
        1 +                  // the num of pkmn byte
        (1 * box_size) + 1 + // list of pkmn in box and terminator
        (pkmn_size * index); // the pokemon we're looking for

    int ot_offset =
        1 +                      // the num of pkmn byte
        (1 * box_size) + 1 +     // list of pkmn in box and terminator
        (pkmn_size * box_size) + // the pokemon structs
        (ot_size * index);       // the ot we're looking for

    int nickname_offset =
        1 +                      // the num of pkmn byte
        (1 * box_size) + 1 +     // list of pkmn in box and terminator
        (pkmn_size * box_size) + // the pokemon structs
        (ot_size * box_size) +   // the ots
        (nickname_size * index); // the nickname we're looking for

    num_in_box = party_data[0];
    index_in_box = index;

    switch (gen)
    {
    case 1:
        // ptgb_write(std::to_string(party_data[1121]).c_str());
        // while (true){};
        species_index_party = party_data[party_species_offset];
        species_index_struct = party_data[box_struct_offset + 0x00];
        met_level = party_data[box_struct_offset + 0x03];
        copy_from_to(&party_data[box_struct_offset + 0x08], &moves[0], 4, false);
        copy_from_to(&party_data[box_struct_offset + 0x0C], &trainer_id[0], 2, false);
        exp = 0;
        for (int i = 0; i < 3; i++)
        {
            exp += party_data[box_struct_offset + 0x0E + i];
        }
        copy_from_to(&party_data[box_struct_offset + 0x1B], &dvs[0], 2, false);
        copy_from_to(&party_data[box_struct_offset + 0x1D], &pp_values[0], 4, false);
        copy_from_to(&party_data[nickname_offset], &nickname[0], 10, false);
        copy_from_to(&party_data[ot_offset], &trainer_name[0], 7, false);
        // Data not in gen 1
        pokerus = 0x00;
        caught_data[0] = 0x00;
        caught_data[1] = 0x00;
        item = 0;

        break;
    case 2:
        species_index_party = party_data[party_species_offset];
        species_index_struct = party_data[box_struct_offset + 0x00];
        item = party_data[box_struct_offset + 0x01];
        copy_from_to(&party_data[box_struct_offset + 0x02], &moves[0], 4, false);
        copy_from_to(&party_data[box_struct_offset + 0x06], &trainer_id[0], 2, false);
        exp = 0;
        for (int i = 0; i < 3; i++)
        {
            exp += party_data[box_struct_offset + 0x08 + i] << (8 * (2 - i));
        }
        copy_from_to(&party_data[box_struct_offset + 0x15], &dvs[0], 2, false);
        copy_from_to(&party_data[box_struct_offset + 0x17], &pp_values[0], 4, false);
        pokerus = party_data[box_struct_offset + 0x1C];
        copy_from_to(&party_data[box_struct_offset + 0x1D], &caught_data[0], 2, false);
        met_level = party_data[box_struct_offset + 0x1F];
        copy_from_to(&party_data[nickname_offset], &nickname[0], 10, false);
        copy_from_to(&party_data[ot_offset + 0x00], &trainer_name[0], 7, false);
        break;
    }

    // box_struct_offset = 0;
    if (SHOW_DATA_PACKETS)
    {
        tte_set_pos(8, 120);
        ptgb_write("struct offset: ");
        ptgb_write(std::to_string(box_struct_offset).c_str());
        ptgb_write("\nbox_size: ");
        ptgb_write(std::to_string(box_size).c_str());
        ptgb_write("\npkmn_size: ");
        ptgb_write(std::to_string(pkmn_size).c_str());
        ptgb_write("\nindex: ");
        ptgb_write(std::to_string(index).c_str());
        ptgb_write(", game: ");
        ptgb_write(std::to_string(game).c_str());
        while (!key_hit(KEY_A))
        {
            global_next_frame();
        }
        global_next_frame();
    }
}
void Pokemon::convert_to_gen_three(Conversion_Types conv_type, bool simplified, bool stabilize_mythical)
{
    // Convert the species indexes
    if (gen == 1)
    {
        if (species_index_struct > 190)
        {
            species_index_struct = 0;
        }
        else
        {
            species_index_struct = gen_1_index_array[species_index_struct];
            if (species_index_struct == 0xFF)
            {
                is_missingno = true;
                species_index_struct = 0x89; // Porygon
            }
        }
        species_index_party = species_index_struct;
    }

    if (                                                                          // index_in_box % 4 == 0 ||
        (species_index_struct > NUM_POKEMON - (get_treecko_enabled() ? 0 : 1)) || // Checks if the Pokemon is beyond the supported Pokemon
        species_index_struct == 0 ||                                              // Checks that the Pokemon isn't a blank party space
        species_index_struct != species_index_party ||                            // Checks that the Pokemon isn't a hybrid or an egg
        index_in_box >= num_in_box ||                                             // Checks that we're not reading beyond the Pokemon in the box
        item != 0)                                                                // Checks that the Pokemon doesn't have an item
    {
        if (!DONT_HIDE_INVALID_PKMN)
        {
            is_valid = false;
            return;
        }
    }
    is_valid = true;

    nature_mod = exp % 25; // save the nature mod in case the level is changed
    // Update dex if not simple
    if (!simplified && !is_caught(species_index_struct))
    {
        is_new = true;
        set_caught(species_index_struct);
    }

    // Set nickname
    if (language == KOR_ID)
    {

        gen_3_pkmn[18] = JPN_ID; // Set to JPN
        byte new_nickname[10];
        byte new_ot[7];
        for (int i = 0; i < 6; i++)
        { // Read the JPN name and convert it
            new_nickname[i] = get_gen_3_char(JPN_NAMES[species_index_struct][i], true);
        }

        if (gen == 1)
        {
            // レッド (Red)
            new_ot[0] = 0x7A; // レ
            new_ot[1] = 0xA0; // ッ
            new_ot[2] = 0x95; // ド
            new_ot[3] = 0xFF;
        }
        else
        {
            if (((caught_data[1] & 0b10000000) >> 7) == 1) // Checks if the Gen 2 player is male or female
            {
                // クリス (Kurisu)
                new_ot[0] = 0x58; // ク
                new_ot[1] = 0x78; // リ
                new_ot[2] = 0x5D; // ス
                new_ot[3] = 0xFF;
            }
            else
            {
                // ヒビキ (Hibiki)
                new_ot[0] = 0x6B; // ヒ
                new_ot[1] = 0x97; // ビ
                new_ot[2] = 0x57; // キ
                new_ot[3] = 0xFF;
            }
        }
        copy_from_to(&new_nickname[0], &gen_3_pkmn[8], 10, false); // Nickname
        copy_from_to(&new_ot[0], &gen_3_pkmn[20], 7, false);       // OT Name
    }
    else
    {
        gen_3_pkmn[18] = language;                                                                 // Language
        copy_from_to(convert_text(&nickname[0], 10, gen, language), &gen_3_pkmn[8], 10, false);    // Nickname
        copy_from_to(convert_text(&trainer_name[0], 7, gen, language), &gen_3_pkmn[20], 7, false); // OT Name
    }

    // Make sure Level is not over 100 based on EXP
    u32 max_exp = get_max_exp(species_index_struct);
    if (exp > max_exp)
    {
        exp = max_exp;
    }

    // Truncate the EXP down to the current level
    if (conv_type == Virtual)
    {
        switch (EXP_GROUPS[species_index_struct])
        {
        case EXP_FAST:
            exp = (4 * (met_level * met_level * met_level)) / 5;
            break;

        case EXP_MED_FAST:
            exp = (met_level * met_level * met_level);
            break;

        case EXP_MED_SLOW:
            exp = ((6 * met_level * met_level * met_level) / 5) - (15 * met_level * met_level) + (100 * met_level) - 140;
            break;

        case EXP_SLOW:
            exp = (5 * (met_level * met_level * met_level)) / 4;
            break;
        }
    }

    // Check if shiny
    is_shiny =
        ((dvs[1] == 0b10101010) &&      // Checks if the Speed and Special DVs equal 10
         ((dvs[0] & 0xF) == 0b1010) &&  // Checks if the Defense DVs equal 10
         ((dvs[0] & 0b00100000) >> 5)); // Checks if the second bit of the Attack DV is true

    if (species_index_struct == 52 && fnv1a_hash(nickname, 7) == 1515822901 &&
        (fnv1a_hash(trainer_name, 7) == 2671449886 || fnv1a_hash(trainer_name, 7) == 1342961308))
    {
        is_shiny = true;
        dvs[0] = 0xFF;
        dvs[1] = 0xFF;
    }

    if (species_index_struct == 201) // Checks if the Pokemon is Unown
    {
        unown_letter = 0;
        unown_letter |= ((dvs[0] >> 5) & 0b11) << 6;
        unown_letter |= ((dvs[0] >> 1) & 0b11) << 4;
        unown_letter |= ((dvs[1] >> 5) & 0b11) << 2;
        unown_letter |= ((dvs[1] >> 1) & 0b11);
        unown_letter = unown_letter / 10;
    }
    else
    {
        unown_letter = -1;
    }

    if (simplified)
    {
        if ((species_index_struct == 151 || species_index_struct == 251) && exp < 560) // Minimum EXP for level 10
        {
            met_level = 10;
        }
        return;
    }

    // Separate the PP Up values from the Move PP values
    for (int i = 0; i < 4; i++)
    {
        pure_pp_values[i] = (pp_values[i] & 0b00111111); // Take only the bottom six bits
        if (conv_type == Virtual)
        {
            pp_bonus[i] = 0; // Reset bonus
        }
        else
        {
            pp_bonus[i] = (pp_values[i] >> 6); // Take only the top two bits
        }
    }

    if (conv_type == Legal)
    {
        // Check that the moves are valid
        if (is_missingno)
        {
            moves[0] = 55;  // Water Gun
            moves[1] = 143; // Sky Attack
            moves[2] = 6;   // Pay Day
            moves[3] = 20;  // Bind
            for (int i = 0; i < 4; i++)
            {
                pp_bonus[i] = 0;
            }
        }
        else if ((species_index_struct != 0xEB) && (species_index_struct != 0xFC)) // Ignore Smeargle due to Sketch, Ignore Treecko because Treecko
        {
            for (int i = 0; i < 4; i++)
            {
                if ((!can_learn_move(species_index_struct, moves[i])) && (moves[i] != 0))
                {
                    moves[i] = 0;    // Remove the move
                    pp_bonus[i] = 0; // Remove the PP bonus
                }
            }
        }

        // Make sure it has at least one move
        if (moves[0] + moves[1] + moves[2] + moves[3] == 0)
        {
            moves[0] = get_earliest_move(species_index_struct);
        }

        // Bubble valid moves to the top
        int i, j;
        bool swapped;
        for (i = 0; i < 3; i++)
        {
            swapped = false;
            for (j = 0; j < 3 - i; j++)
            {
                if ((moves[j] < moves[j + 1]) && moves[j] == 0)
                {
                    // Move the move *and* PP bonus up if there is a blank space
                    moves[j] = moves[j + 1];
                    pp_bonus[j] = pp_bonus[j + 1];
                    moves[j + 1] = 0;
                    pp_bonus[j + 1] = 0;
                    swapped = true;
                }
            }

            // If no two elements were swapped
            // by inner loop, then break
            if (swapped == false)
                break;
        }
    }
    // Restore the PP values
    for (int i = 0; i < 4; i++)
    {
        pure_pp_values[i] = POWER_POINTS[moves[i]] + ((POWER_POINTS[moves[i]] / 5) * pp_bonus[i]);
    }

    // This is everything the mythical needs, don't change anything else
    if (stabilize_mythical && (species_index_struct == 151 || species_index_struct == 251))
    {
        set_to_event(nature_mod);
        return;
    }

    // Generate PID
    disable_auto_random();
    u32 n_pid;
    if (ENABLE_MATCH_PID)
    {
        n_pid = generate_pid_iv_match(species_index_struct, nature_mod, &dvs[0]);
        ///n_pid = generate_pid_iv_legendary(species_index_struct, &dvs[0], &ivs[0]);
        
                u16 curr_rand = get_rand_u16();
                ivs[0] = (curr_rand >> 0) & 0b11111;
                ivs[1] = (curr_rand >> 5) & 0b11111;
                ivs[2] = (curr_rand >> 10) & 0b11111;
                curr_rand = get_rand_u16();
                ivs[3] = (curr_rand >> 0) & 0b11111;
                ivs[4] = (curr_rand >> 5) & 0b11111;
                ivs[5] = (curr_rand >> 10) & 0b11111;
        
        iv_egg_ability = 0;
        for (int i = 0; i < 6; i++)
        {
            iv_egg_ability |= ((ivs[i] & 0b11111) << (i * 5));
        }
    }
    else
    {
        n_pid = generate_pid_save_iv(species_index_struct, nature_mod, &dvs[0]);

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
    }
    for (int i = 0; i < 4; i++)
    {
        pid[i] = (n_pid >> (i * 8)) & 0xFF;
    }
    enable_auto_random();

    // Determine and set Ability based off PID
    iv_egg_ability |= ((pid[0] & 0x1) ? get_num_abilities(species_index_struct) : 0) << 31;

    // Origin info
    if (conv_type == Faithful || conv_type == Legal)
    {
        origin_info |= ((caught_data[1] & 0b10000000) << 8); // OT gender - We would shift left 15 bits, but the bit is already shifted over 7
    }
    if (is_missingno)
    {
        origin_info |= (1 << 11); // Master Ball
    }
    else
    {
        origin_info |= (4 << 11); // Poke Ball
    }
    origin_info |= (((gen == 1 || conv_type == Legal) ? 4 : 7) << 7); // Game

    if (conv_type != Legal)
    {
        origin_info |= met_level; // Level met. Set to zero (ie do nothing) if legal, so it is "hatched"
    }

    // Ribbons and Obedience
    // ribbons[2] |= 0b00000100; // Artist Ribbon
    if (species_index_struct == 151 || species_index_struct == 251) // Pokemon is Mew or Celebi
    {
        ribbons[3] |= 0b10000000; // Fateful Encounter flag
    }
    else if (is_missingno)
    {
        ribbons[3] |= 0b10000000; // Fateful Encounter flag
        // ribbons[3] |= 0b00000100; // World Ribbon
    }

    // Personality Value
    copy_from_to(&pid[0], &gen_3_pkmn[0], 4, false);
    // Trainer ID
    copy_from_to(&trainer_id[0], &gen_3_pkmn[4], 2, true);

    // Check if the Pokemon is shiny
    if (is_shiny)
    {
        secret_id[0] = trainer_id[1] ^ pid[0] ^ pid[2] ^ 0x0; // This value at the end should be random between 0 - 15, if that is to be implemented
        secret_id[1] = trainer_id[0] ^ pid[1] ^ pid[3] ^ 0x0;
        // Randomly shift by 16 (maybe)
    }
    else // Not shiny, make sure it isn't
    {
        secret_id[0] = dvs[0];
        secret_id[1] = dvs[1];

        if (((trainer_id[0] ^ secret_id[0] ^ pid[0] ^ pid[2]) == 0) &&
            ((trainer_id[1] ^ secret_id[1] ^ pid[1] ^ pid[3]) < 8))
        {
            secret_id[1] += 8;
        }
    }
    copy_from_to(&secret_id[0], &gen_3_pkmn[6], 2, false); // Set SID

    gen_3_pkmn[19] = 0b00000010; // Egg Name (has species sanity flag)
    gen_3_pkmn[27] = 0b00000000; // Markings

    // Data:

    // Reset the data sections (in case the player runs the program twice)
    for (int i = 0; i < 12; i++)
    {
        data_section_G[i] = 0;
        data_section_A[i] = 0;
        data_section_E[i] = 0;
        data_section_M[i] = 0;
    }

    data_section_G[0] = (species_index_struct != 252 ? species_index_struct : 277); // Treecko check
    data_section_G[1] = (species_index_struct != 252 ? 0x00 : 0x01);                // Treecko check;
    data_section_G[2] = (is_new ? 0x44 : 0x00);                                     // Rare Candy if new
    data_section_G[3] = 0x00;
    for (int i = 0; i < 3; i++)
    {
        data_section_G[4 + i] = exp >> (8 * i);
    }
    data_section_G[8] = (pp_bonus[0] << 0 | pp_bonus[1] << 2 | pp_bonus[2] << 4 | pp_bonus[3] << 6);

    data_section_A[0] = moves[0];                                   // Move 1
    data_section_A[2] = moves[1];                                   // Move 2
    data_section_A[4] = moves[2];                                   // Move 3
    data_section_A[6] = moves[3];                                   // Move 4
    copy_from_to(&pure_pp_values[0], &data_section_A[8], 4, false); // PP Values

    // Data section E is all zero (EVs and Contest Stats)

    byte met_location = 0xFF; // Fateful Encounter
    if (conv_type == Legal)
    {
        switch (species_index_struct)
        {
        case 144:                // Articuno
            met_location = 0x8B; // Seafoam Islands
            break;
        case 145:                // Zapdos
            met_location = 0x8E; // Power Plant
            break;
        case 146:                // Moltres
            met_location = 0xAF; // Mt. Ember
            break;
        case 150:                // Mewtwo
            met_location = 0x8D; // Cerulean Cave
            break;
        case 201:                // Unown
            met_location = 0xB8; // Tanoby Chambers
            break;
        case 243:                // Raikou
            met_location = 0x6E; // Route 10 - in reference to the Power Plant
            break;
        case 244:                // Entei
            met_location = 0x79; // Route 21 - in reference to the Cinnabar Volcano
            break;
        case 245:                // Suicune
            met_location = 0x7D; // Route 25 - in reference to their final encounter in HGSS
            break;
        case 249:                // Lugia
        case 250:                // Ho-Oh
            met_location = 0xAE; // Navel Rock
            break;
        default:
            met_location == 0xD7; // Met in a trade?
            break;
        }
    }

    data_section_M[0] = (conv_type == Virtual ? 0 : pokerus);
    data_section_M[1] = met_location;              // Met location, will be replaced by Pal Park in gen 4
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
    global_next_frame();
}

void Pokemon::copy_from_to(const byte *source, byte *destination, int size, bool reverse_endian)
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

byte *Pokemon::convert_text(byte *text_array, int size, int gen, int lang)
{
    for (int i = 0; i < size; i++)
    {
        switch (gen)
        {
        case 1:
            switch (lang)
            {
            case JPN_ID:
                text_array[i] = get_gen_3_char(gen_1_Jpn_char_array[text_array[i]], true);
                break;
            case ENG_ID:
            default:
                text_array[i] = get_gen_3_char(gen_1_Eng_char_array[text_array[i]], false);
                break;
            case FRE_ID:
            case GER_ID:
                text_array[i] = get_gen_3_char(gen_1_FreGer_char_array[text_array[i]], false);
                break;
            case SPA_ID:
            case ITA_ID:
                text_array[i] = get_gen_3_char(gen_1_ItaSpa_char_array[text_array[i]], false);
                break;
            }
            break;
        case 2:
        default:
            switch (lang)
            {
            case JPN_ID:
                text_array[i] = get_gen_3_char(gen_2_Jpn_char_array[text_array[i]], true);
                break;
            case ENG_ID:
            default:
                text_array[i] = get_gen_3_char(gen_2_Eng_char_array[text_array[i]], false);
                break;
            case FRE_ID:
            case GER_ID:
                text_array[i] = get_gen_3_char(gen_2_FreGer_char_array[text_array[i]], false);
                break;
            case SPA_ID:
            case ITA_ID:
                text_array[i] = get_gen_3_char(gen_2_ItaSpa_char_array[text_array[i]], false);
                break;
            }
            break;
        }
    }
    return text_array;
}

u32 Pokemon::generate_pid_iv_match(byte pid_species_index, byte nature, byte *pid_dvs)
{
    u32 new_pid = 0;
    byte new_nature = 0;
    byte new_gender = 0;
    byte new_letter = 0;
    int gen2_gender_threshold = get_gender_threshold(pid_species_index, false);
    int gen3_gender_threshold = get_gender_threshold(pid_species_index, true);
    bool gender = (((pid_dvs[0] >> 4) & 0b1111) < gen2_gender_threshold);

    do
    {
        new_pid = get_rand_u16() | (get_rand_u16() << 16);
        new_nature = get_nature_from_pid(new_pid);
        new_gender = get_gender_from_pid(new_pid);
        new_letter = get_letter_from_pid(new_pid);
    } while (!(
        (unown_letter != -1 ? new_letter == unown_letter : true) &&
        new_nature == nature &&
        (gen2_gender_threshold != -1
             ? ((new_gender < gen3_gender_threshold) == gender)
             : true)));

    return new_pid;
}

u32 Pokemon::generate_pid_iv_legendary(byte pid_species_index, byte *pid_dvs, byte *out_ivs)
{
    // Convert and set IVs

    // This stores the DVs in the IV order
    byte ivs[6] = {
        (((dvs[0] >> 4) & 0b1) << 3) |
            (((dvs[0] >> 0) & 0b1) << 2) |
            (((dvs[1] >> 4) & 0b1) << 1) |
            (((dvs[1] >> 0) & 0b1) << 0),

        (dvs[0] >> 4) & 0b1111, // Attack
        (dvs[0] >> 0) & 0b1111, // Defense
        (dvs[1] >> 4) & 0b1111, // Speed
        (dvs[1] >> 0) & 0b1111, // Special Attack
        (dvs[1] >> 0) & 0b1111, // Special Defense
    };

    u32 iv_low_rng;
    u32 iv_high_rng;
    u32 pid_high_rng;
    u32 pid_low_rng;
    u32 pid;
    u32 seed;

    u32 comp;
    u32 n_val;
    u32 n_comp;

    for (int i = 0; i < 65535; i++)
    {
        // Generate the low IV byte, being the SpD, SpA, Spe
        iv_low_rng = (i % 2) << 31 | (ivs[5] << 27) | (ivs[4] << 22) | (ivs[3] << 17) | (i >> 1);
        iv_high_rng = get_rev_rand_u32(iv_low_rng);
        pid_high_rng = get_rev_rand_u32(iv_high_rng);
        pid_low_rng = get_rev_rand_u32(pid_high_rng);
        seed = get_rev_rand_u32(pid_low_rng);
        pid = ((pid_high_rng & 0xFFFF0000) << 0) | (pid_low_rng & 0xFFFF0000) >> 16;

        // Test it against the high IV byte, being the Def, Atk, HP
        comp = (ivs[2] << 11) | (ivs[1] << 6) | (ivs[0] << 1);
        n_val = (iv_high_rng >> 16) & 0b0111101111011110;
        n_comp = comp & 0b0111101111011110;

        if (n_comp == n_val)
        {
            if ((pid % 25) % 6 == 0)
            {
                out_ivs[0] = (iv_low_rng >> 0) & 0b11111; // HP
                out_ivs[1] = (iv_low_rng >> 5) & 0b11111; // Atk
                out_ivs[2] = (iv_low_rng >> 10) & 0b11111; // Def
                out_ivs[3] = (iv_high_rng >> 5) & 0b11111; // SpA
                out_ivs[4] = (iv_high_rng >> 10) & 0b11111; // SpD
                out_ivs[5] = (iv_high_rng >> 0) & 0b11111; // Spe

                return pid_low_rng | seed;
            }
        }
    }
    return 0;
}

u8 Pokemon::get_letter_from_pid(u32 pid)
{
    return (
               ((pid & 0x03000000) >> 18) +
               ((pid & 0x00030000) >> 12) +
               ((pid & 0x00000300) >> 6) +
               ((pid & 0x00000003) >> 0)) %
           28;
};
u8 Pokemon::get_nature_from_pid(u32 pid)
{
    return (pid % 25);
};
u8 Pokemon::get_gender_from_pid(u32 pid)
{
    return (pid & 0xFF);
};

u32 Pokemon::generate_pid_save_iv(byte pid_species_index, byte nature, byte *pid_dvs)
{
    // Set Unown Letter
    u32 new_pid = 0;
    if (pid_species_index == 0xC9) // Checks if the Pokemon is Unown
    {
        byte letter_mod = rand_reverse_mod(28, unown_letter);
        for (int i = 0; i < 4; i++)
        {
            new_pid |= ((letter_mod >> (i * 2)) & 0b11) << (8 * i);
        }

        // Randomize rest of PID
        new_pid |= get_rand_u32() & 0xFCFCFCFC;

        // Set Nature
        while ((new_pid % 25) != nature)
        {
            // Keep adding 0b100 to the PID until the nature matches
            // 0b100 ensures that the 2 LSBs are maintained, as they determine the letter
            new_pid = (new_pid & 0xFFFFFF00) | ((new_pid + 0b100) & 0xFF);
        }
        return new_pid;
    }
    else
    {
        // Set the correct gender for the Pokemon
        new_pid |= get_rand_gender_byte(pid_species_index, ((pid_dvs[0] >> 4) & 0b1111));

        // Randomize rest of PID
        new_pid |= get_rand_u32() & 0xFFFFFF00;

        // Set nature
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

byte Pokemon::get_dex_number()
{
    return (is_valid ? species_index_struct : 0);
}

bool Pokemon::get_validity()
{
    return is_valid;
}

bool Pokemon::get_is_shiny()
{
    return is_shiny;
}

bool Pokemon::get_is_new()
{
    return (is_valid ? is_new : false);
}

Simplified_Pokemon Pokemon::get_simple_pkmn()
{
    Simplified_Pokemon curr_pkmn;
    curr_pkmn.dex_number = get_dex_number();
    curr_pkmn.met_level = met_level;
    for (int i = 0; i < 10; i++)
    {
        curr_pkmn.nickname[i] = nickname[i];
    }
    curr_pkmn.is_valid = get_validity();
    curr_pkmn.is_transferred = false;
    curr_pkmn.is_shiny = get_is_shiny();
    curr_pkmn.unown_letter = unown_letter;
    curr_pkmn.is_missingno = is_missingno;
    return curr_pkmn;
}

void Pokemon::set_to_event(byte nature)
{
    int event_id = 0;
    if (species_index_struct == 151)
    {
        switch (language)
        {
        case JPN_ID:
        case KOR_ID:
            event_id = 0;
            break;
        case ENG_ID:
            event_id = 1;
            break;
        case FRE_ID:
            event_id = 2;
            break;
        case ITA_ID:
            event_id = 3;
            break;
        case GER_ID:
            event_id = 4;
            break;
        case SPA_ID:
            event_id = 5;
            break;
        }
    }
    else
    {
        switch (language)
        {
        case JPN_ID:
        case KOR_ID:
            event_id = 6;
            break;
        case ENG_ID:
        case FRE_ID:
        case ITA_ID:
        case GER_ID:
        case SPA_ID:
            event_id = 7;
            break;
        }
    }

    // Load the event into the Pokemon array and unencrypted data array
    for (int i = 0; i < 0x20; i++)
    {
        if (i == 0x08)
        {
            i += 10; // Skip over the nickname
        }
        gen_3_pkmn[i] = EVENT_PKMN[event_id][i];
    }

    for (int i = 0; i < 12; i++)
    {
        data_section_G[i] = EVENT_PKMN[event_id][i + 0x20 + 0];
        data_section_A[i] = EVENT_PKMN[event_id][i + 0x20 + 12];
        data_section_E[i] = EVENT_PKMN[event_id][i + 0x20 + 24];
        data_section_M[i] = EVENT_PKMN[event_id][i + 0x20 + 36];
    }

    // insert moves and PP bonuses
    data_section_G[8] = (pp_bonus[0] << 0 | pp_bonus[1] << 2 | pp_bonus[2] << 4 | pp_bonus[3] << 6);
    data_section_A[0] = moves[0]; // Move 1
    data_section_A[2] = moves[1]; // Move 2
    data_section_A[4] = moves[2]; // Move 3
    data_section_A[6] = moves[3]; // Move 4

    // get a new PID in the BACD_R format, and make sure it isn't shiny
    disable_auto_random();
    u32 n_pid;
    do
    {
        // Make the seed 16 bits long, per the BACD_R format
        rand_set_seed(rand_get_seed() & 0xFFFF);
        n_pid = (get_rand_u16() << 16) | get_rand_u16();
        for (int i = 0; i < 4; i++)
        {
            gen_3_pkmn[i] = (n_pid >> (i * 8)) & 0xFF;
            pid[i] = (n_pid >> (i * 8)) & 0xFF;
        };
    } while (((pid[0] ^ pid[2] ^ gen_3_pkmn[4] ^ gen_3_pkmn[6]) < 8) &&
             ((pid[1] ^ pid[3] ^ gen_3_pkmn[5] ^ gen_3_pkmn[7]) == 0) &&
             (n_pid % 25 != nature)); // maintain the nature

    // Set and fill the IVs
    u16 curr_rand = get_rand_u16();
    ivs[0] = (curr_rand >> 0) & 0b11111;
    ivs[1] = (curr_rand >> 5) & 0b11111;
    ivs[2] = (curr_rand >> 10) & 0b11111;
    curr_rand = get_rand_u16();
    ivs[3] = (curr_rand >> 0) & 0b11111;
    ivs[4] = (curr_rand >> 5) & 0b11111;
    ivs[5] = (curr_rand >> 10) & 0b11111;

    iv_egg_ability = 0;
    for (int i = 0; i < 6; i++)
    {
        iv_egg_ability |= ((ivs[i] & 0b11111) << (i * 5));
    }
    enable_auto_random();

    // Determine and set Ability
    iv_egg_ability |= ((pid[0] & 0x1) ? get_num_abilities(species_index_struct) : 0) << 31;

    // Set IVs, Egg, and Ability
    for (int i = 0; i < 4; i++)
    {
        data_section_M[i + 4] = (iv_egg_ability >> (i * 8) & 0xFF);
    }

    // Determine and set OT gender
    data_section_M[3] |= (caught_data[1] & 0b10000000);

    // Check the level
    if (exp < 560) // Minimum EXP for level 10
    {
        exp = 560;
    }

    data_section_G[2] = (is_new ? 0x44 : 0x00); // Rare Candy if new

    // Update and set the checksum
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

    // Determine the encryption key
    for (int i = 0; i < 4; i++)
    {
        encryption_key[i] = gen_3_pkmn[4 + i] ^ pid[i]; // XOR SID and TID with PID
    }

    // Encrypt the data
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
    return;
}
