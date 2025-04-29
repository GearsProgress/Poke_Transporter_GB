#ifndef _OPTIMIZE_MOVESETS_H
#define _OPTIMIZE_MOVESETS_H

#include "pokemon_data.h"

typedef struct optimize_moveset_result
{
    u16 num_unique_rows;
    u16 num_bytes;
} optimize_moveset_result;

/**
 * input_buffer has 32 bytes for each pokémon. The first row is index 0, which doesn't actually represent a pokémon
 * because the pokémon species index is 1-based. 
 * 
 * Anyway, the 32 bytes of the input_data have 1 bit for every available gen I/II move
 * 
 * But we want to optimize it better for compression. For instance, there's a lot of overlap between the bits of evolutions vs base forms.
 * So, as optimization, we could clear every move bit of an evolution that is also set for its base form.
 * 
 * This way we can make the evolutions' moveset data a lot of zeros. That will compress better.
 * 
 * But another optimization we can do is to deduplicate the resulting table and only store the unique rows.
 * 
 * TL;DR: this function will turn the original MOVESETS table into this format:
 * 
 * First 252 bytes: this chunk will associate a row index to every pokemon based on (species index - 1)
 * Next bytes: rows of 32 bytes each for which every bit of these 32 bytes associates with a gen 1/2 move.
 */
optimize_moveset_result optimize_movesets(u8 *output_buffer, const u8 *input_buffer, u16 input_buffer_size);

#endif