#ifndef PAYLOAD_BUILDER_H
#define PAYLOAD_BUILDER_H

#define TRANSFER 1
#define EVENT 2
#define TEST 3

#include "gb_rom_values/base_gb_rom_struct.h"
#include <vector>

#define DATA_PER_PACKET 8
#define PACKET_DATA_START 2
#define PACKET_DATA_AT(i) (PACKET_DATA_START + (i * 2))
#define PACKET_FLAG_AT(i) (PACKET_DATA_START + (i * 2) + 1)
#define PACKET_CHECKSUM (PACKET_DATA_START + (2 * DATA_PER_PACKET))
#define PACKET_LOCATION_UPPER (PACKET_CHECKSUM + 1)
#define PACKET_LOCATION_LOWER (PACKET_CHECKSUM + 2)

// 0xFD, 0x00, data bytes per packet, flag bytes per packet, the checksum, and two location bytes
#define PACKET_SIZE (1 + 1 + (2 * DATA_PER_PACKET) + 1 + 2) // Originally 13


byte* generate_payload(GB_ROM curr_rom, int type, bool debug);

#endif