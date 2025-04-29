#include "optimize_movesets.h"
#include <cstring>

const u8 EVOLUTIONS[POKEMON_ARRAY_SIZE]{
    0,    // Offset the list to remove "off by one" errors
    0x0,  // Bulbasaur is a base evolution
    0x1,  // Ivysaur evolves from Bulbasaur
    0x2,  // Venusaur evolves from Ivysaur
    0x0,  // Charmander is a base evolution
    0x4,  // Charmeleon evolves from Charmander
    0x5,  // Charizard evolves from Charmeleon
    0x0,  // Squirtle is a base evolution
    0x7,  // Wartortle evolves from Squirtle
    0x8,  // Blastoise evolves from Wartortle
    0x0,  // Caterpie is a base evolution
    0xa,  // Metapod evolves from Caterpie
    0xb,  // Butterfree evolves from Metapod
    0x0,  // Weedle is a base evolution
    0xd,  // Kakuna evolves from Weedle
    0xe,  // Beedrill evolves from Kakuna
    0x0,  // Pidgey is a base evolution
    0x10, // Pidgeotto evolves from Pidgey
    0x11, // Pidgeot evolves from Pidgeotto
    0x0,  // Rattata is a base evolution
    0x13, // Raticate evolves from Rattata
    0x0,  // Spearow is a base evolution
    0x15, // Fearow evolves from Spearow
    0x0,  // Ekans is a base evolution
    0x17, // Arbok evolves from Ekans
    0xac, // Pikachu evolves from Pichu
    0x19, // Raichu evolves from Pikachu
    0x0,  // Sandshrew is a base evolution
    0x1b, // Sandslash evolves from Sandshrew
    0x0,  // Nidoran-f is a base evolution
    0x1d, // Nidorina evolves from Nidoran-f
    0x1e, // Nidoqueen evolves from Nidorina
    0x0,  // Nidoran-m is a base evolution
    0x20, // Nidorino evolves from Nidoran-m
    0x21, // Nidoking evolves from Nidorino
    0xad, // Clefairy evolves from Cleffa
    0x23, // Clefable evolves from Clefairy
    0x0,  // Vulpix is a base evolution
    0x25, // Ninetales evolves from Vulpix
    0xae, // Jigglypuff evolves from Igglybuff
    0x27, // Wigglytuff evolves from Jigglypuff
    0x0,  // Zubat is a base evolution
    0x29, // Golbat evolves from Zubat
    0x0,  // Oddish is a base evolution
    0x2b, // Gloom evolves from Oddish
    0x2c, // Vileplume evolves from Gloom
    0x0,  // Paras is a base evolution
    0x2e, // Parasect evolves from Paras
    0x0,  // Venonat is a base evolution
    0x30, // Venomoth evolves from Venonat
    0x0,  // Diglett is a base evolution
    0x32, // Dugtrio evolves from Diglett
    0x0,  // Meowth is a base evolution
    0x34, // Persian evolves from Meowth
    0x0,  // Psyduck is a base evolution
    0x36, // Golduck evolves from Psyduck
    0x0,  // Mankey is a base evolution
    0x38, // Primeape evolves from Mankey
    0x0,  // Growlithe is a base evolution
    0x3a, // Arcanine evolves from Growlithe
    0x0,  // Poliwag is a base evolution
    0x3c, // Poliwhirl evolves from Poliwag
    0x3d, // Poliwrath evolves from Poliwhirl
    0x0,  // Abra is a base evolution
    0x3f, // Kadabra evolves from Abra
    0x40, // Alakazam evolves from Kadabra
    0x0,  // Machop is a base evolution
    0x42, // Machoke evolves from Machop
    0x43, // Machamp evolves from Machoke
    0x0,  // Bellsprout is a base evolution
    0x45, // Weepinbell evolves from Bellsprout
    0x46, // Victreebel evolves from Weepinbell
    0x0,  // Tentacool is a base evolution
    0x48, // Tentacruel evolves from Tentacool
    0x0,  // Geodude is a base evolution
    0x4a, // Graveler evolves from Geodude
    0x4b, // Golem evolves from Graveler
    0x0,  // Ponyta is a base evolution
    0x4d, // Rapidash evolves from Ponyta
    0x0,  // Slowpoke is a base evolution
    0x4f, // Slowbro evolves from Slowpoke
    0x0,  // Magnemite is a base evolution
    0x51, // Magneton evolves from Magnemite
    0x0,  // Farfetchd is a base evolution
    0x0,  // Doduo is a base evolution
    0x54, // Dodrio evolves from Doduo
    0x0,  // Seel is a base evolution
    0x56, // Dewgong evolves from Seel
    0x0,  // Grimer is a base evolution
    0x58, // Muk evolves from Grimer
    0x0,  // Shellder is a base evolution
    0x5a, // Cloyster evolves from Shellder
    0x0,  // Gastly is a base evolution
    0x5c, // Haunter evolves from Gastly
    0x5d, // Gengar evolves from Haunter
    0x0,  // Onix is a base evolution
    0x0,  // Drowzee is a base evolution
    0x60, // Hypno evolves from Drowzee
    0x0,  // Krabby is a base evolution
    0x62, // Kingler evolves from Krabby
    0x0,  // Voltorb is a base evolution
    0x64, // Electrode evolves from Voltorb
    0x0,  // Exeggcute is a base evolution
    0x66, // Exeggutor evolves from Exeggcute
    0x0,  // Cubone is a base evolution
    0x68, // Marowak evolves from Cubone
    0xec, // Hitmonlee evolves from Tyrogue
    0xec, // Hitmonchan evolves from Tyrogue
    0x0,  // Lickitung is a base evolution
    0x0,  // Koffing is a base evolution
    0x6d, // Weezing evolves from Koffing
    0x0,  // Rhyhorn is a base evolution
    0x6f, // Rhydon evolves from Rhyhorn
    0x0,  // Chansey is a base evolution (in gen 2)
    0x0,  // Tangela is a base evolution
    0x0,  // Kangaskhan is a base evolution
    0x0,  // Horsea is a base evolution
    0x74, // Seadra evolves from Horsea
    0x0,  // Goldeen is a base evolution
    0x76, // Seaking evolves from Goldeen
    0x0,  // Staryu is a base evolution
    0x78, // Starmie evolves from Staryu
    0x0,  // Mr-mime is a base evolution (in gen 2)
    0x0,  // Scyther is a base evolution
    0xee, // Jynx evolves from Smoochum
    0xef, // Electabuzz evolves from Elekid
    0xf0, // Magmar evolves from Magby
    0x0,  // Pinsir is a base evolution
    0x0,  // Tauros is a base evolution
    0x0,  // Magikarp is a base evolution
    0x81, // Gyarados evolves from Magikarp
    0x0,  // Lapras is a base evolution
    0x0,  // Ditto is a base evolution
    0x0,  // Eevee is a base evolution
    0x85, // Vaporeon evolves from Eevee
    0x85, // Jolteon evolves from Eevee
    0x85, // Flareon evolves from Eevee
    0x0,  // Porygon is a base evolution
    0x0,  // Omanyte is a base evolution
    0x8a, // Omastar evolves from Omanyte
    0x0,  // Kabuto is a base evolution
    0x8c, // Kabutops evolves from Kabuto
    0x0,  // Aerodactyl is a base evolution
    0x0,  // Snorlax is a base evolution (in gen 2)
    0x0,  // Articuno is a base evolution
    0x0,  // Zapdos is a base evolution
    0x0,  // Moltres is a base evolution
    0x0,  // Dratini is a base evolution
    0x93, // Dragonair evolves from Dratini
    0x94, // Dragonite evolves from Dragonair
    0x0,  // Mewtwo is a base evolution
    0x0,  // Mew is a base evolution
    0x0,  // Chikorita is a base evolution
    0x98, // Bayleef evolves from Chikorita
    0x99, // Meganium evolves from Bayleef
    0x0,  // Cyndaquil is a base evolution
    0x9b, // Quilava evolves from Cyndaquil
    0x9c, // Typhlosion evolves from Quilava
    0x0,  // Totodile is a base evolution
    0x9e, // Croconaw evolves from Totodile
    0x9f, // Feraligatr evolves from Croconaw
    0x0,  // Sentret is a base evolution
    0xa1, // Furret evolves from Sentret
    0x0,  // Hoothoot is a base evolution
    0xa3, // Noctowl evolves from Hoothoot
    0x0,  // Ledyba is a base evolution
    0xa5, // Ledian evolves from Ledyba
    0x0,  // Spinarak is a base evolution
    0xa7, // Ariados evolves from Spinarak
    0x2a, // Crobat evolves from Golbat
    0x0,  // Chinchou is a base evolution
    0xaa, // Lanturn evolves from Chinchou
    0x0,  // Pichu is a base evolution
    0x0,  // Cleffa is a base evolution
    0x0,  // Igglybuff is a base evolution
    0x0,  // Togepi is a base evolution
    0xaf, // Togetic evolves from Togepi
    0x0,  // Natu is a base evolution
    0xb1, // Xatu evolves from Natu
    0x0,  // Mareep is a base evolution
    0xb3, // Flaaffy evolves from Mareep
    0xb4, // Ampharos evolves from Flaaffy
    0x2c, // Bellossom evolves from Gloom
    0x0,  // Marill is a base evolution (in gen 2)
    0xb7, // Azumarill evolves from Marill
    0x0,  // Sudowoodo is a base evolution (in gen 2)
    0x3d, // Politoed evolves from Poliwhirl
    0x0,  // Hoppip is a base evolution
    0xbb, // Skiploom evolves from Hoppip
    0xbc, // Jumpluff evolves from Skiploom
    0x0,  // Aipom is a base evolution
    0x0,  // Sunkern is a base evolution
    0xbf, // Sunflora evolves from Sunkern
    0x0,  // Yanma is a base evolution
    0x0,  // Wooper is a base evolution
    0xc2, // Quagsire evolves from Wooper
    0x85, // Espeon evolves from Eevee
    0x85, // Umbreon evolves from Eevee
    0x0,  // Murkrow is a base evolution
    0x4f, // Slowking evolves from Slowpoke
    0x0,  // Misdreavus is a base evolution
    0x0,  // Unown is a base evolution
    0x0,  // Wobbuffet is a base evolution (in gen 2)
    0x0,  // Girafarig is a base evolution
    0x0,  // Pineco is a base evolution
    0xcc, // Forretress evolves from Pineco
    0x0,  // Dunsparce is a base evolution
    0x0,  // Gligar is a base evolution
    0x5f, // Steelix evolves from Onix
    0x0,  // Snubbull is a base evolution
    0xd1, // Granbull evolves from Snubbull
    0x0,  // Qwilfish is a base evolution
    0x7b, // Scizor evolves from Scyther
    0x0,  // Shuckle is a base evolution
    0x0,  // Heracross is a base evolution
    0x0,  // Sneasel is a base evolution
    0x0,  // Teddiursa is a base evolution
    0xd8, // Ursaring evolves from Teddiursa
    0x0,  // Slugma is a base evolution
    0xda, // Magcargo evolves from Slugma
    0x0,  // Swinub is a base evolution
    0xdc, // Piloswine evolves from Swinub
    0x0,  // Corsola is a base evolution
    0x0,  // Remoraid is a base evolution
    0xdf, // Octillery evolves from Remoraid
    0x0,  // Delibird is a base evolution
    0x0,  // Mantine is a base evolution (in gen 2)
    0x0,  // Skarmory is a base evolution
    0x0,  // Houndour is a base evolution
    0xe4, // Houndoom evolves from Houndour
    0x75, // Kingdra evolves from Seadra
    0x0,  // Phanpy is a base evolution
    0xe7, // Donphan evolves from Phanpy
    0x89, // Porygon2 evolves from Porygon
    0x0,  // Stantler is a base evolution
    0x0,  // Smeargle is a base evolution
    0x0,  // Tyrogue is a base evolution
    0xec, // Hitmontop evolves from Tyrogue
    0x0,  // Smoochum is a base evolution
    0x0,  // Elekid is a base evolution
    0x0,  // Magby is a base evolution
    0x0,  // Miltank is a base evolution
    0x71, // Blissey evolves from Chansey
    0x0,  // Raikou is a base evolution
    0x0,  // Entei is a base evolution
    0x0,  // Suicune is a base evolution
    0x0,  // Larvitar is a base evolution
    0xf6, // Pupitar evolves from Larvitar
    0xf7, // Tyranitar evolves from Pupitar
    0x0,  // Lugia is a base evolution
    0x0,  // Ho-oh is a base evolution
    0x0,  // Celebi is a base evolution
    0x0,  // Treecko is a base evolution
};

static void deduplicate_bits_across_evolutions(u8 *output_buffer, const u8 *input_buffer)
{
    const u8 *cur_input = input_buffer;
    const u8 ROWSIZE = 32;
    u8 base_moveset[ROWSIZE];
    u8 evolution;
    u8 i, j;
    for(i=0; i < POKEMON_ARRAY_SIZE; ++i)
    {
        evolution = EVOLUTIONS[i];
        if(evolution == 0)
        {
            memcpy(output_buffer, cur_input, ROWSIZE);
        }
        else
        {
            memcpy(base_moveset, input_buffer + (evolution * ROWSIZE), ROWSIZE);
            // combine moveset of all base forms before comparing with our current moveset
            // at most 2 base forms in gen I or gen II
            evolution = EVOLUTIONS[evolution];

            if(evolution)
            {
                for(j = 0; j < ROWSIZE; ++j)
                {
                    base_moveset[j] |= input_buffer[evolution * ROWSIZE + j];
                }
            }
            // we want to set the resulting bit to 0 if it already was zero or if the basemoveset and current moveset both have 1
            // if only the current moveset is set to 1, it should be 1.
            // This looks like a XOR operation is appropriate.
            // technically a side-effect would be that if the base set has it set to 1 and the current moveset doesn't, that it will end up
            // being a 1. But I don't think that's a valid scenario, especially because can_learn_move() in PTGB already OR'ed
            // the results of evolution + bases together.

            for (j = 0; j < ROWSIZE; ++j)
            {
                output_buffer[j] = cur_input[j] ^ base_moveset[j];
            }
        }
        output_buffer += ROWSIZE;
        cur_input += ROWSIZE;
    }
}

static u16 deduplicate_rows(u8 *output_buffer, const u8 *input_buffer)
{
    u16 num_unique_rows;
    u8 *row_index = output_buffer;
    u8 *row_space = output_buffer + POKEMON_ARRAY_SIZE;
    const u8 ROWSIZE = 32;
    u8 i;
    int16_t j;
    bool found;

    // first row is all zeros
    memcpy(row_space, input_buffer, ROWSIZE);
    row_index[0] = 0;
    num_unique_rows = 1;

    for(i = 1; i < POKEMON_ARRAY_SIZE; ++i)
    {
        found = false;
        for(j = num_unique_rows - 1; j >= 0; --j)
        {
            if(!memcmp(row_space + (j * ROWSIZE), input_buffer + (i * ROWSIZE), ROWSIZE))
            {
                // matching entry found in previous rows. store a reference to it in the row index
                row_index[i] = static_cast<uint8_t>(j);
                found = true;
                break;
            }
        }

        if(!found)
        {
            // no matching entry found in previous rows (which means this is a unique entry up until now)
            // insert the current entry into the resulting table and 
            memcpy(row_space + (num_unique_rows * ROWSIZE), input_buffer + (i * ROWSIZE), ROWSIZE);
            row_index[i] = num_unique_rows;
            ++num_unique_rows;
        }
    }

    return num_unique_rows;
}

#include <cstdio>

void check_unique_rows(const u8 *input_buffer)
{
    uint8_t unique_rows = 0;
    const u8 *cur;
    const u8 *row;
    bool foundMatch;

    for(uint8_t i=0; i < POKEMON_ARRAY_SIZE; ++i)
    {
        cur = input_buffer + (i * 32);
        row = input_buffer;
        foundMatch = false;

        while(row < input_buffer + POKEMON_ARRAY_SIZE * 32)
        {
            if(row == cur)
            {
                row += 32;
                continue;
            }
            if(!memcmp(cur, row, 32))
            {
                foundMatch = true;
                break;
            }
            row += 32;
        }

        if(!foundMatch)
        {
            ++unique_rows;
        }
    }

    //printf("Unique rows: %hhu\n", unique_rows);
}

/**
 * This function is similar to the original implementation in PTGB's pokemon_data.cpp
 * But it is used to test for differences between the optimized MOVESETS table and the unoptimized one.
 */
static bool can_learn_move(const u8* movesets_table, int pkmn_index, int move_index)
{
    u16 table_index = pkmn_index * 32 + (move_index / 8);
    byte data_byte = movesets_table[table_index];
    table_index = EVOLUTIONS[pkmn_index] * 32 + (move_index / 8);
    data_byte |= movesets_table[table_index];             // add in the previous evolution's moves (if they exist)
    table_index = EVOLUTIONS[EVOLUTIONS[pkmn_index]] * 32 + (move_index / 8);
    data_byte |= movesets_table[table_index]; // add in the first evolution's moves (if they exist)
    return (data_byte >> (7 - (move_index % 8))) & 0x1;
}

optimize_moveset_result optimize_movesets(u8 *output_buffer, const u8 *input_buffer, u16 input_buffer_size)
{
    optimize_moveset_result result = {0, 0};
    u8 work_buffer[MOVESETS_size];

    if(input_buffer_size % 32)
    {
        // invalid input buffer. Must be divisible by 32 bytes!
        return result;
    }

    deduplicate_bits_across_evolutions(output_buffer, input_buffer);
    check_unique_rows(output_buffer);
    result.num_bytes = input_buffer_size;

    #if 0
    // test optimized table
    bool problem_found = false;
    for(u16 i=0; i < POKEMON_ARRAY_SIZE; ++i)
    {
        for(u16 move = 0; move < 256; ++move)
        {
            if(can_learn_move((const uint8_t*)MOVESETS, i, move) != can_learn_move(output_buffer, i, move))
            {
                printf("ERROR: optimized MOVESETS differs at pkmn %hu, move %hhu!\n", i, move);
                problem_found = true;
            }
        }
    }
    if(problem_found)
    {
        printf("ERROR: one or more issues detected in the optimized MOVESETS table\n");
    }
    else
    {
        printf("INFO: no problems found in the optimized MOVESETS table!\n");
    }
    #endif

    //deduplicate_bits_across_evolutions(work_buffer, input_buffer);
    //check_unique_rows(work_buffer);
    //result.num_unique_rows = deduplicate_rows(output_buffer, work_buffer);
    //result.num_bytes = NUM_POKEMON + (result.num_unique_rows * 32);

    return result;
}