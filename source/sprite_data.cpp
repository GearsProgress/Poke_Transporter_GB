#include <tonc.h>
#include <cstring>
#include "sprite_data.h"
#include "debug_mode.h"

#define SPRITE_CHAR_BLOCK 4

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *)obj_buffer;

// These are the two pallets used by the menu sprites,
// it's easier to set them up this way instead of through grit
// (R + G*32 + B*1024)
#define WHITE (31 + 31 * 32 + 31 * 1024)
#define YELLOW (31 + 19 * 32 + 10 * 1024)
#define RED (31 + 07 * 32 + 04 * 1024)
#define BLACK (00 + 00 * 32 + 00 * 1024)
const unsigned short frame_one_pal[16] = {
    WHITE, WHITE, WHITE, WHITE,
    YELLOW, YELLOW, YELLOW, YELLOW,
    RED, RED, RED, RED,
    BLACK, BLACK, BLACK, BLACK};
const unsigned short frame_two_pal[16] = {
    WHITE,
    YELLOW,
    RED,
    BLACK,
    WHITE,
    YELLOW,
    RED,
    BLACK,
    WHITE,
    YELLOW,
    RED,
    BLACK,
    WHITE,
    YELLOW,
    RED,
    BLACK,
};

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

int num_sprites = 0;
//OBJ_ATTR *testroid = &obj_buffer[num_sprites++];
OBJ_ATTR *prof = &obj_buffer[num_sprites++];
OBJ_ATTR *ptgb_logo_l = &obj_buffer[num_sprites++];
OBJ_ATTR *ptgb_logo_r = &obj_buffer[num_sprites++];

OBJ_ATTR *btn_t_l = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_t_r = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_p_l = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_p_r = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_c_l = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_c_r = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_d_l = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_d_r = &obj_buffer[num_sprites++];
OBJ_ATTR *button_yes = &obj_buffer[num_sprites++];
OBJ_ATTR *button_no = &obj_buffer[num_sprites++];
OBJ_ATTR *button_blank_left = &obj_buffer[num_sprites++];
OBJ_ATTR *button_blank_right = &obj_buffer[num_sprites++];
OBJ_ATTR *button_blank_left_2 = &obj_buffer[num_sprites++];
OBJ_ATTR *button_blank_right_2 = &obj_buffer[num_sprites++];

OBJ_ATTR *dex_sprites[3][6] = { // Fills the dex sprites top to bottom, left to right
    {&obj_buffer[num_sprites++], &obj_buffer[num_sprites++], &obj_buffer[num_sprites++],
     &obj_buffer[num_sprites++], &obj_buffer[num_sprites++], &obj_buffer[num_sprites++]},
    {&obj_buffer[num_sprites++], &obj_buffer[num_sprites++], &obj_buffer[num_sprites++],
     &obj_buffer[num_sprites++], &obj_buffer[num_sprites++], &obj_buffer[num_sprites++]},
    {&obj_buffer[num_sprites++], &obj_buffer[num_sprites++], &obj_buffer[num_sprites++],
     &obj_buffer[num_sprites++], &obj_buffer[num_sprites++], &obj_buffer[num_sprites++]}};

OBJ_ATTR *btn_lang_jpn = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_lang_eng = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_lang_fre = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_lang_ita = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_lang_ger = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_lang_spa = &obj_buffer[num_sprites++];
OBJ_ATTR *btn_lang_kor = &obj_buffer[num_sprites++];

OBJ_ATTR *button_green_left = &obj_buffer[num_sprites++];
OBJ_ATTR *button_green_right = &obj_buffer[num_sprites++];
OBJ_ATTR *button_blue_left = &obj_buffer[num_sprites++];
OBJ_ATTR *button_blue_right = &obj_buffer[num_sprites++];
OBJ_ATTR *button_red_left = &obj_buffer[num_sprites++];
OBJ_ATTR *button_red_right = &obj_buffer[num_sprites++];
OBJ_ATTR *button_yellow_left = &obj_buffer[num_sprites++];
OBJ_ATTR *button_yellow_right = &obj_buffer[num_sprites++];
OBJ_ATTR *button_gold_left = &obj_buffer[num_sprites++];
OBJ_ATTR *button_gold_right = &obj_buffer[num_sprites++];
OBJ_ATTR *button_silver_left = &obj_buffer[num_sprites++];
OBJ_ATTR *button_silver_right = &obj_buffer[num_sprites++];
OBJ_ATTR *button_crystal_left = &obj_buffer[num_sprites++];
OBJ_ATTR *button_crystal_right = &obj_buffer[num_sprites++];

OBJ_ATTR *box_select = &obj_buffer[num_sprites++];

OBJ_ATTR *party_sprites[30] = {
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
    &obj_buffer[num_sprites++],
};

OBJ_ATTR *button_cancel_left = &obj_buffer[num_sprites++];
OBJ_ATTR *button_cancel_right = &obj_buffer[num_sprites++];
OBJ_ATTR *button_confirm_left = &obj_buffer[num_sprites++];
OBJ_ATTR *button_confirm_right = &obj_buffer[num_sprites++];

u32 global_tile_id_end = 0;

void load_eternal_sprites()
{
    //memcpy(pal_obj_mem + (METR_PAL * 16), metrPal, metrPalLen);
    memcpy(pal_obj_mem + (PROF_PAL * 16), profPal, profPalLen);
    memcpy(pal_obj_mem + (BTN_PAL * 16), btn_t_lPal, btn_t_lPalLen);
    memcpy(pal_obj_mem + (BTN_LIT_PAL * 16), btn_t_rPal, btn_t_rPalLen);
    memcpy(pal_obj_mem + (LOGO_PAL * 16), ptgb_logo_lPal, ptgb_logo_lPalLen);

    u32 curr_tile_id = 0;
    //load_sprite(testroid, metrTiles, metrTilesLen, curr_tile_id, METR_PAL, ATTR0_SQUARE, ATTR1_SIZE_64x64, 0);
    load_sprite(prof, profTiles, profTilesLen, curr_tile_id, PROF_PAL, ATTR0_SQUARE, ATTR1_SIZE_64x64, 2);
    load_sprite(ptgb_logo_l, ptgb_logo_lTiles, ptgb_logo_lTilesLen, curr_tile_id, LOGO_PAL, ATTR0_SQUARE, ATTR1_SIZE_64x64, 1);
    load_sprite(ptgb_logo_r, ptgb_logo_rTiles, ptgb_logo_rTilesLen, curr_tile_id, LOGO_PAL, ATTR0_SQUARE, ATTR1_SIZE_64x64, 1);
    load_sprite(btn_t_l, btn_t_lTiles, btn_t_lTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(btn_t_r, btn_t_rTiles, btn_t_rTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(btn_p_l, btn_p_lTiles, btn_p_lTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(btn_p_r, btn_p_rTiles, btn_p_rTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(btn_c_l, btn_c_lTiles, btn_c_lTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(btn_c_r, btn_c_rTiles, btn_c_rTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(btn_d_l, btn_d_lTiles, btn_d_lTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(btn_d_r, btn_d_rTiles, btn_d_rTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(button_yes, button_yesTiles, button_yesTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(button_no, button_noTiles, button_noTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(button_blank_left, button_blank_leftTiles, button_blank_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(button_blank_right, button_game_select_edgeTiles, button_game_select_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
    load_sprite(button_blank_left_2, button_blank_leftTiles, button_blank_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(button_blank_right_2, button_game_select_edgeTiles, button_game_select_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
    global_tile_id_end = curr_tile_id;
}

void load_temp_sprites(int sprite_batch_id)
{
    u32 curr_tile_id = global_tile_id_end;
    switch (sprite_batch_id)
    {
    case SPRITE_BATCH_DEX:
        for (int col = 0; col < 6; col++)
        {
            load_sprite(dex_sprites[DEX_SPRITE_LEFT][col], dex_lTiles, dex_lTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 2);
            load_sprite(dex_sprites[DEX_SPRITE_MID][col], dex_mTiles, dex_mTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 2);
            load_sprite(dex_sprites[DEX_SPRITE_RIGHT][col], dex_rTiles, dex_rTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_16x32, 2);
        }
        break;
    case SPRITE_BATCH_LANG:
        load_sprite(btn_lang_jpn, btn_lang_jpnTiles, btn_lang_jpnTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(btn_lang_eng, btn_lang_engTiles, btn_lang_engTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(btn_lang_fre, btn_lang_freTiles, btn_lang_freTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(btn_lang_ita, btn_lang_itaTiles, btn_lang_itaTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(btn_lang_ger, btn_lang_gerTiles, btn_lang_gerTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(btn_lang_spa, btn_lang_spaTiles, btn_lang_spaTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(btn_lang_kor, btn_lang_korTiles, btn_lang_korTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        break;

    case SPRITE_BATCH_GAMES:
        load_sprite(button_green_left, button_green_leftTiles, button_green_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(button_green_right, button_game_select_edgeTiles, button_game_select_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
        load_sprite(button_blue_left, button_blue_leftTiles, button_blue_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(button_blue_right, button_game_select_edgeTiles, button_game_select_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
        load_sprite(button_red_left, button_red_leftTiles, button_red_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(button_red_right, button_game_select_edgeTiles, button_game_select_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
        load_sprite(button_yellow_left, button_yellow_leftTiles, button_yellow_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(button_yellow_right, button_game_select_edgeTiles, button_game_select_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
        load_sprite(button_gold_left, button_gold_leftTiles, button_gold_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(button_gold_right, button_game_select_edgeTiles, button_game_select_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
        load_sprite(button_silver_left, button_silver_leftTiles, button_silver_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(button_silver_right, button_game_select_edgeTiles, button_game_select_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
        load_sprite(button_crystal_left, button_crystal_leftTiles, button_crystal_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
        load_sprite(button_crystal_right, button_game_select_edgeTiles, button_game_select_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
        break;
    }
}

void load_temp_box_sprites(Pokemon_Party party_data)
{
    u32 curr_tile_id = global_tile_id_end;
    for (int i = 0; i < 30; i++)
    {
        if (party_data.get_simple_pkmn(i).is_valid || SHOW_INVALID_PKMN)
        {
            load_sprite(party_sprites[i], &duel_frame_menu_spritesTiles[(MENU_SPRITES[party_data.get_simple_pkmn(i).dex_number] - 1) * 32], 256, curr_tile_id, MENU_SPRITE_PAL, ATTR0_SQUARE, ATTR1_SIZE_16x16, 1);
            obj_set_pos(party_sprites[i], (16 * (i % 10)) + 40, (16 * (i / 10)) + 24);
        }
        curr_tile_id += 4;
    }
    load_sprite(box_select, box_selectTiles, box_selectTilesLen, curr_tile_id, BTN_PAL, ATTR0_SQUARE, ATTR1_SIZE_16x16, 0);
    load_sprite(button_cancel_left, button_cancel_leftTiles, button_cancel_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(button_cancel_right, button_game_select_edgeTiles, button_game_select_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
    load_sprite(button_confirm_left, button_confirm_leftTiles, button_confirm_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(button_confirm_right, button_game_select_edgeTiles, button_game_select_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
}

void load_sprite(OBJ_ATTR *sprite, const unsigned int objTiles[], int objTilesLen,
                 u32 &tile_id, u32 pal_bank, int attr0, int attr1, u32 priority)
{
    memcpy(&tile_mem[SPRITE_CHAR_BLOCK][tile_id], objTiles, objTilesLen);
    obj_set_attr(sprite, attr0, attr1, ATTR2_PALBANK(pal_bank) | tile_id | ATTR2_PRIO(priority));
    tile_id += objTilesLen / 32;
    obj_hide(sprite);
};