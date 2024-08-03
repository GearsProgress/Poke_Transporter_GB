#ifndef PAYLOAD_BUILDER_H
#define PAYLOAD_BUILDER_H

#define TRANSFER 1
#define EVENT 2
#define TEST 3

#include "gb_rom_values/base_gb_rom_struct.h"
#include <vector>

byte* generate_payload(GB_ROM curr_rom, int type, bool debug);

#endif