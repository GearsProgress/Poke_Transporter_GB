#include "script_array.h"
#include "script_obj.h"
#include "pokemon_party.h"

#include <tonc.h>

script_obj script[11] = 
{
    script_obj("", 2, CHECK_GAME, 1),                                                                   // 0
    script_obj("Game not detected. Please turn off your system and upload the program again.", 2),      // 1
    script_obj("Welcome to Pokemon Mirror!", 3),                                                        // 2
    script_obj("Please connect your GBA to a GB in the trading room, and press A", 4, START_LINK),      // 3
    script_obj("", 6, ERROR_COM_ENDED, 5),                                                              // 4
    script_obj("Error: Communication ended.", 3),                                                       // 5
    script_obj("", 8, ERROR_DISCONNECT, 7),                                                             // 6
    script_obj("Error: Cable disconnected.", 3),                                                        // 7
    script_obj("", 10, ERROR_TIMEOUT, 9),                                                               // 8
    script_obj("Error: Timed out.", 3),                                                                 // 9
    script_obj("Connection successful! Transfering in Pokemon now", 5),                                 // 10
};

void add_script_party_var(Pokemon_Party *var){
    for (int i = 0; i < 11; i++){
        script[i].link_party_var(var);
    }
}


