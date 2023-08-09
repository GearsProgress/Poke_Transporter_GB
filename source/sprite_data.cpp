#include <tonc.h>
#include <cstring>
#include "sprite_data.h"



#include "brin.h"
void load_background(){
    int CBB = 0;
    int SBB = 1;
    // Load palette
    memcpy(pal_bg_mem, brinPal, brinPalLen);
    // Load tiles into CBB 0
    memcpy(&tile_mem[CBB][0], brinTiles, brinTilesLen);
    // Load map into SBB 30
    memcpy(&se_mem[SBB][0], brinMap, brinMapLen);

    // set up BG0 for a 4bpp 32x32t map, using
    // using charblock CBB and screenblock SBB
    REG_BG0CNT= BG_CBB(CBB) | BG_SBB(SBB) | BG_4BPP | BG_REG_32x32 | BG_PRIO(3);
}

#include "textboxBG.h"
void load_textbox_background(){
    int CBB = 1;
    int SBB = 9;
    // Load palette
    memcpy(pal_bg_mem + 16, textBoxBGPal, textBoxBGPalLen);
    // Load tiles into CBB 0
    memcpy(&tile_mem[CBB][0], textBoxBGTiles, textBoxBGTilesLen);
    // Load map into SBB 0
    memcpy(&se_mem[SBB][0], textBoxBGMap, textBoxBGMapLen);

    // set up BG0 for a 4bpp 32x32t map, using
    // using charblock CBB and screenblock SBB
    REG_BG2VOFS = 96;
    REG_BG2CNT = BG_CBB(CBB) | BG_SBB(SBB) | BG_4BPP | BG_REG_32x32 | BG_PRIO(2);
}

#include "metr.h" // 41 tiles
void load_testroid(OBJ_ATTR obj_buffer[]){
	// Text box
	// (1) Places the tiles of a 4bpp boxed sprite 
    //   into LOW obj memory (cbb == 4)
    memcpy(&tile_mem[4][0], metrTiles, metrTilesLen);
    memcpy(pal_obj_mem, metrPal, metrPalLen);

    // (2) Initialize all sprites
    //oam_init(obj_buffer, 128);

	int x= 0, y= 0;
    u32 tid= 0, pb= 0;      // (3) tile id, pal-bank
    OBJ_ATTR *testroid= &obj_buffer[0];

    obj_set_attr(testroid, 
        ATTR0_SQUARE,              // Square, regular sprite
        ATTR1_SIZE_64x64,              // 64x64p, 
        ATTR2_PALBANK(pb) | tid);   // palbank 0, tile 0

    // (4) position sprite (redundant here; the _real_ position
    // is set further down
    obj_set_pos(testroid, x, y);
    obj_hide(testroid);
    obj_unhide(testroid, 0);

}
