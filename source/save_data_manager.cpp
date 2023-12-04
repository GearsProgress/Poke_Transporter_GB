#include <tonc.h>
#include "save_data_manager.h"
#include "flash_mem.h"
#include "debug_mode.h"
#include "main_menu.h"
#include "pokemon_data.h"
#include "save.h"


byte save_data_array[SAVE_DATA_SIZE];

void load_custom_save_data()
{
    copy_save_to_ram(HALL_OF_FAME + 0x1000, &global_memory_buffer[0], 0x1000);
    for (int i = 0; i < SAVE_DATA_SIZE; i++)
    {
        save_data_array[i] = global_memory_buffer[HOF_SECTION + i];
    }
}

void write_custom_save_data()
{
    copy_save_to_ram(HALL_OF_FAME + 0x1000, &global_memory_buffer[0], 0x1000);
    for (int i = 0; i < SAVE_DATA_SIZE; i++)
    {
        global_memory_buffer[HOF_SECTION + i] = save_data_array[i];
    }
    update_memory_buffer_checksum(true);
    erase_sector(HALL_OF_FAME + 0x1000);
    copy_ram_to_save(&global_memory_buffer[0], HALL_OF_FAME + 0x1000, 0x1000);
}

bool is_caught(int dex_num)
{
    return (((save_data_array[CAUGHT_DATA + (dex_num / 8)]) >> dex_num % 8) & 1);
}

void set_caught(int dex_num)
{
    save_data_array[CAUGHT_DATA + (dex_num / 8)] = save_data_array[CAUGHT_DATA + (dex_num / 8)] | (1 << (dex_num % 8));
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

int get_def_lang_num()
{
    return save_data_array[DEFAULT_LANGUAGE];
}

void set_def_lang(int nLang)
{
    save_data_array[DEFAULT_LANGUAGE] = nLang;
}

void set_tutorial_flag(bool value)
{
    save_data_array[TUTORIAL_FLAG] = value;
}

bool get_tutorial_flag()
{
    return save_data_array[TUTORIAL_FLAG];
}

void initalize_save_data()
{
    for (int i = 0; i < SAVE_DATA_SIZE; i++)
    {
        save_data_array[i] = 0;
    }
    write_custom_save_data();
}