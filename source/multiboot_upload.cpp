#include <tonc.h>

#include "global_frame_controller.h"
#include "background_engine.h"
#include "libraries/gba-link-connection/LinkCableMultiboot.hpp"
#include "text_engine.h"

void multiboot_upload_screen()
{
	LinkCableMultiboot linkCableMultiboot;
	tte_erase_rect(0, 0, RIGHT, BOTTOM);
	create_textbox(4, 1, 152, 100, true);
	ptgb_write(send_multiboot_instructions, true);

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
	tte_erase_rect(0, 0, RIGHT, BOTTOM);
	create_textbox(4, 1, 152, 70, true);
	ptgb_write(send_multiboot_wait, true);
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
	if (multibootResult == LinkCableMultiboot::Result::SUCCESS)
	{
		tte_erase_rect(0, 0, RIGHT, BOTTOM);
		create_textbox(4, 1, 152, 70, true);
		ptgb_write(send_multiboot_success, true);
	}
	else
	{
		tte_erase_rect(0, 0, RIGHT, BOTTOM);
		create_textbox(4, 1, 152, 70, true);
		ptgb_write(send_multiboot_failure, true);
	}

	// wait for keypress again.
	do
	{
		global_next_frame();
	} while (!key_hit(KEY_A));
}