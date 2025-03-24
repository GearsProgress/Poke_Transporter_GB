#include <tonc.h>
#include <string.h>

// This file is autogenerated from the file in the graphics folder
#include "ptgb_logo_l.h"
#include "ptgb_logo_r.h"
#include "multiboot_rom_bin.h"

#define SPRITE_CHAR_BLOCK 4
#define DST_EWRAM (void*)0x02000000
#define MULTIBOOT_ENTRY_POINT (void*)0x020000C0

/**
 * An enum with an entry for every separate sprite we load in.
 * We use this to ensure a valid index for each sprite
 */
enum SpriteTypes
{
	SPRITE_LOGO_L,
	SPRITE_LOGO_R
};

/**
 * Similarly, the PaletteTypes enum has an entry for every separate palette we're using here.
 */
enum PaletteTypes
{
	PAL_LOGO
};

OBJ_ATTR obj_buffer[128];
OBJ_ATTR* logoL = &obj_buffer[SPRITE_LOGO_L];
OBJ_ATTR* logoR = &obj_buffer[SPRITE_LOGO_R];

/**
 * Taken from sprite_data.cpp
 */
static void loadSprite(OBJ_ATTR *sprite, const unsigned int objTiles[], int objTilesLen,
	u32* tile_id, u32 pal_bank, int attr0, int attr1, u32 priority)
{
	memcpy32(&tile_mem[SPRITE_CHAR_BLOCK][*tile_id], objTiles, objTilesLen);
	obj_set_attr(sprite, attr0, attr1, ATTR2_PALBANK(pal_bank) | *tile_id | ATTR2_PRIO(priority));
	*tile_id += objTilesLen / 32;
	obj_hide(sprite);
};

/**
 * This function exists to simply load and position the Poke Transporter GB logo
 */
static void load_logo(u32* curSpriteIndex)
{
	// load palette
	memcpy32(pal_obj_mem + (PAL_LOGO * 16), ptgb_logo_lPal, ptgb_logo_lPalLen);

	// now load the tiles of the logo
	loadSprite(logoL, ptgb_logo_lTiles, ptgb_logo_lTilesLen, curSpriteIndex, PAL_LOGO, ATTR0_SQUARE, ATTR1_SIZE_64x64, 1);
	loadSprite(logoR, ptgb_logo_rTiles, ptgb_logo_rTilesLen, curSpriteIndex, PAL_LOGO, ATTR0_SQUARE, ATTR1_SIZE_64x64, 1);

	// Set position
	obj_set_pos(logoL, 56, 12);
	obj_set_pos(logoR, 56 + 64, 12);
	obj_unhide_multi(logoL, 1, 2);

	oam_copy(oam_mem, obj_buffer, 2); // Update first OAM object
}

/**
 * Loads the PokeTransporter multiboot rom into EWRAM
 */
static void load_multiboot_rom(const void *src, u32 size)
{
	memcpy(DST_EWRAM, src, size);
}

/**
 * Now jump to the multiboot rom address and start execution
 */
void execute_multiboot()
{
    // Disable interrupts
	// During the time the user could swap out the cartridge, we should disable interrupts
    REG_IME = 0;

    // Set up waitstates (multiboot defaults to faster EWRAM access)
    REG_WAITCNT = 0x4317;

    // Function pointer to EWRAM execution entry
    void (*entry)(void) = MULTIBOOT_ENTRY_POINT;
    entry();  // Jump to loaded ROM
}

int main(void)
{
	u32 curSpriteIndex = 0;

	irq_init(NULL);
	irq_enable(II_VBLANK);

	tte_init_chr4c_default(0, BG_CBB(0) | BG_SBB(31));
	tte_set_pos(92, 68);
	tte_write("Loading...");
	
	oam_init(obj_buffer, 128);

	load_logo(&curSpriteIndex);

	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;

	VBlankIntrWait();

	load_multiboot_rom(multiboot_rom_bin, multiboot_rom_bin_size);
	execute_multiboot();
}
