#include "script_array.h"
#include "main_menu.h"
#include "text_engine.h"
#include "mystery_gift_injector.h"
#include "sprite_data.h"
#include <tonc.h>

int last_error;
Pokemon_Party party_data;

script_obj script[SCRIPT_SIZE];
std::string_view dialogue[DIA_SIZE];

void populate_dialogue()
{
    dialogue[DIA_INDEX_OPEN] = "Hey there! I'm Professor\nFennel. As you can see, I'm\na scientist.|In fact, the subject I'm \nresearching is Trainers!|My dream is to collect save files of various trainers, \nbut I haven't had any \nbreakthroughs yet...|So in the meantime, I have a\ndifferent project!|In my home region, there's a\nlocation that can make a\nPokemon's dreams into\nreality.|This means that any other\nPokemon they meet in their\ndreams become real!|That's fantastic, but my\ngoal is to do the same-\njust with a trainer's dream\ninstead!|I've successfully been able\nto send a Pokemon into\nand out of a trainer's\ndream...|but I've been unsuccessful\nin pulling out a new Pokemon\nwithout...\ncatastrophic results.|That's when I had a\nbreakthrough- I realized if \nI sent in a DITTO,|it could transform into the\nPokemon found within that\ntrainer's dream!|That's why I need your help!\nI want to bring as many\nPokemon out of your dreams\nas possible!|There's just over 250\nPokemon I want to catalogue\nin my Dream Pokedex-\nor Dream Dex for short.|But I'll let you keep any\nPokemon- they're from your\ndreams after all!|I think that's everything...\nwhenever you're ready to\nstart, just let me know!";
    dialogue[DIA_INDEX_E4] = "Hi trainer! I'm thrilled\nyou've decided to help with our research, but we need\nthe best of the best!";
    dialogue[DIA_INDEX_MG] = "Looks like Mystery gift isn't enabled...";
    dialogue[DIA_INDEX_START] = "Please connect your Game Boy\nAdvance to a Game Boy family\nsystem|using a Game Boy Color link\ncable.|Load the Game Boy Pokemon game you want to transfer Pokemon from.|Once both devices have been connected and the Game Boy Pokemon game has been loaded, press A.";
    dialogue[DIA_INDEX_ERROR_1] = "Hmm, it looks like\nsomething isn't right.\nLet's try that again!";
    dialogue[DIA_INDEX_CONN_GOOD] = "Great! Now head to the\nearest Pokemon Center.|Put any Pokemon you wish\to bring out of your dreams into your party, and go to\the Cable Club attendant.|Ask them to perform a\nLink Trade, and then\npress A.|";
    dialogue[DIA_INDEX_LINK_GOOD] = "We're almost set!\nOnce you're ready,\ntalk to the trainer across the table from you\to start the process!";
    dialogue[DIA_INDEX_TRANS_GOOD] = "Amazing! Fantastic!!\nEverything went perfectly!";
    dialogue[DIA_INDEX_NEW_DEX] = "It looks like there's at\nleast one new Pokemon\nhere that isn't in the\nDream Dex!|I'll give it something extra\nsweet as a reward\nfor you both.";
    dialogue[DIA_INDEX_NO_NEW_DEX] = "It doesn't look like there's\nanything new for your Dream\nDex, but that's okay!|Any research is good\research!";
    dialogue[DIA_INDEX_SEND_FRIEND] = "I'll send these Pokemon to my friend Bill/Lannette so that you can pick them up. Did you know they developed the Storage System for the Kanto/Hoenn region? My younger sister developed the Storage System where I'm from, so Bill/Lannette is a good friend of ours!";
    dialogue[DIA_INDEX_THANK] = "Thank you so much for\nassisting with my research! Whenever you want to\ntransfer more Pokemon, just\nlet me know!";
    dialogue[DIA_INDEX_GET_MON] = "Get your Pokemon, press A, then talk to the link cable club person";

    dialogue[DIA_ERROR_COLOSSEUM] = "Went to colo";
    dialogue[DIA_ERROR_COM_ENDED] = "com ended";
    dialogue[DIA_ERROR_DISCONNECT] = "no cable";
    dialogue[DIA_ERROR_TIME_ONE] = "timeout 1";
    dialogue[DIA_ERROR_TIME_TWO] = "timeout 2";
}

void populate_script()
{
    // Check that the conditions are set for the transfer
    script[SCRIPT_START] = script_obj(CMD_SHOW_PROF, COND_BEAT_E4);
    script[COND_BEAT_E4] = script_obj(COND_BEAT_E4, COND_MG_ENABLED, DIA_INDEX_E4);
    script[DIA_INDEX_E4] = script_obj(dialogue[DIA_INDEX_E4], CMD_HIDE_PROF);
    script[COND_MG_ENABLED] = script_obj(COND_MG_ENABLED, COND_TUTORIAL_COMPLETE, DIA_INDEX_MG);
    script[DIA_INDEX_MG] = script_obj(dialogue[DIA_INDEX_E4], CMD_HIDE_PROF);
    script[COND_TUTORIAL_COMPLETE] = script_obj(COND_TUTORIAL_COMPLETE, DIA_INDEX_START, DIA_INDEX_OPEN);
    script[DIA_INDEX_OPEN] = script_obj(dialogue[DIA_INDEX_OPEN], CMD_HIDE_PROF);
    script[DIA_INDEX_START] = script_obj(dialogue[DIA_INDEX_GET_MON], CMD_START_LINK);
    script[CMD_START_LINK] = script_obj(CMD_START_LINK, COND_ERROR_TIMEOUT_ONE);

    // Initiate the transfer and check for errors
    script[COND_ERROR_TIMEOUT_ONE] = script_obj(COND_ERROR_TIMEOUT_ONE, COND_ERROR_TIMEOUT_TWO, DIA_ERROR_TIME_ONE);
    script[DIA_ERROR_TIME_ONE] = script_obj(dialogue[DIA_ERROR_TIME_ONE], DIA_INDEX_START);
    script[COND_ERROR_TIMEOUT_TWO] = script_obj(COND_ERROR_TIMEOUT_TWO, COND_ERROR_COM_ENDED, DIA_ERROR_TIME_TWO);
    script[DIA_ERROR_TIME_TWO] = script_obj(dialogue[DIA_ERROR_TIME_TWO], DIA_INDEX_START);
    script[COND_ERROR_COM_ENDED] = script_obj(COND_ERROR_COM_ENDED, COND_ERROR_COLOSSEUM, DIA_ERROR_COM_ENDED);
    script[DIA_ERROR_COM_ENDED] = script_obj(dialogue[DIA_ERROR_COM_ENDED], DIA_INDEX_START);
    script[COND_ERROR_COLOSSEUM] = script_obj(COND_ERROR_COLOSSEUM, COND_ERROR_DISCONNECT, DIA_ERROR_COLOSSEUM);
    script[DIA_ERROR_COLOSSEUM] = script_obj(dialogue[DIA_ERROR_COLOSSEUM], DIA_INDEX_START);
    script[COND_ERROR_DISCONNECT] = script_obj(COND_ERROR_DISCONNECT, DIA_INDEX_TRANS_GOOD, DIA_ERROR_DISCONNECT);
    script[DIA_ERROR_DISCONNECT] = script_obj(dialogue[DIA_ERROR_DISCONNECT], DIA_INDEX_START);

    // Complete the transfer and give messages based on the transfered Pokemon
    script[DIA_INDEX_TRANS_GOOD] = script_obj(dialogue[DIA_INDEX_TRANS_GOOD], CMD_HIDE_PROF);

    // Hide the dialouge and professor
    script[CMD_HIDE_PROF] = script_obj(CMD_HIDE_PROF, CMD_BACK_TO_MENU);
    script[CMD_BACK_TO_MENU] = script_obj(CMD_BACK_TO_MENU, SCRIPT_START);

    /*
    script[0] = script_obj("", 17, CMD_SHOW_PROF);                                                                                            // 0
    script[1] = script_obj("Game not detected. Please turn off your system and upload the program again.", 2);                            // 1
    script[2] = script_obj("Welcome to Pokemon Mirror!", 3);                                                                              // 2
    script[3] = script_obj("Please connect your GBA to a GB in the trading room, and press A", 4, CMD_START_LINK);                            // 3
    script[4] = script_obj("", 6, COND_ERROR_COM_ENDED, 5);                                                                                    // 4
    script[5] = script_obj("Error: Communication ended.", 3);                                                                             // 5
    script[6] = script_obj("", 8, COND_ERROR_DISCONNECT, 7);                                                                                   // 6
    script[7] = script_obj("Error: Cable disconnected.", 3);                                                                              // 7
    script[8] = script_obj("", 10, COND_ERROR_TIMEOUT_ONE, 9);                                                                                 // 8
    script[9] = script_obj("Error: Timed out (1).", 3);                                                                                   // 9
    script[10] = script_obj("", 12, COND_ERROR_TIMEOUT_TWO, 11);                                                                                // 10
    script[11] = script_obj("Error: Timed out (2)", 3);                                                                                    // 11
    script[12] = script_obj("", 14, COND_ERROR_COLOSSEUM, 13);                                                                                  // 12
    script[13] = script_obj("Error: Went into Colosseum", 3);                                                                              // 13
    script[14] = script_obj("Connection successful! Transfering in Pokemon now", 15);                                                      // 14
    script[15] = script_obj("", 16, CMD_IMPORT_POKEMON);                                                                                       // 15
    script[16] = script_obj("Bye!", 21);                                                                                                   // 16
    script[17] = script_obj("", 2, COND_BEAT_E4, 18);                                                                                           // 17
    script[18] = script_obj("Hi trainer! I'm thrilled\nyou've decided to help with our research, but we need\nthe best of the best!", 19); // 18                                                                                                             // 17
    script[19] = script_obj("Come back once you've taken down the Elite Four!", 20);                                                       // 19
    script[20] = script_obj("", 21, CMD_HIDE_PROF);                                                                                            // 20
    script[21] = script_obj("", 0, CMD_BACK_TO_MENU);
    */
};

void add_script_party_var(Pokemon_Party var)
{
    party_data = var;
}

bool run_conditional(int index)
{
    // Here is most of the logic that drives what lines show up where. It's probably not the best way to code it, but it works
    switch (index)
    {

    case CMD_START_LINK:
        party_data.start_link();
        return true;

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

    case CMD_IMPORT_POKEMON:
        party_data.load_pokemon();
        inject_mystery(party_data.get_full_pokemon_array());
        return true;

    case CMD_BACK_TO_MENU:
        text_disable();
        main_menu_exit();
        return true;

    case COND_BEAT_E4:
        return true;

    case CMD_SHOW_PROF:
        obj_unhide(prof, 0);
        return true;

    case CMD_HIDE_PROF:
        obj_hide(prof);
        return true;

    case COND_MG_ENABLED:
        return true;

    case COND_TUTORIAL_COMPLETE:
        return true;

    default:
        tte_set_pos(0, 0);
        tte_write("ERROR! No conditional found.");
        return false;
    }
}