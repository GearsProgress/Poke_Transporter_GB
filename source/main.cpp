#include <tonc.h>
#include <string>

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
#include <cstring>

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

INJECTION:
- Redo injection to be picked up like a Mystery Gift
- Double check that returns false when PC is full BEFORE injecting
- Fix coruption and Pokemon injection
- Add Pokemon to Pokedex
- Randomize base seed
- Enable ribbon viewing

TESTING:
- Test all the aspects of a Pokemon (Shiny, Pokerus, etc.)
- Test invalid moves
- Test move bubbling
--------
*/

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *)obj_buffer;

Pokemon_Party party = Pokemon_Party();
text_engine main_text = text_engine();

int main(void)
{

	// Initalizations
	linkGPIO->reset();

	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ | DCNT_OBJ_1D;

	irq_init(NULL);
	irq_enable(II_VBLANK);

	flash_init(FLASH_SIZE_128KB);
	initalize_memory_locations();
	rand_set_seed(0x12162001);

	add_script_party_var(party);

	load_background();
	load_textbox_background();
	load_testroid(obj_buffer);

	// MAIN LOOP
	while (1)
	{
		key_poll();
		rand_next_frame();
		background_frame();
		main_text.next_frame();
		oam_copy(oam_mem, obj_buffer, 1);
	}
}

/*Credits:
https://github.com/laqieer/libsavgba
https://github.com/rodri042/gba-link-connection
arduino-boy

Notes:
- GBA and GBC link cables are different, that's why it didn't work initally on mGBA
*/
