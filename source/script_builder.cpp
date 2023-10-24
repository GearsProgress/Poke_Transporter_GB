#include <tonc.h>
#include "script_builder.h"
#include "pokemon_party.h"

int var_callASM = (VAR_ID_START + 0x00);
int var_script_ptr_low = (VAR_ID_START + 0x01);
int var_script_ptr_high = (VAR_ID_START + 0x02);
int var_call_return_1 = (VAR_ID_START + 0x03);
int var_call_check_flag = (VAR_ID_START + 0x04);
int var_call_return_2 = (VAR_ID_START + 0x05);
int var_box_return = (VAR_ID_START + 0x06);
int var_index = (VAR_ID_START + 0x07);
int var_pkmn_offset = (VAR_ID_START + 0x08);

int ptr_callASM;
int ptr_script_ptr_low;
int ptr_script_ptr_high;
int ptr_call_return_1;
int ptr_call_check_flag;
int ptr_call_return_2;
int ptr_box_return;
int ptr_index;
int ptr_pkmn_offset;

int ptr_block_ptr_low;
int ptr_block_ptr_high;

int flag_pkmn_1 = (FLAG_ID_START + 0x0);
int flag_pkmn_2 = (FLAG_ID_START + 0x1);
int flag_pkmn_3 = (FLAG_ID_START + 0x2);
int flag_pkmn_4 = (FLAG_ID_START + 0x3);
int flag_pkmn_5 = (FLAG_ID_START + 0x4);
int flag_pkmn_6 = (FLAG_ID_START + 0x5);
int flag_all_collected = (FLAG_ID_START + 0x6);

int loc_sendMonToPC;
int loc_gSpecialVar_0x8000;
int loc_gSaveBlock1PTR;
int offset_ramscript; // Source: https://github.com/pret/pokeemerald/blob/master/include/global.h#L1012
int offset_flags;     // Flag offset as found within the SaveBlock1 struct in global.h
int offset_wondercard;
int offset_script;
std::string_view pc_maker;

mystery_gift_script::mystery_gift_script()
{
    curr_index = NPC_LOCATION_OFFSET;

    switch (get_gamecode())
    {
    case (RUBY_ID):
    case (SAPPHIRE_ID):

        pc_maker = "LANETTE";
        offset_wondercard = 0;
        offset_script = 0x0810;
        switch (get_version())

        {
        case (VERS_1_0):
            loc_sendMonToPC = 0;
            loc_gSpecialVar_0x8000 = 0;
            loc_gSaveBlock1PTR = 0;
            offset_ramscript = 0;
            offset_flags = 0;
            break;
        case (VERS_1_1):
            loc_sendMonToPC = 0;
            loc_gSpecialVar_0x8000 = 0;
            loc_gSaveBlock1PTR = 0;
            offset_ramscript = 0;
            offset_flags = 0;
            break;
        case (VERS_1_2):
            loc_sendMonToPC = 0;
            loc_gSpecialVar_0x8000 = 0;
            loc_gSaveBlock1PTR = 0;
            offset_ramscript = 0;
            offset_flags = 0;
            break;
        }
        break;

    case (FIRERED_ID):
    case (LEAFGREEN_ID):

        pc_maker = "BILL";
        offset_wondercard = 0x0460;
        offset_script = 0x079C;
        switch (get_version())
        {
        case (VERS_1_0):
            loc_sendMonToPC = 0;
            loc_gSpecialVar_0x8000 = 0;
            loc_gSaveBlock1PTR = 0;
            offset_ramscript = 0;
            offset_flags = 0;
            break;
        case (VERS_1_1):
            loc_sendMonToPC = 0x08040BA4;
            loc_gSpecialVar_0x8000 = 0x020370B8;
            loc_gSaveBlock1PTR = 0x03005008;
            offset_ramscript = 0x361C;
            offset_flags = 0x0EE0;
            break;
        }
        break;

    case (EMERALD_ID):

        pc_maker = "LANETTM";
        offset_wondercard = 0x056C;
        offset_script = 0x08A8;

        loc_sendMonToPC = 0x0806B490;
        loc_gSpecialVar_0x8000 = 0x020375D8;
        loc_gSaveBlock1PTR = 0x03005D8C;
        offset_ramscript = 0x3728;
        offset_flags = 0x1270;
        break;
    }

    ptr_callASM = (loc_gSpecialVar_0x8000 + 0x00);
    ptr_script_ptr_low = (loc_gSpecialVar_0x8000 + 0x02);
    ptr_script_ptr_high = (loc_gSpecialVar_0x8000 + 0x04);
    ptr_call_return_1 = (loc_gSpecialVar_0x8000 + 0x06);
    ptr_call_check_flag = (loc_gSpecialVar_0x8000 + 0x08);
    ptr_call_return_2 = (loc_gSpecialVar_0x8000 + 0x0A);
    ptr_box_return = (loc_gSpecialVar_0x8000 + 0x0C);
    ptr_index = (loc_gSpecialVar_0x8000 + 0x0E);
    ptr_pkmn_offset = (loc_gSpecialVar_0x8000 + 0x10);

    ptr_block_ptr_low = (loc_gSaveBlock1PTR + 0x00);
    ptr_block_ptr_high = (loc_gSaveBlock1PTR + 0x02);
}

void mystery_gift_script::build_script(Pokemon incoming_party_array[])
{
    // Located at 0x?8A8 in the .sav
    init_npc_location(0xFF, 0xFF, 0xFF);                              // Set the location of the NPC
    setvirtualaddress(0x08000000);                                    // Set virtual address
    lock();                                                           // Lock the player
    faceplayer();                                                     // Have the NPC face the player
    checkflag(flag_all_collected);                                    // Check if the "all collected" flag has been set
    virtualgotoif(COND_FLAGTRUE, JUMP_ALL_COLLECTED);                 // If "all collected" is true, then jump to the "thank you" text
    virtualmsgbox(TEXT_GREET);                                        // Otherwise, greet the player
    waitmsg();                                                        // Wait for the message to finish
    waitkeypress();                                                   // Wait for the player to press A/B
    setvar(var_index, 0);                                             // set the index to 0
    setvar(var_callASM, rev_endian(0x0023));                          // set the call_asm variable to 0x23: 0x23 = CALL ASM
    setvar(var_pkmn_offset, 0);                                       // Set the Pokemon struct offset to 0
    copybyte(ptr_script_ptr_low, ptr_block_ptr_low);                  // Copy the first byte of the saveblock1ptr to a variable
    copybyte(ptr_script_ptr_low + 1, ptr_block_ptr_low + 1);          // Copy the second byte of the saveblock1ptr to a variable
    copybyte(ptr_script_ptr_high, ptr_block_ptr_high);                // Copy the third byte of the saveblock1ptr to a variable
    copybyte(ptr_script_ptr_high + 1, ptr_block_ptr_high + 1);        // Copy the fourth byte of the saveblock1ptr to a variable
    addvar(var_script_ptr_low, offset_ramscript + 8 + READ_AS_THUMB); // add the offset for ramscript, plus 8. 8 is for the 8 bytes of Checksum, padding and NPC info
    addvar(var_script_ptr_low, get_ptr_offset(REL_PTR_ASM_START));    // Add the offset for the start of ASM
    setvar(var_call_return_1, rev_endian(0x0300));                    // Set the vairable to 0x03. 0x03 = RETURN
    setvar(var_call_check_flag, rev_endian(0x2B00));                  // Set the variable to 0x2B. 0x2B = CHECK FLAG
    addvar(var_call_check_flag, rev_endian(FLAG_ID_START));           // Add the starting flag ID to the check flag ASM variable
    setvar(var_call_return_2, rev_endian(0x0003));                    // Set the variable to 0x03. 0x03 = RETURN
    set_jump_destination(JUMP_LOOP);                                  // Set the jump destination for the JUMP_LOOP
    call(ptr_call_check_flag);                                        // Call the check flag ASM
    virtualgotoif(COND_FLAGFALSE, JUMP_PKMN_COLLECTED);               // If the "pokemon collected" flag is false, jump to the end of the loop
    call(ptr_callASM);                                                // Call SendMonToPC ASM
    compare(var_box_return, 2);                                       // Compare the resulting return to #2
    virtualgotoif(COND_EQUALS, JUMP_BOX_FULL);                        // If the return value was #2, jump to the box full message
    set_jump_destination(JUMP_PKMN_COLLECTED);                        // Set the jump destination for if the Pokemon has already been collected
    addvar(var_pkmn_offset, POKEMON_SIZE);                            // Add the size of one Pokmeon to the Pokemon offset
    addvar(var_index, 1);                                             // Add one to the index
    addvar(var_call_check_flag, rev_endian(1));                       // Add one to the flag index
    compare(var_index, 6);                                            // Compare the index to 6
    virtualgotoif(COND_LESSTHAN, JUMP_LOOP);                          // if index is less than six, jump to the start of the loop
    setflag(flag_all_collected);                                      // Set the "all collected" flag
    fanfare(0xA4);                                                    // Play the received fanfare
    virtualmsgbox(TEXT_RECEIVED);                                     // Display the recieved text
    waitfanfare();                                                    // Wait for the fanfare
    waitmsg();                                                        // Wait for the text to finish
    waitkeypress();                                                   // Wait for the player to press A/B
    set_jump_destination(JUMP_ALL_COLLECTED);                         // Set the destination for if all the Pokemon have already been collected
    virtualmsgbox(TEXT_THANK);                                        // Display the thank test
    waitmsg();                                                        // Wait for the message
    waitkeypress();                                                   // Wait for the player to press A/B
    release();                                                        // Release the player
    end();                                                            // End the script
    set_jump_destination(JUMP_BOX_FULL);                              // Set the destination for if the box is full
    virtualmsgbox(TEXT_FULL);                                         // Display the full box message
    waitmsg();                                                        // Wait for the message
    waitkeypress();                                                   // Wait for the player to presse A/B
    release();                                                        // Release the player
    end();                                                            // End the script

    insert_textboxes();
    four_align();

    set_ptr_destination(REL_PTR_ASM_START);
    push(rlist_lr);                                        //    save the load register to the stack
    ldr3(r3, asm_offset_distance(ASM_OFFSET_PKMN_OFFSET)); //    set r3 to variable to the pokemon offset, variable 0x8008's pointer
    ldr1(r3, r3, 0);                                       //    set r3 to the value in memory r3 points to
    add5(r0, asm_offset_distance(ASM_OFFSET_PKMN_STRUCT)); //    set r0 to a pointer 28 bytes ahead, which is the start of the Pokemon struct.
    add3(r0, r0, r3);                                      //    add r3 to r0, giving it the correct offset for the current index
    ldr3(r1, asm_offset_distance(ASM_OFFSET_SENDMON_PTR)); //    set r1 to the location of "SendMonToPC" plus one, since it is thumb code
    mov3(r2, r15);                                         //    move r15 (the program counter) to r2
    add2(r2, 5);                                           //    add 7 to r2 to compensate for the four following bytes, plus to tell the system to read as thumb code
    mov3(r14, r2);                                         //    move r2 into r14 (the load register)
    bx(r1);                                                //    jump to the pointer stored in r1 (SendMonToPC)
    ldr3(r2, asm_offset_distance(ASM_OFFSET_BOX_SUC_PTR)); //    load variable 0x8006's pointer into r2
    str1(r0, r2, 0);                                       //    put the value of r0 into the memory location pointed at by r2, plus 0
    pop(rlist_r0);                                         //    remove r0 from the stack and put it into r0
    bx(r0);                                                //    jump to r0 (return to where the function was called)
    set_asm_offset_destination(ASM_OFFSET_SENDMON_PTR);    //    set the SENDMON ptr offset
    add_word(loc_sendMonToPC + READ_AS_THUMB);             //    the location of "SendMonToPC", plus one (so it is interpreted as thumb code)
    set_asm_offset_destination(ASM_OFFSET_BOX_SUC_PTR);    //    set the BOX_SUCCESS ptr offset
    add_word(ptr_box_return);                              //    the location of variable "0x8006" (the return value)
    set_asm_offset_destination(ASM_OFFSET_PKMN_OFFSET);    //    set the PKMN_OFFSET ptr offset
    add_word(ptr_pkmn_offset);                             //    the location of variable "0x8008" (the pokemon offset)
    set_asm_offset_destination(ASM_OFFSET_PKMN_STRUCT);    //    set the PKMN_STRUCT ptr offset

    for (int i = 0; i < 6; i++)
    {
        Pokemon curr_pkmn = incoming_party_array[i];
        for (int curr_byte = 0; curr_byte < POKEMON_SIZE; curr_byte++)
        {
            mg_script[curr_index] = curr_pkmn.get_gen_3_data(curr_byte);
            curr_index++;
        }
    }

    fill_jumppoint_pointers();
    fill_textbox_pointers();
    fill_asm_pointers();
    fill_relative_pointers();

    if (curr_index > MG_SCRIPT_SIZE)
    {
        tte_erase_screen();
        int val = (curr_index - MG_SCRIPT_SIZE) - four_align_value;
        tte_write("Script exceeded by ");
        tte_write(std::to_string(val).c_str());
        tte_write(" bytes");
        while (true)
        {
        }
    }
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

int mystery_gift_script::get_offset_wondercard()
{
    return offset_wondercard;
}

int mystery_gift_script::get_offset_script()
{
    return offset_script;
}

int mystery_gift_script::get_offset_flags()
{
    return offset_flags;
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
        textbox_destination[i] = curr_index - NPC_LOCATION_OFFSET;
        if (i != TEXT_RECEIVED)
        {
            for (unsigned int parser = 0; parser < pc_maker.length(); parser++)
            {
                mg_script[curr_index] = convert_char(pc_maker.at(parser));
                curr_index++;
            }
        }
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
    case '%':
        return 0x06;
    case '!':
        return 0xAB;
    case '?':
        return 0xAC;
    case '.':
        return 0xAD;
    case '\'':
        return 0xB4;
    case ':':
        return 0xF0;
    case '_': // ...
        return 0xB0;
    case '/': // Variable escape sequence
        return 0xFD;
    case '*': // Player name
        return 0x01;
    case '^': // Wait for button and scroll text
        return 0xFA;
    case '-': // Wait for button and clear text
        return 0xFB;
    case '~': // New line
        return 0xFE;
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

void mystery_gift_script::add_asm(u16 command)
{
    mg_script[curr_index] = command >> 0;
    mg_script[curr_index + 1] = command >> 8;
    curr_index += 2;
}

void mystery_gift_script::fill_asm_pointers()
{
    for (int i = 0; i < NUM_ASM_OFFSET; i++)
    {
        mg_script[asm_offset_location[i]] |= ((asm_offset_destination[i] - (asm_offset_location[i] + 2)) / 4) & 0xFF;
    }
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
    jumppoint_destination[jumppoint_id] = curr_index - NPC_LOCATION_OFFSET;
}

u8 mystery_gift_script::get_ptr_offset(u8 jumppoint_id)
{
    relative_offset_location[jumppoint_id] = curr_index + 3;
    return 0xFE;
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

void mystery_gift_script::fanfare(u16 fanfare_number)
{
    value_buffer[0] = 0x31;
    value_buffer[1] = fanfare_number >> 0;
    value_buffer[2] = fanfare_number >> 8;
    add_command(3);
}

void mystery_gift_script::waitfanfare()
{
    value_buffer[0] = 0x32;
    add_command(1);
}

void mystery_gift_script::release()
{
    value_buffer[0] = 0x6C;
    add_command(1);
}

void mystery_gift_script::end()
{
    value_buffer[0] = 0x02;
    add_command(1);
}

void mystery_gift_script::init_npc_location(u8 bank, u8 map, u8 npc)
{
    mg_script[0] = 0x33; // File ID?
    mg_script[1] = bank;
    mg_script[2] = map;
    mg_script[3] = npc;
}

// ASM Commands
// Documentation found here:
// https://github.com/LunarLambda/arm-docs

/**
 * @brief PUSH (Push Multiple Registers) stores a subset (or possibly all) of the general-purpose registers R0-R7 and the LR to the stack
 *
 * @param register_list Is the list of registers to be stored, separated by commas and surrounded by { and }. The list is encoded in the register_list field of the instruction, by setting bit[i] to 1 if register Ri is included in the list and to 0 otherwise, for each of i=0 to 7. The R bit (bit[8]) is set to 1 if the LR is in the list and to 0 otherwise.
 */
void mystery_gift_script::push(u16 register_list)
{
    add_asm((0b1011010 << 9) | register_list);
}

/**
 * @brief LDR (3) loads 32-bit memory data into a general-purpose register. The addressing mode is useful for accessing PC-relative data.
 *
 * @param rd Is the destination register for the word loaded from memory.
 * @param immed_8 Is an 8-bit value that is multiplied by 4 and added to the value of the PC to form the memory address.
 */
void mystery_gift_script::ldr3(u8 rd, u8 immed_8)
{
    add_asm(0b01001 << 11 | rd << 8 | immed_8);
}

/**
 * @brief LDR (1) (Load Register) allows 32-bit memory data to be loaded into a general-purpose register. The addressing mode is useful for accessing structure (record) fields. With an offset of zero, the address produced is the unaltered value of the base register <Rn>.
 *
 * @param rd Is the destination register for the word loaded from memory.
 * @param rn Is the register containing the base address for the instruction.
 * @param immed_5 Is a 5-bit value that is multiplied by 4 and added to the value of <Rn> to form the memory address.
 */
void mystery_gift_script::ldr1(u8 rd, u8 rn, u8 immed_5)
{
    add_asm(0b01101 << 11 | immed_5 << 6 | rn << 3 | rd);
}

/**
 * @brief ADD (5) adds an immediate value to the PC and writes the resulting PC-relative address to a destination register. The immediate can be any multiple of 4 in the range 0 to 1020.
 *
 * @param rd Is the destination register for the completed operation.
 * @param immed_8 Specifies an 8-bit immediate value that is quadrupled and added to the value of the PC.
 */
void mystery_gift_script::add5(u8 rd, u8 immed_8)
{
    add_asm(0b10100 << 11 | rd << 8 | immed_8);
}

/**
 * @brief ADD (3) adds the value of one register to the value of a second register, and stores the result in a third register. It updates the condition code flags, based on the result.
 *
 * @param rd Is the destination register for the completed operation.
 * @param rn Specifies the register containing the first value for the addition.
 * @param rm Specifies the register containing the second value for the addition.
 */
void mystery_gift_script::add3(u8 rd, u8 rn, u8 rm)
{
    add_asm(0b0001100 << 9 | rm << 6 | rn << 3 | rd);
}

/**
 * @brief MOV (3) moves a value to, from, or between high registers. Unlike the low register MOV instruction described in MOV (2) on page A7-73, this instruction does not change the flags.
 *
 * @param rd Is the destination register for the operation. It can be any of R0 to R15, and its number is encoded in the instruction in H1 (most significant bit) and Rd (remaining three bits)
 * @param rm Is the register containing the value to be copied. It can be any of R0 to R15, and its number is encoded in the instruction in H2 (most significant bit) and Rm (remaining three bits).
 */
void mystery_gift_script::mov3(u8 rd, u8 rm)
{
    add_asm(0b01000110 << 8 | (rd >> 3) << 7 | (rm >> 3) << 6 | (rm & 0b111) << 3 | (rd & 0b111));
}

/**
 * @brief ADD (2) adds a large immediate value to the value of a register and stores the result back in the same register. The condition code flags are updated, based on the result.
 *
 * @param rd Holds the first operand for the addition, and is the destination register for the completed operation.
 * @param immed_8 Specifies an 8-bit immediate value that is added to the value of <Rd>
 */
void mystery_gift_script::add2(u8 rd, u8 immed_8)
{
    add_asm(0b00110 << 11 | rd << 8 | immed_8);
}

/**
 * @brief BX (Branch and Exchange) branches between ARM code and Thumb code.
 *
 * @param rm Is the register that contains the branch target address. It can be any of R0 to R15. The register number is encoded in the instruction in H2 (most significant bit) and Rm (remaining three bits)
 */
void mystery_gift_script::bx(u8 rm)
{
    add_asm(0b010001110 << 7 | (rm >> 3) << 6 | (rm & 0b111) << 3);
}

/**
 * @brief STR (1) (Store Register) stores 32-bit data from a general-purpose register to memory. The addressing mode is useful for accessing structure (record) fields. With an offset of zero, the address produced is the unaltered value of the base register <Rn>.
 *
 * @param rd Is the register that contains the word to be stored to memory.
 * @param rn Is the register containing the base address for the instruction.
 * @param immed_5 Is a 5-bit value that is multiplied by 4 and added to the value of <Rn> to form the memory address.
 */
void mystery_gift_script::str1(u8 rd, u8 rn, u8 immed_5)
{
    add_asm(0b01100 << 11 | immed_5 << 6 | rn << 3 | rd);
}

/**
 * @brief POP (Pop Multiple Registers) loads a subset (or possibly all) of the general-purpose registers R0-R7 and the PC from the stack.
 *
 * @param register_list Is the list of registers, separated by commas and surrounded by { and }. The list is encoded in the register_list field of the instruction, by setting bit[i] to 1 if register Ri is included in the list and to 0 otherwise, for each of i=0 to 7. The R bit (bit[8]) is set to 1 if the PC is in the list and to 0 otherwise.
 */
void mystery_gift_script::pop(u16 register_list)
{
    add_asm(0b1011110 << 9 | register_list);
}

void mystery_gift_script::add_word(u32 word)
{
    add_asm(word >> 0);
    add_asm(word >> 16);
}

void mystery_gift_script::set_asm_offset_destination(u8 asm_offset_id)
{
    asm_offset_destination[asm_offset_id] = curr_index;
}

u8 mystery_gift_script::asm_offset_distance(u8 asm_offset_id)
{
    asm_offset_location[asm_offset_id] = curr_index;
    return 0x00;
}

void mystery_gift_script::four_align()
{
    for (int i = 0; i < curr_index % 4; i++)
    {
        mg_script[curr_index] = 0xFF;
        curr_index++;
        four_align_value++;
    }
}

void mystery_gift_script::fill_relative_pointers()
{
    for (int i = 0; i < NUM_RELATIVE_PTR; i++)
    {
        mg_script[relative_offset_location[i]] = relative_offset_destination[i] >> 0;
        mg_script[relative_offset_location[i] + 1] = relative_offset_destination[i] >> 8;
    }
}

void mystery_gift_script::set_ptr_destination(u8 relative_ptr_id)
{
    relative_offset_destination[relative_ptr_id] = curr_index - 4;
}