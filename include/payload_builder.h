#ifndef PAYLOAD_BUILDER_H
#define PAYLOAD_BUILDER_H

#define TRANSFER 1
#define EVENT 2

#include "gb_rom_values/base_gb_rom_struct.h"

byte *generate_payload(GB_ROM curr_rom, int type, bool debug);
void write_call(int generation, byte array_data[], int& offset, word call_location);
void insert_ext_copy_cmd(int *offset, word source, hword destination, byte size);
void insert_int_copy_cmd(int *offset, hword destination, byte size, byte data[]);


#endif