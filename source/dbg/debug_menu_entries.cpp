#include "dbg/debug_menu.h"
#include "dbg/debug_menu_entries.h"
#include "dbg/debug_menu_functions.h"
#include "dbg/debug_mode.h"
#include "soundbank.h"
#include "vertical_menu.h"

#include <cstdlib>

static const option_data toggle_options[2] = {
    {
        .text = "Off",
        .value = 0
    },
    {
        .text = "On",
        .value = 1
    }
};

/**
 * @brief This helper function makes it easy to define a multiple choice debug row.
 */
static debug_menu_row_widget* __attribute__((noinline)) define_debug_choice_row(const u16 *charset, const char *labelText, on_execute_callback option_activate_callback, const option_data *options_metadata, u8 num_options, bool should_delete_options, u8 default_option_index, void *context)
{
    const debug_menu_row_data row_data = {
        .charset = charset,
        .labelText = labelText,
        .option_section = {
            .num_options = num_options,
            .options = options_metadata,
            .on_option_activate = option_activate_callback,
            .selected_option_index = default_option_index,
            .should_free_on_destruct = should_delete_options
        },
        .on_execute = nullptr,
        .context = context,
        .user_param = 0
    };
    return new debug_menu_row_widget(row_data);
}

/**
 * @brief This helper function makes it easy to define a toggle row.
 */
static debug_menu_row_widget* define_toggle_row(const u16 *charset, const char* labelText, on_execute_callback on_toggle_callback, bool default_value, void *context)
{
    return define_debug_choice_row(charset, labelText, on_toggle_callback, toggle_options, 2, false, default_value ? 1 : 0, context);
}

/**
 * @brief This helper function will define the song row, which will let you toggle between any available maxmod song or None at all.
 */
static debug_menu_row_widget* __attribute__((noinline)) define_song_row(const u16 *charset, const char* labelText)
{
    option_data *song_options = (option_data*)malloc(sizeof(option_data) * (MSL_NSONGS + 1));
    song_options[0] = {
        .text = "None",
        .value = UINT32_MAX
    };

    for(unsigned i = 0; i < MSL_NSONGS; ++i)
    {
        song_options[i + 1] = {
            .text = nullptr,
            .value = i
        };
    }

    return define_debug_choice_row(charset, labelText, dbg_play_song, song_options,  MSL_NSONGS + 1, true, 0, nullptr);
}

/**
 * @brief This helper function makes it easy to define a row that executes a function when you select it and press A.
 */
static debug_menu_row_widget* __attribute__((noinline)) define_executable_row(const u16 *charset, const char* labelText, on_execute_callback on_execute, unsigned user_param, void *context)
{
    const debug_menu_row_data row_data = {
        .charset = charset,
        .labelText = labelText,
        .option_section = {
            .num_options = 0,
            .options = nullptr,
            .on_option_activate = nullptr,
            .selected_option_index = 0,
            .should_free_on_destruct = false
        },
        .on_execute = on_execute,
        .context = context,
        .user_param = user_param
    };
    return new debug_menu_row_widget(row_data);
}

// Here we define the actual entries of the debug menu, using the helper functions defined above.
void fill_debug_menu_with_entries(vertical_menu &menu, u16 *charset)
{
    i_item_widget* item_widgets[] = {
#if ENABLE_TEXT_DEBUG_SCREEN
        define_executable_row(charset, "Text Debug", show_text_debug_screen, 0, nullptr),
#endif
        define_executable_row(charset, "Info", show_debug_info_screen, 0, nullptr),
#if ENABLE_DEBUG_PKMN_INJECTION
        define_executable_row(charset, "Inject Celebi", dbg_inject_pkmn, 0, nullptr),
#endif
        define_song_row(charset, "Song"),
        define_toggle_row(charset, "Print Link", dbg_set_boolean_flag, g_debug_options.print_link_data, &g_debug_options.print_link_data),
        define_toggle_row(charset, "Instant Text", dbg_set_boolean_flag, g_debug_options.instant_text_speed, &g_debug_options.instant_text_speed),
        define_toggle_row(charset, "Ign Cart", dbg_set_boolean_flag, g_debug_options.ignore_game_pak, &g_debug_options.ignore_game_pak),
        define_toggle_row(charset, "Ign Sprites", dbg_set_boolean_flag, g_debug_options.ignore_game_pak_sprites, &g_debug_options.ignore_game_pak_sprites),
        define_toggle_row(charset, "Ign Link", dbg_set_boolean_flag, g_debug_options.ignore_link_cable, &g_debug_options.ignore_link_cable),
        define_toggle_row(charset, "Ign MG/E4", dbg_set_boolean_flag, g_debug_options.ignore_mg_e4_flags, &g_debug_options.ignore_mg_e4_flags),
        define_toggle_row(charset, "Ign Unrec PKMN", dbg_set_boolean_flag, g_debug_options.ignore_unreceived_pkmn, &g_debug_options.ignore_unreceived_pkmn),
        define_toggle_row(charset, "Force Tut", dbg_set_boolean_flag, g_debug_options.force_tutorial, &g_debug_options.force_tutorial),
        define_toggle_row(charset, "Show Invalid", dbg_set_boolean_flag, g_debug_options.dont_hide_invalid_pkmn, &g_debug_options.dont_hide_invalid_pkmn),
        define_toggle_row(charset, "Ign Dex Compl", dbg_set_boolean_flag, g_debug_options.ignore_dex_completion, &g_debug_options.ignore_dex_completion),
        define_toggle_row(charset, "Force Caught", dbg_set_boolean_flag, g_debug_options.force_all_caught, &g_debug_options.force_all_caught),
        define_toggle_row(charset, "Write Cbl Data", dbg_set_boolean_flag, g_debug_options.write_cable_data_to_save, &g_debug_options.write_cable_data_to_save),
        define_toggle_row(charset, "Disp CtrlChr", dbg_set_boolean_flag, g_debug_options.display_control_char, &g_debug_options.display_control_char)
    };

    menu.add_item_widgets(item_widgets, sizeof(item_widgets) / sizeof(item_widgets[0]));
}