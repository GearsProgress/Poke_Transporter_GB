#include <tonc.h>
#include <string>
#include <cstring>
//#include <maxmod.h> //Music

#include "debug.h"
#include "flash_mem.h"
#include "gba_flash.h"
#include "interrupt.h"
#include "gb_link.h"
#include "gameboy_colour.h"
#include "LinkGPIO.h"
#include "pokemon.h"
#include "random.h"
#include "text_engine.h"
#include "background_engine.h"
#include "pokemon_party.h"
#include "script_array.h"
#include "sprite_data.h"
#include "button_handler.h"
#include "main_menu.h"
#include "debug_mode.h"
#include "soundbank.h"
#include "soundbank_bin.h"
#include "dex_handler.h"
#include "pokedex.h"
#include "global_frame_counter.h"
#include "pkmn_font.h"
#include "save_data_manager.h"
#include "script.h"
#include "script_builder.h"

/*TODO:
--------
ACCURACY:
- See if shiny Pokemon from gen 2 can be square shinies or if they're all normal
- See what happens with hybrid Pokemon

LINK CABLE:
- Figure out JP Green

CONVERSION:
- Fix fateful encounter so Mew and Celebi work
- Fix unown sometimes not being right (J becomes N)
- Add in check for glitch Pokemon
- Add in check for egg
- Restrict illegal moves
- Set full default PP points for ALL moves (and PP ups)
- Check for duplicate moves?
- What happens with Smeargle?
- Check Pokerus
- Fix egg moves only being on the baby Pokemon. TLDR anything Horsea can learn Seadra can too
- Find automatic detection for languages. Japanese is longer, while other languages only use certian characters

INJECTION:
- Redo injection to be picked up like a Mystery Gift
- Double check that returns false when PC is full BEFORE injecting
- Fix coruption and Pokemon injection
- Add Pokemon to Pokedex
- Randomize base seed
- Enable ribbon viewing

SAVE DATA:
- Add warning
- Add ability to erase
- Add check for Hall of Fame

TESTING:
- Test all the aspects of a Pokemon (Shiny, Pokerus, etc.)
- Test invalid moves
- Test move bubbling
--------
*/

Pokemon_Party party = Pokemon_Party();

/*
int test_main(void)
{

	irq_init(NULL);
	// Initialize maxmod with default settings
	// pass soundbank address, and allocate 8 channels.

	irq_set(II_VBLANK, mmVBlank, 0);
	irq_enable(II_VBLANK);

	mmInitDefault((mm_addr)soundbank_bin, 8);

	mmStart(MOD_FLATOUTLIES, MM_PLAY_LOOP);
	// Song is playing now (well... almost)
	while (1)
	{
		// ..process game logic..

		// Update Maxmod
		mmFrame();

		// Wait for new frame (SWI 5)
		VBlankIntrWait();

		// ..update graphical data..
	}
}
*/
int main(void)
{
	int delay_counter = 0;

	// Initalizations
	linkGPIO->reset();

	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ | DCNT_OBJ_1D;

	irq_init(NULL);
	irq_enable(II_VBLANK);

	flash_init(FLASH_SIZE_128KB);
	initalize_memory_locations();
	rand_set_seed(0x12162001);
	init_text_engine();
	add_script_party_var(party);

	// Sound bank init
	irq_init(NULL);
	//irq_set(II_VBLANK, mmVBlank, 0); //Music
	irq_enable(II_VBLANK);
	//mmInitDefault((mm_addr)soundbank_bin, 8); //Music
	//mmStart(MOD_FLATOUTLIES, MM_PLAY_LOOP); //Music

	// Graphics init
	oam_init(obj_buffer, 128);

	load_background();
	load_textbox_background();
	load_opening_background();
	load_testroid();
	load_professor();
	load_btn_t_l();
	load_btn_t_r();
	load_btn_p_l();
	load_btn_p_r();
	load_btn_c_l();
	load_btn_c_r();
	load_dex_l();
	load_dex_m();
	load_dex_r();

	Button transfer_btn = Button(btn_t_l, btn_t_r, 128, 160);
	Button pokedex_btn = Button(btn_p_l, btn_p_r, 192, 224);
	Button credits_btn = Button(btn_c_l, btn_c_r, 256, 288);

	pokedex_init(); // Why does this cause the music to stop playing? Also the loop doesn't work

	load_save_data();
	main_menu_init(transfer_btn, pokedex_btn, credits_btn);

	text_disable();

	load_gamecode();
	// Check if the game has been loaded correctly.
	while (!((get_gamecode() == RUBY_ID) ||
			 (get_gamecode() == SAPPHIRE_ID) ||
			 (get_gamecode() == FIRERED_ID) ||
			 (get_gamecode() == LEAFGREEN_ID) ||
			 (get_gamecode() == EMERALD_ID)))
	{
		REG_BG0CNT = (REG_BG0CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
		REG_BG1CNT = (REG_BG1CNT & ~BG_PRIO_MASK) | BG_PRIO(2);
		REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(1);
		REG_BG2VOFS = 0;
		tte_set_pos(40, 24);
		tte_set_margins(40, 24, 206, 104);
		//tte_write("The Pokemon save\nfile was not loaded successfully. Please\nrestart the console,\nload the Pokemon\ngame normally, and\nthen upload the\nprogram again.");
		tte_write(std::to_string(get_gamecode()).c_str());
		key_poll();
		while (!key_hit(KEY_A))
		{
			key_poll();
			VBlankIntrWait();
		}
		tte_erase_screen();
		delay_counter = 0;
		while (delay_counter < 60)
		{
			delay_counter++;
			VBlankIntrWait();
		}
	}

	// Legal mumbo jumbo
	tte_set_pos(8, 0);
	tte_write("\n\nPokemon Mirror was created\nout of love and appreciation\nfor the Pokemon franchise\nwith no profit in mind.\nIt will ALWAYS be free.\n\nPlease support the original developers-\nNintendo and GAME FREAK.\n\nAll Pokemon names, sprites, and music are owned by \nNintendo, Creatures Inc, and\nGAME FREAK Inc.");
	while (delay_counter < 2500000)
	{
		delay_counter++;
		rand_next_frame();
		key_poll();
		if (key_hit(KEY_A))
		{
			delay_counter = 2500000;
		}
		VBlankIntrWait();
	}
	key_poll();
	// Gears of Progress
	tte_erase_rect(0, 0, 240, 160);
	REG_BG1VOFS = 0;
	delay_counter = 0;
	while (delay_counter < 2500000)
	{
		delay_counter++;
		rand_next_frame();
		key_poll();
		if (key_hit(KEY_A))
		{
			delay_counter = 2500000;
		}
		VBlankIntrWait();
	}
	key_poll();
	REG_BG1CNT = REG_BG1CNT | BG_PRIO(3);

	// Set up blend to fade to white/black

	set_caught(3);
	set_caught(15);
	set_caught(5);

	// MAIN LOOP
	while (1)
	{
		switch (main_menu_loop())
		{
		case (TRANSFER):
			text_enable();
			break;
		case (POKEDEX):
			pokedex_show();
			pokedex_loop();
			if (key_hit(KEY_B))
			{
				pokedex_hide();
				main_menu_exit();
			}
			break;
		case (CREDITS):
			tte_set_pos(0, 0);
			tte_write("wow cool credits man");
			if (key_hit(KEY_B))
			{
				tte_erase_rect(0, 0, 240, 160);
				main_menu_exit();
			}
			break;
		}

		key_poll();
		rand_next_frame();
		background_frame();
		text_next_frame();
		oam_copy(oam_mem, obj_buffer, 26);

		VBlankIntrWait();
		//mmFrame(); //Music
		global_next_frame();
	}
}

/*Credits:
https://github.com/laqieer/libsavgba
https://github.com/rodri042/gba-link-connection
arduino-boy

Notes:
- GBA and GBC link cables are different, that's why it didn't work initally on mGBA
*/
