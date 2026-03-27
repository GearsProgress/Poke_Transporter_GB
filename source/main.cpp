#include <tonc.h>
#include <cstdlib>
#include "libstd_replacements.h"
#include "flash_mem.h"
#include "interrupt.h"
#include "gb_link.h"
#include "gameboy_colour.h"
#include "random.h"
#include "text_engine.h"
#include "background_engine.h"
#include "pokemon_party.h"
#include "pokemon_data.h"
#include "script_array.h"
#include "sprite_data.h"
#include "button_handler.h"
#include "button_menu.h"
#include "dbg/debug_mode.h"
#include "dbg/debug_menu.h"
#include "dex_handler.h"
#include "pokedex.h"
#include "global_frame_controller.h"
#include "pkmn_font.h"
#include "ptgb_save_data_manager.h"
#include "mystery_gift_injector.h"
#include "mystery_gift_builder.h"
#include "multiboot_upload.h"
#include "rom_data.h"
#include "libraries/Pokemon-Gen3-to-Gen-X/include/save.h"
#include "text_data_table.h"
#include "custom_malloc.h"
#include "sound.h"

#define MACRO_AS_STR_IMPL(x) #x
#define MACRO_AS_STR(x) MACRO_AS_STR_IMPL(x)

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
rom_data curr_GBA_rom;
Button_Menu yes_no_menu(1, 2, 40, 24, false);

// (R + G*32 + B*1024)
#define RGB(r, g, b) (r + (g * 32) + (b * 1024))

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

void initialization_script(void)
{
	// Initializations
	REG_DISPCNT = DCNT_BLANK | DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ | DCNT_OBJ_1D;

	// Disable for save data read/write
	REG_IME = 0;
	REG_IE = 0;

	// Sound bank init
	irq_init(NULL);
	irq_enable(II_VBLANK);
	// This currently crashes when you try to transfer a Pokemon:
	//sound_init();

	// Graphics init
	oam_init(obj_buffer, 128);
	load_graphics();

	// Prepare text engine for dialogue
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

	create_textbox(4, 1, 152, 100, true);

	{
		u8 general_text_table_buffer[2048];
		text_data_table general_text(general_text_table_buffer);

		general_text.decompress(get_compressed_text_table(GENERAL_INDEX));
		ptgb_write(general_text.get_text_entry(GENERAL_cart_load_error), true);
	}

	key_poll();
	do
	{
		global_next_frame();
	} while (!key_hit(KEY_A) && !key_hit(KEY_SELECT));

	tte_erase_rect(0, 0, H_MAX, V_MAX);

	if (key_hit(KEY_SELECT))
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
	tte_set_margins(8, 8, H_MAX - 8, V_MAX);
	tte_set_pos(8, 8);
	tte_set_ink(INK_ROM_COLOR);

	{
		u8 general_text_table_buffer[2048];
		text_data_table general_text(general_text_table_buffer);

		general_text.decompress(get_compressed_text_table(GENERAL_INDEX));
		ptgb_write(general_text.get_text_entry(GENERAL_intro_first), true);
	}

	while (!key_hit(KEY_A))
	{
		global_next_frame();
	}
	tte_erase_rect(0, 0, H_MAX, V_MAX);
}

int credits()
{
	u8 text_decompression_buffer[2048];
	text_data_table credits_text_table(text_decompression_buffer);
	int curr_credits_num = 0;

	credits_text_table.decompress(get_compressed_text_table(CREDITS_INDEX));
	bool update = true;

	global_next_frame();
	while (true)
	{
		if (update)
		{
			create_textbox(1, 1, 200, 120, true);
			show_text_box();
			ptgb_write(credits_text_table.get_text_entry(curr_credits_num), true);
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
		if (key_hit(KEY_RIGHT) && curr_credits_num < (credits_text_table.get_number_of_text_entries() - 1))
		{
			curr_credits_num++;
			update = true;
		}

		global_next_frame();
	}
};

int main_menu_loop()
{
#define NUM_MENU_OPTIONS 3
	const uint8_t menu_options[NUM_MENU_OPTIONS] = {GENERAL_option_transfer, GENERAL_option_dreamdex, GENERAL_option_credits};
	int return_values[NUM_MENU_OPTIONS] = {BTN_TRANSFER, BTN_POKEDEX, BTN_CREDITS};

	uint8_t general_text_table_buffer[2048];
	text_data_table general_text(general_text_table_buffer);
	bool update = true;
	const uint8_t *text_entry;
	u16 test = 0;

	general_text.decompress(get_compressed_text_table(GENERAL_INDEX));

	while (true)
	{
		if (update)
		{
			tte_erase_rect(0, 80, 240, 160);
			for (int i = 0; i < NUM_MENU_OPTIONS; i++)
			{
				text_entry = general_text.get_text_entry(menu_options[i]);
				int string_length = get_string_length(text_entry);
				int x = ((240 - string_length) / 2);
				tte_set_pos(x, ((i * (16 + 10)) + 70));
				if (i == curr_selection)
				{
					tte_set_ink(INK_WHITE);
				}
				else
				{
					tte_set_ink(INK_ROM_COLOR);
				}
				ptgb_write(text_entry, true);
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
		else if ((key_held(KEY_L) && key_held(KEY_R)))
		{
			return BTN_DEBUG_MENU;
		}
		else
		{
			update = false;
		}

		global_next_frame();
	}
}

// Legal stuff
static void show_legal_text(const u8 *intro_text)
{
	tte_set_margins(4, 0, H_MAX - 4, V_MAX);
	tte_set_pos(4, 0);
	tte_set_ink(INK_ROM_COLOR);
	ptgb_write(intro_text, true);
	bool wait = true;
	while (wait)
	{
		global_next_frame();
		if (key_hit(KEY_A))
		{
			wait = false;
		}
	}
}

// Gears of Progress
static void show_gears_of_progress()
{
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
}

// split off from the main function in order to keep the scope of the variables limited to the execution of this function
// otherwise they stick around for the entire runtime of the program
// the attribute noinline is used to prevent the compiler from inlining this function back into the main function
// this decision was based on the output of build/main.su after adding the -fstack-usage compile flag
static void __attribute__((noinline)) show_intro()
{
	bool start_pressed = false;
	u8 general_text_table_buffer[2048];
	u8 press_start_text[32];
	u8 press_start_text_length;

	text_data_table general_text(general_text_table_buffer);
	const u8 *text_entry;

	general_text.decompress(get_compressed_text_table(GENERAL_INDEX));

	text_entry = general_text.get_text_entry(GENERAL_press_start);
	press_start_text_length = get_string_char_count(text_entry);
	memcpy(press_start_text, text_entry, press_start_text_length + 1);
	text_entry = general_text.get_text_entry(GENERAL_intro_legal);

	show_legal_text(text_entry);
	show_gears_of_progress();

	REG_BG1CNT = REG_BG1CNT | BG_PRIO(3);

	key_poll(); // Reset the keys
	curr_GBA_rom.load_rom(false);

	obj_set_pos(ptgb_logo_l, 56, 12);
	obj_set_pos(ptgb_logo_r, 56 + 64, 12);
	obj_unhide_multi(ptgb_logo_l, 1, 2);

	REG_BLDCNT = BLD_BUILD(BLD_BG3, BLD_BG0, 1);

#ifndef PTGB_BUILD_LANGUAGE

#error PTGB_NOT_DEFINED
#endif
#ifndef JPN_ID
#error JPN_ID_NOT_DEFINED
#endif

#pragma message("PTGB_BUILD_LANGUAGE=" MACRO_AS_STR(PTGB_BUILD_LANGUAGE))
#pragma message("JPN_ID=" MACRO_AS_STR(JPN_ID))

	int char_width = (PTGB_BUILD_LANGUAGE == JPN_ID ? 8 : 6);
	int x = ((240 - (press_start_text_length * char_width)) / 2);
	tte_set_pos(x, 12 * 8);

	tte_set_ink(INK_DARK_GREY);
	ptgb_write(press_start_text, true);

	int fade = 0;
	while (!start_pressed)
	{
		fade = abs(((get_frame_count() / 6) % 24) - 12);
		global_next_frame();
		start_pressed = key_hit(KEY_START) | key_hit(KEY_A);
		REG_BLDALPHA = BLDA_BUILD(0b10000, fade);
	}
}

int main(void)
{
	malloc_init_default_pool();
	initialization_script();

	// Set colors based on current ROM
	set_background_pal(0, false, false);

	/* First load message doesn't really make sense anymore, since you have to load the ROM first.
	if (!get_tutorial_flag())
	{
		first_load_message();
	}*/

	show_intro();

	key_poll();
	tte_erase_rect(0, 0, H_MAX, V_MAX);
	REG_BLDALPHA = BLDA_BUILD(0b10000, 0); // Reset fade

	//  Check if the game has been loaded correctly.
	bool debug = false;
	while (!curr_GBA_rom.load_rom(debug))
	{
		if (g_debug_options.ignore_game_pak)
		{
			debug = true;
		}
		else
		{
			obj_hide_multi(ptgb_logo_l, 2);
			global_next_frame();
			game_load_error();
			// initialization_script();
		}
	}

	// Initialize memory and save data after loading the game
	reset_textbox();
	REG_BG2CNT = REG_BG2CNT | BG_PRIO(3);
	init_bank();
	initialize_memory_locations();
	load_custom_save_data();

	set_background_pal(curr_GBA_rom.gamecode, false, true);

	if (!g_debug_options.ignore_mg_e4_flags && (!get_tutorial_flag() || g_debug_options.force_tutorial))
	{
		obj_hide_multi(ptgb_logo_l, 2);
		text_loop(BTN_TRANSFER);
		initialize_save_data();
		// TODO: We should be able to test for a Bootleg rom in here- if the save data isn't written, then it is bootleg.
	}

	obj_unhide_multi(ptgb_logo_l, 1, 2);

	// MAIN LOOP
	while (true)
	{
		if (DEBUG_MODE && false) // This isn't really needed anymore
		{
			print_mem_section();
			curr_GBA_rom.print_rom_info();
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
			load_flex_background(BG_FENNEL, 3);
			text_loop(SCRIPT_TRANSFER);
			break;
		case (BTN_POKEDEX):
			if (get_tutorial_flag())
			{
				obj_hide_multi(ptgb_logo_l, 2);
				global_next_frame();
				load_flex_background(BG_DEX, 2);
				set_background_pal(curr_GBA_rom.gamecode, true, false);
				pokedex_loop();
				load_flex_background(BG_DEX, 3);
				set_background_pal(curr_GBA_rom.gamecode, false, false);
			}
			break;
		case (BTN_CREDITS):
			tte_set_ink(INK_DARK_GREY);
			// create_textbox(0, 0, 160, 80, true);
			// show_text_box();
			REG_BG1CNT = (REG_BG1CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
			obj_set_pos(ptgb_logo_l, 56, 108);
			obj_set_pos(ptgb_logo_r, 56 + 64, 108);
			credits();
			break;
		case (BTN_EVENTS):
			obj_hide_multi(ptgb_logo_l, 2);
			text_loop(SCRIPT_EVENT);
			break;
#if ENABLE_DEBUG_MENU
		case (BTN_DEBUG_MENU):
			obj_hide_multi(ptgb_logo_l, 2);
			show_debug_menu();
			break;
#endif
		default:
			global_next_frame();
		}
	}
}