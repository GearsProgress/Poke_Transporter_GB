#include <tonc.h>
#include "save_data_manager.h"
#include "gba_flash.h"
#include "flash_mem.h"
#include "debug_mode.h"

int gamecode;
int version;

void load_gamecode()
{
    if (DEBUG_MODE)
    {
        gamecode = DEBUG_GAME;
        version = DEBUG_VERS;
    }
    else
    {
        gamecode = (*(vu8 *)(0x80000AC)) << 0x18 |
                   (*(vu8 *)(0x80000AD)) << 0x10 |
                   (*(vu8 *)(0x80000AE)) << 0x08 |
                   (*(vu8 *)(0x80000AF)) << 0x00;
        version = (*(vu8 *)(0x80000BC));
    }
}

void load_save_data()
{
    flash_read(HALL_OF_FAME + 0x1000, &global_memory_buffer[0], 0x1000);
}

void write_save_data()
{
    flash_write(HALL_OF_FAME + 0x1000, &global_memory_buffer[0], 0x1000);
}

bool is_caught(int dex_num)
{
    return (((global_memory_buffer[HOF_SECTION + CAUGHT_DATA + (dex_num / 8)]) >> dex_num % 8) & 1);
}

void set_caught(int dex_num)
{
    load_save_data();
    global_memory_buffer[HOF_SECTION + CAUGHT_DATA + (dex_num / 8)] = global_memory_buffer[HOF_SECTION + CAUGHT_DATA + (dex_num / 8)] | (1 << (dex_num % 8));
    write_save_data();
}

int get_gamecode(){
    return gamecode;
}

int get_version(){
    return version;
}
