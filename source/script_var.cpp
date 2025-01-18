#include <tonc.h>
#include <string>
#include "script_var.h"
#include "pokemon_data.h"
#include "debug_mode.h"

extern rom_data curr_rom;

script_var::script_var(u32 nValue, std::vector<script_var *> &var_list_ref, int *nCurr_loc_ptr)
{
    var_list_ref.push_back(this); // Place the new object in the var_list
    value = nValue;
    curr_loc_ptr = nCurr_loc_ptr;
};

script_var::script_var(std::vector<script_var *> &var_list_ref, int *nCurr_loc_ptr)
{
    var_list_ref.push_back(this); // Place the new object in the var_list
    curr_loc_ptr = nCurr_loc_ptr;
};

u32 script_var::place_word()
{
    set_start();
    return value;
}

void script_var::set_start()
{
    tte_write("set_start error");
    while (true)
    {
        // This should never run
    }
}

void script_var::fill_refrences(u8 mg_array[])
{
    tte_write("fill_refrences error");
    while (true)
    {
        // This should never run
    };
}

// ASM VAR ----------------

void asm_var::set_start()
{
    start_location_in_script = *curr_loc_ptr - 2;
    isDirect = false;
}

void asm_var::set_start(bool nIsDirect)
{
    start_location_in_script = *curr_loc_ptr - 2;
    isDirect = nIsDirect;
}

u8 asm_var::add_reference()
{
    return add_reference(0);
}

u8 asm_var::add_reference(int nCommand_offset)
{
    location_list.push_back(*curr_loc_ptr + nCommand_offset);
    return 0x00;
}

void asm_var::fill_refrences(u8 mg_array[])
{
    for (unsigned int i = 0; i < location_list.size(); i++)
    {
        if (isDirect)
        {
            for (int j = 0; j < 4; j++)
            {
                mg_array[location_list[i] + j] += (start_location_in_script + curr_rom.loc_gSaveBlock1 + curr_rom.offset_ramscript + 7) >> (j * 8);
            }
        }
        else
        {
            mg_array[location_list[i]] += ((start_location_in_script - location_list[i]) / 4) & 0xFF;
        }
    }
}

u32 asm_var::get_loc_in_sec30()
{
    return start_location_in_script + curr_rom.loc_gSaveDataBuffer + 3; // plus 3 to offset the -2 in set_start, and one for reading as thumb
}

// XSE VAR ----------------

void xse_var::set_start()
{
    start_location_in_script = *curr_loc_ptr - 4;
}

u8 xse_var::add_reference(int nCommand_offset)
{
    location_list.push_back(*curr_loc_ptr + nCommand_offset);
    command_offset = nCommand_offset;
    has_reference_var = false;
    refrence_var = nullptr;
    return 0x0000;
}

u8 xse_var::add_reference(int nCommand_offset, xse_var *offset_from)
{
    add_reference(nCommand_offset);
    has_reference_var = true;
    refrence_var = offset_from;
    return 0x0000;
}

void xse_var::fill_refrences(u8 mg_array[])
{
    for (unsigned int i = 0; i < location_list.size(); i++)
    {
        int internal_offset = 0;
        if (has_reference_var)
        {
            internal_offset = refrence_var->start_location_in_script;
        }
        mg_array[location_list[i]] += (start_location_in_script - internal_offset) & 0xFF;
        mg_array[location_list[i] + 1] += ((start_location_in_script - internal_offset) & 0xFF00) >> 8;
    }
}

u32 xse_var::get_loc_in_sec30()
{
    return start_location_in_script + curr_rom.loc_gSaveDataBuffer;
}

// TEXTBOX VAR

void textbox_var::set_text(std::u16string_view nText)
{
    text = nText;
}

void textbox_var::set_start()
{
    start_location_in_script = *curr_loc_ptr - (ENABLE_OLD_EVENT * 4);
}

void textbox_var::set_virtual_start()
{
    start_location_in_script = *curr_loc_ptr - 4;
}

void textbox_var::insert_text(u8 mg_array[])
{
    set_start();
    for (unsigned int parser = 0; parser < text.length(); parser++)
    {
        byte character = get_gen_3_char((char16_t)(text.at(parser)), false);
        if (curr_rom.is_hoenn() && (character == 0xFC) && (get_gen_3_char((char16_t)(text.at(parser + 1)), false) == 0x01)) // Removes colored text
        {
            parser += 2;
        }
        else
        {
            mg_array[*curr_loc_ptr] = character;
            (*curr_loc_ptr)++;
        }
    }
    mg_array[*curr_loc_ptr] = 0xFF; // End string
    (*curr_loc_ptr)++;
}

void textbox_var::insert_virtual_text(u8 mg_array[])
{
    set_virtual_start();
    for (unsigned int parser = 0; parser < text.length(); parser++)
    {
        byte character = get_gen_3_char((char16_t)(text.at(parser)), false);
        if (curr_rom.is_hoenn() && (character == 0xFC) && (get_gen_3_char((char16_t)(text.at(parser + 1)), false) == 0x01)) // Removes colored text
        {
            parser += 2;
        }
        else
        {
            mg_array[*curr_loc_ptr] = character;
            (*curr_loc_ptr)++;
        }
    }
    mg_array[*curr_loc_ptr] = 0xFF; // End string
    (*curr_loc_ptr)++;
}

// MOVEMENT VAR

void movement_var::set_movement(const int nMovement[], unsigned int nSize)
{
    movement = nMovement;
    size = nSize;
}

void movement_var::set_start()
{
    start_location_in_script = *curr_loc_ptr;
}

void movement_var::insert_movement(u8 mg_array[])
{
    set_start();
    for (unsigned int parser = 0; parser < size; parser++)
    {
        mg_array[*curr_loc_ptr] = movement[parser];
        (*curr_loc_ptr)++;
    }
    mg_array[*curr_loc_ptr] = 0xFE; // End list
    (*curr_loc_ptr)++;
}

// SPRITE VAR

void sprite_var::set_start()
{
    start_location_in_script = *curr_loc_ptr;
}

void sprite_var::insert_sprite_data(u8 mg_array[], const unsigned int sprite_array[], unsigned int size, const unsigned short palette_array[])
{

    set_start();
    u32 pointer = curr_rom.loc_gSaveDataBuffer + *curr_loc_ptr + 8;
    for (int i = 0; i < 4; i++)
    {
        mg_array[*curr_loc_ptr] = pointer >> (8 * i);
        (*curr_loc_ptr)++;
    }
    for (int i = 0; i < 4; i++)
    {
        mg_array[*curr_loc_ptr] = size >> (8 * i);
        (*curr_loc_ptr)++;
    }

    LZ77UnCompWram(sprite_array, &mg_array[*curr_loc_ptr]);
    *curr_loc_ptr += size;

    for (unsigned int parser = 0; parser < 32; parser++)
    {
        mg_array[*curr_loc_ptr] = palette_array[parser / 2] >> (8 * (parser % 2));
        (*curr_loc_ptr)++;
    }
}

// MUSIC VAR

void music_var::set_start()
{
    start_location_in_script = *curr_loc_ptr;
}

void music_var::add_track(std::vector<byte> track)
{
    trackArrays.push_back(track);
}

void music_var::insert_music_data(u8 mg_array[], u8 blockCount, u8 priority, u8 reverb, u32 toneDataPointer)
{
    for (unsigned int i = 0; i < trackArrays.size(); i++)
    {
        trackPointers.push_back(*curr_loc_ptr + curr_rom.loc_gSaveDataBuffer);
        for (unsigned int j = 0; j < trackArrays[i].size(); j++)
        {
            mg_array[(*curr_loc_ptr)++] = trackArrays[i][j];
        }
    }

    while ((*curr_loc_ptr) % 4 != 0)
    {
        (*curr_loc_ptr)++;
    }
    set_start();
    mg_array[(*curr_loc_ptr)++] = trackArrays.size();
    mg_array[(*curr_loc_ptr)++] = blockCount;
    mg_array[(*curr_loc_ptr)++] = priority;
    mg_array[(*curr_loc_ptr)++] = reverb;
    for (int i = 0; i < 4; i++)
    {
        mg_array[(*curr_loc_ptr)++] = toneDataPointer >> (8 * i);
    }

    for (unsigned int i = 0; i < trackArrays.size(); i++)
    {
        mg_array[(*curr_loc_ptr)++] = trackPointers[i] >> 0;
        mg_array[(*curr_loc_ptr)++] = trackPointers[i] >> 8;
        mg_array[(*curr_loc_ptr)++] = trackPointers[i] >> 16;
        mg_array[(*curr_loc_ptr)++] = trackPointers[i] >> 24;
    }
}