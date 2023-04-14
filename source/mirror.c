#include <tonc.h>
#include "mirror.h"

vu32 newest_save_offset = MEM_CRAM + SAVE_A_OFFSET;
vu32 memory_section_array[14] = {};
vu32 pkmn[20] = {};

void initalize_memory_locations(){
    if(read_four_bytes(MEM_CRAM + SAVE_B_OFFSET + SAVE_INDEX_OFFSET, true) > read_four_bytes(MEM_CRAM + SAVE_A_OFFSET + SAVE_INDEX_OFFSET, true)){
        newest_save_offset = MEM_CRAM + SAVE_B_OFFSET;
    }
    for (vu32 i = 0; i < 14; i++){
        memory_section_array[*(vu8*)(newest_save_offset + (i * 0x1000) + SECTION_ID_OFFSET)] = newest_save_offset + (i * 0x1000);
    }

}

vu32 read_four_bytes(vu32 address, bool flip_endian){
    vu32 output = (*(vu8*)(address + 0) << (24 - (24 * flip_endian))) 
                + (*(vu8*)(address + 1) << (16 - (8  * flip_endian))) 
                + (*(vu8*)(address + 2) << (8  + (8  * flip_endian)))
                + (*(vu8*)(address + 3) << (0  + (24 * flip_endian)));
    return output;
}

void insert_pokemon(int box_num, int box_spot){
    
}
