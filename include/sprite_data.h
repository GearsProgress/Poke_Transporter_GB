#ifndef SPRITE_DATA_H
#define SPRITE_DATA_H

#include <tonc.h>

extern OBJ_ATTR obj_buffer[128];
extern OBJ_AFFINE *obj_aff_buffer;
extern int num_sprites;

#include "metr.h"
extern OBJ_ATTR *testroid;
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

#include "dex_l.h"
#define DEX_SPRITE_LEFT 0
#include "dex_m.h"
#define DEX_SPRITE_MID 1
#include "dex_r.h"
#define DEX_SPRITE_RIGHT 2
extern OBJ_ATTR *dex_sprites[3][6];

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
#include "lang_arrow.h"
extern OBJ_ATTR *lang_arrow;

#define METR_PAL 0
#define PROF_PAL 1
#define BTN_PAL 2
#define BTN_LIT_PAL 3

void load_sprite(OBJ_ATTR *sprite, const unsigned int objTiles[], int objTilesLen,
                 u32 &tile_id, u32 pal_bank, int attr0, int attr1, u32 priority);
void load_background();
void load_textbox_background();
void load_opening_background();
void load_sprites();
void load_btn_lang_eng();
void load_btn_lang_fre();
void load_btn_lang_ita();
void load_btn_lang_ger();
void load_btn_lang_spa();
void load_btn_lang_kor();
void load_lang_arrow();

#endif