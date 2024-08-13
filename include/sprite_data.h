#ifndef SPRITE_DATA_H
#define SPRITE_DATA_H

#include <tonc.h>
#include "pokemon.h"
#include "pokemon_data.h"
#include "pokemon_party.h"

extern OBJ_ATTR obj_buffer[128];
extern OBJ_AFFINE *obj_aff_buffer;
extern int num_sprites;

// #include "metr.h"
// extern OBJ_ATTR *testroid;
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
#include "button_game_select_edge.h"

#include "types.h"
extern OBJ_ATTR *type_sprites[14];

#include "flag_jpn.h"
#include "flag_eng.h"
#include "flag_fre.h"
#include "flag_ita.h"
#include "flag_ger.h"
#include "flag_spa.h"
#include "flag_kor.h"
extern OBJ_ATTR *flag;
#include "Label_Green.h"
#include "Label_Red.h"
#include "Label_Blue.h"
#include "Label_Yellow.h"
#include "Label_Gold.h"
#include "Label_Silver.h"
#include "Label_Crystal.h"
extern OBJ_ATTR *cart_label;
#include "GB_Shell.h"
#include "GBC_Shell.h"
#include "GBS_Shell.h"
#include "GBCS_Shell.h"
extern OBJ_ATTR *cart_shell;

#include "arrows.h"
extern OBJ_ATTR *up_arrow;
extern OBJ_ATTR *down_arrow;
extern OBJ_ATTR *point_arrow;

#include "duel_frame_menu_sprites.h"
extern OBJ_ATTR *party_sprites[30];
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

#define BG2VOF_SMALL_TEXTBOX 96
#define BG2VOF_LARGE_TEXTBOX 0

#define METR_PAL 0
#define PROF_PAL 1
#define BTN_PAL 2
#define BTN_LIT_PAL 3
#define MENU_SPRITE_PAL 4
#define LOGO_PAL 5
#define TYPES_PAL1 6
#define TYPES_PAL2 7
#define CART_PAL 8
#define FLAG_PAL 9

#define BG_OPENING 0
#define BG_FENNEL 1
#define BG_DEX 2

void load_sprite(OBJ_ATTR *sprite, const unsigned int objTiles[], int objTilesLen,
                 u32 &tile_id, u32 pal_bank, int attr0, int attr1, u32 priority);
void load_background();
void modify_background_pal(bool dark);
void load_textbox_background();
void load_flex_background(int background_id, int layer);
void load_eternal_sprites();
void load_temp_box_sprites(Pokemon_Party party_data);
void load_type_sprites(int pkmn_index, int dex_offset, bool is_caught);
void add_menu_box(int options);
void reload_textbox_background();
void load_cart(int game_id, int lang);
void load_flag(int lang_id);

#endif