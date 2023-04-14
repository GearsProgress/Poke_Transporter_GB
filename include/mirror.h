#ifndef MIRROR_H
#define MIRROR_H
#include <tonc.h>


#define MEM_CRAM	        0x0E000000	//!< Cart RAM

#define SAVE_A_OFFSET       0x00000000 //!< Offset of Game Save A
#define SAVE_B_OFFSET       0x0000E000 //!< Offset of Game Save B

#define SECTION_ID_OFFSET   0x00000FF4
#define SAVE_INDEX_OFFSET   0x00000FFC

extern vu32 newest_save_offset;
extern vu32 memory_section_array[14];
extern vu8 pkmn[80];

void initalize_memory_locations();
vu32 read_four_bytes(vu32 address, bool flip_endian);

#endif