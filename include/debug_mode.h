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

#define PRINT_LINK_DATA (false && DEBUG_MODE)
#define INSTANT_TEXT_SPEED (false && DEBUG_MODE)
#define IGNORE_GAME_PAK (true && DEBUG_MODE)
#define IGNORE_GAME_PAK_SPRITES (false && DEBUG_MODE)
#define IGNORE_LINK_CABLE (true && DEBUG_MODE)
#define IGNORE_MG_E4_FLAGS (true && DEBUG_MODE)
#define IGNORE_UNRECEIVED_PKMN (false && DEBUG_MODE)
#define FORCE_TUTORIAL (false && DEBUG_MODE)
#define DONT_REMOVE_PKMN (false && DEBUG_MODE)
#define DONT_HIDE_INVALID_PKMN (false && DEBUG_MODE)
#define IGNORE_DEX_COMPLETION (false && DEBUG_MODE)
#define FORCE_ALL_CAUGHT (true && DEBUG_MODE)
#define WRITE_CABLE_DATA_TO_SAVE (false && DEBUG_MODE)
#define SHOW_DATA_PACKETS (false && DEBUG_MODE)
#define DISPLAY_CONTROL_CHAR (false && DEBUG_MODE)
#define PAYLOAD_EXPORT_TEST (false && DEBUG_MODE)
#define DONT_TRANSFER_POKEMON_AT_INDEX_X (false && DEBUG_MODE)
#define POKEMON_INDEX_TO_SKIP 5
#define ENABLE_TEXT_DEBUG_SCREEN (true && DEBUG_MODE)
#define DEBUG_PAYLOADS (false && DEBUG_MODE)


#define DEBUG_GAME EMERALD_ID
#define DEBUG_VERS VERS_1_0
#define DEBUG_LANG LANG_ENG

#define ENABLE_MATCH_PID true
#define ENABLE_DEBUG_SCREEN true

#define USE_CUSTOM_MALLOC 1
// needs to be a value divisible by 4
#define CUSTOM_MALLOC_POOL_SIZE 8192

#endif