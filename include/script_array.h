#ifndef SCRIPT_ARRAY_H
#define SCRIPT_ARRAY_H

#include "script_obj.h"
#include "pokemon_party.h"
#include "rom_data.h"

// Dialouge
#define DIA_OPEN                    0
#define DIA_E4                      1
#define DIA_MG_RS                   2
#define DIA_MG_FRLGE                3
#define DIA_START                   4
#define DIA_LETS_START              5
#define DIA_ERROR_1                 6
#define DIA_CONN_GOOD               7
#define DIA_LINK_GOOD               8
#define DIA_TRANS_GOOD              9    
#define DIA_NEW_DEX                 10
#define DIA_NO_NEW_DEX              11
#define DIA_SEND_FRIEND_HOENN_RS    12
#define DIA_SEND_FRIEND_KANTO       13
#define DIA_THANK                   14
#define DIA_GET_MON                 15
#define DIA_ERROR_TIME_ONE          16
#define DIA_ERROR_TIME_TWO          17
#define DIA_ERROR_DISCONNECT        18
#define DIA_ERROR_COM_ENDED         19
#define DIA_ERROR_COLOSSEUM         20
#define DIA_MG_OTHER_EVENT          21
#define DIA_PKMN_TO_COLLECT         22
#define DIA_NO_VALID_PKMN           23
#define DIA_WHAT_GAME_TRANS         24
#define DIA_WHAT_LANG_TRANS         25
#define DIA_ASK_QUEST               26
#define DIA_NO_GB_ROM               27
#define DIA_IN_BOX                  28
#define DIA_MYTHIC_CONVERT          29
#define DIA_CANCEL                  30
#define DIA_WHAT_LANG_EVENT         31
#define DIA_WHAT_GAME_EVENT         32
#define DIA_K_DEX_NOT_FULL          33
#define DIA_J_DEX_NOT_FULL          34
#define DIA_SOME_INVALID_PKMN       35
#define DIA_MENU_BACK               36
#define DIA_SEND_FRIEND_HOENN_E     37
#define DIA_IS_MISSINGNO            38

#define                    DIA_SIZE 39
#define DIA_END DIA_SIZE

// Commands
#define T_SCRIPT_START          DIA_END + 0
#define E_SCRIPT_START          DIA_END + 1
#define CMD_START_LINK          DIA_END + 2
#define CMD_IMPORT_POKEMON      DIA_END + 3     // This one is special because it can be true or false
#define CMD_BACK_TO_MENU        DIA_END + 4
#define CMD_SHOW_PROF           DIA_END + 5
#define CMD_HIDE_PROF           DIA_END + 6
#define CMD_SET_TUTOR_TRUE      DIA_END + 7
#define CMD_END_SCRIPT          DIA_END + 8
#define CMD_GAME_MENU           DIA_END + 9
#define CMD_LANG_MENU           DIA_END + 10
#define CMD_SLIDE_PROF_LEFT     DIA_END + 11
#define CMD_SLIDE_PROF_RIGHT    DIA_END + 12
#define CMD_CONTINUE_LINK       DIA_END + 13
#define CMD_BOX_MENU            DIA_END + 14
#define CMD_MYTHIC_MENU         DIA_END + 15
#define CMD_LOAD_SIMP           DIA_END + 16
#define CMD_CANCEL_LINK         DIA_END + 17
#define CMD_END_MISSINGNO       DIA_END + 18

#define                         CMD_SIZE  19
#define CMDS_END DIA_END + CMD_SIZE

// Conditionals
#define COND_ERROR_TIMEOUT_ONE      CMDS_END + 0    // Didn't talk to the Cable Club attendant fast enough or cable not connected
#define COND_ERROR_DISCONNECT       CMDS_END + 1    // If you unplug the cable after starting SPI
#define COND_ERROR_COM_ENDED        CMDS_END + 2    // If you don't save the game
#define COND_ERROR_TIMEOUT_TWO      CMDS_END + 3    // ???
#define COND_ERROR_COLOSSEUM        CMDS_END + 4    // If the player selects the battle colosseum (shouldn't be possible)
#define COND_BEAT_E4                CMDS_END + 5
#define COND_MG_ENABLED             CMDS_END + 6
#define COND_TUTORIAL_COMPLETE      CMDS_END + 7
#define COND_NEW_POKEMON            CMDS_END + 8
#define COND_IS_HOENN_RS            CMDS_END + 9
#define COND_IS_FRLGE               CMDS_END + 10
#define COND_MG_OTHER_EVENT         CMDS_END + 11
#define COND_PKMN_TO_COLLECT        CMDS_END + 12
#define COND_GB_ROM_EXISTS          CMDS_END + 13
#define COND_CHECK_MYTHIC           CMDS_END + 14
#define COND_CHECK_DEX              CMDS_END + 15
#define COND_CHECK_KANTO            CMDS_END + 16
#define COND_SOME_INVALID_PKMN      CMDS_END + 17
#define COND_IS_HOENN_E             CMDS_END + 18
#define COND_CHECK_MISSINGNO        CMDS_END + 19

#define                             COND_SIZE  20
#define COND_END CMDS_END + COND_SIZE

// Ends

#define SCRIPT_SIZE COND_END

extern script_obj transfer_script[];
extern script_obj event_script[];
extern rom_data curr_rom;

void populate_script();
void populate_dialogue();
void populate_lang_menu();
void populate_game_menu(int lang);
bool run_conditional(int index);

#endif