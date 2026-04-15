#ifndef _DEBUG_MENU_FUNCTIONS_H
#define _DEBUG_MENU_FUNCTIONS_H

// Here we define debug menu callback functions, to be used as on_execute_callback or on_option_activate in the debug menu entries.

/**
 * @brief This function will open the text debug screen.
 */
void show_text_debug_screen(void *context, unsigned user_param);

/**
 * @brief This function will show the debug info screen, which contains various flags and info about the current game state.
 */
void show_debug_info_screen(void *context, unsigned user_param);

/**
 * @brief This generic boolean callback function can be used to set/unset any boolean flag.
 *
 * @param context a (bool *) pointer to the flag you want to set/unset.
 * @param user_param the value to set the flag to. 0 -> false, anything else -> true.
 */
void dbg_set_boolean_flag(void *context, unsigned user_param);

/**
 * @brief This function will take a song index and play the corresponding song.
 * If the index is UINT32_MAX, it will stop the music instead.
 */
void dbg_play_song(void *context, unsigned user_param);

/**
 * @brief This function will inject a Pokémon into the game.
 * (right now this is just Jirachi)
 */
void dbg_inject_pkmn(void *context, unsigned user_param);

void dbg_unlock_mystery(void *context, unsigned user_param);

#endif