#include "dbg/debug_menu_functions.h"
#include "libraries/nanoprintf/nanoprintf.h"
#include "text_engine.h"
#include "pokemon_data.h"
#include "sprite_data.h"
#include "global_frame_controller.h"
#include "flash_mem.h"
#include "ptgb_save_data_manager.h"
#include "background_engine.h"
#include "libstd_replacements.h"
#include "sound.h"

void show_text_debug_screen(void *context, unsigned user_param)
{
    (void)context;
    (void)user_param;

    tte_set_ink(INK_DARK_GREY);
    BG_FLEX = (BG_FLEX & ~BG_PRIO_MASK) | BG_PRIO(3);
    text_loop(SCRIPT_DEBUG);
}

void show_debug_info_screen(void *context, unsigned user_param)
{
    (void)context;
    (void)user_param;

    char flags_hex_str[16];
    char def_lang_hex_str[16];
    char text_buffer[256];
    uint16_t charset[256];
    const char *game_code;
    u32 pkmn_flags = 0;

    load_localized_charset(charset, 3, ENGLISH);
    if (key_held(KEY_UP) && key_held(KEY_L) && key_held(KEY_R))
    {
        set_treecko(true);
    }

    bool e4_flag = read_flag(curr_GBA_rom.e4_flag);
    bool mg_flag = read_flag(curr_GBA_rom.mg_flag);
    bool all_collected_flag = read_flag(curr_GBA_rom.all_collected_flag);
    for (int i = 0; i < 30; i++)
    {
        pkmn_flags |= (read_flag(curr_GBA_rom.pkmn_collected_flag_start + i) << i);
    }

    bool tutorial = get_tutorial_flag();
    int def_lang = get_def_lang_num();

    switch (curr_GBA_rom.gamecode)
    {
    case RUBY_ID:
        game_code = "-R-";
        break;
    case SAPPHIRE_ID:
        game_code = "-S-";
        break;
    case FIRERED_ID:
        game_code = "-F-";
        break;
    case LEAFGREEN_ID:
        game_code = "-L-";
        break;
    case EMERALD_ID:
        game_code = "-E-";
        break;
    }

    n2hexstr(flags_hex_str, pkmn_flags);
    n2hexstr(def_lang_hex_str, def_lang);

    //create_textbox(4, 1, 160, 80, true);
    show_textbox();

    npf_snprintf(text_buffer, sizeof(text_buffer),
        "Debug info:\n\nG: %d%s%d\nF: %d%d%d-%s\nS:   %d-%s\n%s%s",
        curr_GBA_rom.language,
        game_code,
        curr_GBA_rom.version,
        e4_flag,
        mg_flag,
        all_collected_flag,
        flags_hex_str,
        tutorial,
        def_lang_hex_str,
        BUILD_INFO,
        get_treecko_enabled() ? ".T" : ""
    );

    ptgb_write_debug(charset, text_buffer, true);

    while (true)
    {
        if (key_hit(KEY_B))
        {
            hide_textbox();
            reload_textbox_background();
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