#include <tonc.h>
#include "save_data_manager.h"
#include "gba_flash.h"
#include "flash_mem.h"

void load_save_data(){
    flash_read(HALL_OF_FAME + 0x1000, &global_memory_buffer[0], 0x1000);
}

void write_save_data(){
    flash_write(HALL_OF_FAME + 0x1000, &global_memory_buffer[0], 0x1000);
}

bool is_caught(int dex_num){
    return (((global_memory_buffer[HOF_SECTION + (dex_num / 8)]) >> dex_num % 8) & 1);
}

void set_caught(int dex_num){
    load_save_data();
    global_memory_buffer[HOF_SECTION + (dex_num / 8)] = global_memory_buffer[HOF_SECTION + (dex_num / 8)] | (1 << (dex_num % 8));
    write_save_data();
}

/* Data map:

Byte 0: Has made it through the tutorial
0 - 31: Caught data



*/