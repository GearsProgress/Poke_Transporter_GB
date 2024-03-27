// This file is a MESS and needs to be made way more clean.

#include <tonc.h>
#include <cstring>
#include "sprite_data.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *)obj_buffer;

// BACKGROUNDS

#include "background.h"
void load_background()
{
    int CBB = 0;
    int SBB = 1;
    // Load palette
    memcpy(pal_bg_mem, backgroundPal, backgroundPalLen);
    // Load tiles into CBB 0
    memcpy(&tile_mem[CBB][0], backgroundTiles, backgroundTilesLen);
    // Load map into SBB 30
    memcpy(&se_mem[SBB][0], backgroundMap, backgroundMapLen);

    REG_BG0CNT = BG_CBB(CBB) | BG_SBB(SBB) | BG_4BPP | BG_REG_32x32 | BG_PRIO(2);
}

#include "openingBG.h"
void load_opening_background()
{
    int CBB = 1;
    int SBB = 9;
    // Load palette
    memcpy(pal_bg_mem + 32, openingBGPal, openingBGPalLen);
    // Load tiles into CBB 0
    memcpy(&tile_mem[CBB][0], openingBGTiles, openingBGTilesLen);
    // Load map into SBB 0
    memcpy(&se_mem[SBB][0], openingBGMap, openingBGMapLen);

    REG_BG1VOFS = 96;
    REG_BG1CNT = BG_CBB(CBB) | BG_SBB(SBB) | BG_4BPP | BG_REG_32x32 | BG_PRIO(1);
}

#include "textboxBG.h"
void load_textbox_background()
{
    int CBB = 2;
    int SBB = 17;
    // Load palette
    memcpy(pal_bg_mem + 16, textBoxBGPal, textBoxBGPalLen);
    // Load tiles into CBB 0
    memcpy(&tile_mem[CBB][0], textBoxBGTiles, textBoxBGTilesLen);
    // Load map into SBB 0
    memcpy(&se_mem[SBB][0], textBoxBGMap, textBoxBGMapLen);

    REG_BG2VOFS = 96;
    REG_BG2CNT = BG_CBB(CBB) | BG_SBB(SBB) | BG_4BPP | BG_REG_32x32 | BG_PRIO(3);
}

// SPRITES

#include "metr.h"
OBJ_ATTR *testroid = &obj_buffer[0];
void load_testroid()
{

    memcpy(&tile_mem[4][0], metrTiles, metrTilesLen);
    memcpy(pal_obj_mem, metrPal, metrPalLen);

    int x = 0, y = 0;
    u32 tid = 0, pb = 0; // tile id, pal-bank

    obj_set_attr(testroid,
                 ATTR0_SQUARE,
                 ATTR1_SIZE_64x64,
                 ATTR2_PALBANK(pb) | tid);

    obj_set_pos(testroid, x, y);
    obj_hide(testroid);
    // obj_unhide(testroid, 0);
}

#include "prof.h"
OBJ_ATTR *prof = &obj_buffer[1];
void load_professor()
{
    memcpy(&tile_mem[4][64], profTiles, profTilesLen);
    memcpy(pal_obj_mem + 16, profPal, profPalLen);

    int x = 96, y = 56;
    u32 tid = 64, pb = 1; // tile id, pal-bank

    obj_set_attr(prof,
                 ATTR0_SQUARE,
                 ATTR1_SIZE_64x64,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(2));
    obj_set_pos(prof, x, y);
    obj_hide(prof);
    //obj_unhide(prof, 0);
}

#include "btn_t_l.h"
OBJ_ATTR *btn_t_l = &obj_buffer[2];
void load_btn_t_l()
{
    memcpy(&tile_mem[4][128], btn_t_lTiles, btn_t_lTilesLen);
    memcpy(pal_obj_mem + 32, btn_t_lPal, btn_t_lPalLen);

    int x = 0, y = 0;
    u32 tid = 128, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_t_l,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));
    obj_set_pos(btn_t_l, x, y);
    obj_hide(btn_t_l);
    // obj_unhide(btn_t_l, 0);
}

#include "btn_t_r.h"
OBJ_ATTR *btn_t_r = &obj_buffer[3];
void load_btn_t_r()
{
    memcpy(&tile_mem[4][160], btn_t_rTiles, btn_t_rTilesLen);
    memcpy(pal_obj_mem + 48, btn_t_rPal, btn_t_rPalLen);

    int x = 0, y = 0;
    u32 tid = 160, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_t_r,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));

    obj_set_pos(btn_t_r, x, y);
    obj_hide(btn_t_r);
    // obj_unhide(btn_t_r, 0);
}

#include "btn_p_l.h"
OBJ_ATTR *btn_p_l = &obj_buffer[4];
void load_btn_p_l()
{
    memcpy(&tile_mem[4][192], btn_p_lTiles, btn_p_lTilesLen);
    // memcpy(pal_obj_mem + 32, btn_p_lPal, btn_p_lPalLen);

    int x = 0, y = 0;
    u32 tid = 192, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_p_l,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));
    obj_set_pos(btn_p_l, x, y);
    obj_hide(btn_p_l);
    // obj_unhide(btn_p_l, 0);
}

#include "btn_p_r.h"
OBJ_ATTR *btn_p_r = &obj_buffer[5];
void load_btn_p_r()
{
    memcpy(&tile_mem[4][224], btn_p_rTiles, btn_p_rTilesLen);
    // memcpy(pal_obj_mem + 48, btn_p_rPal, btn_p_rPalLen);

    int x = 0, y = 0;
    u32 tid = 224, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_p_r,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));

    obj_set_pos(btn_p_r, x, y);
    obj_hide(btn_p_r);
    // obj_unhide(btn_p_r, 0);
}

#include "btn_c_l.h"
OBJ_ATTR *btn_c_l = &obj_buffer[6];
void load_btn_c_l()
{
    memcpy(&tile_mem[4][256], btn_c_lTiles, btn_c_lTilesLen);
    // memcpy(pal_obj_mem + 32, btn_c_lPal, btn_c_lPalLen);

    int x = 0, y = 0;
    u32 tid = 256, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_c_l,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));
    obj_set_pos(btn_c_l, x, y);
    obj_hide(btn_c_l);
    // obj_unhide(btn_c_l, 0);
}

#include "btn_c_r.h"
OBJ_ATTR *btn_c_r = &obj_buffer[7];
void load_btn_c_r()
{
    memcpy(&tile_mem[4][288], btn_c_rTiles, btn_c_rTilesLen);
    // memcpy(pal_obj_mem + 48, btn_c_rPal, btn_c_rPalLen);

    int x = 0, y = 0;
    u32 tid = 288, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_c_r,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));

    obj_set_pos(btn_c_r, x, y);
    obj_hide(btn_c_r);
    // obj_unhide(btn_c_r, 0);
}

#include "dex_l.h"
OBJ_ATTR *dex_l[6] = {
    &obj_buffer[8],
    &obj_buffer[11],
    &obj_buffer[14],
    &obj_buffer[17],
    &obj_buffer[20],
    &obj_buffer[23]};

void load_dex_l()
{
    memcpy(&tile_mem[4][320], dex_lTiles, dex_lTilesLen);
    // memcpy(pal_obj_mem + 48, dex_lPal, dex_lPalLen);

    int x = 0, y = 0;
    u32 tid = 320, pb = 2; // tile id, pal-bank

    for (int i = 0; i < 6; i++)
    {
        obj_set_attr(dex_l[i],
                     ATTR0_WIDE,
                     ATTR1_SIZE_64x32,
                     ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(2));

        obj_set_pos(dex_l[i], x, y);
        obj_hide(dex_l[i]);
        // obj_unhide(dex_l, 0);
    }
}

#include "dex_m.h"
OBJ_ATTR *dex_m[6] = {
    &obj_buffer[9],
    &obj_buffer[12],
    &obj_buffer[15],
    &obj_buffer[18],
    &obj_buffer[21],
    &obj_buffer[24]};
void load_dex_m()
{
    memcpy(&tile_mem[4][352], dex_mTiles, dex_mTilesLen);
    // memcpy(pal_obj_mem + 48, dex_mPal, dex_mPalLen);

    int x = 0, y = 0;
    u32 tid = 352, pb = 2; // tile id, pal-bank
    for (int i = 0; i < 6; i++)
    {
        obj_set_attr(dex_m[i],
                     ATTR0_WIDE,
                     ATTR1_SIZE_64x32,
                     ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(2));

        obj_set_pos(dex_m[i], x, y);
        obj_hide(dex_m[i]);
        // obj_unhide(dex_m, 0);
    }
}

#include "dex_r.h"
OBJ_ATTR *dex_r[6] = {
    &obj_buffer[10],
    &obj_buffer[13],
    &obj_buffer[16],
    &obj_buffer[19],
    &obj_buffer[22],
    &obj_buffer[25]};
void load_dex_r()
{
    memcpy(&tile_mem[4][384], dex_rTiles, dex_rTilesLen);
    // memcpy(pal_obj_mem + 48, dex_rPal, dex_rPalLen);

    int x = 0, y = 0;
    u32 tid = 384, pb = 2; // tile id, pal-bank
    for (int i = 0; i < 6; i++)
    {
        obj_set_attr(dex_r[i],
                     ATTR0_TALL,
                     ATTR1_SIZE_16x32,
                     ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(2));

        obj_set_pos(dex_r[i], x, y);
        obj_hide(dex_r[i]);
        // obj_unhide(dex_r, 0);
    }
}

#include "btn_d_l.h"
OBJ_ATTR *btn_d_l = &obj_buffer[26];
void load_btn_d_l()
{
    memcpy(&tile_mem[4][416], btn_d_lTiles, btn_d_lTilesLen);
    memcpy(pal_obj_mem + 32, btn_d_lPal, btn_d_lPalLen);

    int x = 0, y = 0;
    u32 tid = 416, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_d_l,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));
    obj_set_pos(btn_d_l, x, y);
    obj_hide(btn_d_l);
    // obj_unhide(btn_d_l, 0);
}

#include "btn_d_r.h"
OBJ_ATTR *btn_d_r = &obj_buffer[27];
void load_btn_d_r()
{
    memcpy(&tile_mem[4][448], btn_d_rTiles, btn_d_rTilesLen);
    //memcpy(pal_obj_mem + 48, btn_d_rPal, btn_d_rPalLen);

    int x = 0, y = 0;
    u32 tid = 448, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_d_r,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));

    obj_set_pos(btn_d_r, x, y);
    obj_hide(btn_d_r);
    // obj_unhide(btn_d_r, 0);
}

#include "btn_lang_eng.h"
OBJ_ATTR *btn_lang_eng = &obj_buffer[28];
void load_btn_lang_eng()
{
    memcpy(&tile_mem[4][480], btn_lang_engTiles, btn_lang_engTilesLen);
    //memcpy(pal_obj_mem + 48, btn_lang_engPal, btn_lang_engPalLen);

    int x = 0, y = 0;
    u32 tid = 480, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_lang_eng,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));

    obj_set_pos(btn_lang_eng, x, y);
    obj_hide(btn_lang_eng);
    // obj_unhide(btn_lang_eng, 0);
}

#include "btn_lang_fre.h"
OBJ_ATTR *btn_lang_fre = &obj_buffer[29];
void load_btn_lang_fre()
{
    memcpy(&tile_mem[4][512], btn_lang_freTiles, btn_lang_freTilesLen);
    //memcpy(pal_obj_mem + 48, btn_lang_frePal, btn_lang_frePalLen);

    int x = 0, y = 0;
    u32 tid = 512, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_lang_fre,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));

    obj_set_pos(btn_lang_fre, x, y);
    obj_hide(btn_lang_fre);
    // obj_unhide(btn_lang_fre, 0);
}

#include "btn_lang_ita.h"
OBJ_ATTR *btn_lang_ita = &obj_buffer[30];
void load_btn_lang_ita()
{
    memcpy(&tile_mem[4][544], btn_lang_itaTiles, btn_lang_itaTilesLen);
    //memcpy(pal_obj_mem + 48, btn_lang_itaPal, btn_lang_itaPalLen);

    int x = 0, y = 0;
    u32 tid = 544, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_lang_ita,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));

    obj_set_pos(btn_lang_ita, x, y);
    obj_hide(btn_lang_ita);
    // obj_unhide(btn_lang_ita, 0);
}

#include "btn_lang_ger.h"
OBJ_ATTR *btn_lang_ger = &obj_buffer[31];
void load_btn_lang_ger()
{
    memcpy(&tile_mem[4][576], btn_lang_gerTiles, btn_lang_gerTilesLen);
    //memcpy(pal_obj_mem + 48, btn_lang_gerPal, btn_lang_gerPalLen);

    int x = 0, y = 0;
    u32 tid = 576, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_lang_ger,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));

    obj_set_pos(btn_lang_ger, x, y);
    obj_hide(btn_lang_ger);
    // obj_unhide(btn_lang_ger, 0);
}

#include "btn_lang_spa.h"
OBJ_ATTR *btn_lang_spa = &obj_buffer[32];
void load_btn_lang_spa()
{
    memcpy(&tile_mem[4][608], btn_lang_spaTiles, btn_lang_spaTilesLen);
    //memcpy(pal_obj_mem + 48, btn_lang_spaPal, btn_lang_spaPalLen);

    int x = 0, y = 0;
    u32 tid = 608, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_lang_spa,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));

    obj_set_pos(btn_lang_spa, x, y);
    obj_hide(btn_lang_spa);
    // obj_unhide(btn_lang_spa, 0);
}

#include "btn_lang_kor.h"
OBJ_ATTR *btn_lang_kor = &obj_buffer[33];
void load_btn_lang_kor()
{
    memcpy(&tile_mem[4][640], btn_lang_korTiles, btn_lang_korTilesLen);
    //memcpy(pal_obj_mem + 48, btn_lang_korPal, btn_lang_korPalLen);

    int x = 0, y = 0;
    u32 tid = 640, pb = 2; // tile id, pal-bank

    obj_set_attr(btn_lang_kor,
                 ATTR0_WIDE,
                 ATTR1_SIZE_64x32,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));

    obj_set_pos(btn_lang_kor, x, y);
    obj_hide(btn_lang_kor);
    // obj_unhide(btn_lang_kor, 0);
}

#include "lang_arrow.h"
OBJ_ATTR *lang_arrow = &obj_buffer[34];
void load_lang_arrow()
{
    memcpy(&tile_mem[4][672], lang_arrowTiles, lang_arrowTilesLen);
    //memcpy(pal_obj_mem + 48, lang_arrowPal, lang_arrowPalLen);

    int x = 0, y = 0;
    u32 tid = 672, pb = 2; // tile id, pal-bank

    obj_set_attr(lang_arrow,
                 ATTR0_SQUARE,
                 ATTR1_SIZE_8x8,
                 ATTR2_PALBANK(pb) | tid | ATTR2_PRIO(1));

    obj_set_pos(lang_arrow, x, y);
    obj_hide(lang_arrow);
    // obj_unhide(lang_arrow, 0);
}

