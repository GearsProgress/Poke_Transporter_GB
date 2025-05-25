#include "script_array.h"
#include "button_menu.h"
#include "text_engine.h"
#include "mystery_gift_injector.h"
#include "sprite_data.h"
#include "flash_mem.h"
#include "pokemon_data.h"
#include "mystery_gift_builder.h"
#include "global_frame_controller.h"
#include "box_menu.h"
#include <tonc.h>
#include "background_engine.h"
#include "select_menu.h"
#include "translated_text.h"

int last_error;
Pokemon_Party party_data;

Select_Menu langs(false, LANG_MENU, 18, 0);
Select_Menu games(false, CART_MENU, 18, 0);
Box_Menu box_viewer;

// For documentation purposes, here's an overview of the categories of the transfer script:
// -------- TRANSFER SCRIPT --------
//
// Check that the conditions are set for the transfer
// T_SCRIPT_START
// COND_TUTORIAL_COMPLETE
// DIA_OPEN
// CMD_SET_TUTOR_TRUE
// COND_BEAT_E4
// DIA_E4
// COND_MG_ENABLED
// COND_IS_FRLGE
// DIA_MG_FRLGE
// DIA_MG_RS
// COND_MG_OTHER_EVENT
// COND_PKMN_TO_COLLECT
// DIA_MG_OTHER_EVENT
// DIA_PKMN_TO_COLLECT
//
// Ask the user what game and language they're using
// DIA_WHAT_GAME_TRANS
// CMD_GAME_MENU
// DIA_WHAT_LANG_TRANS
// CMD_LANG_MENU
// DIA_ASK_QUEST
// CMD_SLIDE_PROF_LEFT
// CMD_SLIDE_PROF_RIGHT
// COND_GB_ROM_EXISTS
// DIA_NO_GB_ROM
// DIA_MENU_BACK
//
// Initiate the transfer and check for errors
// DIA_LETS_START
// DIA_START
// CMD_START_LINK
// COND_ERROR_TIMEOUT_ONE
// DIA_ERROR_TIME_ONE
// COND_ERROR_TIMEOUT_TWO
// DIA_ERROR_TIME_TWO
// COND_ERROR_COM_ENDED
// DIA_ERROR_COM_ENDED
// COND_ERROR_COLOSSEUM
// DIA_ERROR_COLOSSEUM
// COND_ERROR_DISCONNECT
// DIA_ERROR_DISCONNECT
//
// Pause the transfer and show the user their box data
// CMD_LOAD_SIMP
// DIA_NO_VALID_PKMN
// COND_SOME_INVALID_PKMN
// DIA_SOME_INVALID_PKMN
// COND_CHECK_MYTHIC
// DIA_MYTHIC_CONVERT
// CMD_MYTHIC_MENU
// COND_CHECK_MISSINGNO
// DIA_IS_MISSINGNO
// DIA_IN_BOX
// CMD_BOX_MENU
// DIA_CANCEL
// CMD_IMPORT_POKEMON
// CMD_CONTINUE_LINK
// CMD_CANCEL_LINK
// CMD_END_MISSINGNO
//
// Complete the transfer and give messages based on the transfered Pokemon
// DIA_TRANS_GOOD
// COND_NEW_POKEMON
// DIA_NEW_DEX
// DIA_NO_NEW_DEX
// COND_IS_HOENN_RS
// COND_IS_HOENN_E
// DIA_SEND_FRIEND_HOENN_RS
// DIA_SEND_FRIEND_HOENN_E
// DIA_SEND_FRIEND_KANTO
// DIA_THANK
//
// Hide the dialogue and professor
// CMD_END_SCRIPT
// CMD_BACK_TO_MENU

// The array below is exactly in order of the DIA, commands and condition int values
// So if adding a new dia, command or condition, make sure to add it in the right position/index.
// defining it this way does not generate an expensive function. It's all stored as read-only data in EWRAM.
const script_obj_params transfer_script_params[SCRIPT_SIZE] = {
    // DIA_OPEN
    {
        .text_entry_index = DIA_OPEN,
        .next_if_true = CMD_SET_TUTOR_TRUE
    },
    // DIA_E4
    {
        .text_entry_index = DIA_E4,
        .next_if_true = CMD_END_SCRIPT
    },
    // DIA_MG_FRLGE
    {
        .text_entry_index = DIA_MG_FRLGE,
        .next_if_true = CMD_END_SCRIPT
    },
    // DIA_MG_RS
    {
        .text_entry_index = DIA_MG_RS,
        .next_if_true = CMD_END_SCRIPT
    },
    // DIA_LETS_START
    {
        .text_entry_index = DIA_LETS_START,
        .next_if_true = DIA_START
    },
    // DIA_START
    {
        .text_entry_index = DIA_START,
        .next_if_true = CMD_START_LINK
    },
    // DIA_TRANS_GOOD
    {
        .text_entry_index = DIA_TRANS_GOOD,
        .next_if_true = COND_NEW_POKEMON
    },
    // DIA_NEW_DEX
    {
        .text_entry_index = DIA_NEW_DEX,
        .next_if_true = COND_IS_HOENN_RS
    },
    // DIA_NO_NEW_DEX
    {
        .text_entry_index = DIA_NO_NEW_DEX,
        .next_if_true = COND_IS_HOENN_RS
    },
    // DIA_SEND_FRIEND_KANTO
    {
        .text_entry_index = DIA_SEND_FRIEND_KANTO,
        .next_if_true = DIA_THANK
    },
    // DIA_SEND_FRIEND_HOENN_RS
    {
        .text_entry_index = DIA_SEND_FRIEND_HOENN_RS,
        .next_if_true = DIA_THANK
    },
    // DIA_SEND_FRIEND_HOENN_E
    {
        .text_entry_index = DIA_SEND_FRIEND_HOENN_E,
        .next_if_true = DIA_THANK
    },
    // DIA_THANK
    {
        .text_entry_index = DIA_THANK,
        .next_if_true = CMD_END_SCRIPT
    },
    // DIA_GET_MON (unused)
    {
        .text_entry_index = DIA_GET_MON,
        .next_if_true = CMD_END_SCRIPT
    },
    // DIA_MG_OTHER_EVENT
    {
        .text_entry_index = DIA_MG_OTHER_EVENT,
        .next_if_true = DIA_ASK_QUEST
    },
    // DIA_PKMN_TO_COLLECT
    {
        .text_entry_index = DIA_PKMN_TO_COLLECT,
        .next_if_true = CMD_END_SCRIPT
    },
    // DIA_NO_VALID_PKMN
    {
        .text_entry_index = DIA_NO_VALID_PKMN,
        .next_if_true = CMD_CANCEL_LINK
    },
    // DIA_ASK_QUEST
    {
        .text_entry_index = DIA_ASK_QUEST,
        .next_if_true = CMD_SLIDE_PROF_LEFT
    },
    // DIA_WHAT_GAME_TRANS
    {
        .text_entry_index = DIA_WHAT_GAME_TRANS,
        .next_if_true = CMD_GAME_MENU
    },
    // DIA_WHAT_LANG_TRANS
    {
        .text_entry_index = DIA_WHAT_LANG_TRANS,
        .next_if_true = CMD_LANG_MENU
    },
    // DIA_NO_GB_ROM
    {
        .text_entry_index = DIA_NO_GB_ROM,
        .next_if_true = DIA_WHAT_LANG_TRANS
    },
    // DIA_IN_BOX
    {
        .text_entry_index = DIA_IN_BOX,
        .next_if_true = CMD_BOX_MENU
    },
    // DIA_MYTHIC_CONVERT
    {
        .text_entry_index = DIA_MYTHIC_CONVERT,
        .next_if_true = CMD_MYTHIC_MENU
    },
    // DIA_CANCEL
    {
        .text_entry_index = DIA_CANCEL,
        .next_if_true = CMD_CANCEL_LINK
    },
    // DIA_SOME_INVALID_PKMN
    {
        .text_entry_index = DIA_SOME_INVALID_PKMN,
        .next_if_true = COND_CHECK_MYTHIC
    },
    // DIA_MENU_BACK
    {
        .text_entry_index = DIA_MENU_BACK,
        .next_if_true = CMD_END_SCRIPT
    },
    // DIA_IS_MISSINGNO
    {
        .text_entry_index = DIA_IS_MISSINGNO,
        .next_if_true = DIA_IN_BOX
    },
    // DIA_ERROR_COLOSSEUM
    {
        .text_entry_index = DIA_ERROR_COLOSSEUM,
        .next_if_true = DIA_START
    },
    // DIA_ERROR_COM_ENDED
    {
        .text_entry_index = DIA_ERROR_COM_ENDED,
        .next_if_true = DIA_START
    },
    // DIA_ERROR_DISCONNECT
    {
        .text_entry_index = DIA_ERROR_DISCONNECT,
        .next_if_true = DIA_START
    },
    // DIA_ERROR_TIME_ONE
    {
        .text_entry_index = DIA_ERROR_TIME_ONE,
        .next_if_true = DIA_START
    },
    // DIA_ERROR_TIME_TWO
    {
        .text_entry_index = DIA_ERROR_TIME_TWO,
        .next_if_true = DIA_START
    },
    // DIA_WHAT_LANG_EVENT
    {
        .text_entry_index = DIA_WHAT_LANG_EVENT,
        .next_if_true = CMD_LANG_MENU
    },
    // DIA_WHAT_GAME_EVENT
    {
        .text_entry_index = DIA_WHAT_GAME_EVENT,
        .next_if_true = CMD_GAME_MENU
    },
    // DIA_K_DEX_NOT_FULL
    {
        .text_entry_index = DIA_K_DEX_NOT_FULL,
        .next_if_true = CMD_END_SCRIPT
    },
    // DIA_J_DEX_NOT_FULL
    {
        .text_entry_index = DIA_J_DEX_NOT_FULL,
        .next_if_true = CMD_END_SCRIPT
    },
    // T_SCRIPT_START
    {
        .conditional_index = CMD_SHOW_PROF,
        .next_if_true = COND_TUTORIAL_COMPLETE
    },
    // E_SCRIPT_START
    {
        .conditional_index = CMD_SHOW_PROF,
        .next_if_true = DIA_ASK_QUEST
    },
    // CMD_START_LINK
    {
        .conditional_index = CMD_START_LINK,
        .next_if_true = COND_ERROR_TIMEOUT_ONE
    },
    // CMD_IMPORT_POKEMON
    {
        .conditional_index = CMD_IMPORT_POKEMON,
        .next_if_true = CMD_CONTINUE_LINK
    },
    // CMD_BACK_TO_MENU
    {
        .conditional_index = CMD_BACK_TO_MENU,
        .next_if_true = T_SCRIPT_START
    },
    // CMD_SHOW_PROF (unused in this manner (not used in a next_if_true). Therefore this is a dummy entry)
    // we even need to define such unused values to keep the array element positions in order
    {
    },
    // CMD_HIDE_PROF (unused in this manner (not used in a next_if_true). Therefore this is a dummy entry)
    {
    },
    // CMD_SET_TUTOR_TRUE
    {
        .conditional_index = CMD_SET_TUTOR_TRUE,
        .next_if_true = CMD_END_SCRIPT
    },
    // CMD_END_SCRIPT
    {
        .conditional_index = CMD_END_SCRIPT,
        .next_if_true = CMD_BACK_TO_MENU
    },
    // CMD_GAME_MENU
    {
        .conditional_index = CMD_GAME_MENU,
        .next_if_true = COND_GB_ROM_EXISTS,
        .next_if_false = DIA_WHAT_LANG_TRANS
    },
    // CMD_LANG_MENU
    {
        .conditional_index = CMD_LANG_MENU,
        .next_if_true = DIA_WHAT_GAME_TRANS
    },
    // CMD_SLIDE_PROF_LEFT
    {
        .conditional_index = CMD_SLIDE_PROF_LEFT,
        .next_if_true = DIA_WHAT_LANG_TRANS
    },
    // CMD_SLIDE_PROF_RIGHT
    {
        .conditional_index = CMD_SLIDE_PROF_RIGHT,
        .next_if_true = DIA_LETS_START
    },
    // CMD_CONTINUE_LINK
    {
        .conditional_index = CMD_CONTINUE_LINK,
        .next_if_true = CMD_END_MISSINGNO
    },
    // CMD_BOX_MENU
    {
        .conditional_index = CMD_BOX_MENU,
        .next_if_true = CMD_IMPORT_POKEMON,
        .next_if_false = DIA_CANCEL
    },
    // CMD_MYTHIC_MENU
    {
        .conditional_index = CMD_MYTHIC_MENU,
        .next_if_true = COND_CHECK_MISSINGNO
    },
    // CMD_LOAD_SIMP
    {
        .conditional_index = CMD_LOAD_SIMP,
        .next_if_true = COND_SOME_INVALID_PKMN,
        .next_if_false = DIA_NO_VALID_PKMN
    },
    // CMD_CANCEL_LINK
    {
        .conditional_index = CMD_CANCEL_LINK,
        .next_if_true = CMD_END_SCRIPT
    },
    // CMD_END_MISSINGNO
    {
        .conditional_index = CMD_END_MISSINGNO,
        .next_if_true = DIA_TRANS_GOOD
    },
    // COND_ERROR_TIMEOUT_ONE
    {
        .conditional_index = COND_ERROR_TIMEOUT_ONE,
        .next_if_true = COND_ERROR_TIMEOUT_TWO,
        .next_if_false = DIA_ERROR_TIME_ONE
    },
    // COND_ERROR_DISCONNECT
    {
        .conditional_index = COND_ERROR_DISCONNECT,
        .next_if_true = CMD_LOAD_SIMP,
        .next_if_false = DIA_ERROR_DISCONNECT
    },
    // COND_ERROR_COM_ENDED
    {
        .conditional_index = COND_ERROR_COM_ENDED,
        .next_if_true = COND_ERROR_COLOSSEUM,
        .next_if_false = DIA_ERROR_COM_ENDED
    },
    // COND_ERROR_TIMEOUT_TWO
    {
        .conditional_index = COND_ERROR_TIMEOUT_TWO,
        .next_if_true = COND_ERROR_COM_ENDED,
        .next_if_false = DIA_ERROR_TIME_TWO
    },
    // COND_ERROR_COLOSSEUM
    {
        .conditional_index = COND_ERROR_COLOSSEUM,
        .next_if_true = COND_ERROR_DISCONNECT,
        .next_if_false = DIA_ERROR_COLOSSEUM
    },
    // COND_BEAT_E4
    {
        .conditional_index = COND_BEAT_E4,
        .next_if_true = COND_MG_ENABLED,
        .next_if_false = DIA_E4
    },
    // COND_MG_ENABLED
    {
        .conditional_index = COND_MG_ENABLED,
        .next_if_true = COND_MG_OTHER_EVENT,
        .next_if_false = COND_IS_FRLGE
    },
    // COND_TUTORIAL_COMPLETE
    {
        .conditional_index = COND_TUTORIAL_COMPLETE,
        .next_if_true = COND_BEAT_E4,
        .next_if_false = DIA_OPEN
    },
    // COND_NEW_POKEMON
    {
        .conditional_index = COND_NEW_POKEMON,
        .next_if_true = DIA_NEW_DEX,
        .next_if_false = DIA_NO_NEW_DEX
    },
    // COND_IS_HOENN_RS
    {
        .conditional_index = COND_IS_HOENN_RS,
        .next_if_true = DIA_SEND_FRIEND_HOENN_RS,
        .next_if_false = DIA_SEND_FRIEND_KANTO
    },
    // COND_IS_FRLGE
    {
        .conditional_index = COND_IS_FRLGE,
        .next_if_true = DIA_MG_FRLGE,
        .next_if_false = DIA_MG_RS
    },
    // COND_MG_OTHER_EVENT
    {
        .conditional_index = COND_MG_OTHER_EVENT,
        .next_if_true = DIA_MG_OTHER_EVENT,
        .next_if_false = COND_PKMN_TO_COLLECT
    },
    // COND_PKMN_TO_COLLECT
    {
        .conditional_index = COND_PKMN_TO_COLLECT,
        .next_if_true = DIA_PKMN_TO_COLLECT,
        .next_if_false = DIA_ASK_QUEST
    },
    // COND_GB_ROM_EXISTS
    {
        .conditional_index = COND_GB_ROM_EXISTS,
        .next_if_true = CMD_SLIDE_PROF_RIGHT,
        .next_if_false = DIA_NO_GB_ROM
    },
    // COND_CHECK_MYTHIC
    {
        .conditional_index = COND_CHECK_MYTHIC,
        .next_if_true = DIA_MYTHIC_CONVERT,
        .next_if_false = COND_CHECK_MISSINGNO
    },
    // COND_CHECK_DEX
    {
        .conditional_index = COND_CHECK_DEX,
        .next_if_true = 0,
        .next_if_false = COND_CHECK_KANTO
    },
    // COND_CHECK_KANTO
    {
        .conditional_index = COND_CHECK_KANTO,
        .next_if_true = DIA_K_DEX_NOT_FULL,
        .next_if_false = DIA_J_DEX_NOT_FULL
    },
    // COND_SOME_INVALID_PKMN
    {
        .conditional_index = COND_SOME_INVALID_PKMN,
        .next_if_true = DIA_SOME_INVALID_PKMN,
        .next_if_false = COND_CHECK_MYTHIC
    },
    // COND_IS_HOENN_E
    {
        .conditional_index = COND_IS_HOENN_E,
        .next_if_true = DIA_SEND_FRIEND_HOENN_E,
        .next_if_false = DIA_SEND_FRIEND_KANTO
    },
    // COND_CHECK_MISSINGNO
    {
        .conditional_index = COND_CHECK_MISSINGNO,
        .next_if_true = DIA_IS_MISSINGNO,
        .next_if_false = DIA_IN_BOX
    }
};

// For documentation purposes, here's an overview of the categories of the events script:
// -------- EVENTS SCRIPT --------
// Start the dialogue and show the menu
// E_SCRIPT_START
// DIA_ASK_QUEST
//
// Ask the user what game and language they're using
// DIA_WHAT_GAME_EVENT
// CMD_GAME_MENU
// DIA_WHAT_LANG_EVENT
// CMD_LANG_MENU
// DIA_ASK_QUEST
// CMD_SLIDE_PROF_LEFT
// CMD_SLIDE_PROF_RIGHT
// COND_GB_ROM_EXISTS
// DIA_NO_GB_ROM
//
// Check the player's dex
// COND_CHECK_DEX
// COND_CHECK_KANTO
// DIA_K_DEX_NOT_FULL
// DIA_J_DEX_NOT_FULL
//
// Hide the dialogue and professor
// CMD_END_SCRIPT
// CMD_BACK_TO_MENU

// The array below is exactly in order of the DIA, commands and condition int values
// So if adding a new dia, command or condition, make sure to add it in the right position/index.
// because things are in order, it also means we have to define every possible entry even if we don't use it.
// defining it this way does not generate an expensive function. It's all stored as read-only data in EWRAM.
// Although frankly given the small amount of defined entries, we ARE wasting a lot of space with this one. (probably around 500 bytes)
const script_obj_params event_script_params[SCRIPT_SIZE] = {
    {}, // DIA_OPEN
    {}, // DIA_E4
    {}, // DIA_MG_FRLGE
    {}, // DIA_MG_RS
    {}, // DIA_LETS_START
    {}, // DIA_START
    {}, // DIA_TRANS_GOOD
    {}, // DIA_NEW_DEX
    {}, // DIA_NO_NEW_DEX
    {}, // DIA_SEND_FRIEND_KANTO
    {}, // DIA_SEND_FRIEND_HOENN_RS
    {}, // DIA_SEND_FRIEND_HOENN_E
    {}, // DIA_THANK
    {}, // DIA_GET_MON
    {}, // DIA_MG_OTHER_EVENT
    {}, // DIA_PKMN_TO_COLLECT
    {}, // DIA_NO_VALID_PKMN
    // DIA_ASK_QUEST
    {
        .text_entry_index = DIA_ASK_QUEST,
        .next_if_true = CMD_SLIDE_PROF_LEFT
    },
    {}, // DIA_WHAT_GAME_TRANS
    {}, // DIA_WHAT_LANG_TRANS
    // DIA_NO_GB_ROM
    {
        .text_entry_index = DIA_NO_GB_ROM,
        .next_if_true = DIA_WHAT_LANG_EVENT
    },
    {}, // DIA_IN_BOX
    {}, // DIA_MYTHIC_CONVERT
    {}, // DIA_CANCEL
    {}, // DIA_SOME_INVALID_PKMN
    {}, // DIA_MENU_BACK
    {}, // DIA_IS_MISSINGNO
    {}, // DIA_ERROR_COLOSSEUM
    {}, // DIA_ERROR_COM_ENDED
    {}, // DIA_ERROR_DISCONNECT
    {}, // DIA_ERROR_TIME_ONE
    {}, // DIA_ERROR_TIME_TWO
    // DIA_WHAT_LANG_EVENT
    {
        .text_entry_index = DIA_WHAT_LANG_EVENT,
        .next_if_true = CMD_LANG_MENU
    },
    // DIA_WHAT_GAME_EVENT
    {
        .text_entry_index = DIA_WHAT_GAME_EVENT,
        .next_if_true = CMD_GAME_MENU
    },
    // DIA_K_DEX_NOT_FULL
    {
        .text_entry_index = DIA_K_DEX_NOT_FULL,
        .next_if_true = CMD_END_SCRIPT
    },
    // DIA_J_DEX_NOT_FULL
    {
        .text_entry_index = DIA_J_DEX_NOT_FULL,
        .next_if_true = CMD_END_SCRIPT
    },
    {}, // T_SCRIPT_START
    // E_SCRIPT_START
    {
        .conditional_index = CMD_SHOW_PROF,
        .next_if_true = DIA_ASK_QUEST
    },
    {}, // CMD_START_LINK
    {}, // CMD_IMPORT_POKEMON
    // CMD_BACK_TO_MENU
    {
        .conditional_index = CMD_BACK_TO_MENU,
        .next_if_true = T_SCRIPT_START
    },
    {}, // CMD_SHOW_PROF
    {}, // CMD_HIDE_PROF
    {}, // CMD_SET_TUTOR_TRUE
    // CMD_END_SCRIPT
    {
        .conditional_index = CMD_END_SCRIPT,
        .next_if_true = CMD_BACK_TO_MENU
    },
    // CMD_GAME_MENU
    {
        .conditional_index = CMD_GAME_MENU,
        .next_if_true = COND_GB_ROM_EXISTS,
        .next_if_false = DIA_WHAT_LANG_EVENT
    },
    // CMD_LANG_MENU
    {
        .conditional_index = CMD_LANG_MENU,
        .next_if_true = DIA_WHAT_GAME_EVENT
    },
    // CMD_SLIDE_PROF_LEFT
    {
        .conditional_index = CMD_SLIDE_PROF_LEFT,
        .next_if_true = DIA_WHAT_LANG_EVENT
    },
    // CMD_SLIDE_PROF_RIGHT
    {
        .conditional_index = CMD_SLIDE_PROF_RIGHT,
        .next_if_true = COND_CHECK_DEX
    },
    {}, // CMD_CONTINUE_LINK
    {}, // CMD_BOX_MENU
    {}, // CMD_MYTHIC_MENU
    {}, // CMD_LOAD_SIMP
    {}, // CMD_CANCEL_LINK
    {}, // CMD_END_MISSINGNO
    {}, // COND_ERROR_TIMEOUT_ONE
    {}, // COND_ERROR_DISCONNECT
    {}, // COND_ERROR_COM_ENDED
    {}, // COND_ERROR_TIMEOUT_TWO
    {}, // COND_ERROR_COLOSSEUM
    {}, // COND_BEAT_E4
    {}, // COND_MG_ENABLED
    {}, // COND_TUTORIAL_COMPLETE
    {}, // COND_NEW_POKEMON
    {}, // COND_IS_HOENN_RS
    {}, // COND_IS_FRLGE
    {}, // COND_MG_OTHER_EVENT
    {}, // COND_PKMN_TO_COLLECT
    // COND_GB_ROM_EXISTS
    {
        .conditional_index = COND_GB_ROM_EXISTS,
        .next_if_true = CMD_SLIDE_PROF_RIGHT,
        .next_if_false = DIA_NO_GB_ROM
    },
    {}, // COND_CHECK_MYTHIC
    // COND_CHECK_DEX
    {
        .conditional_index = COND_CHECK_DEX,
        .next_if_true = 0,
        .next_if_false = COND_CHECK_KANTO
    },
    // COND_CHECK_KANTO
    {
        .conditional_index = COND_CHECK_KANTO,
        .next_if_true = DIA_K_DEX_NOT_FULL,
        .next_if_false = DIA_J_DEX_NOT_FULL
    },
    {}, // COND_SOME_INVALID_PKMN
    {}, // COND_IS_HOENN_E
    {}, // COND_CHECK_MISSINGNO
};

void populate_lang_menu()
{
    langs.add_option(GENERAL_option_english, ENG_ID);
    langs.add_option(GENERAL_option_japanese, JPN_ID);
    langs.add_option(GENERAL_option_spanish, SPA_ID);
    langs.add_option(GENERAL_option_french, FRE_ID);
    langs.add_option(GENERAL_option_german, GER_ID);
    langs.add_option(GENERAL_option_italian, ITA_ID);
    langs.add_option(GENERAL_option_korean, KOR_ID);
    langs.add_option(GENERAL_option_cancel, UINT8_MAX);
}

void populate_game_menu(int lang)
{
    switch (lang)
    {
    case (JPN_ID):
        games.add_option(GENERAL_option_red, RED_ID);
        games.add_option(GENERAL_option_green, GREEN_ID);
        games.add_option(GENERAL_option_blue, BLUE_ID);
        games.add_option(GENERAL_option_yellow, YELLOW_ID);
        games.add_option(GENERAL_option_gold, GOLD_ID);
        games.add_option(GENERAL_option_silver, SILVER_ID);
        games.add_option(GENERAL_option_crystal, CRYSTAL_ID);
        games.add_option(GENERAL_option_cancel, UINT8_MAX);
        break;

    case (KOR_ID):
        games.add_option(GENERAL_option_gold, GOLD_ID);
        games.add_option(GENERAL_option_silver, SILVER_ID);
        games.add_option(GENERAL_option_cancel, UINT8_MAX);
        break;

    default:
        games.add_option(GENERAL_option_red, RED_ID);
        games.add_option(GENERAL_option_blue, BLUE_ID);
        games.add_option(GENERAL_option_yellow, YELLOW_ID);
        games.add_option(GENERAL_option_gold, GOLD_ID);
        games.add_option(GENERAL_option_silver, SILVER_ID);
        games.add_option(GENERAL_option_crystal, CRYSTAL_ID);
        games.add_option(GENERAL_option_cancel, UINT8_MAX);
        break;
    }
}

static bool load_simple_party_data()
{
    PokemonTables data_tables;
    return party_data.fill_simple_pkmn_array(data_tables);
}

bool run_conditional(int index)
{
    // Here is most of the logic that drives what lines show up where. It's probably not the best way to code it, but it works
    int game;
    int lang;
    bool ret;
    switch (index)
    {

    case COND_ERROR_COM_ENDED:
        return party_data.get_last_error() != COND_ERROR_COM_ENDED;

    case COND_ERROR_DISCONNECT:
        return party_data.get_last_error() != COND_ERROR_DISCONNECT;

    case COND_ERROR_TIMEOUT_ONE:
        return party_data.get_last_error() != COND_ERROR_TIMEOUT_ONE;

    case COND_ERROR_TIMEOUT_TWO:
        return party_data.get_last_error() != COND_ERROR_TIMEOUT_TWO;

    case COND_ERROR_COLOSSEUM:
        return party_data.get_last_error() != COND_ERROR_COLOSSEUM;

    case COND_BEAT_E4:
        return read_flag(curr_rom.e4_flag) || IGNORE_MG_E4_FLAGS;

    case COND_MG_ENABLED:
        return read_flag(curr_rom.mg_flag) || IGNORE_MG_E4_FLAGS;

    case COND_TUTORIAL_COMPLETE:
        return get_tutorial_flag() && !FORCE_TUTORIAL;

    case COND_NEW_POKEMON:
        return party_data.get_has_new_pkmn();

    case COND_IS_HOENN_RS:
        return curr_rom.is_ruby_sapphire();

    case COND_IS_FRLGE:
        return !curr_rom.is_ruby_sapphire();

    case COND_MG_OTHER_EVENT:
        return compare_map_and_npc_data(curr_rom.def_map_bank, curr_rom.def_map_id, curr_rom.def_npc_id) && !IGNORE_MG_E4_FLAGS;

    case COND_PKMN_TO_COLLECT:
        return compare_map_and_npc_data(curr_rom.map_bank, curr_rom.map_id, curr_rom.npc_id) && !read_flag(curr_rom.all_collected_flag) && !IGNORE_UNRECEIVED_PKMN;

    case COND_GB_ROM_EXISTS:
        return party_data.load_gb_rom();

    case COND_CHECK_MYTHIC:
        return party_data.get_contains_mythical();

    case COND_CHECK_DEX:
        if (party_data.get_game_gen() == 1)
        {
            return (get_dex_completion(1, false) == 150) || IGNORE_DEX_COMPLETION;
        }
        else
        {
            return (get_dex_completion(1, false) == 99) || IGNORE_DEX_COMPLETION;
        }

    case COND_CHECK_KANTO:
        return party_data.get_game_gen() == 1;

    case COND_SOME_INVALID_PKMN:
        return party_data.get_contains_invalid();

    case COND_IS_HOENN_E:
        return curr_rom.gamecode == EMERALD_ID;

    case COND_CHECK_MISSINGNO:
        if (party_data.get_contains_missingno())
        {
            set_missingno(true);
            return true;
        }
        return false;

    case CMD_START_LINK:
        load_flex_background(BG_FENNEL, 3);
        link_animation_state(STATE_CONNECTION);
        party_data.start_link();
        reset_textbox();
        load_flex_background(BG_FENNEL, 2);
        link_animation_state(0);
        return true;

    case CMD_IMPORT_POKEMON:
        inject_mystery(party_data);
        return true;

    case CMD_BACK_TO_MENU:
        set_text_exit();
        REG_BG1HOFS = 0;
        load_flex_background(BG_FENNEL, 3);
        return true;

    case CMD_SHOW_PROF:
        load_flex_background(BG_FENNEL, 2);
        return true;

    case CMD_HIDE_PROF:
        load_flex_background(BG_FENNEL, 3);
        return true;

    case CMD_SET_TUTOR_TRUE:
        set_tutorial_flag(true);
        return true;

    case CMD_END_SCRIPT:
        if (get_missingno_enabled())
        {
            set_missingno(false);
        }
        return true;

    case CMD_LANG_MENU:
        populate_lang_menu();
        lang = langs.select_menu_main();
        if (lang == BUTTON_CANCEL)
        {
            return false;
        }
        games.set_lang(static_cast<u8>(lang));
        party_data.set_lang(static_cast<u8>(lang));
        return true;

    case CMD_GAME_MENU:
        populate_game_menu(party_data.get_lang());
        game = games.select_menu_main();
        if (game == BUTTON_CANCEL)
        {
            return false;
        }
        party_data.set_game(game);
        return true;

    case CMD_SLIDE_PROF_LEFT:
        for (int i = 0; i <= (8 * 7); i += 2)
        {
            REG_BG1HOFS = i + FENNEL_SHIFT;
            if (!INSTANT_TEXT_SPEED)
            {
                global_next_frame();
            }
        }
        return true;

    case CMD_SLIDE_PROF_RIGHT:
        for (int i = (8 * 7); i >= 0; i -= 2)
        {
            REG_BG1HOFS = i + FENNEL_SHIFT;
            if (!INSTANT_TEXT_SPEED)
            {
                global_next_frame();
            }
        }
        return true;

    case CMD_CONTINUE_LINK:
        party_data.continue_link(false);
        return true;

    case CMD_BOX_MENU:
        hide_text_box();
        ret = (box_viewer.box_main(party_data) == CONFIRM_BUTTON);
        show_text_box();
        return ret;

    case CMD_MYTHIC_MENU:
        party_data.set_mythic_stabilization(yes_no_menu.button_main());
        return true;

    case CMD_LOAD_SIMP:
        return load_simple_party_data();
    case CMD_CANCEL_LINK:
        party_data.continue_link(true);
        return true;

    case CMD_END_MISSINGNO:
        if (get_missingno_enabled())
        {
            set_missingno(false);
        }
        return true;

    default:
        tte_set_pos(0, 0);
        tte_write("ERROR! No conditional found.");
        return false;
    }
}