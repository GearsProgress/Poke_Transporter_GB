#include "script_array.h"
#include "main_menu.h"
#include "text_engine.h"
#include "script.h"
#include "sprite_data.h"
#include <tonc.h>

int last_error;
Pokemon_Party party_data;

script_obj script[SCRIPT_SIZE];
std::string_view dialouge[DIA_SIZE];

void populate_dialouge()
{
    dialouge[DIA_INDEX_OPEN] = "Hey there! I'm Professor Fennel. As you can see, I'm a scientist. In fact, the subject I'm researching is Trainers! My dream is to collect save files of various trainers, but I haven't had any breakthroughs yet. In the center of the region where I'm from, there's a location that can make a Pokemon's dreams into reality! This means that any other Pokemon they meet in their dreams become real! That's fantastic, but my goal is to do the same- but for a trainer! I've successfully been able send a Pokemon in and out of a trainer's dream, but I've been unsuccessful in pulling out a Pokemon without... catastrophic results. That's when I had a breakthrough- I realized if I sent in a DITTO, it could transform into the Pokemon found within that trainer's dream! That's why you're here today- I want to bring as many Pokemon out of your dreams as possible! There's just over 250 different Pokemon I want to catalogue in my Dream Pokedex- or Dream Dex for short. But I'll let you keep any Pokemon- they're from your dreams after all! I think that's everything... whenever you're ready, just let me know!";
    dialouge[DIA_INDEX_E4_1] = "Hi trainer! I'm thrilled\nyou've decided to help with our research, but we need\nthe best of the best!";
    dialouge[DIA_INDEX_E4_2] = "Come back once you've taken down the Elite Four!";
    dialouge[DIA_INDEX_MG] = "Looks like Mystery gift isn't enabled...";
    dialouge[DIA_INDEX_START] = "Alright then, let's get started! Please connect your Game Boy Advance to a Game Boy family system, using a Game Boy Color link cable. Load the Game Boy Pokemon game you want to transfer Pokemon from. Once both devices have been connected and the Game Boy Pokemon game has been loaded, press A.";
    dialouge[DIA_INDEX_ERROR_1] = "Hmm, it looks like something isn't right. Let's try that again!";
    dialouge[DIA_INDEX_CONN_GOOD] = "Great! Now head to the nearest Pokemon Center. Put any Pokemon you wish to bring out of your dreams into your party, and go to the Cable Club attendant. Ask them to perform a Link Trade, and then press A.";
    dialouge[DIA_INDEX_LINK_GOOD] = "We're almost set! Once you're ready, talk to the trainer across the table from you to start the process!";
    dialouge[DIA_INDEX_TRANS_GOOD] = "Amazing! Fantastic!! Everything went perfectly!";
    dialouge[DIA_INDEX_NEW_DEX] = "It looks like there's at least one new Pokemon here that isn't in the Dream Dex! I'll give it something extra sweet as a reward for you both.";
    dialouge[DIA_INDEX_NO_NEW_DEX] = "It doesn't look like there's anything new for your Dream Dex, but that's okay! Any research is good research!";
    dialouge[DIA_INDEX_SEND_FRIEND] = "I'll send these Pokemon to my friend Bill/Lannette so that you can pick them up. Did you know they developed the Storage System for the Kanto/Hoenn region? My younger sister developed the Storage System where I'm from, so Bill/Lannette is a good friend of ours!";
    dialouge[DIA_INDEX_THANK] = "Thank you so much for assisting with my research! Whenever you want to transfer more Pokemon, just let me know!";
}

void populate_script()
{
    
    script[SCRIPT_START] = script_obj(CMD_SHOW_PROF, COND_BEAT_E4);
    script[COND_BEAT_E4] = script_obj(COND_BEAT_E4, COND_MG_ENABLED, DIA_F_E4_1);
    script[COND_MG_ENABLED] = script_obj(COND_MG_ENABLED, DIA_F_START, DIA_F_MG);

    script[CMD_BACK_TO_MENU] = script_obj(CMD_BACK_TO_MENU, SCRIPT_START);

    script[DIA_F_START] = script_obj("welcome", CMD_START_LINK, DIA_F_CONN_GOOD);
    script[DIA_F_CONN_GOOD] = script_obj("good", CMD_IMPORT_POKEMON, CMD_BACK_TO_MENU);
    script[DIA_F_E4_1] = script_obj(dialouge[DIA_INDEX_E4_1], DIA_F_E4_2);
    script[DIA_F_E4_2] = script_obj(dialouge[DIA_INDEX_E4_2], CMD_HIDE_PROF, CMD_BACK_TO_MENU);
    script[DIA_F_MG] = script_obj(dialouge[DIA_INDEX_MG], CMD_HIDE_PROF, CMD_BACK_TO_MENU);
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
    // 21
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

    default:
        tte_set_pos(0, 0);
        tte_write("ERROR! No conditional found.");
        return false;
    }
}