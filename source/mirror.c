#include <tonc.h>
#include "mirror.h"
#include "gba_flash.h"

vu32 newest_save_offset = MEM_CRAM + SAVE_A_OFFSET;

vu32 memory_section_array[14] = {};
u8 memory_buffer[0x1000];
vu8 pkmn[80] = {};

void initalize_memory_locations(){
    u8 save_A_index[4];
    u8 save_B_index[4];
    flash_read(MEM_CRAM + SAVE_A_OFFSET + SAVE_INDEX_OFFSET, &save_A_index[0], 0x04);
    flash_read(MEM_CRAM + SAVE_B_OFFSET + SAVE_INDEX_OFFSET, &save_B_index[0], 0x04);
    
    if(*(vu32*)save_B_index > *(vu32*)save_A_index){
        newest_save_offset = MEM_CRAM + SAVE_B_OFFSET;
    }
    for (vu32 i = 0; i < 14; i++){
        memory_section_array[*(vu8*)(newest_save_offset + (i * 0x1000) + SECTION_ID_OFFSET)] = newest_save_offset + (i * 0x1000);
    }

}

bool insert_pokemon(){
    flash_read(0x0E00D000, &memory_buffer[0], 0x1000);
    
    memory_buffer[4] = 0x0E;

    flash_write(0x0E00D000, &memory_buffer[0], 0x1000);
    return true;
}
