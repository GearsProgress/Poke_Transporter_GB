#include "dbg/debug_menu_functions.h"
#include "libraries/nanoprintf/nanoprintf.h"
#include "text_engine.h"
#include "pokemon_data.h"
#include "sprite_data.h"
#include "global_frame_controller.h"
#include "flash_mem.h"
#include "save_data_manager.h"
#include "background_engine.h"
#include "libstd_replacements.h"
#include "sound.h"

void show_text_debug_screen(void *context, unsigned user_param)
{
    (void)context;
    (void)user_param;

    tte_set_ink(INK_DARK_GREY);
    REG_BG1CNT = (REG_BG1CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
    obj_hide_multi(ptgb_logo_l, 2);
    text_loop(SCRIPT_DEBUG);
}

void show_debug_info_screen(void *context, unsigned user_param)
{
    (void)context;
    (void)user_param;

    char hexBuffer[16];
    uint16_t charset[256];
    load_localized_charset(charset, 3, ENGLISH);
    if (key_held(KEY_UP) && key_held(KEY_L) && key_held(KEY_R))
    {
        set_treecko(true);
    }
    u32 pkmn_flags = 0;
    bool e4_flag = read_flag(curr_GBA_rom.e4_flag);
    bool mg_flag = read_flag(curr_GBA_rom.mg_flag);
    bool all_collected_flag = read_flag(curr_GBA_rom.all_collected_flag);
    for (int i = 0; i < 30; i++)
    {
        pkmn_flags |= (read_flag(curr_GBA_rom.pkmn_collected_flag_start + i) << i);
    }

    bool tutorial = get_tutorial_flag();
    int def_lang = get_def_lang_num();

    create_textbox(4, 1, 160, 80, true);
    show_text_box();
    ptgb_write_debug(charset, "Debug info:\n\nG: ", true);
    ptgb_write_debug(charset, ptgb::to_string(curr_GBA_rom.language), true);
    switch (curr_GBA_rom.gamecode)
    {
    case RUBY_ID:
        ptgb_write_debug(charset, "-R-", true);
        break;
    case SAPPHIRE_ID:
        ptgb_write_debug(charset, "-S-", true);
        break;
    case FIRERED_ID:
        ptgb_write_debug(charset, "-F-", true);
        break;
    case LEAFGREEN_ID:
        ptgb_write_debug(charset, "-L-", true);
        break;
    case EMERALD_ID:
        ptgb_write_debug(charset, "-E-", true);
        break;
    }

    ptgb_write_debug(charset, ptgb::to_string(curr_GBA_rom.version), true);

    ptgb_write_debug(charset, "\nF: ", true);
    ptgb_write_debug(charset, ptgb::to_string(e4_flag), true);
    ptgb_write_debug(charset, ptgb::to_string(mg_flag), true);
    ptgb_write_debug(charset, ptgb::to_string(all_collected_flag), true);
    ptgb_write_debug(charset, "-", true);

    n2hexstr(hexBuffer, pkmn_flags);
    ptgb_write_debug(charset, hexBuffer, true);
    ptgb_write_debug(charset, "\nS:   ", true);
    ptgb_write_debug(charset, ptgb::to_string(tutorial), true);
    ptgb_write_debug(charset, "-", true);
    n2hexstr(hexBuffer, def_lang);
    ptgb_write_debug(charset, hexBuffer, true);

    ptgb_write_debug(charset, "\n", true);
    ptgb_write_debug(charset, BUILD_INFO, true);
    if (get_treecko_enabled())
    {
        ptgb_write_debug(charset, ".T", true);
    }
    while (true)
    {
        if (key_hit(KEY_B))
        {
            hide_text_box();
            reset_textbox();
            return;
        }
        global_next_frame();
    }
}

void dbg_set_boolean_flag(void *context, unsigned user_param)
{
    bool *flag_ptr = (bool*)context;
    *flag_ptr = (user_param != 0);
}

void dbg_play_song(void *context, unsigned user_param)
{
    if(user_param == UINT32_MAX)
    {
        stop_song();
        return;
    }
    play_song(user_param, true);
}