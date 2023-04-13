#ifndef MIRROR_H
#define MIRROR_H
#include <tonc.h>

#define MEM_CRAM	        0x0E000000	//!< Cart RAM

#define SAVE_A_OFFSET       0x00000000 //!< Offset of Game Save A
#define SAVE_B_OFFSET       0x0000E000 //!< Offset of Game Save B

#define SECTION_OFFSET      0x00000FFC

#define SAVE_INDEX_OFFSET   0x00000FFC

extern vu32 newest_save_offset;

void initalize_memory_locations();

#endif