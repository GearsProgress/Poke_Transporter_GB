#include <tonc.h>
#include <string>
#include <cstring>
// #include <maxmod.h> //Music

#include "flash_mem.h"
#include "interrupt.h"
#include "gb_link.h"
#include "gameboy_colour.h"
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
#include "global_frame_controller.h"
#include "pkmn_font.h"
#include "save_data_manager.h"
#include "mystery_gift_injector.h"
#include "mystery_gift_builder.h"
#include "rom_data.h"
#include "libraries/Pokemon-Gen3-to-Gen-X/include/save.h"

/*

TODO:
- Implement patch list (as described here: https://web.archive.org/web/20180508011842/https://vaguilar.js.org/posts/1/)
	But this isn't going to be relevant after the ACE is implemented, since we will be pulling directly from the box... right?
	is 0xFE being a terminator part of the SPI function or is it implemented specifically in the trade/battle code?
- Rename to PokeTransporter GB
- Implement global next frame
- Remove global variables
- Better custom sprites (Progress, Fennel, Title)
- Add a % or x/250 for the Dream Dex
- Determine if transfered Shiny Pokemon are square/star sparkles
- Music and sound effects
- Simplify the sprite initalization
- Smoother transitions
- Wii Channel
- Events
- ignore Mew/Celebi
- MissingNo/Enigma Berry
- Text translations
- Add support for other languages
- Doxygen generation
--------
*/

int delay_counter = 0;
bool skip = true;
rom_data curr_rom;
Button_Menu main_menu(3, 1, 96, 32, false);

/*
int test_main(void) Music
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

void load_graphics()
{
	// Load opening background first so it hides everything else
	load_opening_background();
	load_background();
	load_textbox_background();
	load_eternal_sprites();

	// Set up main menu
	main_menu.clear_vector();
	main_menu.add_button(Button(btn_t_l, btn_t_r, 48), BTN_TRANSFER);
	main_menu.add_button(Button(btn_p_l, btn_p_r, 48), BTN_POKEDEX);
	//main_menu.add_button(Button(btn_d_l, btn_d_r), BTN_LANGUAGE);
	main_menu.add_button(Button(btn_c_l, btn_c_r, 48), BTN_CREDITS);
}

void initalization_script(void)
{
	// Initalizations
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ | DCNT_OBJ_1D;
	irq_init(NULL);
	irq_enable(II_VBLANK);

	// Disable for save data read/write
	REG_IME = 0;
	REG_IE = 0;

	// Sound bank init
	irq_init(NULL);
	irq_enable(II_VBLANK);
	// irq_set(II_VBLANK, mmVBlank, 0); //Music
	// mmInitDefault((mm_addr)soundbank_bin, 8); //Music
	// mmStart(MOD_FLATOUTLIES, MM_PLAY_LOOP); //Music

	// Graphics init
	oam_init(obj_buffer, 128);
	load_graphics();

	// Prepare dialouge
	populate_dialogue();
	populate_script();
	init_text_engine();

	// Set the random seed
	rand_set_seed(0x1216);
};

void game_load_error(void)
{
	REG_BG0CNT = (REG_BG0CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
	REG_BG1CNT = (REG_BG1CNT & ~BG_PRIO_MASK) | BG_PRIO(2);
	REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(1);
	REG_BG2VOFS = 0;
	tte_set_pos(40, 24);
	tte_set_margins(40, 24, 206, 104);
	tte_write("#{cx:0xF000}The Pok@mon save\nfile was not loaded successfully.\n\nPlease remove and\nreinsert the Game\nPak, and then press the A button.");
	// tte_write(std::to_string(get_gamecode() >> 8).c_str());
	key_poll();
	while (!key_hit(KEY_A))
	{
		global_next_frame();
	}
	tte_erase_screen();
	delay_counter = 0;

	while (delay_counter < 60)
	{
		delay_counter++;
		global_next_frame();
	}
}

void first_load_message(void)
{
	tte_set_pos(8, 0);
	tte_set_ink(10);
	tte_write("#{cx:0xE000}Hello! Thank you for using\nPok@ Transporter GB!\n\nJust as a word of caution- \nPok@ Transporter GB WILL modify\nyour generation 3 save file.\nThe program is designed to\nnot corrupt anything, but if\nyou do not wish to modify\nyour save file, please turn\noff your Game Boy Advance.\n\nPlease note that Pok@mon\nMirror is still in beta, so\nsave file backups are HIGHLY\nrecommended before using.\nWith that all out of the\nway, please enjoy!\n\n      -The Gears of Progress");
	while (!key_hit(KEY_A))
	{
		global_next_frame();
	}
	tte_erase_rect(0, 0, H_MAX, V_MAX);
}

int credits()
{
	#define CREDITS_ARRAY_SIZE 15
	int curr_credits_num = 0;
	std::string credits_array[CREDITS_ARRAY_SIZE] = {
		"Developed by:\n\n\nThe Gears\nof Progress",
		"Built using:\n\n\n-DevkitPro\n-LibTonc\n-LibGBA",
		"Inspired by the\nworks of:\n\n-Goppier\n-Lorenzooone\n-im a blisy\n-RETIRE",
		"Programs used:\n\n\n-HexManiacAdvance\n-PKHeX\n-WC3Tool\n-Usenti\n",
		"Open Source Code and\nLibraries:\n\n-libtonc-examples\n-PokemonGen3toGenX\n-gba-link-connection\n-awesome-gbadev\n-arduino-poke-gen2",
		"Research resources:\n\n-arm-docs\n-PokemonGen3toGenX\n\nFull links can be\nfound on this\nprogram's GitHub",
		"ROM data obtained\nfrom decompilations created by the PRET team",
		"Pok@mon data\nobtained from:\n\n-Bulbapedia\n-Serebii\n-PokeAPI.com",
		"Discord community\nassistance:\n\n-Hex Maniac Advance\n Development\n-gbadev\n-pret",
		"Sprite work:\n\n\n-lite_thespark",
		"Writing assistance:\n\n\n-Mad",
		"An immense thanks to\nLorenzooone for\ntheir assistance in\nreading/writing save\ndata. Without them,\nthis project would\nnot have been\npossible.",
		"Special thanks:\n\n\nEnn, Roku, Luca,\nArctic, and everyone\nwho has listened to me talk about this\nfor months",
		"All Pok@mon names,\nsprites, and names\nof related resources\nare copyright\nNintendo,\nCreatures Inc.,\nand GAME FREAK Inc.",
		"This project is not endorsed or\nsupported by\nGameFreak/Nintendo.\n\nPlease support the\noriginal developers.",
	};

	while (true)
	{
		tte_set_pos(40, 24);
		tte_set_margins(40, 24, 206, 104);
		tte_erase_screen();
		tte_write(credits_array[curr_credits_num].c_str());
		REG_BG0CNT = (REG_BG0CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
		REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(2);
		REG_BG2VOFS = 0;
		if (key_hit(KEY_B))
		{
			tte_erase_rect(0, 0, H_MAX, V_MAX);
			REG_BG0CNT = (REG_BG0CNT & ~BG_PRIO_MASK) | BG_PRIO(2);
			REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
			REG_BG2VOFS = 96;
			return 0;
		}
		if (key_hit(KEY_LEFT) && curr_credits_num > 0)
		{
			curr_credits_num--;
		}
		if (key_hit(KEY_RIGHT) && curr_credits_num < (CREDITS_ARRAY_SIZE - 1))
		{
			curr_credits_num++;
		}
		global_next_frame();
	}
}

int main(void)
{
	initalization_script();

	// Check if the game has been loaded correctly.
	while (!curr_rom.load_rom())
	{
		game_load_error();
		initalization_script();
	}

	// Initalize memory and save data after loading the game
	init_bank();
	initalize_memory_locations();
	load_custom_save_data();

	if (get_tutorial_flag() == false)
	{
		first_load_message();
		initalize_save_data();
	}

	// Legal mumbo jumbo
	tte_set_pos(8, 0);
	tte_write("#{cx:0xE000}\n\nPok@ Transporter GB was made\nout of love and appreciation\nfor the Pokemon franchise\nwith no profit in mind.\nIt will ALWAYS be free.\n\nPlease support the original developers-\nNintendo and GAME FREAK.\n\nAll Pokemon names, sprites, and music are owned by \nNintendo, Creatures Inc, and\nGAME FREAK Inc.");
	tte_write("#{cx:0xF000}"); // Set the color to grey
	while (delay_counter < (15 * 60))
	{
		global_next_frame();
		delay_counter++;
		if (key_hit(KEY_A))
		{
			delay_counter = (15 * 60);
		}
	}

	// Gears of Progress
	tte_erase_rect(0, 0, 240, 160);
	REG_BG1VOFS = 0;
	delay_counter = 0;
	while (delay_counter < (15 * 60))
	{
		global_next_frame();
		delay_counter++;
		if (key_hit(KEY_A))
		{
			delay_counter = (15 * 60);
		}
	}
	REG_BG1CNT = REG_BG1CNT | BG_PRIO(3);

	// Set up blend to fade to white/black

	key_poll(); // Reset the keys
	curr_rom.load_rom();
	// MAIN LOOP
	while (1)
	{
		if (DEBUG_MODE)
		{
			print_mem_section();
			curr_rom.print_rom_info();
		}
		switch (main_menu.button_main())
		{
		case (BTN_TRANSFER):
			text_loop();
			break;
		case (BTN_POKEDEX):
			pokedex_loop();
			break;
		case (BTN_CREDITS):
			credits();
			break;
		default:
			global_next_frame();
		}
	}
}