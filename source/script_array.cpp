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
    dialogue[DIA_INDEX_E4] = "Hi trainer! I'm thrilled\nyou've decided to help with our research, but we need\nthe best of the best!|Come back after you've\nbeaten the Elite Four and\nbecome the Champion!";
    dialogue[DIA_INDEX_MG_FRLGE] = "Sorry trainer, one more\nthing to take care of before\nwe can begin- you need to\nenable MYSTERY GIFT!|Head to the nearest Pok@\nMart and fill out the\nquestionnaire as follows:\nLINK TOGETHER WITH ALL|After that, you should be\nall set to go!|See you soon!";
    dialogue[DIA_INDEX_MG_RS] = "Sorry trainer, one more\nthing to take care of before\nwe can begin- you need to\nenable MYSTERY EVENT!|Head to the PETALBURG\nPok@mon Center and tell the\nman next to the PC:\nMYSTERY EVENT IS EXCITING|After that, you should be\nall set to go!|See you soon!";
    dialogue[DIA_INDEX_LETS_START] = "Let's get started!";
    dialogue[DIA_INDEX_START] = "On a second Game Boy family\nsystem, please load the Game\nBoy Pok@mon game you wish to\ntransfer from.|In your Game Boy Pok@mon\ngame, put any Pokemon you\nwant to bring out of\nyour dreams into your party.|Then connect this Game Boy\nAdvance to the other Game\nBoy family system using a\nGame Boy Color link cable.|Once you're ready, press A\non this device, talk to the Cable Club attendant, and\nthen initiate a trade.";
    dialogue[DIA_INDEX_TRANS_GOOD] = "Amazing! Fantastic!\nEverything went perfectly!";
    dialogue[DIA_INDEX_NEW_DEX] = "It looks like there's at\nleast one new Pokemon here\nthat isn't in the Dream Dex!|I'll give them something\nextra sweet as a reward for you both.";
    dialogue[DIA_INDEX_NO_NEW_DEX] = "It doesn't look like there's\nanything new for your Dream\nDex, but that's okay!|Any research is good\research!";
    dialogue[DIA_INDEX_SEND_FRIEND_KANTO] = "I'm going to send these\nPokemon to my friend BILL so\nthat you can pick them up.\nThey live on Route 25!|Did you know they developed the Storage System for the\nKanto region?|My younger sister developed a version of the Storage\nSystem too, so BILL is a\ngood friend of ours!";
    dialogue[DIA_INDEX_SEND_FRIEND_HOENN] = "I'm going to send these\nPokemon to my friend LANNETE so\nthat you can pick them up.\nThey live on route 114!|Did you know they developed the Storage System for the\nHoenn region?|My younger sister developed a version of the Storage\nSystem too, so LANNETE is a\ngood friend of ours!";
    dialogue[DIA_INDEX_THANK] = "Thank you so much for your\nhelp! Whenever you want to\ntransfer more Pokemon, just\nlet me know!|See you around!";
    dialogue[DIA_INDEX_GET_MON] = "Let's get started! Please connect Load the Game Boy Pok@mon game you want to transfer from, and put the Pok@mon you want to transfer into your party. ";

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
    script[COND_BEAT_E4] = script_obj(COND_BEAT_E4, COND_MG_ENABLED, DIA_INDEX_E4);
    script[DIA_INDEX_E4] = script_obj(dialogue[DIA_INDEX_E4], CMD_HIDE_PROF);
    script[COND_MG_ENABLED] = script_obj(COND_MG_ENABLED, COND_TUTORIAL_COMPLETE, COND_IS_FRLGE);
    script[COND_IS_FRLGE] = script_obj(COND_IS_FRLGE, DIA_INDEX_MG_FRLGE, DIA_INDEX_MG_RS);
    script[DIA_INDEX_MG_FRLGE] = script_obj(dialogue[DIA_INDEX_MG_FRLGE], CMD_HIDE_PROF);
    script[DIA_INDEX_MG_RS] = script_obj(dialogue[DIA_INDEX_MG_RS], CMD_HIDE_PROF);
    script[COND_TUTORIAL_COMPLETE] = script_obj(COND_TUTORIAL_COMPLETE, DIA_INDEX_LETS_START, DIA_INDEX_OPEN);
    script[DIA_INDEX_OPEN] = script_obj(dialogue[DIA_INDEX_OPEN], CMD_SET_TUTOR_TRUE);
    script[CMD_SET_TUTOR_TRUE] = script_obj(CMD_SET_TUTOR_TRUE, CMD_HIDE_PROF);
    script[DIA_INDEX_LETS_START] = script_obj(dialogue[DIA_INDEX_LETS_START], DIA_INDEX_START);
    script[DIA_INDEX_START] = script_obj(dialogue[DIA_INDEX_START], CMD_START_LINK);
    script[CMD_START_LINK] = script_obj(CMD_START_LINK, COND_ERROR_TIMEOUT_ONE);

    // Initiate the transfer and check for errors
    script[COND_ERROR_TIMEOUT_ONE] = script_obj(COND_ERROR_TIMEOUT_ONE, COND_ERROR_TIMEOUT_TWO, DIA_ERROR_TIME_ONE);
    script[DIA_ERROR_TIME_ONE] = script_obj(dialogue[DIA_ERROR_TIME_ONE], DIA_INDEX_LETS_START);
    script[COND_ERROR_TIMEOUT_TWO] = script_obj(COND_ERROR_TIMEOUT_TWO, COND_ERROR_COM_ENDED, DIA_ERROR_TIME_TWO);
    script[DIA_ERROR_TIME_TWO] = script_obj(dialogue[DIA_ERROR_TIME_TWO], DIA_INDEX_LETS_START);
    script[COND_ERROR_COM_ENDED] = script_obj(COND_ERROR_COM_ENDED, COND_ERROR_COLOSSEUM, DIA_ERROR_COM_ENDED);
    script[DIA_ERROR_COM_ENDED] = script_obj(dialogue[DIA_ERROR_COM_ENDED], DIA_INDEX_LETS_START);
    script[COND_ERROR_COLOSSEUM] = script_obj(COND_ERROR_COLOSSEUM, COND_ERROR_DISCONNECT, DIA_ERROR_COLOSSEUM);
    script[DIA_ERROR_COLOSSEUM] = script_obj(dialogue[DIA_ERROR_COLOSSEUM], DIA_INDEX_LETS_START);
    script[COND_ERROR_DISCONNECT] = script_obj(COND_ERROR_DISCONNECT, DIA_INDEX_TRANS_GOOD, DIA_ERROR_DISCONNECT);
    script[DIA_ERROR_DISCONNECT] = script_obj(dialogue[DIA_ERROR_DISCONNECT], DIA_INDEX_LETS_START);

    // Complete the transfer and give messages based on the transfered Pokemon
    script[DIA_INDEX_TRANS_GOOD] = script_obj(dialogue[DIA_INDEX_TRANS_GOOD], CMD_IMPORT_POKEMON);
    script[CMD_IMPORT_POKEMON] = script_obj(CMD_IMPORT_POKEMON, COND_NEW_POKEMON);
    script[COND_NEW_POKEMON] = script_obj(COND_NEW_POKEMON, DIA_INDEX_NEW_DEX, DIA_INDEX_NO_NEW_DEX);
    script[DIA_INDEX_NEW_DEX] = script_obj(dialogue[DIA_INDEX_NEW_DEX], COND_IS_HOENN);
    script[DIA_INDEX_NO_NEW_DEX] = script_obj(dialogue[DIA_INDEX_NO_NEW_DEX], COND_IS_HOENN);
    script[COND_IS_HOENN] = script_obj(COND_IS_HOENN, DIA_INDEX_SEND_FRIEND_HOENN, DIA_INDEX_SEND_FRIEND_KANTO);
    script[DIA_INDEX_SEND_FRIEND_HOENN] = script_obj(dialogue[DIA_INDEX_SEND_FRIEND_HOENN], DIA_INDEX_THANK);
    script[DIA_INDEX_SEND_FRIEND_KANTO] = script_obj(dialogue[DIA_INDEX_SEND_FRIEND_KANTO], DIA_INDEX_THANK);
    script[DIA_INDEX_THANK] = script_obj(dialogue[DIA_INDEX_THANK], CMD_HIDE_PROF);

    // Hide the dialouge and professor
    script[CMD_HIDE_PROF] = script_obj(CMD_HIDE_PROF, CMD_BACK_TO_MENU);
    script[CMD_BACK_TO_MENU] = script_obj(CMD_BACK_TO_MENU, SCRIPT_START);
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
    // Emerald Flag ID 0x860 + 0x1F
    
        return true;

    case COND_MG_ENABLED:
    // Emerald flag ID (SYSTEM_FLAGS + 0x7B)
        return true;

    case COND_TUTORIAL_COMPLETE:
        return get_tutorial_flag();

    case COND_NEW_POKEMON:
        return true;

    case COND_IS_HOENN:
        return curr_rom.is_hoenn();

    case COND_IS_FRLGE:
        return !curr_rom.is_ruby_sapphire();

    case CMD_START_LINK:
        party_data.start_link();
        return true;

    case CMD_IMPORT_POKEMON:
        party_data.load_pokemon();
        inject_mystery(party_data.get_full_pokemon_array());
        return true;

    case CMD_BACK_TO_MENU:
        text_disable();
        main_menu_exit();
        return true;

    case CMD_SHOW_PROF:
        obj_unhide(prof, 0);
        return true;

    case CMD_HIDE_PROF:
        obj_hide(prof);
        return true;

    case CMD_SET_TUTOR_TRUE:
        set_tutorial_flag(true);
        return true;

    default:
        tte_set_pos(0, 0);
        tte_write("ERROR! No conditional found.");
        return false;
    }
}