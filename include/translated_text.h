#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <string>
#include <tonc.h>

#define DIA_OPEN 0
#define DIA_E4 1
#define DIA_MG_FRLGE 2
#define DIA_MG_RS 3
#define DIA_LETS_START 4
#define DIA_START 5
#define DIA_TRANS_GOOD 6
#define DIA_NEW_DEX 7
#define DIA_NO_NEW_DEX 8
#define DIA_SEND_FRIEND_KANTO 9
#define DIA_SEND_FRIEND_HOENN_RS 10
#define DIA_SEND_FRIEND_HOENN_E 11
#define DIA_THANK 12
#define DIA_GET_MON 13
#define DIA_MG_OTHER_EVENT 14
#define DIA_PKMN_TO_COLLECT 15
#define DIA_NO_VALID_PKMN 16
#define DIA_ASK_QUEST 17
#define DIA_WHAT_GAME_TRANS 18
#define DIA_WHAT_LANG_TRANS 19
#define DIA_NO_GB_ROM 20
#define DIA_IN_BOX 21
#define DIA_MYTHIC_CONVERT 22
#define DIA_CANCEL 23
#define DIA_SOME_INVALID_PKMN 24
#define DIA_MENU_BACK 25
#define DIA_IS_MISSINGNO 26
#define DIA_ERROR_COLOSSEUM 27
#define DIA_ERROR_COM_ENDED 28
#define DIA_ERROR_DISCONNECT 29
#define DIA_ERROR_TIME_ONE 30
#define DIA_ERROR_TIME_TWO 31
#define DIA_WHAT_LANG_EVENT 32
#define DIA_WHAT_GAME_EVENT 33
#define DIA_K_DEX_NOT_FULL 34
#define DIA_J_DEX_NOT_FULL 35

#define DIA_SIZE 36
#define DIA_END DIA_SIZE

extern const byte *dialogue[DIA_SIZE];

extern const byte dia_textGreet_rse[];
extern const byte dia_textGreet_frlg[];
extern const byte dia_textMoveBox_rs[];
extern const byte dia_textMoveBox_frlg[];
extern const byte dia_textMoveBox_e[];
extern const byte dia_textWeHere_r[];
extern const byte dia_textWeHere_s[];
extern const byte dia_textWeHere_frlg[];
extern const byte dia_textWeHere_e[];
extern const byte dia_textRecieved[];
extern const byte dia_textYouMustBe_first[];
extern const byte dia_textYouMustBe_second[];
extern const byte dia_textIAm_first[];
extern const byte dia_textIAm_second[];
extern const byte dia_textPCConvo[];
extern const byte dia_textPCThanks[];
extern const byte dia_textThank[];
extern const byte dia_textPCFull[];
extern const byte dia_textLookerFull[];extern const byte option_english[];
extern const byte option_japanese[];
extern const byte option_spanish[];
extern const byte option_french[];
extern const byte option_german[];
extern const byte option_italian[];
extern const byte option_korean[];
extern const byte option_green[];
extern const byte option_red[];
extern const byte option_blue[];
extern const byte option_yellow[];
extern const byte option_gold[];
extern const byte option_silver[];
extern const byte option_crystal[];
extern const byte option_cancel[];
extern const byte press_start[];
extern const byte option_transfer[];
extern const byte option_dreamdex[];
extern const byte option_credits[];
extern const byte intro_first[];
extern const byte intro_legal[];
extern const byte cart_load_error[];
extern const byte pulled_cart_error[];
extern const byte send_multiboot_instructions[];
extern const byte send_multiboot_wait[];
extern const byte send_multiboot_success[];
extern const byte send_multiboot_failure[];
extern const byte kanto_name[];
extern const byte johto_name[];
extern const byte credits_page_1[];
extern const byte credits_page_2[];
extern const byte credits_page_3[];
extern const byte credits_page_4[];
extern const byte credits_page_5[];
extern const byte credits_page_6[];
extern const byte credits_page_7[];
extern const byte credits_page_8[];
extern const byte credits_page_9[];
extern const byte credits_page_10[];
extern const byte credits_page_11[];
extern const byte credits_page_12[];
extern const byte credits_page_13[];
extern const byte credits_page_14[];
extern const byte credits_page_15[];
extern const byte credits_page_16[];
extern const byte credits_page_17[];
extern const byte credits_page_18[];
extern const byte credits_page_19[];
extern const byte *PKMN_NAMES[252];

#endif