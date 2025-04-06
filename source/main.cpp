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
#include "button_menu.h"
#include "debug_mode.h"
// #include "soundbank.h"
// #include "soundbank_bin.h"
#include "dex_handler.h"
#include "pokedex.h"
#include "global_frame_controller.h"
#include "pkmn_font.h"
#include "save_data_manager.h"
#include "mystery_gift_injector.h"
#include "mystery_gift_builder.h"
#include "multiboot_upload.h"
#include "rom_data.h"
#include "libraries/Pokemon-Gen3-to-Gen-X/include/save.h"

/*

TODO:
- Add in putting item from Pkmn to bag in gen 2
- Determine if transfered Shiny Pokemon are square/star sparkles
- Music and sound effects
- Wii Channel
- Events
- MissingNo/Enigma Berry
- Text translations
- Add support for other languages
- Add in dolls for gen 2/3
- Doxygen generation
--------
*/

int delay_counter = 0;
int curr_selection = 0;
bool skip = true;
rom_data curr_rom;
Button_Menu yes_no_menu(1, 2, 40, 24, false);

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

// (R + G*32 + B*1024)
#define RGB(r, g, b) (r + (g * 32) + (b * 1024))

template <typename I>
std::string n2hexstr(I w, size_t hex_len = sizeof(I) << 1)
{
	static const char *digits = "0123456789ABCDEF";
	std::string rc(hex_len, '0');
	for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
		rc[i] = digits[(w >> j) & 0x0f];
	return rc;
}

void load_graphics()
{

	tte_erase_rect(0, 0, H_MAX, V_MAX);
	// Load opening background first so it hides everything else
	load_flex_background(BG_OPENING, 1);
	load_background();
	load_textbox_background();
	load_eternal_sprites();

	// Set up global yes no button
	yes_no_menu.clear_vector();
	yes_no_menu.add_button(Button(button_yes), true);
	yes_no_menu.add_button(Button(button_no), false);
}

void initalization_script(void)
{
	// Initalizations
	REG_DISPCNT = DCNT_BLANK | DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ | DCNT_OBJ_1D;
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
	populate_script();
	init_text_engine();

	// Set the random seed
	rand_set_seed(0x1216);

	// Clean up the main screen quick
	tte_erase_rect(0, 0, 240, 160);

	VBlankIntrWait();
	REG_DISPCNT &= ~DCNT_BLANK;
};

void game_load_error(void)
{
	REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(1);

	create_textbox(4, 1, 160, 80, true);
	ptgb_write(cart_load_error, true);
	key_poll();
	do
	{
		global_next_frame();
	}
	while(!key_hit(KEY_A) && !key_hit(KEY_SELECT));

	tte_erase_screen();

	if(key_hit(KEY_SELECT))
	{
    	// We also want to give the option in this screen to upload the multiboot rom to another GBA.
	// This can be useful when the user wants to work with a flashcart in single rom mode.
	// The EZ Flash Omega (DE) for instance, triggers a reset of the gba if you insert it while the GBA is turned on.
	// So the only way to work with it, is to boot Poke Transporter GB over multiboot and have the flashcart already inserted.
	// It would be a shame not to support this flashcart, because it's awesome for pokémon fans. After all: it supports ds transfer
	// and should support connecting with the gamecube games.
		multiboot_upload_screen();
		return;
	}
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
	tte_set_ink(INK_ROM_COLOR);
	ptgb_write(intro_first, true);
	while (!key_hit(KEY_A))
	{
		global_next_frame();
	}
	tte_erase_rect(0, 0, H_MAX, V_MAX);
}

int credits()
{
#define CREDITS_ARRAY_SIZE 19
	int curr_credits_num = 0;
	const byte *credits_array[CREDITS_ARRAY_SIZE] = {
		credits_page_1,
		credits_page_2,
		credits_page_3,
		credits_page_4,
		credits_page_5,
		credits_page_6,
		credits_page_7,
		credits_page_8,
		credits_page_9,
		credits_page_10,
		credits_page_11,
		credits_page_12,
		credits_page_13,
		credits_page_14,
		credits_page_15,
		credits_page_16,
		credits_page_17,
		credits_page_18,
		credits_page_19,
		// Add translators
	};

	bool update = true;

	while (true)
	{
		if (update)
		{
			create_textbox(4, 1, 160, 80, true);
			show_text_box();
			ptgb_write(credits_array[curr_credits_num], true);
			update = false;
		}

		if (key_hit(KEY_B))
		{
			hide_text_box();
			reset_textbox();
			return 0;
		}
		if (key_hit(KEY_LEFT) && curr_credits_num > 0)
		{
			curr_credits_num--;
			update = true;
		}
		if (key_hit(KEY_RIGHT) && curr_credits_num < (CREDITS_ARRAY_SIZE - 1))
		{
			curr_credits_num++;
			update = true;
		}
		if (ENABLE_DEBUG_SCREEN && key_hit(KEY_SELECT))
		{
			if (key_held(KEY_UP) && key_held(KEY_L) && key_held(KEY_R))
			{
				set_treecko(true);
			}
			u32 pkmn_flags = 0;
			bool e4_flag = read_flag(curr_rom.e4_flag);
			bool mg_flag = read_flag(curr_rom.mg_flag);
			bool all_collected_flag = read_flag(curr_rom.all_collected_flag);
			for (int i = 0; i < 30; i++)
			{
				pkmn_flags |= (read_flag(curr_rom.pkmn_collected_flag_start + i) << i);
			}

			bool tutorial = get_tutorial_flag();
			int def_lang = get_def_lang_num();

			create_textbox(4, 1, 160, 80, true);
			ptgb_write_debug("Debug info:\n\nG: ", true);
			std::string lang;
			lang += curr_rom.language;
			ptgb_write_debug(lang.c_str(), true);
			switch (curr_rom.gamecode)
			{
			case RUBY_ID:
				ptgb_write_debug("-R-", true);
				break;
			case SAPPHIRE_ID:
				ptgb_write_debug("-S-", true);
				break;
			case FIRERED_ID:
				ptgb_write_debug("-F-", true);
				break;
			case LEAFGREEN_ID:
				ptgb_write_debug("-L-", true);
				break;
			case EMERALD_ID:
				ptgb_write_debug("-E-", true);
				break;
			}
			ptgb_write_debug(std::to_string(curr_rom.version).c_str(), true);

			ptgb_write_debug("\nF: ", true);
			ptgb_write_debug(std::to_string(e4_flag).c_str(), true);
			ptgb_write_debug(std::to_string(mg_flag).c_str(), true);
			ptgb_write_debug(std::to_string(all_collected_flag).c_str(), true);
			ptgb_write_debug("-", true);
			ptgb_write_debug((n2hexstr(pkmn_flags)).c_str(), true);
			ptgb_write_debug("\nS:   ", true);
			ptgb_write_debug(std::to_string(tutorial).c_str(), true);
			ptgb_write_debug("-", true);
			ptgb_write_debug((n2hexstr(def_lang)).c_str(), true);

			ptgb_write_debug("\n", true);
			ptgb_write_debug(VERSION, true);
			if (get_treecko_enabled())
			{
				ptgb_write_debug(".T", true);
			}
			while (true)
			{
				if (key_hit(KEY_B))
				{
					hide_text_box();
					reset_textbox();
					return 0;
				}
				global_next_frame();
			}
		}
		global_next_frame();
	}
};

#define NUM_MENU_OPTIONS 3

int main_menu_loop()
{
	bool update = true;
	const byte *menu_options[NUM_MENU_OPTIONS] = {option_transfer, option_dreamdex, option_credits};
	int return_values[NUM_MENU_OPTIONS] = {BTN_TRANSFER, BTN_POKEDEX, BTN_CREDITS};
	u16 test = 0;
	while (true)
	{
		if (update)
		{
			tte_erase_rect(0, 80, 240, 160);
			for (int i = 0; i < NUM_MENU_OPTIONS; i++)
			{
				int size = get_string_length(menu_options[i]);
				int char_width = (curr_rom.language == JPN_ID ? 8 : 6);
				int x = ((240 - (size * char_width)) / 2);
				tte_set_pos(x, ((i * 17) + 80));
				if (i == curr_selection)
				{
					tte_set_ink(INK_WHITE);
				}
				else
				{
					tte_set_ink(INK_ROM_COLOR);
				}
				ptgb_write(menu_options[i], true);
				test++;
			}
		}

		update = true;
		if (key_hit(KEY_DOWN))
		{
			curr_selection = ((curr_selection + 1) % NUM_MENU_OPTIONS);
		}
		else if (key_hit(KEY_UP))
		{
			curr_selection = ((curr_selection + (NUM_MENU_OPTIONS - 1)) % NUM_MENU_OPTIONS);
		}
		else if (key_hit(KEY_A))
		{
			tte_erase_rect(0, test, H_MAX, V_MAX);
			ptgb_write("#{cx:0xF000}");
			return return_values[curr_selection];
		}
		else
		{
			update = false;
		}

		global_next_frame();
	}
}

int main(void)
{
	initalization_script();

	// Set colors based on current ROM
	set_background_pal(0, false, false);

	// First load message... which apparently was removed at some point?
	first_load_message();

	// Legal mumbo jumbo
	tte_set_margins(8, 8, H_MAX - 8, V_MAX - 8);
	tte_set_pos(8, 8);
	tte_set_ink(INK_ROM_COLOR);
	ptgb_write(intro_legal, true);
	bool wait = true;
	while (wait)
	{
		global_next_frame();
		if (key_hit(KEY_A))
		{
			wait = false;
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

	key_poll(); // Reset the keys
	curr_rom.load_rom();

	obj_set_pos(ptgb_logo_l, 56, 12);
	obj_set_pos(ptgb_logo_r, 56 + 64, 12);
	obj_unhide_multi(ptgb_logo_l, 1, 2);
	bool start_pressed = false;
	REG_BLDCNT = BLD_BUILD(BLD_BG3, BLD_BG0, 1);

	int char_width = (curr_rom.language == JPN_ID ? 8 : 6);
	int size = get_string_length(press_start);
	int x = ((240 - (size * char_width)) / 2);
	tte_set_pos(x, 12 * 8);

	tte_set_ink(INK_DARK_GREY);
	ptgb_write(press_start, true);
	int fade = 0;
	while (!start_pressed)
	{
		fade = abs(((get_frame_count() / 6) % 24) - 12);
		global_next_frame();
		start_pressed = key_hit(KEY_START) | key_hit(KEY_A);
		REG_BLDALPHA = BLDA_BUILD(0b10000, fade);
	};
	key_poll();
	tte_erase_rect(0, 0, H_MAX, V_MAX);
	REG_BLDALPHA = BLDA_BUILD(0b10000, 0); // Reset fade

	//  Check if the game has been loaded correctly.
	while (!curr_rom.load_rom())
	{
		obj_hide_multi(ptgb_logo_l, 2);
		game_load_error();
		// initalization_script();
	}

	// Initalize memory and save data after loading the game
	reset_textbox();
	REG_BG2CNT = REG_BG2CNT | BG_PRIO(3);
	init_bank();
	initalize_memory_locations();
	load_custom_save_data();

	set_background_pal(curr_rom.gamecode, false, true);

	if (!IGNORE_MG_E4_FLAGS && (!get_tutorial_flag() || FORCE_TUTORIAL))
	{
		obj_hide_multi(ptgb_logo_l, 2);
		text_loop(BTN_TRANSFER);
		initalize_save_data();
	}

	obj_unhide_multi(ptgb_logo_l, 1, 2);

	// MAIN LOOP
	while (true)
	{
		if (DEBUG_MODE && false) // This isn't really needed anymore
		{
			print_mem_section();
			curr_rom.print_rom_info();
		}
		load_flex_background(BG_MAIN_MENU, 2);

		obj_unhide_multi(ptgb_logo_l, 1, 2);
		obj_set_pos(ptgb_logo_l, 56, 12);
		obj_set_pos(ptgb_logo_r, 56 + 64, 12);

		switch (main_menu_loop())
		{
		case (BTN_TRANSFER):
			tte_set_ink(INK_DARK_GREY);
			obj_hide_multi(ptgb_logo_l, 2);
			load_flex_background(BG_FENNEL, 2);
			text_loop(BTN_TRANSFER);
			break;
		case (BTN_POKEDEX):
			load_flex_background(BG_DEX, 2);
			set_background_pal(curr_rom.gamecode, true, false);
			obj_hide_multi(ptgb_logo_l, 2);
			pokedex_loop();
			load_flex_background(BG_DEX, 3);
			set_background_pal(curr_rom.gamecode, false, false);
			break;
		case (BTN_CREDITS):
			tte_set_ink(INK_DARK_GREY);
			//create_textbox(0, 0, 160, 80, true);
			//show_text_box();
			REG_BG1CNT = (REG_BG1CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
			obj_set_pos(ptgb_logo_l, 56, 108);
			obj_set_pos(ptgb_logo_r, 56 + 64, 108);
			credits();
			break;
		case (BTN_EVENTS):
			obj_hide_multi(ptgb_logo_l, 2);
			text_loop(BTN_EVENTS);
			break;
		default:
			global_next_frame();
		}
	}
}