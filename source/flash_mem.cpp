#include <tonc.h>
#include "libstd_replacements.h"
#include "flash_mem.h"
#include "pokemon.h"
#include "rom_data.h"
#include "libraries/Pokemon-Gen3-to-Gen-X/include/save.h"
#include "text_engine.h"

#define pkmn_length 80
#define READ_SAVE_SECTIONS 5
#define TOTAL_SAVE_SECTIONS 14

vu32 newest_save_offset = SAVE_A_OFFSET;

vu32 memory_section_array[READ_SAVE_SECTIONS] = {};
u8 global_memory_buffer[0x1000];
char mem_name = 'A';
u8 mem_id;

// Fills the variables with the current offset information
void initalize_memory_locations()
{
    u8 save_A_index[4];
    u8 save_B_index[4];
    copy_save_to_ram(SAVE_A_OFFSET + SAVE_INDEX_OFFSET, &save_A_index[0], 0x04);
    copy_save_to_ram(SAVE_B_OFFSET + SAVE_INDEX_OFFSET, &save_B_index[0], 0x04);
    reverse_endian(&save_A_index[0], 0x04);
    reverse_endian(&save_B_index[0], 0x04);

    // Determines if save A or B is more recent
    if (*(vu32 *)save_B_index > *(vu32 *)save_A_index)
    {
        newest_save_offset = SAVE_B_OFFSET;
        mem_name = 'B';
    }

    // Populates the memory_section_array with the correct pointer locations
    copy_save_to_ram(newest_save_offset + SECTION_ID_OFFSET, &mem_id, 1);
    for (int i = 0; i < TOTAL_SAVE_SECTIONS; i++)
    {
        if (mem_id < READ_SAVE_SECTIONS)
        {
            memory_section_array[mem_id] = newest_save_offset + (i * 0x1000);
        }
        mem_id = (mem_id + 1) % TOTAL_SAVE_SECTIONS;
    }
    // Bring the Memory ID back to the first one
    mem_id = (mem_id + 1) % TOTAL_SAVE_SECTIONS;

    if (false) // This will print out a section of the FLASH mem for debugging purposes
    {
        int mem_start = 0xF80;
        int mem_section = 1;
        copy_save_to_ram(memory_section_array[mem_section], &global_memory_buffer[0], 0x1000);
        tte_set_pos(8, 0);
        tte_write("loc: ");
        tte_write(ptgb::to_string(memory_section_array[mem_section] + mem_start));
        tte_write("\n");
        for (int i = mem_start; i < (128 + mem_start); i++)
        {
            if (i % 2 == 0)
            {
                tte_write("#{cx:0xE000}");
            }
            else
            {
                tte_write("#{cx:0xD000}");
            }
            tte_write(ptgb::to_string(global_memory_buffer[i]));
            if (i % 8 == 7)
            {
                tte_write("\n");
            }
            else
            {
                if (global_memory_buffer[i] < 10)
                {
                    tte_write("  ");
                }
                else if (global_memory_buffer[i] < 100)
                {
                    tte_write(" ");
                }
                else
                {
                    tte_write("");
                }
            }
        }
        while (true)
        {
        };
    }
}

void print_mem_section()
{
    return; // This function isn't really needed now
    byte out[4] = {0, 0, 0, 0xFF};
    out[0] = get_gen_3_char(mem_name, false);
    out[1] = get_gen_3_char('-', false);
    out[2] = get_gen_3_char(mem_id + 0xA1, false); // Kinda a dumb way to 
    tte_set_pos(0, 0);
    ptgb_write(out, true);
}

// Reverses the endian of the given array
void reverse_endian(u8 *data, size_t size)
{
    u8 temp;
    for (unsigned int i = 0; i < (size / 2); i++)
    {
        temp = data[i];
        data[i] = data[(size - 1) - i];
        data[(size - 1) - i] = temp;
    }
}

void update_memory_buffer_checksum(bool hall_of_fame)
{
    vu32 checksum = 0x00;

    vu32 num_of_bytes = 3968;
    if (global_memory_buffer[0x0FF4] == 13)
    {
        num_of_bytes = 2000;
    }

    for (unsigned int i = 0; i < num_of_bytes / 4; i++)
    {
        checksum += (global_memory_buffer[(4 * i) + 3] << 24) |
                    (global_memory_buffer[(4 * i) + 2] << 16) |
                    (global_memory_buffer[(4 * i) + 1] << 8) |
                    (global_memory_buffer[(4 * i) + 0] << 0);
    }

    vu16 small_checksum = ((checksum & 0xFFFF0000) >> 16) + (checksum & 0x0000FFFF);
    if (hall_of_fame)
    {
        global_memory_buffer[0x0FF4] = small_checksum & 0x00FF;
        global_memory_buffer[0x0FF5] = (small_checksum & 0xFF00) >> 8;
    }
    else
    {
        global_memory_buffer[0x0FF6] = small_checksum & 0x00FF;
        global_memory_buffer[0x0FF7] = (small_checksum & 0xFF00) >> 8;
    }
}

bool read_flag(u16 flag_id)
{
    if (false)
    {
        tte_set_pos(0, 0);
        tte_write("#{cx:0xD000}Attempting to read byte ");
        tte_write(ptgb::to_string((curr_rom.offset_flags + (flag_id / 8)) % 0xF80));
        tte_write(" of memory section ");
        tte_write(ptgb::to_string(1 + ((curr_rom.offset_flags + (flag_id / 8)) / 0xF80)));
        tte_write(" for flag ");
        tte_write(ptgb::to_string(flag_id));
        tte_write(". Flag is ");
        copy_save_to_ram(memory_section_array[1 + ((curr_rom.offset_flags + (flag_id / 8)) / 0xF80)], &global_memory_buffer[0], 0x1000);
        u8 flags = global_memory_buffer[(curr_rom.offset_flags + (flag_id / 8)) % 0xF80];
        tte_write(ptgb::to_string((flags >> (flag_id % 8)) & 0b1));
        while (true)
        {
        };
    }

    copy_save_to_ram(memory_section_array[1 + ((curr_rom.offset_flags + (flag_id / 8)) / 0xF80)], &global_memory_buffer[0], 0x1000);
    u8 flags = global_memory_buffer[(curr_rom.offset_flags + (flag_id / 8)) % 0xF80];
    return (flags >> (flag_id % 8)) & 0b1;
}

bool compare_map_and_npc_data(int map_bank, int map_id, int npc_id)
{
    copy_save_to_ram(memory_section_array[4], &global_memory_buffer[0], 0x1000);
    return (global_memory_buffer[curr_rom.offset_script + 5] == map_bank &&
            global_memory_buffer[curr_rom.offset_script + 6] == map_id &&
            global_memory_buffer[curr_rom.offset_script + 7] == npc_id);
}