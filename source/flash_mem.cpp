#include <tonc.h>
#include <string>
#include "flash_mem.h"
#include "gba_flash.h"
#include "pokemon.h"
#include "rom_data.h"

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
    flash_read(SAVE_A_OFFSET + SAVE_INDEX_OFFSET, &save_A_index[0], 0x04);
    flash_read(SAVE_B_OFFSET + SAVE_INDEX_OFFSET, &save_B_index[0], 0x04);
    reverse_endian(&save_A_index[0], 0x04);
    reverse_endian(&save_B_index[0], 0x04);

    // Determines if save A or B is more recent
    if (*(vu32 *)save_B_index > *(vu32 *)save_A_index)
    {
        newest_save_offset = SAVE_B_OFFSET;
        mem_name = 'B';
    }

    // Populates the memory_section_array with the correct pointer locations
    flash_read(newest_save_offset + SECTION_ID_OFFSET, &mem_id, 1);
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
        flash_read(memory_section_array[mem_section], &global_memory_buffer[0], 0x1000);
        tte_set_pos(8, 0);
        tte_write("loc: ");
        tte_write(std::to_string(memory_section_array[mem_section] + mem_start).c_str());
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
            tte_write(std::to_string(global_memory_buffer[i]).c_str());
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
    std::string out;
    out.append(1, mem_name);
    out += "-";
    out += std::to_string(mem_id);
    tte_set_pos(0, 0);
    tte_write(out.c_str());
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

// Inserts "total_num" Pokemon from the party array
/*
bool insert_pokemon(Pokemon party[], int total_num)
{
    int pkmn_num = 0;
    int mem_section = 5;
    int byte_location = 4;
    int pkmn_byte = 0;
    bool write_pkmn = false;

    flash_read(memory_section_array[mem_section], &global_memory_buffer[0], 0x1000);

    while (pkmn_num < total_num)
    {
        // Checks if we are currently beyond PC box information bounds. If so, return false
        if ((mem_section == 13) && (byte_location >= 1860))
        {
            update_memory_buffer_checksum();
            flash_write(memory_section_array[mem_section], &global_memory_buffer[0], 0x1000);
            return false;
        }

        // Determines if there is space to write a Pokemon, or if a Pokemon is currently being written
        write_pkmn = (write_pkmn | (global_memory_buffer[byte_location] == 0x00));

        // Writes a byte of the current Pokemon to the current spot
        if (write_pkmn)
        {
            global_memory_buffer[byte_location] = party[pkmn_num].get_full_gen_3_array()[pkmn_byte];
            byte_location++;
            pkmn_byte++;
            // Determines if the whole Pokemon has been written
            if (pkmn_byte == pkmn_length)
            {
                pkmn_byte = 0x00;
                write_pkmn = false;
                pkmn_num++;
            }
        }
        else
        {
            byte_location += pkmn_length;
        }
        // If at any point we are beyond the bounds of the current memory section,
        // we move to the next memory buffer and save the current one
        if (byte_location >= 3968)
        {
            update_memory_buffer_checksum();
            flash_write(memory_section_array[mem_section], &global_memory_buffer[0], 0x1000);
            mem_section++;
            flash_read(memory_section_array[mem_section], &global_memory_buffer[0], 0x1000);
            byte_location = byte_location % 3968;
        }
    }
    update_memory_buffer_checksum();
    flash_write(memory_section_array[mem_section], &global_memory_buffer[0], 0x1000);
    return true;
}
*/

// Updates the checksum in the current memory buffer to match what is expected
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
        checksum += (global_memory_buffer[(4 * i) + 3] << 24) | (global_memory_buffer[(4 * i) + 2] << 16) | (global_memory_buffer[(4 * i) + 1] << 8) | (global_memory_buffer[(4 * i) + 0] << 0);
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
        tte_write(std::to_string((curr_rom.offset_flags + (flag_id / 8)) % 0xF80).c_str());
        tte_write(" of memory section ");
        tte_write(std::to_string(1 + ((curr_rom.offset_flags + (flag_id / 8)) / 0xF80)).c_str());
        tte_write(" for flag ");
        tte_write(std::to_string(flag_id).c_str());
        tte_write(". Flag is ");
        flash_read(memory_section_array[1 + ((curr_rom.offset_flags + (flag_id / 8)) / 0xF80)], &global_memory_buffer[0], 0x1000);
        u8 flags = global_memory_buffer[(curr_rom.offset_flags + (flag_id / 8)) % 0xF80];
        tte_write(std::to_string((flags >> (flag_id % 8)) & 0b1).c_str());
        while (true)
        {
        };
    }

    flash_read(memory_section_array[1 + ((curr_rom.offset_flags + (flag_id / 8)) / 0xF80)], &global_memory_buffer[0], 0x1000);
    u8 flags = global_memory_buffer[(curr_rom.offset_flags + (flag_id / 8)) % 0xF80];
    return (flags >> (flag_id % 8)) & 0b1;
}

bool compare_map_and_npc_data(int map_bank, int map_id, int npc_id)
{
    flash_read(memory_section_array[4], &global_memory_buffer[0], 0x1000);
    return (global_memory_buffer[curr_rom.offset_script + 5] == map_bank &&
            global_memory_buffer[curr_rom.offset_script + 6] == map_id &&
            global_memory_buffer[curr_rom.offset_script + 7] == npc_id);
}