#ifndef DEBUG_MODE_H
#define DEBUG_MODE_H

#ifndef BUILD_INFO
#define BUILD_INFO "NaN"
#endif

#ifndef PTGB_BUILD_LANGUAGE
#define PTGB_BUILD_LANGUAGE 1
#endif

#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif

/**
 * @brief This structs contains debug options
 * that can be influenced through the debug menu.
 */
typedef struct debug_options
{
    bool print_link_data;
    bool instant_text_speed;
    bool ignore_game_pak;
    bool ignore_game_pak_sprites;
    bool ignore_link_cable;
    bool ignore_mg_e4_flags;
    bool ignore_unreceived_pkmn;
    bool force_tutorial;
    bool dont_hide_invalid_pkmn;
    bool ignore_dex_completion;
    bool force_all_caught;
    bool write_cable_data_to_save;
    bool display_control_char;
} debug_options;

extern debug_options g_debug_options;


// Options that affect and require payload_builder
// (and therefore can't be put in the debug menu)
#define SHOW_DATA_PACKETS (false && DEBUG_MODE)
#define PAYLOAD_EXPORT_TEST (false && DEBUG_MODE)
#define DEBUG_PAYLOADS (false && DEBUG_MODE)
#define DONT_REMOVE_PKMN (false && DEBUG_MODE)

// impractical to add to debug menu.
#define DONT_TRANSFER_POKEMON_AT_INDEX_X (false && DEBUG_MODE)
#define POKEMON_INDEX_TO_SKIP 5

// not sure if we want these in the debug menu.
#define DEBUG_GAME EMERALD_ID
#define DEBUG_VERS VERS_1_0
#define DEBUG_LANG LANG_ENG

// Compile time options
#define ENABLE_DEBUG_MENU true
#define ENABLE_TEXT_DEBUG_SCREEN true
#define USE_CUSTOM_MALLOC 1
// needs to be a value divisible by 4
#define CUSTOM_MALLOC_POOL_SIZE 8192

#endif