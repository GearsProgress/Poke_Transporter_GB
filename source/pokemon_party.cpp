#include "gameboy_colour.h"
#include "pokemon_party.h"
#include "pokemon.h"
#include "flash_mem.h"
#include "debug_mode.h"
#include "mystery_gift_injector.h"

/*
byte debug_party_data[GEN2_INT_SIZE + 4] = { // Japanese Gen 1
	0x07, 0xD8, 0xE3, 0xAB, 0x50, 0x8B,
	0x06,
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
	0xFF,
	0x01, 0x00, 0x14, 0x00, 0x00, 0x15, 0x15, 0x2D, 0x21, 0x27, 0x00, 0x00, 0x2E, 0x75, 0x00, 0x00, 0xCA, 0x00, 0x2D, 0x00, 0x31, 0x00, 0x31, 0x00, 0x2D, 0x00, 0x41, 0x59, 0x19, 0x23, 0x1D, 0x00, 0x00, 0x06, 0x00, 0x17, 0x00, 0x0B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x0C,
	0x02, 0x00, 0x17, 0x06, 0x00, 0x15, 0x15, 0x2D, 0x21, 0x27, 0x00, 0x00, 0x2E, 0x75, 0x00, 0x00, 0xCA, 0x00, 0x2D, 0x00, 0x31, 0x00, 0x31, 0x00, 0x2D, 0x00, 0x41, 0x59, 0x19, 0x23, 0x1D, 0x00, 0x00, 0x06, 0x00, 0x17, 0x00, 0x0B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x0C,
	0x03, 0x00, 0x17, 0x06, 0x00, 0x15, 0x15, 0x2D, 0x21, 0x27, 0x00, 0x00, 0x2E, 0x75, 0x00, 0x00, 0xCA, 0x00, 0x2D, 0x00, 0x31, 0x00, 0x31, 0x00, 0x2D, 0x00, 0x41, 0x59, 0x19, 0x23, 0x1D, 0x00, 0x00, 0x06, 0x00, 0x17, 0x00, 0x0B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x0C,
	0x04, 0x00, 0x17, 0x06, 0x00, 0x15, 0x15, 0x2D, 0x21, 0x27, 0x00, 0x00, 0x2E, 0x75, 0x00, 0x00, 0xCA, 0x00, 0x2D, 0x00, 0x31, 0x00, 0x31, 0x00, 0x2D, 0x00, 0x41, 0x59, 0x19, 0x23, 0x1D, 0x00, 0x00, 0x06, 0x00, 0x17, 0x00, 0x0B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x0C,
	0x05, 0x00, 0x17, 0x06, 0x00, 0x15, 0x15, 0x2D, 0x21, 0x27, 0x00, 0x00, 0x2E, 0x75, 0x00, 0x00, 0xCA, 0x00, 0x2D, 0x00, 0x31, 0x00, 0x31, 0x00, 0x2D, 0x00, 0x41, 0x59, 0x19, 0x23, 0x1D, 0x00, 0x00, 0x06, 0x00, 0x17, 0x00, 0x0B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x0C,
	0x06, 0x00, 0x17, 0x06, 0x00, 0x15, 0x15, 0x2D, 0x21, 0x27, 0x00, 0x00, 0x2E, 0x75, 0x00, 0x00, 0xCA, 0x00, 0x2D, 0x00, 0x31, 0x00, 0x31, 0x00, 0x2D, 0x00, 0x41, 0x59, 0x19, 0x23, 0x1D, 0x00, 0x00, 0x06, 0x00, 0x17, 0x00, 0x0B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x0C,

	0x07, 0xD8, 0xE3, 0xAB, 0x50, 0x8B,
	0x07, 0xD8, 0xE3, 0xAB, 0x50, 0x8B,
	0x07, 0xD8, 0xE3, 0xAB, 0x50, 0x8B,
	0x07, 0xD8, 0xE3, 0xAB, 0x50, 0x8B,
	0x07, 0xD8, 0xE3, 0xAB, 0x50, 0x8B,
	0x07, 0xD8, 0xE3, 0xAB, 0x50, 0x8B,

	0x80, 0x50, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00,

	0x40, 0x00, 0x00,
	0xFD, 0xFD, 0xFD, 0xFD};
*/

byte debug_party_data[GEN2_INT_SIZE + 4] = { // International Gen 2
	0x8A, 0x91, 0x88, 0x92, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50,
	0x06,
	0x81, 0xC9, 0xA1, 0x97, 0xFB, 0x24,
	0xFF,
	0x25, 0xDA,

	0x81, 0x00, 0x37, 0x21, 0x2C, 0x2B, 0x25, 0xDA, 0x00, 0x00, 0xA7, 0x00, 0x46, 0x00, 0x5C, 0x00, 0x44, 0x00, 0x28, 0x00, 0x46, 0xFA, 0xAA, 0x1F, 0x1E, 0xC0, 0x00, 0x45, 0xF2, 0x85, 0x81, 0x05, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x13, 0x00, 0x0A, 0x00, 0x09, 0x00, 0x0B, 0x00, 0x0B, 0x00, 0x0A,
	0xC9, 0x00, 0x21, 0x27, 0xED, 0x00, 0x25, 0xDA, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2D, 0x11, 0x23, 0x1E, 0x00, 0x00, 0x46, 0x00, 0x82, 0x82, 0x02, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x0D, 0x00, 0x07, 0x00, 0x06, 0x00, 0x07, 0x00, 0x06, 0x00, 0x06,
	0xA1, 0x00, 0x21, 0x00, 0x00, 0x00, 0x25, 0xDA, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x8B, 0x23, 0x00, 0x00, 0x00, 0x46, 0x00, 0x83, 0x82, 0x03, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x08, 0x00, 0x07, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08,
	0x97, 0x00, 0x21, 0x00, 0x00, 0x00, 0x25, 0xDA, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDB, 0x87, 0x21, 0x00, 0x00, 0x00, 0x46, 0x00, 0x82, 0x02, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x0D, 0x00, 0x07, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x07,
	0xFB, 0x00, 0x21, 0x00, 0x00, 0x00, 0x25, 0xDA, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x34, 0x21, 0x00, 0x00, 0x00, 0x46, 0x00, 0x83, 0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x00, 0x07, 0x00, 0x07, 0x00, 0x06, 0x00, 0x07, 0x00, 0x07,
	0x24, 0x00, 0x01, 0x2F, 0x21, 0x00, 0x25, 0xDA, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x23, 0x00, 0x00, 0x00, 0x46, 0x00, 0x82, 0x02, 0x02, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x0D, 0x00, 0x07, 0x00, 0x06, 0x00, 0x05, 0x00, 0x06, 0x00, 0x06,

	0x8A, 0x91, 0x88, 0x92, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50,
	0x8A, 0x91, 0x88, 0x92, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50,
	0x8A, 0x91, 0x88, 0x92, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50,
	0x8A, 0x91, 0x88, 0x92, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50,
	0x8A, 0x91, 0x88, 0x92, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50,
	0x8A, 0x91, 0x88, 0x92, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50,

	0x82, 0x98, 0x8D, 0x83, 0x80, 0x90, 0x94, 0x88, 0x8B, 0x50, 0x50,
	0x91, 0x80, 0x93, 0x93, 0x80, 0x93, 0x80, 0x50, 0x50, 0x50, 0x50,
	0xF1, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xE1, 0xE2, 0x50, 0x50,
	0x92, 0x84, 0x8D, 0x93, 0x91, 0x84, 0x93, 0x50, 0x50, 0x50, 0x50,
	0x92, 0x84, 0x8D, 0x93, 0x91, 0x84, 0x93, 0x50, 0x50, 0x50, 0x50,
	0xE3, 0xE6, 0xE7, 0xF3, 0xF2, 0xF4, 0x7F, 0x50, 0x50, 0x50, 0x50,

	0x00, 0x00, 0x00,
	0xFD, 0xFD, 0xFD, 0xFD};

Pokemon_Party::Pokemon_Party(){};
void Pokemon_Party::start_link()
{
	if (IGNORE_LINK_CABLE)
	{
		for (int i = 0; i < GEN2_INT_SIZE + 4; i++)
		{
			party_data_array[i] = debug_party_data[i];
		}
	}
	else
	{
		setup();
		last_error = loop(&party_data_array[0]);
	}
}

int Pokemon_Party::get_last_error()
{
	return last_error;
}

void Pokemon_Party::load_pokemon()
{
	for (int i = 0; i < 6; i++)
	{
		party[i].load_data(i, &party_data_array[0]);
		party[i].convert_to_gen_three();
	}
}

Pokemon *Pokemon_Party::get_full_pokemon_array()
{
	return party;
}

bool Pokemon_Party::get_has_new_pkmn()
{
	for (int i = 0; i < 6; i++)
	{
		if (party[i].get_is_new())
		{
			return true;
		}
	}
	return false;
}