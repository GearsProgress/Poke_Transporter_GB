#ifndef MIRROR_H
#define MIRROR_H
#include <tonc.h>
#include "pokemon.h"
#include "rom_data.h"


#define MEM_CRAM	        0x0E000000	// Cart RAM

#define SAVE_A_OFFSET       0x00000000 // Offset of Game Save A
#define SAVE_B_OFFSET       0x0000E000 // Offset of Game Save B

#define SECTION_ID_OFFSET   0x00000FF4
#define SAVE_INDEX_OFFSET   0x00000FFC

extern vu32 newest_save_offset;
extern vu32 memory_section_array[];
extern char mem_name;
extern u8 global_memory_buffer[0x1000];
extern rom_data curr_rom;

void initalize_memory_locations();
//bool insert_pokemon(Pokemon party_array[], int num);
void reverse_endian(u8 *data, size_t size);
void update_memory_buffer_checksum();
bool get_flag(u16 flag_id);


#endif