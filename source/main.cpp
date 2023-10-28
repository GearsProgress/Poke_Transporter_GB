#include <tonc.h>
#include <string>
#include <cstring>
// #include <maxmod.h> //Music

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

LINK CABLE:
- Figure out JP Gen 2

CONVERSION:
- Add Korean conversion

INJECTION:
- Add Pokemon to Pokedex
- Randomize base seed
- Enable ribbon viewing
- Set flags for the number of Pokemon injected
- Set Pokedex flags
- Check what happens when the PC is full, but the last Pokemon doesn't exist (is zero)
- Set text color for FRLG (what happens if you set it in RSE?)

SAVE DATA:
- Add warning
- Add ability to erase
- Add check for Hall of Fame

TESTING:
- Test all the aspects of a Pokemon (Shiny, Pokerus, etc.)
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

	// Prepare dialouge
	populate_dialouge();
	populate_script();

	// Sound bank init
	irq_init(NULL);
	// irq_set(II_VBLANK, mmVBlank, 0); //Music
	irq_enable(II_VBLANK);
	// mmInitDefault((mm_addr)soundbank_bin, 8); //Music
	// mmStart(MOD_FLATOUTLIES, MM_PLAY_LOOP); //Music

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
	load_btn_d_l();
	load_btn_d_r();
	load_btn_lang_eng();
	load_btn_lang_fre();
	load_btn_lang_ita();
	load_btn_lang_ger();
	load_btn_lang_spa();
	load_btn_lang_kor();
	load_lang_arrow();

	main_menu_btn_init(Button(btn_t_l, btn_t_r, 128, 160), BTN_TRANSFER);
	main_menu_btn_init(Button(btn_p_l, btn_p_r, 192, 224), BTN_POKEDEX);
	main_menu_btn_init(Button(btn_c_l, btn_c_r, 256, 288), BTN_CREDITS);
	main_menu_btn_init(Button(btn_d_l, btn_d_r, 416, 448), BTN_LANGUAGE);

	main_menu_btn_init(Button(btn_lang_eng, 480), BTN_ENG);
	main_menu_btn_init(Button(btn_lang_fre, 512), BTN_FRE);
	main_menu_btn_init(Button(btn_lang_ita, 544), BTN_ITA);
	main_menu_btn_init(Button(btn_lang_ger, 576), BTN_GER);
	main_menu_btn_init(Button(btn_lang_spa, 608), BTN_SPA);
	main_menu_btn_init(Button(btn_lang_kor, 640), BTN_KOR);
	main_menu_btn_init(Button(lang_arrow, 672), LANG_ARROW);

	pokedex_init(); // Why does this cause the music to stop playing? Also the loop doesn't work

	load_save_data();
	// main_menu_init(transfer_btn, pokedex_btn, credits_btn, language_btn);

	text_disable();

	// Check if the game has been loaded correctly.
	load_gamecode();
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
		tte_write("The Pokemon save\nfile was not loaded successfully. Please\nrestart the console,\nload the Pokemon\ngame normally, and\nthen upload the\nprogram again.");
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

	int curr_lang_btn_num = 3;
	int old_lang_btn_num = -1;
	set_arrow_point(curr_lang_btn_num);

	// MAIN LOOP
	while (1)
	{
		switch (main_menu_loop())
		{
		case (BTN_TRANSFER):
			text_enable();
			break;
		case (BTN_POKEDEX):
			pokedex_show();
			pokedex_loop();
			if (key_hit(KEY_B))
			{
				pokedex_hide();
				main_menu_exit();
			}
			break;
		case (BTN_LANGUAGE):
			REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(1); // Enable text box
			show_lang_btns();
			tte_set_pos(LEFT, TOP);
			tte_write("Choose the default language\nfor transfering from a non\nJapanese game. Setting will\nbe saved after next transfer.");
			if (key_hit(KEY_LEFT) && ((curr_lang_btn_num % 3) != 0))
			{
				curr_lang_btn_num--;
			}
			if (key_hit(KEY_RIGHT) && ((curr_lang_btn_num % 3) != 2))
			{
				curr_lang_btn_num++;
			}
			if (key_hit(KEY_UP) && ((curr_lang_btn_num > 2)))
			{
				curr_lang_btn_num -= 3;
			}
			if (key_hit(KEY_DOWN) && ((curr_lang_btn_num <= 2)))
			{
				curr_lang_btn_num += 3;
			}
			if (curr_lang_btn_num != old_lang_btn_num)
			{
				highlight_lang_btn(old_lang_btn_num, false);
				highlight_lang_btn(curr_lang_btn_num, true);
				old_lang_btn_num = curr_lang_btn_num;
			}
			if (key_hit(KEY_A))
			{
				set_arrow_point(curr_lang_btn_num);
				set_def_lang(curr_lang_btn_num);
			}
			if (key_hit(KEY_B))
			{
				hide_lang_btns();
				main_menu_exit();
				tte_erase_screen();
				hide_text_box();
			}
			break;
		case (BTN_CREDITS):
			tte_set_pos(0, 0);
			tte_write("wow cool credits man");
			if (key_hit(KEY_B))
			{
				tte_erase_rect(0, 0, H_MAX, V_MAX);
				main_menu_exit();
			}
			break;
		}

		key_poll();
		rand_next_frame();
		background_frame();
		text_next_frame();
		oam_copy(oam_mem, obj_buffer, 35);

		VBlankIntrWait();
		// mmFrame(); //Music
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
