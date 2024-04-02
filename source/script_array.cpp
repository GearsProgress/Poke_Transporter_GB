#include "script_array.h"
#include "main_menu.h"
#include "text_engine.h"
#include "mystery_gift_injector.h"
#include "sprite_data.h"
#include "flash_mem.h"
#include "pokemon_data.h"
#include "mystery_gift_builder.h"
#include "global_frame_controller.h"
#include "box_menu.h"
#include <tonc.h>

int last_error;
Pokemon_Party party_data = Pokemon_Party();

Button_Menu lang_select(2, 4, 40, 24, false);
Button_Menu game_select_def(2, 2, 72, 32, true);
Button_Menu game_select_jpn(3, 2, 72, 32, true);
Button_Menu game_select_kor(1, 1, 72, 32, true);
Box_Menu box_viewer;

script_obj script[SCRIPT_SIZE];
std::string_view dialogue[DIA_SIZE];

void populate_dialogue()
{
    dialogue[DIA_OPEN] = "Hey there! I'm Professor\nFennel. As you can see, I'm\na scientist.|In fact, the subject I'm \nresearching is Trainers!|My dream is to collect save files of various trainers, \nbut I haven't had any \nbreakthroughs yet...|So in the meantime, I have a\ndifferent project!|In my home region, there's a\nlocation that can make a\nPok@mon's dreams into\nreality.|This means that any other\nPok@mon they meet in their\ndreams become real!|That's fantastic, but my\ngoal is to do the same-\njust with a trainer's dream\ninstead!|I've successfully been able\nto send a Pok@mon into\nand out of a trainer's\ndream...|but I've been unsuccessful\nin pulling out a new Pok@mon\nwithout...\ncatastrophic results.|That's when I had a\nbreakthrough- I realized if \nI sent in a DITTO,|it could transform into the\nPok@mon found within that\ntrainer's dream!|That's why I need your help!\nI want to bring as many\nPok@mon out of your dreams\nas possible!|There's just over 250\nPok@mon I want to catalogue\nin my Dream Pok@Dex-\nor Dream Dex for short.|But I'll let you keep any\nPok@mon- they're from your\ndreams after all!|I think that's everything...\nwhenever you're ready to\nstart, just let me know!";
    dialogue[DIA_E4] = "Hi trainer! I'm thrilled\nyou've decided to help with our research, but we need\nthe best of the best!|Come back after you've\nbeaten the Elite Four and\nbecome the Champion!";
    dialogue[DIA_MG_FRLGE] = "Sorry trainer, one more\nthing to take care of before\nwe can begin- you need to\nenable MYSTERY GIFT!|Head to the nearest Pok@\nMart and fill out the\nquestionnaire as follows:\nLINK TOGETHER WITH ALL|After that, you should be\nall set to go!|See you soon!";
    dialogue[DIA_MG_RS] = "Sorry trainer, one more\nthing to take care of before\nwe can begin- you need to\nenable MYSTERY EVENT!|Head to the PETALBURG\nPok@mon Center and tell the\nman next to the PC:\nMYSTERY EVENT IS EXCITING|After that, you should be\nall set to go!|See you soon!";
    dialogue[DIA_LETS_START] = "Perfect, that's all the\ninformation I need! Let's\nget started!";
    dialogue[DIA_START] = "On a second Game Boy family\nsystem, please load the Game\nBoy Pok@mon game you wish to\ntransfer from.|In your Game Boy Pok@mon\ngame, put any Pok@mon you\nwant to bring out of\nyour dreams into your party.|Then connect this Game Boy\nAdvance to the other Game\nBoy family system using a\nGame Boy Color link cable.|Once you're ready, press A\non this device, talk to the Cable Club attendant, and\nthen initiate a trade.";
    dialogue[DIA_TRANS_GOOD] = "Amazing! Fantastic!\nEverything went perfectly!|You may now turn off your\nother Game Boy family\nsystem.";
    dialogue[DIA_NEW_DEX] = "It looks like there's at\nleast one new Pok@mon here\nthat isn't in the Dream Dex!|I'll give them something\nextra sweet as a reward for you both.";
    dialogue[DIA_NO_NEW_DEX] = "It doesn't look like there's\nanything new for your Dream\nDex, but that's okay!|It's important to confirm\nresearch results with\nmultiple tests!";
    dialogue[DIA_SEND_FRIEND_KANTO] = "I'm going to send these\nPok@mon to my friend BILL so\nthat you can pick them up.\nThey live on Route 25!|Did you know they developed the Storage System for the\nKanto region?|My younger sister developed a version of the Storage\nSystem too, so BILL is a\ngood friend of ours!";
    dialogue[DIA_SEND_FRIEND_HOENN] = "I'm going to send these\nPok@mon to my friend LANNETE\nso that you can pick them\nup. They live on route 114!|Did you know they developed the Storage System for the\nHoenn region?|My younger sister developed a version of the Storage\nSystem too, so LANNETE is a\ngood friend of ours!";
    dialogue[DIA_THANK] = "Thank you so much for your\nhelp! Whenever you want to\ntransfer more Pok@mon, just\nlet me know!|See you around!";
    dialogue[DIA_GET_MON] = "Let's get started! Please connect Load the Game Boy Pok@mon game you want to transfer from, and put the Pok@mon you want to transfer into your party. ";
    dialogue[DIA_MG_OTHER_EVENT] = "Hi Trainer! It looks like\nyou have a different event\ncurrently loaded.|That's no problem, but it\nwill be overwritten if you\ncontinue.|Turn off the system now if\nyou want to experience your\ncurrent event,\nbut otherwise-";
    dialogue[DIA_PKMN_TO_COLLECT] = "Hi Trainer! It looks like\nyou still have Pok@mon to\npick up...|I can send in new ones, but do know that the Pok@mon you\nhaven't picked up yet will\nbe replaced.|Turn off the system now if\nyou want to recieve those\nPok@mon, but otherwise-";
    dialogue[DIA_NO_VALID_PKMN] = "Sorry Trainer, it doesn't\nlook like you have any valid\nPok@mon in your party right\nnow.|Double check your party and we'll give it another shot!";
    dialogue[DIA_ASK_QUEST] = "Hi trainer! Before we begin,\nI need to ask you a few\nquestions.";
    dialogue[DIA_WHAT_GAME] = "And which Game Boy Pok@mon\ngame are you transferring\nfrom?";
    dialogue[DIA_WHAT_LANG] = "What language is the Game\nBoy Pok@mon game that you're\ntransferring from?";
    dialogue[DIA_NO_PAYLOAD] = "I'm sorry, but that version\nin that language is not\ncurrently supported.";
    dialogue[DIA_IN_BOX] = "Great! Let's take a look at\nthe Pok@mon that will be\ntransfered.|Please remember, once a\nPok@mon is transfered, it\nCANNOT be returned to the\nGame Boy Game Pak.|Select transfer once you're\nready, or select cancel if\nyou want to keep the Pok@mon\non your Game Boy Game Pak.";

    dialogue[DIA_ERROR_COLOSSEUM] = "It looks like you went to\nthe colosseum instead of the\ntrading room!|Let's try that again!";
    dialogue[DIA_ERROR_COM_ENDED] = "Communication with the other\ndevice was terminated.|Let's try that again!";
    dialogue[DIA_ERROR_DISCONNECT] = "It doesn't look like the\nGame Boy Color link cable is\nconnected correctly.|Let's try that again!";
    dialogue[DIA_ERROR_TIME_ONE] = "It looks like the connection\ntimed out...|Let's try that again!";
    dialogue[DIA_ERROR_TIME_TWO] = "It seems like the connection\ntimed out...|Let's try that again!";
}

void populate_script()
{
    // Check that the conditions are set for the transfer
    script[SCRIPT_START] = script_obj(CMD_SHOW_PROF, COND_BEAT_E4);
    script[COND_BEAT_E4] = script_obj(COND_BEAT_E4, COND_MG_ENABLED, DIA_E4);
    script[DIA_E4] = script_obj(dialogue[DIA_E4], CMD_END_SCRIPT);
    script[COND_MG_ENABLED] = script_obj(COND_MG_ENABLED, COND_TUTORIAL_COMPLETE, COND_IS_FRLGE);
    script[COND_IS_FRLGE] = script_obj(COND_IS_FRLGE, DIA_MG_FRLGE, DIA_MG_RS);
    script[DIA_MG_FRLGE] = script_obj(dialogue[DIA_MG_FRLGE], CMD_END_SCRIPT);
    script[DIA_MG_RS] = script_obj(dialogue[DIA_MG_RS], CMD_END_SCRIPT);
    script[COND_TUTORIAL_COMPLETE] = script_obj(COND_TUTORIAL_COMPLETE, COND_MG_OTHER_EVENT, DIA_OPEN);
    script[DIA_OPEN] = script_obj(dialogue[DIA_OPEN], CMD_SET_TUTOR_TRUE);
    script[CMD_SET_TUTOR_TRUE] = script_obj(CMD_SET_TUTOR_TRUE, CMD_END_SCRIPT);
    script[COND_MG_OTHER_EVENT] = script_obj(COND_MG_OTHER_EVENT, DIA_MG_OTHER_EVENT, COND_PKMN_TO_COLLECT);
    script[COND_PKMN_TO_COLLECT] = script_obj(COND_PKMN_TO_COLLECT, DIA_PKMN_TO_COLLECT, DIA_ASK_QUEST);
    script[DIA_MG_OTHER_EVENT] = script_obj(dialogue[DIA_MG_OTHER_EVENT], DIA_ASK_QUEST);
    script[DIA_PKMN_TO_COLLECT] = script_obj(dialogue[DIA_PKMN_TO_COLLECT], DIA_ASK_QUEST);

    // Ask the user what game and language they're using
    script[DIA_WHAT_GAME] = script_obj(dialogue[DIA_WHAT_GAME], CMD_GAME_MENU);
    script[CMD_GAME_MENU] = script_obj(CMD_GAME_MENU, COND_PAYLOAD_EXISTS, DIA_WHAT_LANG);
    script[DIA_WHAT_LANG] = script_obj(dialogue[DIA_WHAT_LANG], CMD_LANG_MENU);
    script[CMD_LANG_MENU] = script_obj(CMD_LANG_MENU, DIA_WHAT_GAME);
    script[DIA_ASK_QUEST] = script_obj(dialogue[DIA_ASK_QUEST], CMD_SLIDE_PROF_LEFT);
    script[CMD_SLIDE_PROF_LEFT] = script_obj(CMD_SLIDE_PROF_LEFT, DIA_WHAT_LANG);
    script[CMD_SLIDE_PROF_RIGHT] = script_obj(CMD_SLIDE_PROF_RIGHT, DIA_LETS_START);
    script[COND_PAYLOAD_EXISTS] = script_obj(COND_PAYLOAD_EXISTS, CMD_SLIDE_PROF_RIGHT, DIA_NO_PAYLOAD);
    script[DIA_NO_PAYLOAD] = script_obj(dialogue[DIA_NO_PAYLOAD], DIA_WHAT_LANG);

    // Initiate the transfer and check for errors
    script[DIA_LETS_START] = script_obj(dialogue[DIA_LETS_START], DIA_START);
    script[DIA_START] = script_obj(dialogue[DIA_START], CMD_START_LINK);
    script[CMD_START_LINK] = script_obj(CMD_START_LINK, COND_ERROR_TIMEOUT_ONE);
    script[COND_ERROR_TIMEOUT_ONE] = script_obj(COND_ERROR_TIMEOUT_ONE, COND_ERROR_TIMEOUT_TWO, DIA_ERROR_TIME_ONE);
    script[DIA_ERROR_TIME_ONE] = script_obj(dialogue[DIA_ERROR_TIME_ONE], DIA_START);
    script[COND_ERROR_TIMEOUT_TWO] = script_obj(COND_ERROR_TIMEOUT_TWO, COND_ERROR_COM_ENDED, DIA_ERROR_TIME_TWO);
    script[DIA_ERROR_TIME_TWO] = script_obj(dialogue[DIA_ERROR_TIME_TWO], DIA_START);
    script[COND_ERROR_COM_ENDED] = script_obj(COND_ERROR_COM_ENDED, COND_ERROR_COLOSSEUM, DIA_ERROR_COM_ENDED);
    script[DIA_ERROR_COM_ENDED] = script_obj(dialogue[DIA_ERROR_COM_ENDED], DIA_START);
    script[COND_ERROR_COLOSSEUM] = script_obj(COND_ERROR_COLOSSEUM, COND_ERROR_DISCONNECT, DIA_ERROR_COLOSSEUM);
    script[DIA_ERROR_COLOSSEUM] = script_obj(dialogue[DIA_ERROR_COLOSSEUM], DIA_START);
    script[COND_ERROR_DISCONNECT] = script_obj(COND_ERROR_DISCONNECT, DIA_IN_BOX, DIA_ERROR_DISCONNECT);
    script[DIA_ERROR_DISCONNECT] = script_obj(dialogue[DIA_ERROR_DISCONNECT], DIA_START);

    // Pause the transfer and show the user their box data
    script[DIA_IN_BOX] = script_obj(dialogue[DIA_IN_BOX], CMD_SHOW_LARGE_TEXTBOX);
    script[CMD_SHOW_LARGE_TEXTBOX] = script_obj(CMD_SHOW_LARGE_TEXTBOX, CMD_BOX_MENU);
    script[CMD_BOX_MENU] = script_obj(CMD_BOX_MENU, CMD_HIDE_LARGE_TEXTBOX);
    script[CMD_HIDE_LARGE_TEXTBOX] = script_obj(CMD_HIDE_LARGE_TEXTBOX, DIA_LETS_START);

    // Complete the transfer and give messages based on the transfered Pokemon
    script[CMD_IMPORT_POKEMON] = script_obj(CMD_IMPORT_POKEMON, DIA_TRANS_GOOD, DIA_NO_VALID_PKMN);
    script[DIA_NO_VALID_PKMN] = script_obj(dialogue[DIA_NO_VALID_PKMN], CMD_END_SCRIPT);
    script[DIA_TRANS_GOOD] = script_obj(dialogue[DIA_TRANS_GOOD], COND_NEW_POKEMON);
    script[COND_NEW_POKEMON] = script_obj(COND_NEW_POKEMON, DIA_NEW_DEX, DIA_NO_NEW_DEX);
    script[DIA_NEW_DEX] = script_obj(dialogue[DIA_NEW_DEX], COND_IS_HOENN);
    script[DIA_NO_NEW_DEX] = script_obj(dialogue[DIA_NO_NEW_DEX], COND_IS_HOENN);
    script[COND_IS_HOENN] = script_obj(COND_IS_HOENN, DIA_SEND_FRIEND_HOENN, DIA_SEND_FRIEND_KANTO);
    script[DIA_SEND_FRIEND_HOENN] = script_obj(dialogue[DIA_SEND_FRIEND_HOENN], DIA_THANK);
    script[DIA_SEND_FRIEND_KANTO] = script_obj(dialogue[DIA_SEND_FRIEND_KANTO], DIA_THANK);
    script[DIA_THANK] = script_obj(dialogue[DIA_THANK], CMD_END_SCRIPT);

    // Hide the dialouge and professor
    script[CMD_END_SCRIPT] = script_obj(CMD_END_SCRIPT, CMD_BACK_TO_MENU);
    script[CMD_BACK_TO_MENU] = script_obj(CMD_BACK_TO_MENU, SCRIPT_START);
};

void populate_lang_buttons()
{
    lang_select.set_xy_min_max(48, 240, 0, 112);
    lang_select.clear_vector();
    lang_select.add_button(Button(btn_lang_jpn), JPN_ID);
    lang_select.add_button(Button(btn_lang_eng), ENG_ID);
    lang_select.add_button(Button(btn_lang_fre), FRE_ID);
    lang_select.add_button(Button(btn_lang_ita), ITA_ID);
    lang_select.add_button(Button(btn_lang_ger), GER_ID);
    lang_select.add_button(Button(btn_lang_spa), SPA_ID);
    lang_select.add_button(Button(btn_lang_kor), KOR_ID);
}

void populate_game_buttons()
{
    game_select_jpn.clear_vector();
    game_select_jpn.add_button(Button(button_red_green_left, button_red_green_right, 64), RED_GREEN_ID);
    game_select_jpn.add_button(Button(button_blue_left, button_blue_right, 64), BLUE_ID);
    game_select_jpn.add_button(Button(button_yellow_left, button_yellow_right, 64), YELLOW_ID);
    game_select_jpn.add_button(Button(button_gold_silver_left, button_gold_silver_right, 64), GOLD_SILVER_ID);
    game_select_jpn.add_button(Button(button_crystal_left, button_crystal_right, 64), CRYSTAL_ID);
    game_select_jpn.set_xy_min_max(48, 240, 0, 120);

    game_select_kor.clear_vector();
    game_select_kor.add_button(Button(button_gold_silver_left, button_gold_silver_right, 64), GOLD_SILVER_ID);
    game_select_kor.set_xy_min_max(48, 240, 0, 120);

    game_select_def.clear_vector();
    game_select_def.set_rows_and_columns(2, 2);
    game_select_def.add_button(Button(button_red_blue_left, button_red_blue_right, 64), RED_BLUE_ID);
    game_select_def.add_button(Button(button_yellow_left, button_yellow_right, 64), YELLOW_ID);
    game_select_def.add_button(Button(button_gold_silver_left, button_gold_silver_right, 64), GOLD_SILVER_ID);
    game_select_def.add_button(Button(button_crystal_left, button_crystal_right, 64), CRYSTAL_ID);
    game_select_def.set_xy_min_max(48, 240, 0, 120);
}

bool run_conditional(int index)
{
    // Here is most of the logic that drives what lines show up where. It's probably not the best way to code it, but it works
    int game;
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
        return get_tutorial_flag() || IGNORE_MG_E4_FLAGS;

    case COND_NEW_POKEMON:
        return party_data.get_has_new_pkmn();

    case COND_IS_HOENN:
        return curr_rom.is_hoenn();

    case COND_IS_FRLGE:
        return !curr_rom.is_ruby_sapphire();

    case COND_MG_OTHER_EVENT:
        return compare_map_and_npc_data(curr_rom.def_map_bank, curr_rom.def_map_id, curr_rom.def_npc_id) && !IGNORE_MG_E4_FLAGS;

    case COND_PKMN_TO_COLLECT:
        return compare_map_and_npc_data(curr_rom.map_bank, curr_rom.map_id, curr_rom.npc_id) && !read_flag(curr_rom.all_collected_flag) && !IGNORE_MG_E4_FLAGS;

    case COND_PAYLOAD_EXISTS:
        return party_data.load_payload();

    case CMD_START_LINK:
        party_data.start_link();
        return true;

    case CMD_IMPORT_POKEMON:
        // party_data.set_lang(ENG_ID);
        // party_data.set_game(RED_ID);
        //  REMOVE ME ^
        return inject_mystery(party_data);

    case CMD_BACK_TO_MENU:
        set_text_exit();
        obj_hide(prof);
        return true;

    case CMD_SHOW_PROF:
        obj_unhide(prof, 0);
        obj_set_pos(prof, 96, 56);
        return true;

    case CMD_HIDE_PROF:
        obj_hide(prof);
        return true;

    case CMD_SET_TUTOR_TRUE:
        set_tutorial_flag(true);
        return true;

    case CMD_END_SCRIPT:
        return true;

    case CMD_LANG_MENU:
        load_temp_sprites(SPRITE_BATCH_LANG);
        populate_lang_buttons();
        party_data.set_lang(lang_select.button_main());
        return true;

    case CMD_GAME_MENU:
        load_temp_sprites(SPRITE_BATCH_GAMES);
        populate_game_buttons();
        switch (party_data.get_lang())
        {
        case JPN_ID:
            game = game_select_jpn.button_main();
            break;
        case KOR_ID:
            game = game_select_kor.button_main();
            break;
        default:
            game = game_select_def.button_main();
            break;
        }
        if (game == BUTTON_CANCEL)
        {
            return false;
        }
        party_data.set_game(game);
        return true;

    case CMD_SLIDE_PROF_LEFT:
        for (int i = 0; i < 48; i++)
        {
            obj_set_pos(prof, (prof->attr1 & ATTR1_X_MASK) - 2, prof->attr0 & ATTR0_Y_MASK);
            global_next_frame();
        }
        return true;

    case CMD_SLIDE_PROF_RIGHT:
        for (int i = 0; i < 48; i++)
        {
            obj_set_pos(prof, (prof->attr1 & ATTR1_X_MASK) + 2, prof->attr0 & ATTR0_Y_MASK);
            global_next_frame();
        }
        return true;

    case CMD_SHOW_LARGE_TEXTBOX:
        tte_erase_screen();
        obj_hide(prof);
        REG_BG2VOFS = BG2VOF_LARGE_TEXTBOX;
        return true;

    case CMD_HIDE_LARGE_TEXTBOX:
        tte_erase_screen();
        obj_unhide(prof, 0);
        REG_BG2VOFS = BG2VOF_SMALL_TEXTBOX;
        return true;

    case CMD_CONTINUE_LINK:
        party_data.continue_link();
        return true;

    case CMD_BOX_MENU:
        party_data.fill_simple_pkmn_array();
        box_viewer.box_main(party_data);
        return true;

    default:
        tte_set_pos(0, 0);
        tte_write("ERROR! No conditional found.");
        return false;
    }
}