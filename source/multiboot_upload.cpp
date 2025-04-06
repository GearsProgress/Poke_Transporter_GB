#include <tonc.h>

#include "global_frame_controller.h"
#include "background_engine.h"
#include "libraries/gba-link-connection/LinkCableMultiboot.hpp"

static void clear_textbox()
{
	tte_erase_screen();
	tte_set_pos(40, 32);
	tte_set_margins(40, 24, 206, 104);
	set_textbox_large();
}

void multiboot_upload_screen()
{
	LinkCableMultiboot linkCableMultiboot;
	REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(1);
	REG_BG2VOFS = 0;
	clear_textbox();
	tte_write("#{cx:0xF000}To upload this app\nto another GBA,\nconnect a GBA link\ncable.\n\nPress A to upload.\nPress B to cancel.");

	// wait for key press
	do
	{
		global_next_frame();
	}
	while(!key_hit(KEY_A) && !key_hit(KEY_B));

	if(key_hit(KEY_B))
	{
		// cancel
		return;
	}

	// start upload
	clear_textbox();
	tte_set_pos(80, 56);
	tte_write("#{cx:0xF000}Uploading...");
	global_next_frame();

	const u32 romSize = 256 * 1024; // EWRAM = 256 KB
	LinkCableMultiboot::Result multibootResult = linkCableMultiboot.sendRom(
			((const u8*)MEM_EWRAM),
			romSize,
			[]() {
				u16 keys = ~REG_KEYS & KEY_ANY;
				return keys & KEY_B;
				// (when this returns true, the transfer will be canceled)
			}
	);

	// show result
	clear_textbox();
	if(multibootResult == LinkCableMultiboot::Result::SUCCESS)
	{
		tte_write("#{cx:0xF000}Upload Successful!\n\nPress A to continue.");
	}
	else
	{
		tte_write("#{cx:0xF000}Upload Failed...\n\nPress A to continue.");
	}

	// wait for keypress again.
	do
	{
		global_next_frame();
	}
	while(!key_hit(KEY_A));
}