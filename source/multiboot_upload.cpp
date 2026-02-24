#include <tonc.h>

#include "global_frame_controller.h"
#include "background_engine.h"
#include "libraries/gba-link-connection/LinkCableMultiboot.hpp"
#include "text_engine.h"
#include "translated_text.h"
#include "text_data_table.h"

static void multiboot_show_textbox()
{
	tte_erase_rect(0, 0, RIGHT, BOTTOM);
	create_textbox(4, 1, 152, 100, true);
}

void multiboot_upload_screen()
{
	u8 general_text_table_buffer[2048];
	text_data_table general_text(general_text_table_buffer);
	LinkCableMultiboot linkCableMultiboot;

	general_text.decompress(get_compressed_text_table(GENERAL_INDEX));

	multiboot_show_textbox();
	ptgb_write(general_text.get_text_entry(GENERAL_send_multiboot_instructions), true);

	// wait for key press
	do
	{
		global_next_frame();
	} while (!key_hit(KEY_A) && !key_hit(KEY_B));

	if (key_hit(KEY_B))
	{
		// cancel
		return;
	}

	// start upload
	multiboot_show_textbox();
	ptgb_write(general_text.get_text_entry(GENERAL_send_multiboot_wait), true);
	global_next_frame();

	const u32 romSize = 256 * 1024; // EWRAM = 256 KB
	LinkCableMultiboot::Result multibootResult = linkCableMultiboot.sendRom(
		((const u8 *)MEM_EWRAM),
		romSize,
		[]()
		{
			u16 keys = ~REG_KEYS & KEY_ANY;
			return keys & KEY_B;
			// (when this returns true, the transfer will be canceled)
		});
	// show result
	// clear_textbox();
	multiboot_show_textbox();
	if (multibootResult == LinkCableMultiboot::Result::SUCCESS)
	{
		ptgb_write(general_text.get_text_entry(GENERAL_send_multiboot_success), true);
	}
	else
	{
		ptgb_write(general_text.get_text_entry(GENERAL_send_multiboot_failure), true);
	}

	// wait for keypress again.
	do
	{
		global_next_frame();
	} while (!key_hit(KEY_A));
}