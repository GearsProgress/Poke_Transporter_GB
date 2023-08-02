#include "script_array.h"
#include "script_obj.h"

#include <tonc.h>


script_obj script[6] = 
{
    script_obj("", 2, 1, 1),                                                                            // 0
    script_obj("Game not detected. Please turn off your system and upload the program again.", 2),      // 1
    script_obj("Welcome to Pokemon Mirror!", 3),                                                        // 2
    script_obj("Please connect your GBA to a GB in the trading room, and press A", 4, 2, 5),            // 3
    script_obj("Connection successful! Transfering in Pokemon now", 6),                                 // 4
    script_obj("Connection not found, please try again.", 3),                                           // 5
};

