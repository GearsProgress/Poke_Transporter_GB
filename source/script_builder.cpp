#include <tonc.h>
#include "script_builder.h"

mystery_gift_script::mystery_gift_script()
{
    curr_index = 0;
}

void mystery_gift_script::build_script()
{
    set_script();
};

void mystery_gift_script::set_script()
{
    // Located at 0x?8A8 in the .sav
    setvirtualaddress(0x08000000);
    lock();
    faceplayer();
    checkflag(FLAG_ALL_COLLECTED);
    virtualgotoif(COND_FLAGTRUE, JUMP_ALL_COLLECTED);
    virtualmsgbox(TEXT_GREET);
    waitmsg();
    waitkeypress();
    setvar(VAR_INDEX, 0x0000);
    setvar(VAR_CALLASM, rev_endian(0x0023));
    setvar(VAR_PKMN_OFFSET, 0x0000);
    copybyte(PTR_SCRIPT_PTR_LOW, PTR_BLOCK_PTR_LOW);
    copybyte(PTR_SCRIPT_PTR_LOW + 1, PTR_BLOCK_PTR_LOW + 1);
    copybyte(PTR_SCRIPT_PTR_HIGH, PTR_BLOCK_PTR_HIGH);
    copybyte(PTR_SCRIPT_PTR_HIGH + 1, PTR_BLOCK_PTR_HIGH + 1);
    addvar(VAR_SCRIPT_PTR_LOW, 0x3731);
    addvar(VAR_SCRIPT_PTR_LOW, 0x164); // Combine to one line to free up space
    setvar(VAR_CALL_RETURN_1, rev_endian(0x0300));
    setvar(VAR_CALL_CHECK_FLAG, rev_endian(0x2B00));
    addvar(VAR_CALL_CHECK_FLAG, 0x2000);
    setvar(VAR_CALL_RETURN_2, rev_endian(0x0003));
    set_jump_destination(JUMP_LOOP);
    call(PTR_CALL_CHECK_FLAG);
    virtualgotoif(COND_FLAGFALSE, JUMP_PKMN_COLLECTED);
    call(PTR_CALLASM);
    compare(VAR_BOX_RETURN, 0x02);
    virtualgotoif(COND_EQUALS, JUMP_BOX_FULL);
    set_jump_destination(JUMP_PKMN_COLLECTED);
    addvar(VAR_PKMN_OFFSET, 0x64);
    addvar(VAR_INDEX, 0x01);
    addvar(VAR_CALL_CHECK_FLAG, 0x0100);
    compare(VAR_INDEX, 0x06);
    virtualgotoif(COND_LESSTHAN, JUMP_LOOP);
    setflag(FLAG_ALL_COLLECTED);
    set_jump_destination(JUMP_ALL_COLLECTED);
    virtualmsgbox(TEXT_THANK);
    waitmsg();
    waitkeypress();
    release();
    end();
    set_jump_destination(JUMP_BOX_FULL);
    virtualmsgbox(TEXT_FULL);
    waitmsg();
    waitkeypress();
    release();
    end();

    insert_textboxes();

    fill_jumppoint_pointers();
    fill_textbox_pointers();
};

u8 mystery_gift_script::get_script_value_at(int i)
{
    return mg_script[i];
}

u16 mystery_gift_script::rev_endian(u16 num)
{
    return ((num & 0xFF) << 8) | (num >> 8);
}

void mystery_gift_script::add_command(int len)
{
    for (int i = 0; i < len; i++)
    {
        mg_script[curr_index] = value_buffer[i];
        curr_index++;
    }
}

void mystery_gift_script::fill_jumppoint_pointers()
{
    for (int i = 0; i < NUM_JUMPS; i++) // Parse through the script and replace any jump points
                                        // and text boxes to match their locations
    {
        u32 jump_addr = jumppoint_destination[i] + VIR_ADDRESS;
        u32 jump_loc = jumppoint_location[i];
        mg_script[jump_loc] = jump_addr >> 0;
        mg_script[jump_loc + 1] = jump_addr >> 8;
        mg_script[jump_loc + 2] = jump_addr >> 16;
        mg_script[jump_loc + 3] = jump_addr >> 24;
    }
}

void mystery_gift_script::fill_textbox_pointers()
{
    for (int i = 0; i < NUM_TEXTBOXES; i++)
    {
        u32 textbox_addr = textbox_destination[i] + VIR_ADDRESS;
        u32 textbox_loc = textbox_location[i];
        mg_script[textbox_loc] = textbox_addr >> 0;
        mg_script[textbox_loc + 1] = textbox_addr >> 8;
        mg_script[textbox_loc + 2] = textbox_addr >> 16;
        mg_script[textbox_loc + 3] = textbox_addr >> 24;
    }
}

void mystery_gift_script::insert_textboxes()
{
    for (int i = 0; i < NUM_TEXTBOXES; i++)
    {
        textbox_destination[i] = curr_index;
        for (unsigned int parser = 0; parser < textboxes[i].length(); parser++)
        {
            mg_script[curr_index] = convert_char(textboxes[i].at(parser));
            curr_index++;
        }
        mg_script[curr_index] = 0xFF; // End string
        curr_index++;
    }
}

u8 mystery_gift_script::convert_char(char convert_char)
{
    switch (convert_char)
    {
    case '0' ... '9':
        return convert_char + (0xA1 - '0'); // '0' = 0xA1
    case 'A' ... 'Z':
        return convert_char + (0xBB - 'A'); // 'A' = 0xBB
    case 'a' ... 'z':
        return convert_char + (0xD5 - 'a'); // 'a' = 0xD5
    case '!':
        return 0xAB;
    case '?':
        return 0xAC;
    case '.':
        return 0xAD;
    case '#': // Variable escape sequence
        return 0xFD;
    case '*': // Player name
        return 0x01;
    case '^': // Wait for button and scroll text
        return 0xFA;
    case '-': // Wait for button and clear text
        return 0xFB;
    case ' ':
        return 0x00;
    default:
        return 0x00;
    }
}

u16 mystery_gift_script::calc_checksum() // Implementation taken from PokeEmerald Decomp
{
    u16 i, j;
    u16 crc = 0x1121;

    for (i = 0; i < MG_SCRIPT_SIZE; i++)
    {
        crc ^= mg_script[i];
        for (j = 0; j < 8; j++)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0x8408;
            else
                crc >>= 1;
        }
    }
    return ~crc;
}

// Scripting commands:

void mystery_gift_script::setvirtualaddress(u32 location)
{
    value_buffer[0] = 0xB8;
    value_buffer[1] = location >> 0;
    value_buffer[2] = location >> 8;
    value_buffer[3] = location >> 16;
    value_buffer[4] = location >> 24;
    add_command(5);
}

void mystery_gift_script::lock()
{
    value_buffer[0] = 0x6A;
    add_command(1);
}

void mystery_gift_script::faceplayer()
{
    value_buffer[0] = 0x5A;
    add_command(1);
}

void mystery_gift_script::checkflag(u8 flag_id)
{
    value_buffer[0] = 0x2B;
    value_buffer[1] = flag_id >> 0;
    value_buffer[2] = flag_id >> 8;
    add_command(3);
}

void mystery_gift_script::virtualgotoif(u8 condition, u8 jumppoint_id)
{
    jumppoint_location[jumppoint_id] = (curr_index + 2);

    value_buffer[0] = 0xBB;
    value_buffer[1] = condition;
    value_buffer[2] = 0x00;
    value_buffer[3] = 0x00;
    value_buffer[4] = 0x00;
    value_buffer[5] = 0x00;
    add_command(6);
}

void mystery_gift_script::set_jump_destination(u8 jumppoint_id)
{
    jumppoint_destination[jumppoint_id] = curr_index;
}

void mystery_gift_script::virtualmsgbox(u8 textbox_id)
{
    textbox_location[textbox_id] = (curr_index + 1);
    value_buffer[0] = 0xBD;
    value_buffer[1] = 0x00;
    value_buffer[2] = 0x00;
    value_buffer[3] = 0x00;
    value_buffer[4] = 0x00;
    add_command(5);
}

void mystery_gift_script::waitmsg()
{
    value_buffer[0] = 0x66;
    add_command(1);
}

void mystery_gift_script::waitkeypress()
{
    value_buffer[0] = 0x6D;
    add_command(1);
}

void mystery_gift_script::setvar(u16 var_id, u16 value)
{
    value_buffer[0] = 0x16;
    value_buffer[1] = var_id >> 0;
    value_buffer[2] = var_id >> 8;
    value_buffer[3] = value >> 0;
    value_buffer[4] = value >> 8;
    add_command(5);
}

void mystery_gift_script::copybyte(u32 destination, u32 source)
{
    value_buffer[0] = 0x15;
    value_buffer[1] = destination >> 0;
    value_buffer[2] = destination >> 8;
    value_buffer[3] = destination >> 16;
    value_buffer[4] = destination >> 24;
    value_buffer[5] = source >> 0;
    value_buffer[6] = source >> 8;
    value_buffer[7] = source >> 16;
    value_buffer[8] = source >> 24;
    add_command(9);
}

void mystery_gift_script::addvar(u16 var_id, u16 value)
{
    value_buffer[0] = 0x17;
    value_buffer[1] = var_id >> 0;
    value_buffer[2] = var_id >> 8;
    value_buffer[3] = value >> 0;
    value_buffer[4] = value >> 8;
    add_command(5);
}

void mystery_gift_script::call(u32 script_ptr)
{
    value_buffer[0] = 0x04;
    value_buffer[1] = script_ptr >> 0;
    value_buffer[2] = script_ptr >> 8;
    value_buffer[3] = script_ptr >> 16;
    value_buffer[4] = script_ptr >> 24;
    add_command(5);
}

void mystery_gift_script::compare(u16 var_id, u16 value)
{
    value_buffer[0] = 0x21;
    value_buffer[1] = var_id >> 0;
    value_buffer[2] = var_id >> 8;
    value_buffer[3] = value >> 0;
    value_buffer[4] = value >> 8;
    add_command(5);
}

void mystery_gift_script::setflag(u16 flag_id)
{
    value_buffer[0] = 0x29;
    value_buffer[1] = flag_id >> 0;
    value_buffer[2] = flag_id >> 8;
    add_command(3);
}

void mystery_gift_script::release()
{
    value_buffer[0] = 0x6C;
    add_command(1);
}

void mystery_gift_script::end()
{
    value_buffer[0] = 02;
    add_command(1);
}

/* Default script:
void mystery_gift_script::checkflag(int flag_id)
{
    value_buffer[0] = 0x2B;
    value_buffer[1] = flag_id >> 0;
    value_buffer[2] = flag_id >> 8;
    add_command(3);
}
*/