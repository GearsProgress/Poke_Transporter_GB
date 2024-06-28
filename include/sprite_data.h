#ifndef SPRITE_DATA_H
#define SPRITE_DATA_H

#include <tonc.h>
#include "pokemon.h"
#include "pokemon_data.h"
#include "pokemon_party.h"

extern OBJ_ATTR obj_buffer[128];
extern OBJ_AFFINE *obj_aff_buffer;
extern int num_sprites;

//#include "metr.h"
//extern OBJ_ATTR *testroid;
#include "prof.h"
extern OBJ_ATTR *prof;
#include "btn_t_l.h"
extern OBJ_ATTR *btn_t_l;
#include "btn_t_r.h"
extern OBJ_ATTR *btn_t_r;
#include "btn_p_l.h"
extern OBJ_ATTR *btn_p_l;
#include "btn_p_r.h"
extern OBJ_ATTR *btn_p_r;
#include "btn_c_l.h"
extern OBJ_ATTR *btn_c_l;
#include "btn_c_r.h"
extern OBJ_ATTR *btn_c_r;
#include "btn_d_l.h"
extern OBJ_ATTR *btn_d_l;
#include "btn_d_r.h"
extern OBJ_ATTR *btn_d_r;
#include "button_yes.h"
extern OBJ_ATTR *button_yes;
#include "button_no.h"
extern OBJ_ATTR *button_no;
#include "button_blank_left.h"
extern OBJ_ATTR *button_blank_left;
extern OBJ_ATTR *button_blank_right;
extern OBJ_ATTR *button_blank_left_2;
extern OBJ_ATTR *button_blank_right_2;

#define SPRITE_BATCH_DEX 0
#include "dex_l.h"
#define DEX_SPRITE_LEFT 0
#include "dex_m.h"
#define DEX_SPRITE_MID 1
#include "dex_r.h"
#define DEX_SPRITE_RIGHT 2
extern OBJ_ATTR *dex_sprites[3][6];

#define SPRITE_BATCH_LANG 1
#include "btn_lang_jpn.h"
extern OBJ_ATTR *btn_lang_jpn;
#include "btn_lang_eng.h"
extern OBJ_ATTR *btn_lang_eng;
#include "btn_lang_fre.h"
extern OBJ_ATTR *btn_lang_fre;
#include "btn_lang_ita.h"
extern OBJ_ATTR *btn_lang_ita;
#include "btn_lang_ger.h"
extern OBJ_ATTR *btn_lang_ger;
#include "btn_lang_spa.h"
extern OBJ_ATTR *btn_lang_spa;
#include "btn_lang_kor.h"
extern OBJ_ATTR *btn_lang_kor;

#define SPRITE_BATCH_GAMES 2
#include "button_green_left.h"
extern OBJ_ATTR *button_green_left;
extern OBJ_ATTR *button_green_right;
#include "button_blue_left.h"
extern OBJ_ATTR *button_blue_left;
extern OBJ_ATTR *button_blue_right;
#include "button_red_left.h"
extern OBJ_ATTR *button_red_left;
extern OBJ_ATTR *button_red_right;
#include "button_yellow_left.h"
extern OBJ_ATTR *button_yellow_left;
extern OBJ_ATTR *button_yellow_right;
#include "button_gold_left.h"
extern OBJ_ATTR *button_gold_left;
extern OBJ_ATTR *button_gold_right;
#include "button_silver_left.h"
extern OBJ_ATTR *button_silver_left;
extern OBJ_ATTR *button_silver_right;
#include "button_crystal_left.h"
extern OBJ_ATTR *button_crystal_left;
extern OBJ_ATTR *button_crystal_right;
#include "button_game_select_edge.h"

#include "duel_frame_menu_sprites.h"
extern OBJ_ATTR *party_sprites[30];
extern const unsigned short frame_one_pal[16];
extern const unsigned short frame_two_pal[16];
#include "box_select.h"
extern OBJ_ATTR *box_select;
#include "button_cancel_left.h"
extern OBJ_ATTR *button_cancel_left;
extern OBJ_ATTR *button_cancel_right;
#include "button_confirm_left.h"
extern OBJ_ATTR *button_confirm_left;
extern OBJ_ATTR *button_confirm_right;

#include "ptgb_logo_l.h"
extern OBJ_ATTR *ptgb_logo_l;
#include "ptgb_logo_r.h"
extern OBJ_ATTR *ptgb_logo_r;

#include "mario.h"

#define BG2VOF_SMALL_TEXTBOX 96
#define BG2VOF_LARGE_TEXTBOX 0

#define METR_PAL 0
#define PROF_PAL 1
#define BTN_PAL 2
#define BTN_LIT_PAL 3
#define MENU_SPRITE_PAL 4
#define LOGO_PAL 5

void load_sprite(OBJ_ATTR *sprite, const unsigned int objTiles[], int objTilesLen,
                 u32 &tile_id, u32 pal_bank, int attr0, int attr1, u32 priority);
void load_background();
void load_textbox_background();
void load_opening_background();
void load_eternal_sprites();
void load_temp_sprites(int sprite_batch_id);
void load_temp_box_sprites(Pokemon_Party party_data);

#endif