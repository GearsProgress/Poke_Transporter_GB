#include <tonc.h>
#include <cstring>
#include "sprite_data.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *)obj_buffer;

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

// Don't forget to increase the number of sprites loaded in main!!