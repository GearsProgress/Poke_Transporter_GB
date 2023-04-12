#ifndef MIRROR_H
#define MIRROR_H

#define MEM_CRAM	        0x0E000000	//!< Cart RAM

#define SAVE_A              0x00000000 //!< Offset of Game Save A
#define SAVE_B              0x0000E000 //!< Offset of Game Save A
//#define SAVE_RECENT         MEM_CRAM + (((*(vu32*)SAVE_A - *(vu32*)SAVE_B)>>1) & SAVE_B)
#define SAVE_RECENT         MEM_CRAM + (*(vu32*)SAVE_A)

#define SECTION_OFFSET      0x00000FFC

#define SAVE_INDEX_OFFSET   0x00000FFC

#endif