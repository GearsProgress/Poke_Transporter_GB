#ifndef DEBUG_MODE_H
#define DEBUG_MODE_H

#define VERSION "v1.1.1"
#define PTGB_BUILD_LANGUAGE ENG_ID

#define DEBUG_MODE false

#define PRINT_LINK_DATA (false && DEBUG_MODE) // This is currently broken... not sure why
#define INSTANT_TEXT_SPEED (true && DEBUG_MODE)
#define IGNORE_GAME_PAK (true && DEBUG_MODE)
#define IGNORE_LINK_CABLE (false && DEBUG_MODE)
#define IGNORE_MG_E4_FLAGS (true && DEBUG_MODE)
#define IGNORE_UNRECEIVED_PKMN (true && DEBUG_MODE)
#define FORCE_TUTORIAL (false && DEBUG_MODE)
#define DONT_REMOVE_PKMN (true && DEBUG_MODE)
#define NO_INVALID_PKMN (false && DEBUG_MODE)
#define IGNORE_DEX_COMPLETION (false && DEBUG_MODE)
#define WRITE_CABLE_DATA_TO_SAVE (true && DEBUG_MODE)
#define SHOW_DATA_PACKETS (true && DEBUG_MODE)

#define DEBUG_GAME EMERALD_ID
#define DEBUG_VERS VERS_1_0
#define DEBUG_LANG LANG_ENG

#define ENABLE_MATCH_PID true
#define ENABLE_OLD_EVENT false
#define ENABLE_DEBUG_SCREEN true

#endif