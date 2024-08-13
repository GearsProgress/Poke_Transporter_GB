#include <tonc.h>
#include <cstring>
#include <cmath>
#include "sprite_data.h"
#include "debug_mode.h"

#define SPRITE_CHAR_BLOCK 4

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *)obj_buffer;

// These are the two pallets used by the menu sprites,
// it's easier to set them up this way instead of through grit
// (R + G*32 + B*1024)
#define RGB(r, g, b) (r + g * 32 + b * 1024)
#define WHITE RGB(31, 31, 31)
#define YELLOW RGB(31, 19, 10)
#define RED RGB(31, 7, 4)
#define BLACK RGB(0, 0, 0)
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

    REG_BG0CNT = BG_CBB(CBB) | BG_SBB(SBB) | BG_4BPP | BG_REG_32x32 | BG_PRIO(3);
}

void modify_background_pal(bool dark)
{
    if (dark)
    {
        memcpy(pal_bg_mem, &backgroundPal[4], 16);
    }
    else
    {
        memcpy(pal_bg_mem, backgroundPal, backgroundPalLen);
    }
}

#include "openingBG.h"
#include "fennelBG.h"
#include "dexBG.h"
void load_flex_background(int background_id, int layer)
{
    int CBB = 1;  // CBB is the tiles that make up the sprite
    int SBB = 15; // SSB is the array of which tile goes where
    switch (background_id)
    {
    case (BG_OPENING):
        // Load palette
        memcpy(pal_bg_mem + 32, openingBGPal, openingBGPalLen);
        // Load tiles into CBB 0
        memcpy(&tile_mem[CBB][0], openingBGTiles, openingBGTilesLen);
        // Load map into SBB 0
        memcpy(&se_mem[SBB][0], openingBGMap, openingBGMapLen);
        REG_BG1VOFS = 96;
        break;
    case (BG_FENNEL):
        // Load palette
        memcpy(pal_bg_mem + 32, fennelBGPal, fennelBGPalLen);
        // Load tiles into CBB 0
        memcpy(&tile_mem[CBB][0], fennelBGTiles, fennelBGTilesLen);
        // Load map into SBB 0
        memcpy(&se_mem[SBB][0], fennelBGMap, fennelBGMapLen);
        REG_BG1VOFS = 0;
        break;
    case (BG_DEX):
        // Load palette
        memcpy(pal_bg_mem + 32, dexBGPal, dexBGPalLen);
        // Load tiles into CBB 0
        memcpy(&tile_mem[CBB][0], dexBGTiles, dexBGTilesLen);
        // Load map into SBB 0
        memcpy(&se_mem[SBB][0], dexBGMap, dexBGMapLen);
        REG_BG1VOFS = 0;
        break;
    }

    REG_BG1CNT = BG_CBB(CBB) | BG_SBB(SBB) | BG_4BPP | BG_REG_32x32 | BG_PRIO(layer);
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

void reload_textbox_background()
{
    int SBB = 17;
    memcpy(&se_mem[SBB][0], textBoxBGMap, textBoxBGMapLen);
}

// tile ID, VH Flip, Palette Bank
#define TILE_CLEAR (0 | (0b00 << 0xA) | (1 << 0xC))
#define TILE_N (2 | (0b00 << 0xA) | (1 << 0xC))
#define TILE_NE (1 | (0b01 << 0xA) | (1 << 0xC))
#define TILE_E (3 | (0b01 << 0xA) | (1 << 0xC))
#define TILE_SE (5 | (0b01 << 0xA) | (1 << 0xC))
#define TILE_S (6 | (0b00 << 0xA) | (1 << 0xC))
#define TILE_SW (5 | (0b00 << 0xA) | (1 << 0xC))
#define TILE_W (3 | (0b00 << 0xA) | (1 << 0xC))
#define TILE_NW (1 | (0b00 << 0xA) | (1 << 0xC))
#define TILE_MID (4 | (0b00 << 0xA) | (1 << 0xC))
#define MENU_WIDTH 11 - 1

void add_menu_box(int options)
{
    int start = (32 * 13) + 18;
    int SBB = 17;

    se_mem[SBB][start] = TILE_NW;
    se_mem[SBB][start + MENU_WIDTH] = TILE_NE;
    se_mem[SBB][start + (32 * (options + 1))] = TILE_SW;
    se_mem[SBB][start + (32 * (options + 1)) + MENU_WIDTH] = TILE_SE;

    for (int i = 1; i < MENU_WIDTH; i++)
    {
        se_mem[SBB][start + i] = TILE_N;
        se_mem[SBB][start + ((32 * (options + 1))) + i] = TILE_S;
    }

    for (int i = 0; i < options; i++)
    {
        se_mem[SBB][start + (32 * (i + 1)) + MENU_WIDTH] = TILE_E;
        se_mem[SBB][start + (32 * (i + 1))] = TILE_W;
    }

    for (int x = 1; x < MENU_WIDTH; x++)
    {
        for (int y = 1; y < options + 1; y++)
        {
            se_mem[SBB][start + (32 * y) + x] = TILE_MID;
        }
    }
}

// SPRITES

int num_sprites = 0;
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
OBJ_ATTR *cart_shell = &obj_buffer[num_sprites++];
OBJ_ATTR *cart_label = &obj_buffer[num_sprites++];
OBJ_ATTR *flag = &obj_buffer[num_sprites++];

OBJ_ATTR *type_sprites[14] = {
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

OBJ_ATTR *up_arrow = &obj_buffer[num_sprites++];
OBJ_ATTR *down_arrow = &obj_buffer[num_sprites++];
OBJ_ATTR *point_arrow = &obj_buffer[num_sprites++];

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
    memcpy(pal_obj_mem + (BTN_PAL * 16), btn_t_lPal, btn_t_lPalLen);
    memcpy(pal_obj_mem + (BTN_LIT_PAL * 16), btn_t_rPal, btn_t_rPalLen);
    memcpy(pal_obj_mem + (LOGO_PAL * 16), ptgb_logo_lPal, ptgb_logo_lPalLen);
    memcpy(pal_obj_mem + (TYPES_PAL1 * 16), typesPal, typesPalLen);

    u32 curr_tile_id = 0;
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
    load_sprite(cart_label, &Label_GreenTiles[8], Label_GreenTilesLen - 32, curr_tile_id, CART_PAL, ATTR0_SQUARE, ATTR1_SIZE_32x32, 1);
    load_sprite(point_arrow, &arrowsTiles[32], 32, curr_tile_id, BTN_PAL, ATTR0_SQUARE, ATTR1_SIZE_8x8, 1);
    load_sprite(down_arrow, &arrowsTiles[0], 64, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_16x8, 1);
    load_sprite(up_arrow, &arrowsTiles[16], 64, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_16x8, 1);
    obj_set_pos(down_arrow, 14 * 8, 17 * 8);
    obj_set_pos(up_arrow, 14 * 8, 3 * 8);
    global_tile_id_end = curr_tile_id;
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

void load_type_sprites(int pkmn_index, int dex_offset, bool is_caught)
{
    if (is_caught)
    {
        u32 curr_tile_id = global_tile_id_end + (dex_offset * 2 * 4);
        int type1 = TYPES[pkmn_index][0];
        int type2 = TYPES[pkmn_index][1];

        //                                                  V this is super weird because Grit keeps adding in an extra blank tile. Not sure why.
        load_sprite(type_sprites[(dex_offset * 2) + 0], &typesTiles[(type1 * 32) + 8], 128, curr_tile_id, (type1 < 13 ? TYPES_PAL1 : TYPES_PAL2), ATTR0_WIDE, ATTR1_SIZE_32x8, 1);
        load_sprite(type_sprites[(dex_offset * 2) + 1], &typesTiles[(type2 * 32) + 8], 128, curr_tile_id, (type2 < 13 ? TYPES_PAL1 : TYPES_PAL2), ATTR0_WIDE, ATTR1_SIZE_32x8, 1);

        obj_set_pos(type_sprites[(dex_offset * 2) + 0], 19 * 8, (8 * 2 * dex_offset) + (8 * 4));
        obj_set_pos(type_sprites[(dex_offset * 2) + 1], 23 * 8, (8 * 2 * dex_offset) + (8 * 4));

        obj_unhide(type_sprites[(dex_offset * 2) + 0], 0);
        if (type1 != type2)
        {
            obj_unhide(type_sprites[(dex_offset * 2) + 1], 0);
        }
    }
    else
    {
        obj_hide(type_sprites[(dex_offset * 2) + 0]);
        obj_hide(type_sprites[(dex_offset * 2) + 1]);
    }
}

void load_sprite(OBJ_ATTR *sprite, const unsigned int objTiles[], int objTilesLen,
                 u32 &tile_id, u32 pal_bank, int attr0, int attr1, u32 priority)
{
    memcpy(&tile_mem[SPRITE_CHAR_BLOCK][tile_id], objTiles, objTilesLen);
    obj_set_attr(sprite, attr0, attr1, ATTR2_PALBANK(pal_bank) | tile_id | ATTR2_PRIO(priority));
    tile_id += objTilesLen / 32;
    obj_hide(sprite);
};

void load_cart(int game_id, int lang)
{
    //                                    Alpha         Shadow          Main Color       Grey             Black         Mid
    const unsigned short jpn_gb_pal[6] = {RGB(0, 0, 0), RGB(10, 9, 10), RGB(17, 17, 17), RGB(22, 22, 22), RGB(0, 0, 0), RGB(14, 13, 14)};
    const unsigned short eng_red_pal[6] = {RGB(0, 0, 0), RGB(16, 1, 0), RGB(27, 6, 5), RGB(22, 22, 22), RGB(0, 0, 0), RGB(23, 3, 2)};
    const unsigned short eng_blue_pal[6] = {RGB(0, 0, 0), RGB(0, 4, 16), RGB(5, 10, 24), RGB(22, 22, 22), RGB(0, 0, 0), RGB(1, 6, 20)};
    const unsigned short eng_yellow_pal[6] = {RGB(0, 0, 0), RGB(18, 12, 0), RGB(27, 21, 5), RGB(22, 22, 22), RGB(0, 0, 0), RGB(22, 16, 1)};
    const unsigned short eng_gold_pal[6] = {RGB(0, 0, 0), RGB(13, 10, 2), RGB(22, 18, 8), RGB(22, 22, 22), RGB(0, 0, 0), RGB(17, 14, 4)};
    const unsigned short eng_silver_pal[6] = {RGB(0, 0, 0), RGB(11, 12, 14), RGB(20, 22, 23), RGB(22, 22, 22), RGB(0, 0, 0), RGB(15, 16, 19)};
    const unsigned short crystal_pal[6] = {RGB(0, 0, 0), RGB(9, 13, 17), RGB(16, 21, 25), RGB(22, 22, 22), RGB(0, 0, 0), RGB(12, 17, 22)};
    const unsigned short jpn_gold_pal[6] = {RGB(0, 0, 0), RGB(0, 0, 0), RGB(5, 7, 12), RGB(22, 22, 22), RGB(0, 0, 0), RGB(3, 4, 8)};
    const unsigned short jpn_silver_pal[6] = {RGB(0, 0, 0), RGB(5, 4, 5), RGB(11, 10, 10), RGB(22, 22, 22), RGB(0, 0, 0), RGB(8, 7, 7)};

    const unsigned int *label_tiles = 0;
    const unsigned short *label_palette = 0;
    const unsigned int *cart_tiles = 0;
    const unsigned short *cart_palette = 0;
    switch (game_id)
    {
    case (GREEN_ID):
        label_tiles = Label_GreenTiles;
        label_palette = Label_GreenPal;
        cart_tiles = GB_ShellTiles;
        cart_palette = jpn_gb_pal;
        break;

    case (RED_ID):
        label_tiles = Label_RedTiles;
        label_palette = Label_RedPal;
        cart_tiles = GB_ShellTiles;
        if (lang == JPN_ID)
        {
            cart_palette = jpn_gb_pal;
        }
        else
        {
            cart_palette = eng_red_pal;
        }
        break;

    case (BLUE_ID):
        label_tiles = Label_BlueTiles;
        label_palette = Label_BluePal;
        cart_tiles = GB_ShellTiles;
        if (lang == JPN_ID)
        {
            cart_palette = jpn_gb_pal;
        }
        else
        {
            cart_palette = eng_blue_pal;
        }
        break;

    case (YELLOW_ID):
        label_tiles = Label_YellowTiles;
        label_palette = Label_YellowPal;
        cart_tiles = GB_ShellTiles;
        if (lang == JPN_ID)
        {
            cart_palette = jpn_gb_pal;
        }
        else
        {
            cart_palette = eng_yellow_pal;
        }
        break;

    case (GOLD_ID):
        label_tiles = Label_GoldTiles;
        label_palette = Label_GoldPal;
        if (lang == JPN_ID)
        {
            cart_tiles = GB_ShellTiles;
            cart_palette = jpn_gold_pal;
        }
        else if (lang == KOR_ID)
        {
            cart_tiles = GBC_ShellTiles;
            cart_palette = jpn_gold_pal;
        }
        else
        {
            cart_tiles = GBS_ShellTiles;
            cart_palette = eng_gold_pal;
        }
        break;

    case (SILVER_ID):
        label_tiles = Label_SilverTiles;
        label_palette = Label_SilverPal;
        if (lang == JPN_ID)
        {
            cart_tiles = GB_ShellTiles;
            cart_palette = jpn_silver_pal;
        }
        else if (lang == KOR_ID)
        {
            cart_tiles = GBC_ShellTiles;
            cart_palette = jpn_silver_pal;
        }
        else
        {
            cart_tiles = GBS_ShellTiles;
            cart_palette = eng_silver_pal;
        }
        break;

    case (CRYSTAL_ID):
        label_tiles = Label_CrystalTiles;
        label_palette = Label_CrystalPal;
        cart_tiles = GBCS_ShellTiles;
        cart_palette = crystal_pal;
        break;
    }
    u32 curr_tile_id = global_tile_id_end;

    memcpy(pal_obj_mem + (CART_PAL * 16), cart_palette, 12);
    memcpy(pal_obj_mem + (CART_PAL * 16) + 6, label_palette + 6, 20);
    load_sprite(cart_shell, cart_tiles, GB_ShellTilesLen, curr_tile_id, CART_PAL, ATTR0_SQUARE, ATTR1_SIZE_64x64, 1);
    load_sprite(cart_label, &label_tiles[8], Label_GreenTilesLen - 32, curr_tile_id, CART_PAL, ATTR0_SQUARE, ATTR1_SIZE_32x32, 1);
    int y_offset = sin((get_frame_count() * 4) % 360 * (3.1415 / 180)) * 5;
    obj_set_pos(cart_shell, (8 * 12) + 4, (8 * 4) + 11 + y_offset);
    obj_set_pos(cart_label, (8 * 12) + 4 + 8, (8 * 4) + 11 + 13 + y_offset);
    obj_unhide(cart_shell, 0);
    obj_unhide(cart_label, 0);
}

void load_flag(int lang_id)
{
    u32 curr_tile_id = global_tile_id_end;

    const unsigned int *flag_tiles = 0;
    const unsigned short *flag_palette = 0;
    switch (lang_id)
    {
    case JPN_ID:
        flag_tiles = flag_jpnTiles;
        flag_palette = flag_jpnPal;
        break;
    case ENG_ID:
        flag_tiles = flag_engTiles;
        flag_palette = flag_engPal;
        break;
    case FRE_ID:
        flag_tiles = flag_freTiles;
        flag_palette = flag_frePal;
        break;
    case ITA_ID:
        flag_tiles = flag_itaTiles;
        flag_palette = flag_itaPal;
        break;
    case GER_ID:
        flag_tiles = flag_gerTiles;
        flag_palette = flag_gerPal;
        break;
    case SPA_ID:
        flag_tiles = flag_spaTiles;
        flag_palette = flag_spaPal;
        break;
    case KOR_ID:
        flag_tiles = flag_korTiles;
        flag_palette = flag_korPal;
        break;
    }

    load_sprite(flag, flag_tiles, flag_jpnTilesLen, curr_tile_id, FLAG_PAL, ATTR0_WIDE, ATTR1_SIZE_32x64, 1);
    memcpy(pal_obj_mem + (FLAG_PAL * 16), flag_palette, 16); // Grit is being stupid.
    int y_offset = sin((get_frame_count() * 4) % 360 * (3.1415 / 180)) * 5;
    obj_set_pos(flag, (8 * 12) + 4, (8 * 4) + 19 + y_offset);
    obj_unhide(flag, 0);
}