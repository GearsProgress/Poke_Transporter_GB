#include <tonc.h>
#include "script.h"
#include "flash_mem.h"
#include "gba_flash.h"
#include "script_builder.h"

static u32 wonder_card[0x14E] = {
    0xFC, 0x85, 0x00, 0x00, 0xE8, 0x03, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 0xCF, 0xCC, 0xC9, 0xCC, 0xBB, 0xCE, 0xC3, 0xBD, 0xC5, 0xBF, 0xCE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBF, 0xEC, 0xD7, 0xDC, 0xD5, 0xE2, 0xDB, 0xD9, 0x00, 0xBD, 0xD5, 0xE6, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC1, 0xE3, 0x00, 0xE8, 0xE3, 0x00, 0xE8, 0xDC, 0xD9, 0x00, 0xE7, 0xD9, 0xD7, 0xE3, 0xE2, 0xD8, 0x00, 0xDA, 0xE0, 0xE3, 0xE3, 0xE6, 0x00, 0xE3, 0xDA, 0x00, 0xE8, 0xDC, 0xD9, 0x00, 0xCA, 0xC9, 0xC5, 0x1B, 0xC7, 0xC9, 0xC8, 0x00, 0x00, 0x00, 0xBD, 0xBF, 0xC8, 0xCE, 0xBF, 0xCC, 0x00, 0xD5, 0xE2, 0xD8, 0x00, 0xE1, 0xD9, 0xD9, 0xE8, 0x00, 0xE8, 0xDC, 0xD9, 0x00, 0xD8, 0xD9, 0xE0, 0xDD, 0xEA, 0xD9, 0xE6, 0xED, 0x00, 0xE4, 0xD9, 0xE6, 0xE7, 0xE3, 0xE2, 0x00, 0xDD, 0xE2, 0x00, 0x00, 0xDB, 0xE6, 0xD9, 0xD9, 0xE2, 0xAD, 0x00, 0xCC, 0xD9, 0xD7, 0xD9, 0xDD, 0xEA, 0xD9, 0x00, 0xE8, 0xDC, 0xD9, 0x00, 0xBB, 0xCF, 0xCC, 0xC9, 0xCC, 0xBB, 0xCE, 0xC3, 0xBD, 0xC5, 0xBF, 0xCE, 0x00, 0xD5, 0xE2, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xDC, 0xD9, 0xE2, 0x00, 0xE7, 0xD5, 0xEA, 0xD9, 0x00, 0xE8, 0xDC, 0xD9, 0x00, 0xDB, 0xD5, 0xE1, 0xD9, 0xAB, 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBE, 0xE3, 0x00, 0xE2, 0xE3, 0xE8, 0x00, 0xE8, 0xE3, 0xE7, 0xE7, 0x00, 0xE8, 0xDC, 0xDD, 0xE7, 0x00, 0xBF, 0xEC, 0xD7, 0xDC, 0xD5, 0xE2, 0xDB, 0xD9, 0x00, 0xBD, 0xD5, 0xE6, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD6, 0xD9, 0xDA, 0xE3, 0xE6, 0xD9, 0x00, 0xE6, 0xD9, 0xD7, 0xD9, 0xDD, 0xEA, 0xDD, 0xE2, 0xDB, 0x00, 0xE8, 0xDC, 0xD9, 0x00, 0xBB, 0xCF, 0xCC, 0xC9, 0xCC, 0xBB, 0xCE, 0xC3, 0xBD, 0xC5, 0xBF, 0xCE, 0xAB, 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00};

// CRC16 checksum
void inject_mystery(Pokemon incoming_party_aray[])
{

    mystery_gift_script script;
    script.build_script(incoming_party_aray);
    u16 checksum = script.calc_checksum();

    flash_read(memory_section_array[4], &global_memory_buffer[0], 0x1000);
    for (int i = 0; i < 0x14E; i++)
    {
        global_memory_buffer[script.get_offset_wondercard() + i] = wonder_card[i];
    }

    // Set checksum and padding
    global_memory_buffer[script.get_offset_script()] = checksum >> 0;
    global_memory_buffer[script.get_offset_script() + 1] = checksum >> 8;
    global_memory_buffer[script.get_offset_script() + 2] = 0x00;
    global_memory_buffer[script.get_offset_script() + 3] = 0x00;

    // Add in Mystery Script data
    for (int i = 0; i < MG_SCRIPT_SIZE; i++)
    {
        global_memory_buffer[script.get_offset_script() + 4 + i] = script.get_script_value_at(i);
    }
    update_memory_buffer_checksum();
    flash_write(memory_section_array[4], &global_memory_buffer[0], 0x1000);

    // Set flags
    flash_read(memory_section_array[1 + ((script.get_offset_flags() + (FLAG_ID_START / 8)) / 0xF80)], &global_memory_buffer[0], 0x1000);
    global_memory_buffer[(script.get_offset_flags() + (FLAG_ID_START / 8)) % 0xF80] |= (0b00111111 << (FLAG_ID_START % 8));  // Set "to obtain" flags to 1
    global_memory_buffer[(script.get_offset_flags() + (FLAG_ID_START / 8)) % 0xF80] &= (~0b01000000 << (FLAG_ID_START % 8)); // Set "collected all" flag to 0
    update_memory_buffer_checksum();
    flash_write(memory_section_array[1 + ((script.get_offset_flags() + (FLAG_ID_START / 8)) / 0xF80)], &global_memory_buffer[0], 0x1000);
}