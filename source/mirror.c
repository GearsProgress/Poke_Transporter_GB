#include <tonc.h>
#include "mirror.h"

vu32 newest_save_offset;
int save_A_count = MEM_CRAM + SAVE_A_OFFSET + SAVE_INDEX_OFFSET;
int save_B_count = MEM_CRAM + SAVE_A_OFFSET + SAVE_INDEX_OFFSET;

void initalize_memory_locations(){
    newest_save_offset = save_A_count;
}
