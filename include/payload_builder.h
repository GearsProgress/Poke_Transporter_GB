#ifndef PAYLOAD_BUILDER_H
#define PAYLOAD_BUILDER_H

#include "gb_rom_values/base_gb_rom_struct.h"

byte *generate_payload(GB_ROM curr_rom, bool debug);
void write_call(int generation, byte array_data[], int& offset, word call_location);

#endif