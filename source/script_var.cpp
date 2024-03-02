
#include <tonc.h>
#include <string>
#include "script_var.h"
#include "pokemon_data.h"

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
}

u8 asm_var::add_reference()
{
    location_list.push_back(*curr_loc_ptr);
    return 0x00;
}

void asm_var::fill_refrences(u8 mg_array[])
{
    for (unsigned int i = 0; i < location_list.size(); i++)
    {
        mg_array[location_list[i]] += ((start_location_in_script - location_list[i]) / 4) & 0xFF;
    }
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

// TEXTBOX VAR

void textbox_var::set_text(std::u16string_view nText)
{
    text = nText;
}

void textbox_var::insert_text(u8 mg_array[]){
    set_start();
    for (unsigned int parser = 0; parser < text.length(); parser++)
        {
            mg_array[*curr_loc_ptr] = get_gen_3_char((char16_t)(text.at(parser)), false);
            (*curr_loc_ptr)++;
        }
        mg_array[*curr_loc_ptr] = 0xFF; // End string
        (*curr_loc_ptr)++;
}