#include <tonc.h>
#include <cstring>
#include "sprite_data.h"
#include "debug_mode.h"
#include "gba_rom_values/base_gba_rom_struct.h"

#define SPRITE_CHAR_BLOCK 4

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *)obj_buffer;
int curr_flex_background;
int y_offset = 0;
int y_offset_timer = 0;
int y_offset_direction = 1;
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

void set_background_pal(int curr_rom_id, bool dark, bool fade)
{
    COLOR new_pal_bg[8];
    new_pal_bg[0] = (!dark ? RGB15(0, 24, 16) : RGB15(0, 24, 16));
    switch (curr_rom_id)
    {
    case RUBY_ID:
        new_pal_bg[1] = (!dark ? RGB15(12, 3, 9) : RGB15(8, 2, 6));
        new_pal_bg[2] = (!dark ? RGB15(18, 6, 11) : RGB15(12, 4, 7));
        new_pal_bg[3] = (!dark ? RGB15(26, 12, 15) : RGB15(16, 8, 9));
        new_pal_bg[4] = (!dark ? RGB15(28, 19, 21) : RGB15(18, 12, 13));
        break;
    case SAPPHIRE_ID:
        new_pal_bg[1] = (!dark ? RGB15(7, 6, 13) : RGB15(4, 4, 8));
        new_pal_bg[2] = (!dark ? RGB15(7, 9, 21) : RGB15(4, 6, 13));
        new_pal_bg[3] = (!dark ? RGB15(13, 15, 28) : RGB15(8, 10, 18));
        new_pal_bg[4] = (!dark ? RGB15(20, 21, 28) : RGB15(13, 13, 18));
        break;
    case FIRERED_ID:
        new_pal_bg[1] = (!dark ? RGB15(15, 4, 4) : RGB15(9, 3, 3));
        new_pal_bg[2] = (!dark ? RGB15(19, 8, 6) : RGB15(12, 5, 4));
        new_pal_bg[3] = (!dark ? RGB15(24, 13, 10) : RGB15(15, 8, 6));
        new_pal_bg[4] = (!dark ? RGB15(28, 23, 21) : RGB15(17, 14, 13));
        break;
    case LEAFGREEN_ID:
        new_pal_bg[1] = (!dark ? RGB15(5, 11, 5) : RGB15(3, 7, 3));
        new_pal_bg[2] = (!dark ? RGB15(9, 17, 7) : RGB15(6, 11, 4));
        new_pal_bg[3] = (!dark ? RGB15(17, 22, 11) : RGB15(10, 14, 7));
        new_pal_bg[4] = (!dark ? RGB15(24, 26, 19) : RGB15(15, 16, 12));
        break;
    case EMERALD_ID:
        new_pal_bg[1] = (!dark ? RGB15(5, 10, 10) : RGB15(3, 6, 6));
        new_pal_bg[2] = (!dark ? RGB15(7, 15, 13) : RGB15(5, 9, 8));
        new_pal_bg[3] = (!dark ? RGB15(11, 22, 13) : RGB15(7, 14, 8));
        new_pal_bg[4] = (!dark ? RGB15(20, 26, 20) : RGB15(12, 16, 13));
        break;
    case 0xFF: // MissingNo
        new_pal_bg[1] = RGB15(3, 2, 2);
        new_pal_bg[2] = RGB15(31, 31, 30);
        new_pal_bg[3] = RGB15(29, 22, 17);
        new_pal_bg[4] = RGB15(15, 14, 18);
        break;
    default:
        new_pal_bg[1] = (!dark ? RGB15(7, 7, 11) : RGB15(0, 0, 0));
        new_pal_bg[2] = (!dark ? RGB15(13, 13, 16) : RGB15(0, 0, 0));
        new_pal_bg[3] = (!dark ? RGB15(18, 18, 20) : RGB15(0, 0, 0));
        new_pal_bg[4] = (!dark ? RGB15(21, 21, 23) : RGB15(0, 0, 0));
        break;
    }
    if (fade)
    {
#define NUM_CYCLES 30.0
        COLOR curr_pal_bg[8];
        COLOR old_pal[3];
        COLOR new_pal[3];
        memcpy(curr_pal_bg, &pal_bg_mem[0], 16);
        for (int n = 0; n <= NUM_CYCLES; n++)
        {
            for (int i = 1; i < 5; i++)
            {
                for (int b = 0; b < 3; b++)
                {
                    old_pal[b] = (curr_pal_bg[i] >> (b * 5)) & 0b11111;
                    new_pal[b] = (new_pal_bg[i] >> (b * 5)) & 0b11111;
                }
                pal_bg_mem[i] = RGB15(
                    (((NUM_CYCLES - n) / NUM_CYCLES) * old_pal[0]) + ((n / NUM_CYCLES) * new_pal[0]),
                    (((NUM_CYCLES - n) / NUM_CYCLES) * old_pal[1]) + ((n / NUM_CYCLES) * new_pal[1]),
                    (((NUM_CYCLES - n) / NUM_CYCLES) * old_pal[2]) + ((n / NUM_CYCLES) * new_pal[2]));
            }
            global_next_frame();
        }
    }
    else
    {
        memcpy(pal_bg_mem, &new_pal_bg[0], 16);
        // memcpy(&pal_bg_mem[4], &new_pal_bg[4], 2);
    }
    (pal_obj_mem + (BTN_LIT_PAL * 16))[7] = pal_bg_mem[1];
    (pal_obj_mem + (BTN_LIT_PAL * 16))[8] = pal_bg_mem[1];
    (pal_obj_mem + (BTN_LIT_PAL * 16))[9] = pal_bg_mem[1];
    (pal_obj_mem + (BTN_LIT_PAL * 16))[10] = pal_bg_mem[3];
    pal_bg_bank[14][15] = pal_bg_mem[3];
}

#include "openingBG.h"
#include "fennelBG.h"
#include "dexBG.h"
#include "menu_bars.h"
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
        REG_BG1VOFS = FENNEL_SHIFT;
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
    case (BG_MAIN_MENU):
        // Load palette
        memcpy(pal_bg_mem + 32, pal_bg_mem, backgroundPalLen);
        // Load tiles into CBB 0
        memcpy(&tile_mem[CBB][0], menu_barsTiles, menu_barsTilesLen);
        // Load map into SBB 0
        memcpy(&se_mem[SBB][0], menu_barsMap, menu_barsMapLen);
        REG_BG1VOFS = 0;
        break;
    }
    REG_BG1CNT = BG_CBB(CBB) | BG_SBB(SBB) | BG_4BPP | BG_REG_32x32 | BG_PRIO(layer);
    curr_flex_background = background_id;
}
#include "textBoxBG.h"
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

OBJ_ATTR *gba_cart = &obj_buffer[num_sprites++];
OBJ_ATTR *link_frame1 = &obj_buffer[num_sprites++];
OBJ_ATTR *link_frame2 = &obj_buffer[num_sprites++];
OBJ_ATTR *link_frame3 = &obj_buffer[num_sprites++];
OBJ_ATTR *link_blob1 = &obj_buffer[num_sprites++];
OBJ_ATTR *link_blob2 = &obj_buffer[num_sprites++];
OBJ_ATTR *link_blob3 = &obj_buffer[num_sprites++];

u32 global_tile_id_end = 0;

void load_eternal_sprites()
{
    memcpy(pal_obj_mem + (BTN_PAL * 16), button_noPal, button_noPalLen);
    memcpy(pal_obj_mem + (BTN_LIT_PAL * 16), button_yesPal, button_yesPalLen);
    memcpy(pal_obj_mem + (LOGO_PAL * 16), ptgb_logo_lPal, ptgb_logo_lPalLen);
    memcpy(pal_obj_mem + (TYPES_PAL1 * 16), typesPal, typesPalLen);
    memcpy(pal_obj_mem + (LINK_CABLE_PAL * 16), link_frame1Pal, link_frame1PalLen);

    u32 curr_tile_id = 0;
    load_sprite(ptgb_logo_l, ptgb_logo_lTiles, ptgb_logo_lTilesLen, curr_tile_id, LOGO_PAL, ATTR0_SQUARE, ATTR1_SIZE_64x64, 1);
    load_sprite(ptgb_logo_r, ptgb_logo_rTiles, ptgb_logo_rTilesLen, curr_tile_id, LOGO_PAL, ATTR0_SQUARE, ATTR1_SIZE_64x64, 1);
    load_sprite(button_yes, button_yesTiles, button_yesTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(button_no, button_noTiles, button_noTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(cart_label, &Label_GreenTiles[8], Label_GreenTilesLen - 32, curr_tile_id, GB_CART_PAL, ATTR0_SQUARE, ATTR1_SIZE_32x32, 1);
    load_sprite(point_arrow, &arrowsTiles[32], 32, curr_tile_id, BTN_PAL, ATTR0_SQUARE, ATTR1_SIZE_8x8, 1);
    load_sprite(down_arrow, &arrowsTiles[0], 64, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_16x8, 1);
    load_sprite(up_arrow, &arrowsTiles[16], 64, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_16x8, 1);
    load_sprite(link_frame1, link_frame1Tiles, link_frame1TilesLen, curr_tile_id, LINK_CABLE_PAL, ATTR0_SQUARE, ATTR1_SIZE_32x32, 1);
    load_sprite(link_frame2, link_frame2Tiles, link_frame2TilesLen, curr_tile_id, LINK_CABLE_PAL, ATTR0_WIDE, ATTR1_SIZE_8x32, 1);
    load_sprite(link_frame3, link_frame3Tiles, link_frame3TilesLen, curr_tile_id, LINK_CABLE_PAL, ATTR0_WIDE, ATTR1_SIZE_16x32, 1);
    load_sprite(link_blob1, &link_blobsTiles[0], 32, curr_tile_id, LINK_CABLE_PAL, ATTR0_SQUARE, ATTR1_SIZE_8x8, 1);
    load_sprite(link_blob2, &link_blobsTiles[8], 32, curr_tile_id, LINK_CABLE_PAL, ATTR0_SQUARE, ATTR1_SIZE_8x8, 1);
    load_sprite(link_blob3, &link_blobsTiles[16], 32, curr_tile_id, LINK_CABLE_PAL, ATTR0_SQUARE, ATTR1_SIZE_8x8, 1);

    global_tile_id_end = curr_tile_id;

    obj_set_pos(down_arrow, 14 * 8, 17 * 8);
    obj_set_pos(up_arrow, 14 * 8, 3 * 8);
}

void load_temp_box_sprites(Pokemon_Party party_data)
{
    u32 curr_tile_id = global_tile_id_end;
    for (int i = 0; i < 30; i++)
    {
        if (party_data.get_simple_pkmn(i).is_valid || NO_INVALID_PKMN)
        {
            Simplified_Pokemon curr_pkmn = party_data.get_simple_pkmn(i);
            int dex_num = curr_pkmn.dex_number;
            if (dex_num == 201)
            {
                dex_num = 252 + curr_pkmn.unown_letter;
            }
            else if (curr_pkmn.is_missingno)
            {
                dex_num = 0;
            }
            load_sprite(party_sprites[i], &unique_duel_frame_menu_spritesTiles[dex_num * 32], 256, curr_tile_id, MENU_SPRITE_PALS[dex_num][curr_pkmn.is_shiny] + MENU_PAL_START, ATTR0_SQUARE, ATTR1_SIZE_16x16, 1);
            obj_set_pos(party_sprites[i], (16 * (i % 10)) + 40, (16 * (i / 10)) + 24);
            obj_unhide(party_sprites[i], 0);
        }
        curr_tile_id += 4;
    }
    load_sprite(box_select, box_selectTiles, box_selectTilesLen, curr_tile_id, BTN_PAL, ATTR0_SQUARE, ATTR1_SIZE_16x16, 0);
    load_sprite(button_cancel_left, button_cancel_leftTiles, button_cancel_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(button_cancel_right, button_edgeTiles, button_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
    load_sprite(button_confirm_left, button_confirm_leftTiles, button_confirm_leftTilesLen, curr_tile_id, BTN_PAL, ATTR0_WIDE, ATTR1_SIZE_64x32, 1);
    load_sprite(button_confirm_right, button_edgeTiles, button_edgeTilesLen, curr_tile_id, BTN_PAL, ATTR0_TALL, ATTR1_SIZE_8x32, 1);
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

void load_select_sprites(int game_id, int lang)
{
    u32 curr_tile_id = global_tile_id_end;
    //                                    Alpha         Shadow          Main Color       Grey             Black         Mid
    const unsigned short jpn_gb_pal[6] = {RGB15(0, 0, 0), RGB15(10, 9, 10), RGB15(17, 17, 17), RGB15(22, 22, 22), RGB15(0, 0, 0), RGB15(14, 13, 14)};
    const unsigned short eng_red_pal[6] = {RGB15(0, 0, 0), RGB15(16, 1, 0), RGB15(27, 6, 5), RGB15(22, 22, 22), RGB15(0, 0, 0), RGB15(23, 3, 2)};
    const unsigned short eng_blue_pal[6] = {RGB15(0, 0, 0), RGB15(0, 4, 16), RGB15(5, 10, 24), RGB15(22, 22, 22), RGB15(0, 0, 0), RGB15(1, 6, 20)};
    const unsigned short eng_yellow_pal[6] = {RGB15(0, 0, 0), RGB15(18, 12, 0), RGB15(27, 21, 5), RGB15(22, 22, 22), RGB15(0, 0, 0), RGB15(22, 16, 1)};
    const unsigned short eng_gold_pal[6] = {RGB15(0, 0, 0), RGB15(13, 10, 2), RGB15(22, 18, 8), RGB15(22, 22, 22), RGB15(0, 0, 0), RGB15(17, 14, 4)};
    const unsigned short eng_silver_pal[6] = {RGB15(0, 0, 0), RGB15(11, 12, 14), RGB15(20, 22, 23), RGB15(22, 22, 22), RGB15(0, 0, 0), RGB15(15, 16, 19)};
    const unsigned short crystal_pal[6] = {RGB15(0, 0, 0), RGB15(9, 13, 17), RGB15(16, 21, 25), RGB15(22, 22, 22), RGB15(0, 0, 0), RGB15(12, 17, 22)};
    const unsigned short jpn_gold_pal[6] = {RGB15(0, 0, 0), RGB15(0, 0, 0), RGB15(5, 7, 12), RGB15(22, 22, 22), RGB15(0, 0, 0), RGB15(3, 4, 8)};
    const unsigned short jpn_silver_pal[6] = {RGB15(0, 0, 0), RGB15(5, 4, 5), RGB15(11, 10, 10), RGB15(22, 22, 22), RGB15(0, 0, 0), RGB15(8, 7, 7)};

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

    memcpy(pal_obj_mem + (GB_CART_PAL * 16), cart_palette, 12);
    memcpy(pal_obj_mem + (GB_CART_PAL * 16) + 6, label_palette + 6, 20);
    load_sprite(cart_shell, cart_tiles, GB_ShellTilesLen, curr_tile_id, GB_CART_PAL, ATTR0_SQUARE, ATTR1_SIZE_64x64, 1);
    load_sprite(cart_label, &label_tiles[8], Label_GreenTilesLen - 32, curr_tile_id, GB_CART_PAL, ATTR0_SQUARE, ATTR1_SIZE_32x32, 1);

    const unsigned int *flag_tiles = 0;
    const unsigned short *flag_palette = 0;
    switch (lang)
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

    const unsigned int *gba_cart_tiles = 0;
    const unsigned short *gba_cart_palette = 0;
    switch (curr_rom.gamecode)
    {

    case RUBY_ID:
        gba_cart_tiles = ruby_cartTiles;
        gba_cart_palette = ruby_cartPal;
        break;
    case SAPPHIRE_ID:
        gba_cart_tiles = sapphire_cartTiles;
        gba_cart_palette = sapphire_cartPal;
        break;
    case FIRERED_ID:
        gba_cart_tiles = fr_cartTiles;
        gba_cart_palette = fr_cartPal;
        break;
    case LEAFGREEN_ID:
        gba_cart_tiles = lg_cartTiles;
        gba_cart_palette = lg_cartPal;
        break;
    case EMERALD_ID:
        gba_cart_tiles = emerald_cartTiles;
        gba_cart_palette = emerald_cartPal;
        break;
    }

    load_sprite(gba_cart, gba_cart_tiles, 1024, curr_tile_id, GBA_CART_PAL, ATTR0_WIDE, ATTR1_SIZE_32x64, 1);
    memcpy(pal_obj_mem + (GBA_CART_PAL * 16), gba_cart_palette, 32);
}
// tile ID, VH Flip, Palette Bank
#define FEN_BLI_L00 (34 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_BLI_L01 (35 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_BLI_L10 (140 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_BLI_L11 (141 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_BLI_L20 (143 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_BLI_L21 (144 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_BLI_R0 (37 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_BLI_R1 (142 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_BLI_R2 (145 | (0b00 << 0xA) | (2 << 0xC))

// tile ID, VH Flip, Palette Bank
#define FEN_SPE_00 (46 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_SPE_01 (56 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_SPE_10 (146 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_SPE_11 (56 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_SPE_20 (147 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_SPE_21 (149 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_SPE_30 (148 | (0b00 << 0xA) | (2 << 0xC))
#define FEN_SPE_31 (150 | (0b00 << 0xA) | (2 << 0xC))

void fennel_blink(int frame)
{
    bool missingno = get_missingno_enabled();
    int SBB = 15; // SSB is the array of which tile goes where
    switch (frame)
    {
    case 0:
        se_mem[SBB][12 + (5 * 32)] = missingno ? FEN_SPE_00 | FEN_BLI_L20 : FEN_BLI_L20;
        se_mem[SBB][13 + (5 * 32)] = missingno ? FEN_SPE_01 | FEN_BLI_L21 : FEN_BLI_L21;
        se_mem[SBB][15 + (5 * 32)] = missingno ? FEN_SPE_10 | FEN_BLI_R2 : FEN_BLI_R2;
        break;
    case 1:
    case 3:
        se_mem[SBB][12 + (5 * 32)] = missingno ? FEN_SPE_11 | FEN_BLI_L10 : FEN_BLI_L10;
        se_mem[SBB][13 + (5 * 32)] = missingno ? FEN_SPE_20 | FEN_BLI_L11 : FEN_BLI_L11;
        se_mem[SBB][15 + (5 * 32)] = missingno ? FEN_SPE_21 | FEN_BLI_R1 : FEN_BLI_R1;
        break;
    case 2:
        se_mem[SBB][12 + (5 * 32)] = missingno ? FEN_SPE_30 | FEN_BLI_L00 : FEN_BLI_L00;
        se_mem[SBB][13 + (5 * 32)] = missingno ? FEN_SPE_31 | FEN_BLI_L01 : FEN_BLI_L01;
        se_mem[SBB][15 + (5 * 32)] = missingno ? FEN_SPE_00 | FEN_BLI_R0 : FEN_BLI_R0;
        break;
    }
}

void fennel_speak(int frame)
{
    bool missingno = get_missingno_enabled();
    int SBB = 15; // SSB is the array of which tile goes where
    switch (frame)
    {
    case 0:
        se_mem[SBB][14 + (6 * 32)] = missingno ? FEN_SPE_00 | FEN_BLI_L20 : FEN_SPE_00;
        se_mem[SBB][14 + (7 * 32)] = missingno ? FEN_SPE_01 | FEN_BLI_L21 : FEN_SPE_01;
        break;
    case 1:
        se_mem[SBB][14 + (6 * 32)] = missingno ? FEN_SPE_10 | FEN_BLI_R2 : FEN_SPE_10;
        se_mem[SBB][14 + (7 * 32)] = missingno ? FEN_SPE_11 | FEN_BLI_L10 : FEN_SPE_11;
        break;
    case 2:
    case 4:
        se_mem[SBB][14 + (6 * 32)] = missingno ? FEN_SPE_01 | FEN_BLI_L21 : FEN_SPE_20;
        se_mem[SBB][14 + (7 * 32)] = missingno ? FEN_SPE_01 | FEN_BLI_L21 : FEN_SPE_21;
        break;
    case 3:
        se_mem[SBB][14 + (6 * 32)] = missingno ? FEN_SPE_30 | FEN_BLI_L00 : FEN_SPE_30;
        se_mem[SBB][14 + (7 * 32)] = missingno ? FEN_SPE_31 | FEN_BLI_L01 : FEN_SPE_31;
        break;
    }
}

int get_curr_flex_background()
{
    return curr_flex_background;
}

void update_y_offset()
{
    if (y_offset_timer == 0)
    {
        y_offset += y_offset_direction;
        if (y_offset == 6 || y_offset == 2)
        {
            y_offset_timer = 6;
        }
        else
        {
            y_offset_timer = 4;
        }
    }
    if (y_offset == 8 || y_offset == 0)
    {
        y_offset_direction *= -1;
        y_offset += y_offset_direction;
        y_offset_timer = 12;
    }
    y_offset_timer--;
    obj_set_pos(cart_shell, (8 * 11) + 4, (8 * 4) + 11 + y_offset);
    obj_set_pos(cart_label, (8 * 11) + 4 + 8, (8 * 4) + 11 + 13 + y_offset);
    obj_set_pos(flag, (8 * 11) + 4, (8 * 4) + 19 + y_offset);
}