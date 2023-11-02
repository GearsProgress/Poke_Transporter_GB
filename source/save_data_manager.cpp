#include <tonc.h>
#include "save_data_manager.h"
#include "gba_flash.h"
#include "flash_mem.h"
#include "debug_mode.h"
#include "main_menu.h"
#include "pokemon_data.h"

int gamecode;
int version;
byte save_data_array[SAVE_DATA_SIZE];

void load_gamecode()
{
    if (DEBUG_MODE)
    {
        gamecode = DEBUG_GAME;
        version = DEBUG_VERS;
    }
    else
    {
        gamecode = (*(vu8 *)(0x80000AC)) << 0x10 |
                   (*(vu8 *)(0x80000AD)) << 0x08 |
                   (*(vu8 *)(0x80000AE)) << 0x00;
        version = (*(vu8 *)(0x80000BC));
    }
}

void load_save_data()
{
    flash_read(HALL_OF_FAME + 0x1000, &global_memory_buffer[0], 0x1000);
    for (int i = 0; i < SAVE_DATA_SIZE; i++)
    {
        save_data_array[i] = global_memory_buffer[HOF_SECTION + i];
    }
}

void write_save_data()
{
    for (int i = 0; i < SAVE_DATA_SIZE; i++)
    {
        global_memory_buffer[HOF_SECTION + i] = save_data_array[i];
    }
    flash_write(HALL_OF_FAME + 0x1000, &global_memory_buffer[0], 0x1000);
}

bool is_caught(int dex_num)
{
    return (((save_data_array[CAUGHT_DATA + (dex_num / 8)]) >> dex_num % 8) & 1);
}

void set_caught(int dex_num)
{
    load_save_data();
    save_data_array[CAUGHT_DATA + (dex_num / 8)] = global_memory_buffer[HOF_SECTION + CAUGHT_DATA + (dex_num / 8)] | (1 << (dex_num % 8));
}

int get_def_lang()
{
    switch (save_data_array[DEFAULT_LANGUAGE])
    {
    case BTN_ENG:
        return ENG_ID;
    case BTN_FRE:
        return FRE_ID;
    case BTN_ITA:
        return ITA_ID;
    case BTN_GER:
        return GER_ID;
    case BTN_SPA:
        return SPA_ID;
    case BTN_KOR:
        return KOR_ID;
    default:
        return ENG_ID;
    }
}

void set_def_lang(int nLang)
{
    save_data_array[DEFAULT_LANGUAGE] = nLang;
}

int get_gamecode()
{
    return gamecode;
}

int get_version()
{
    return version;
}