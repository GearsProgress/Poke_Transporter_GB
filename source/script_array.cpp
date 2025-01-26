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
#include "dialogue.h"

int last_error;
Pokemon_Party party_data = Pokemon_Party();

Select_Menu langs(false, LANG_MENU);
Select_Menu games(false, CART_MENU);
Box_Menu box_viewer;

script_obj transfer_script[SCRIPT_SIZE];
script_obj event_script[SCRIPT_SIZE];

void populate_script()
{
    // -------- TRANSFER SCRIPT --------
    // Check that the conditions are set for the transfer
    transfer_script[T_SCRIPT_START] = script_obj(CMD_SHOW_PROF, COND_TUTORIAL_COMPLETE);
    transfer_script[COND_TUTORIAL_COMPLETE] = script_obj(COND_TUTORIAL_COMPLETE, COND_BEAT_E4, DIA_OPEN);
    transfer_script[DIA_OPEN] = script_obj(dialogue[DIA_OPEN], CMD_SET_TUTOR_TRUE);
    transfer_script[CMD_SET_TUTOR_TRUE] = script_obj(CMD_SET_TUTOR_TRUE, CMD_END_SCRIPT);
    transfer_script[COND_BEAT_E4] = script_obj(COND_BEAT_E4, COND_MG_ENABLED, DIA_E4);
    transfer_script[DIA_E4] = script_obj(dialogue[DIA_E4], CMD_END_SCRIPT);
    transfer_script[COND_MG_ENABLED] = script_obj(COND_MG_ENABLED, COND_MG_OTHER_EVENT, COND_IS_FRLGE);
    transfer_script[COND_IS_FRLGE] = script_obj(COND_IS_FRLGE, DIA_MG_FRLGE, DIA_MG_RS);
    transfer_script[DIA_MG_FRLGE] = script_obj(dialogue[DIA_MG_FRLGE], CMD_END_SCRIPT);
    transfer_script[DIA_MG_RS] = script_obj(dialogue[DIA_MG_RS], CMD_END_SCRIPT);
    transfer_script[COND_MG_OTHER_EVENT] = script_obj(COND_MG_OTHER_EVENT, DIA_MG_OTHER_EVENT, COND_PKMN_TO_COLLECT);
    transfer_script[COND_PKMN_TO_COLLECT] = script_obj(COND_PKMN_TO_COLLECT, DIA_PKMN_TO_COLLECT, DIA_ASK_QUEST);
    transfer_script[DIA_MG_OTHER_EVENT] = script_obj(dialogue[DIA_MG_OTHER_EVENT], DIA_ASK_QUEST);
    transfer_script[DIA_PKMN_TO_COLLECT] = script_obj(dialogue[DIA_PKMN_TO_COLLECT], CMD_END_SCRIPT);

    // Ask the user what game and language they're using
    transfer_script[DIA_WHAT_GAME_TRANS] = script_obj(dialogue[DIA_WHAT_GAME_TRANS], CMD_GAME_MENU);
    transfer_script[CMD_GAME_MENU] = script_obj(CMD_GAME_MENU, COND_GB_ROM_EXISTS, DIA_WHAT_LANG_TRANS);
    transfer_script[DIA_WHAT_LANG_TRANS] = script_obj(dialogue[DIA_WHAT_LANG_TRANS], CMD_LANG_MENU);
    transfer_script[CMD_LANG_MENU] = script_obj(CMD_LANG_MENU, DIA_WHAT_GAME_TRANS, DIA_MENU_BACK);
    transfer_script[DIA_ASK_QUEST] = script_obj(dialogue[DIA_ASK_QUEST], CMD_SLIDE_PROF_LEFT);
    transfer_script[CMD_SLIDE_PROF_LEFT] = script_obj(CMD_SLIDE_PROF_LEFT, DIA_WHAT_LANG_TRANS);
    transfer_script[CMD_SLIDE_PROF_RIGHT] = script_obj(CMD_SLIDE_PROF_RIGHT, DIA_LETS_START);
    transfer_script[COND_GB_ROM_EXISTS] = script_obj(COND_GB_ROM_EXISTS, CMD_SLIDE_PROF_RIGHT, DIA_NO_GB_ROM);
    transfer_script[DIA_NO_GB_ROM] = script_obj(dialogue[DIA_NO_GB_ROM], DIA_WHAT_LANG_TRANS);
    transfer_script[DIA_MENU_BACK] = script_obj(dialogue[DIA_MENU_BACK], CMD_END_SCRIPT);

    // Initiate the transfer and check for errors
    transfer_script[DIA_LETS_START] = script_obj(dialogue[DIA_LETS_START], DIA_START);
    transfer_script[DIA_START] = script_obj(dialogue[DIA_START], CMD_START_LINK);
    transfer_script[CMD_START_LINK] = script_obj(CMD_START_LINK, COND_ERROR_TIMEOUT_ONE);
    transfer_script[COND_ERROR_TIMEOUT_ONE] = script_obj(COND_ERROR_TIMEOUT_ONE, COND_ERROR_TIMEOUT_TWO, DIA_ERROR_TIME_ONE);
    transfer_script[DIA_ERROR_TIME_ONE] = script_obj(dialogue[DIA_ERROR_TIME_ONE], DIA_START);
    transfer_script[COND_ERROR_TIMEOUT_TWO] = script_obj(COND_ERROR_TIMEOUT_TWO, COND_ERROR_COM_ENDED, DIA_ERROR_TIME_TWO);
    transfer_script[DIA_ERROR_TIME_TWO] = script_obj(dialogue[DIA_ERROR_TIME_TWO], DIA_START);
    transfer_script[COND_ERROR_COM_ENDED] = script_obj(COND_ERROR_COM_ENDED, COND_ERROR_COLOSSEUM, DIA_ERROR_COM_ENDED);
    transfer_script[DIA_ERROR_COM_ENDED] = script_obj(dialogue[DIA_ERROR_COM_ENDED], DIA_START);
    transfer_script[COND_ERROR_COLOSSEUM] = script_obj(COND_ERROR_COLOSSEUM, COND_ERROR_DISCONNECT, DIA_ERROR_COLOSSEUM);
    transfer_script[DIA_ERROR_COLOSSEUM] = script_obj(dialogue[DIA_ERROR_COLOSSEUM], DIA_START);
    transfer_script[COND_ERROR_DISCONNECT] = script_obj(COND_ERROR_DISCONNECT, CMD_LOAD_SIMP, DIA_ERROR_DISCONNECT);
    transfer_script[DIA_ERROR_DISCONNECT] = script_obj(dialogue[DIA_ERROR_DISCONNECT], DIA_START);

    // Pause the transfer and show the user their box data
    transfer_script[CMD_LOAD_SIMP] = script_obj(CMD_LOAD_SIMP, COND_SOME_INVALID_PKMN, DIA_NO_VALID_PKMN);
    transfer_script[DIA_NO_VALID_PKMN] = script_obj(dialogue[DIA_NO_VALID_PKMN], CMD_CANCEL_LINK);
    transfer_script[COND_SOME_INVALID_PKMN] = script_obj(COND_SOME_INVALID_PKMN, DIA_SOME_INVALID_PKMN, COND_CHECK_MYTHIC);
    transfer_script[DIA_SOME_INVALID_PKMN] = script_obj(dialogue[DIA_SOME_INVALID_PKMN], COND_CHECK_MYTHIC);
    transfer_script[COND_CHECK_MYTHIC] = script_obj(COND_CHECK_MYTHIC, DIA_MYTHIC_CONVERT, COND_CHECK_MISSINGNO);
    transfer_script[DIA_MYTHIC_CONVERT] = script_obj(dialogue[DIA_MYTHIC_CONVERT], CMD_MYTHIC_MENU);
    transfer_script[CMD_MYTHIC_MENU] = script_obj(CMD_MYTHIC_MENU, COND_CHECK_MISSINGNO);
    transfer_script[COND_CHECK_MISSINGNO] = script_obj(COND_CHECK_MISSINGNO, DIA_IS_MISSINGNO, DIA_IN_BOX);
    transfer_script[DIA_IS_MISSINGNO] = script_obj(dialogue[DIA_IS_MISSINGNO], DIA_IN_BOX);
    transfer_script[DIA_IN_BOX] = script_obj(dialogue[DIA_IN_BOX], CMD_BOX_MENU);
    transfer_script[CMD_BOX_MENU] = script_obj(CMD_BOX_MENU, CMD_IMPORT_POKEMON, DIA_CANCEL);
    transfer_script[DIA_CANCEL] = script_obj(dialogue[DIA_CANCEL], CMD_CANCEL_LINK);
    transfer_script[CMD_IMPORT_POKEMON] = script_obj(CMD_IMPORT_POKEMON, CMD_CONTINUE_LINK);
    transfer_script[CMD_CONTINUE_LINK] = script_obj(CMD_CONTINUE_LINK, CMD_END_MISSINGNO);
    transfer_script[CMD_CANCEL_LINK] = script_obj(CMD_CANCEL_LINK, CMD_END_SCRIPT);
    transfer_script[CMD_END_MISSINGNO] = script_obj(CMD_END_MISSINGNO, DIA_TRANS_GOOD);

    // Complete the transfer and give messages based on the transfered Pokemon
    transfer_script[DIA_TRANS_GOOD] = script_obj(dialogue[DIA_TRANS_GOOD], COND_NEW_POKEMON);
    transfer_script[COND_NEW_POKEMON] = script_obj(COND_NEW_POKEMON, DIA_NEW_DEX, DIA_NO_NEW_DEX);
    transfer_script[DIA_NEW_DEX] = script_obj(dialogue[DIA_NEW_DEX], COND_IS_HOENN_RS);
    transfer_script[DIA_NO_NEW_DEX] = script_obj(dialogue[DIA_NO_NEW_DEX], COND_IS_HOENN_RS);
    transfer_script[COND_IS_HOENN_RS] = script_obj(COND_IS_HOENN_RS, DIA_SEND_FRIEND_HOENN_RS, COND_IS_HOENN_E);
    transfer_script[COND_IS_HOENN_E] = script_obj(COND_IS_HOENN_E, DIA_SEND_FRIEND_HOENN_E, DIA_SEND_FRIEND_KANTO);
    transfer_script[DIA_SEND_FRIEND_HOENN_RS] = script_obj(dialogue[DIA_SEND_FRIEND_HOENN_RS], DIA_THANK);
    transfer_script[DIA_SEND_FRIEND_HOENN_E] = script_obj(dialogue[DIA_SEND_FRIEND_HOENN_E], DIA_THANK);
    transfer_script[DIA_SEND_FRIEND_KANTO] = script_obj(dialogue[DIA_SEND_FRIEND_KANTO], DIA_THANK);
    transfer_script[DIA_THANK] = script_obj(dialogue[DIA_THANK], CMD_END_SCRIPT);

    // Hide the dialouge and professor
    transfer_script[CMD_END_SCRIPT] = script_obj(CMD_END_SCRIPT, CMD_BACK_TO_MENU);
    transfer_script[CMD_BACK_TO_MENU] = script_obj(CMD_BACK_TO_MENU, T_SCRIPT_START);

    // -------- EVENTS SCRIPT --------
    // Start the dialogue and show the menu
    event_script[E_SCRIPT_START] = script_obj(CMD_SHOW_PROF, DIA_ASK_QUEST);
    event_script[DIA_ASK_QUEST] = script_obj(dialogue[DIA_ASK_QUEST], CMD_SLIDE_PROF_LEFT);

    // Ask the user what game and language they're using
    event_script[DIA_WHAT_GAME_EVENT] = script_obj(dialogue[DIA_WHAT_GAME_EVENT], CMD_GAME_MENU);
    event_script[CMD_GAME_MENU] = script_obj(CMD_GAME_MENU, COND_GB_ROM_EXISTS, DIA_WHAT_LANG_EVENT);
    event_script[DIA_WHAT_LANG_EVENT] = script_obj(dialogue[DIA_WHAT_LANG_EVENT], CMD_LANG_MENU);
    event_script[CMD_LANG_MENU] = script_obj(CMD_LANG_MENU, DIA_WHAT_GAME_EVENT);
    event_script[DIA_ASK_QUEST] = script_obj(dialogue[DIA_ASK_QUEST], CMD_SLIDE_PROF_LEFT);
    event_script[CMD_SLIDE_PROF_LEFT] = script_obj(CMD_SLIDE_PROF_LEFT, DIA_WHAT_LANG_EVENT);
    event_script[CMD_SLIDE_PROF_RIGHT] = script_obj(CMD_SLIDE_PROF_RIGHT, COND_CHECK_DEX);
    event_script[COND_GB_ROM_EXISTS] = script_obj(COND_GB_ROM_EXISTS, CMD_SLIDE_PROF_RIGHT, DIA_NO_GB_ROM);
    event_script[DIA_NO_GB_ROM] = script_obj(dialogue[DIA_NO_GB_ROM], DIA_WHAT_LANG_EVENT);

    // Check the player's dex
    event_script[COND_CHECK_DEX] = script_obj(COND_CHECK_DEX, 0, COND_CHECK_KANTO);
    event_script[COND_CHECK_KANTO] = script_obj(COND_CHECK_KANTO, DIA_K_DEX_NOT_FULL, DIA_J_DEX_NOT_FULL);
    event_script[DIA_K_DEX_NOT_FULL] = script_obj(dialogue[DIA_K_DEX_NOT_FULL], CMD_END_SCRIPT);
    event_script[DIA_J_DEX_NOT_FULL] = script_obj(dialogue[DIA_J_DEX_NOT_FULL], CMD_END_SCRIPT);

    // Hide the dialouge and professor
    event_script[CMD_END_SCRIPT] = script_obj(CMD_END_SCRIPT, CMD_BACK_TO_MENU);
    event_script[CMD_BACK_TO_MENU] = script_obj(CMD_BACK_TO_MENU, T_SCRIPT_START);
};

void populate_lang_menu()
{
    langs.add_option("English", ENG_ID);
    langs.add_option("Japanese", JPN_ID);
    langs.add_option("Spanish", SPA_ID);
    langs.add_option("French", FRE_ID);
    langs.add_option("German", GER_ID);
    langs.add_option("Italian", ITA_ID);
    langs.add_option("Korean", KOR_ID);
    langs.add_option("Cancel", -1);
}

void populate_game_menu(int lang)
{
    switch (lang)
    {
    case (JPN_ID):
        games.add_option("Red", RED_ID);
        games.add_option("Green", GREEN_ID);
        games.add_option("Blue", BLUE_ID);
        games.add_option("Yellow", YELLOW_ID);
        games.add_option("Gold", GOLD_ID);
        games.add_option("Silver", SILVER_ID);
        games.add_option("Crystal", CRYSTAL_ID);
        games.add_option("Cancel", -1);
        break;

    case (KOR_ID):
        games.add_option("Gold", GOLD_ID);
        games.add_option("Silver", SILVER_ID);
        games.add_option("Cancel", -1);
        break;

    default:
        games.add_option("Red", RED_ID);
        games.add_option("Blue", BLUE_ID);
        games.add_option("Yellow", YELLOW_ID);
        games.add_option("Gold", GOLD_ID);
        games.add_option("Silver", SILVER_ID);
        games.add_option("Crystal", CRYSTAL_ID);
        games.add_option("Cancel", -1);
        break;
    }
}

bool run_conditional(int index)
{
    // Here is most of the logic that drives what lines show up where. It's probably not the best way to code it, but it works
    int game;
    int lang;
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
        set_textbox_small();
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
        games.set_lang(lang);
        party_data.set_lang(lang);
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
        return (box_viewer.box_main(party_data) == CONFIRM_BUTTON);

    case CMD_MYTHIC_MENU:
        party_data.set_mythic_stabilization(yes_no_menu.button_main());
        return true;

    case CMD_LOAD_SIMP:
        return party_data.fill_simple_pkmn_array();

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