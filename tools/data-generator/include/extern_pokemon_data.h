#ifndef _POKEMON_DATA_H
#define _POKEMON_DATA_H

#include <cstddef>
#include <cstdint>

#define NUM_POKEMON 252
#define POKEMON_ARRAY_SIZE NUM_POKEMON + 1

#ifndef TONC_TYPES
typedef uint8_t u8;
typedef uint8_t byte;
typedef uint16_t u16;
typedef uint32_t u32;
#endif

void generate_pokemon_data(const char *output_path);

#endif