#include <tonc.h>
#include <vector>
#include "mystery_gift_builder.h"
#include "pokemon_party.h"
#include "pokemon_data.h"
#include "rom_data.h"

extern rom_data curr_rom;

// These are static variables
int var_callASM = (VAR_ID_START + 0x00);
int var_script_ptr_low = (VAR_ID_START + 0x01);
int var_script_ptr_high = (VAR_ID_START + 0x02);
int var_call_return_1 = (VAR_ID_START + 0x03);
int var_call_check_flag = (VAR_ID_START + 0x04);
int var_call_return_2 = (VAR_ID_START + 0x05);
int var_box_return = (VAR_ID_START + 0x06);
int var_dex_seen_caught = (VAR_ID_START + 0x07);
int var_dex_num = (VAR_ID_START + 0x08);
int var_index = (VAR_ID_START + 0x09);
int var_pkmn_offset = (VAR_ID_START + 0x0A);

// int flag_pkmn_1 = (FLAG_ID_START + 0x0);
// int flag_pkmn_2 = (FLAG_ID_START + 0x1);
// int flag_pkmn_3 = (FLAG_ID_START + 0x2);
// int flag_pkmn_4 = (FLAG_ID_START + 0x3);
// int flag_pkmn_5 = (FLAG_ID_START + 0x4);
// int flag_pkmn_6 = (FLAG_ID_START + 0x5);

// These will all be set based on the ROM pointers
/*
int loc_sendMonToPC;
int loc_gSpecialVar_0x8000;
int loc_gSaveBlock1;    // Only used in R/S
int loc_gSaveBlock1PTR; // Only used in FR/LG/E
int loc_setPokedexFlag;
int offset_ramscript; // Source: https://github.com/pret/pokeemerald/blob/master/include/global.h#L1012
int offset_flags;     // Flag offset as found within the SaveBlock1 struct in global.h
int offset_wondercard;
int offset_script;
int text_region;

u8 map_bank;
u8 map_id;
u8 npc_id;
*/

// These values will be defined once we recieve the ROM pointers
int ptr_callASM;
int ptr_script_ptr_low;
int ptr_script_ptr_high;
int ptr_call_return_1;
int ptr_call_check_flag;
int ptr_call_return_2;
int ptr_box_return;
int ptr_dex_seen_caught;
int ptr_index;
int ptr_pkmn_offset;

int ptr_block_ptr_low;
int ptr_block_ptr_high;

mystery_gift_script::mystery_gift_script()
{
#define NUM_RELATIVE_PTR 1 // THIS STAYS AS 1, THERE IS NO RELATIVE POINTER TO DEX AT THE MOMENT, IT IS A STATIC 28!!!
#define REL_PTR_ASM_START 0
#define REL_PTR_DEX_START 1

    curr_index = NPC_LOCATION_OFFSET;

    ptr_callASM = (curr_rom.loc_gSpecialVar_0x8000 + 0x00);
    ptr_script_ptr_low = (curr_rom.loc_gSpecialVar_0x8000 + 0x02);
    ptr_script_ptr_high = (curr_rom.loc_gSpecialVar_0x8000 + 0x04);
    ptr_call_return_1 = (curr_rom.loc_gSpecialVar_0x8000 + 0x06);
    ptr_call_check_flag = (curr_rom.loc_gSpecialVar_0x8000 + 0x08);
    ptr_call_return_2 = (curr_rom.loc_gSpecialVar_0x8000 + 0x0A);
    ptr_box_return = (curr_rom.loc_gSpecialVar_0x8000 + 0x0C);
    ptr_dex_seen_caught = (curr_rom.loc_gSpecialVar_0x8000 + 0x0E);
    ptr_index = (curr_rom.loc_gSpecialVar_0x8000 + 0x12);
    ptr_pkmn_offset = (curr_rom.loc_gSpecialVar_0x8000 + 0x14);

    ptr_block_ptr_low = (curr_rom.loc_gSaveBlock1PTR + 0x00);
    ptr_block_ptr_high = (curr_rom.loc_gSaveBlock1PTR + 0x02);
}

void mystery_gift_script::build_script(Pokemon_Party &incoming_box_data)
{
    std::vector<script_var *> asm_variable_list;
    asm_var sendMonToPC_ptr(curr_rom.loc_sendMonToPC + READ_AS_THUMB, asm_variable_list, &curr_index);
    asm_var returned_box_success_ptr(ptr_box_return, asm_variable_list, &curr_index);
    asm_var curr_pkmn_index_ptr(ptr_pkmn_offset, asm_variable_list, &curr_index);
    asm_var setPokedexFlag_ptr(curr_rom.loc_setPokedexFlag + READ_AS_THUMB, asm_variable_list, &curr_index);
    asm_var dexSeenCaught_ptr(ptr_dex_seen_caught, asm_variable_list, &curr_index);
    asm_var currPkmnIndex_ptr(ptr_index, asm_variable_list, &curr_index);
    asm_var pkmnStruct(curr_rom.loc_gSaveDataBuffer, asm_variable_list, &curr_index);
    asm_var dexStruct(curr_rom.loc_gSaveDataBuffer + (MAX_PKMN_IN_BOX * POKEMON_SIZE), asm_variable_list, &curr_index);
    asm_var flashBuffer_ptr(curr_rom.loc_gSaveDataBuffer, asm_variable_list, &curr_index);
    asm_var readFlashSector_ptr(curr_rom.loc_readFlashSector + READ_AS_THUMB, asm_variable_list, &curr_index);
    xse_var mainAsmStart(asm_variable_list, &curr_index);
    xse_var dexAsmStart(asm_variable_list, &curr_index);
    xse_var readFlashStart(asm_variable_list, &curr_index);

    xse_var jumpLoop(asm_variable_list, &curr_index);
    xse_var jumpBoxFull(asm_variable_list, &curr_index);
    xse_var jumpPkmnCollected(asm_variable_list, &curr_index);
    xse_var jumpAllCollected(asm_variable_list, &curr_index);

    textbox_var textGreet(asm_variable_list, &curr_index);
    textbox_var textReceived(asm_variable_list, &curr_index);
    textbox_var textPCFull(asm_variable_list, &curr_index);
    textbox_var textThank(asm_variable_list, &curr_index);
    textbox_var textTest(asm_variable_list, &curr_index);

    // Ş = Wait for button and scroll text
    // ȼ = Wait for button and clear text
    // Ȇ = Escape character
    // Ʋ = Variable escape sequence
    //      À = Player name
    // Ň = New line
    // ƞ = string terminator
    textGreet.set_text((curr_rom.text_region == TEXT_HOENN)
                           ? u"LANETTE: Hey ƲÀ!ȼPROFESSOR FENNEL told me that you’dŇbe coming by for these POKÉMON!"
                           : u"BILL: Hey ƲÀ!ȼPROFESSOR FENNEL told me that you’dŇbe coming by for these POKÉMON!");
    textThank.set_text(u"Thanks for helping out FENNEL!");
    textPCFull.set_text(u"The PC is full…ȼGo make some more room!");
    textReceived.set_text(u"ȆÀÁƲÀ’S POKÉMON were sent to theŇPC!");
    textTest.set_text(u"Testing...");

    // Located at 0x?8A8 in the .sav
    init_npc_location(curr_rom.map_bank, curr_rom.map_id, curr_rom.npc_id);      // Set the location of the NPC
    setvirtualaddress(VIRTUAL_ADDRESS);                                          // Set virtual address
    lock();                                                                      // Lock the player
    faceplayer();                                                                // Have the NPC face the player
    checkflag(curr_rom.all_collected_flag);                                      // Check if the "all collected" flag has been set
    virtualgotoif(COND_FLAGTRUE, jumpAllCollected.add_reference(2));             // If "all collected" is true, then jump to the "thank you" text
    virtualmsgbox(textGreet.add_reference(1));                                   // Otherwise, greet the player
    waitmsg();                                                                   // Wait for the message to finish
    waitkeypress();                                                              // Wait for the player to press A/B
    setvar(var_index, 0);                                                        // set the index to 0
    setvar(var_callASM, rev_endian(0x0023));                                     // set the call_asm variable to 0x23: 0x23 = CALL ASM
    setvar(var_pkmn_offset, 0);                                                  // Set the Pokemon struct offset to 0
    if (curr_rom.is_ruby_sapphire())                                             // Ruby and Sapphire don't shift their save blocks around, so we can hardcode it
    {                                                                            // FOR RUBY AND SAPPHIRE:
        setvar(var_script_ptr_low, curr_rom.loc_gSaveBlock1 & 0xFFFF);           // Copy the first two bytes of the saveblock1 location to a variable
        setvar(var_script_ptr_high, curr_rom.loc_gSaveBlock1 >> 16);             // Copy the second two bytes of the saveblock1 location to a variable
    }                                                                            //
    else                                                                         //
    {                                                                            // FOR FIRERED, LEAFGREEN, AND EMERALD
        copybyte(ptr_script_ptr_low, ptr_block_ptr_low);                         // Copy the first byte of the saveblock1ptr to a variable
        copybyte(ptr_script_ptr_low + 1, ptr_block_ptr_low + 1);                 // Copy the second byte of the saveblock1ptr to a variable
        copybyte(ptr_script_ptr_high, ptr_block_ptr_high);                       // Copy the third byte of the saveblock1ptr to a variable
        copybyte(ptr_script_ptr_high + 1, ptr_block_ptr_high + 1);               // Copy the fourth byte of the saveblock1ptr to a variable
    }                                                                            //
    addvar(var_script_ptr_low, curr_rom.offset_ramscript + 8 + READ_AS_THUMB);   // add the offset for ramscript, plus 8. 8 is for the 8 bytes of Checksum, padding and NPC info
    addvar(var_script_ptr_low, readFlashStart.add_reference(3));                 // Add the offset for the start of ASM
    setvar(var_call_return_1, rev_endian(0x0300));                               // Set the vairable to 0x03. 0x03 = RETURN
    setvar(var_call_check_flag, rev_endian(0x2B00));                             // Set the variable to 0x2B. 0x2B = CHECK FLAG
    addvar(var_call_check_flag, rev_endian(curr_rom.pkmn_collected_flag_start)); // Add the starting flag ID (plus one to ignore the is collected flag) to the check flag ASM variable
    setvar(var_call_return_2, rev_endian(0x0003));                               // Set the variable to 0x03. 0x03 = RETURN
    jumpLoop.set_start();                                                        // Set the jump destination for the JUMP_LOOP
    call(ptr_call_check_flag);                                                   // Call the check flag ASM
    virtualgotoif(COND_FLAGFALSE, jumpPkmnCollected.add_reference(2));           // If the "pokemon collected" flag is false, jump to the end of the loop

    call(ptr_callASM);                                                           // Call readFlash ASM
    addvar(var_script_ptr_low, mainAsmStart.add_reference(3, &readFlashStart));

    call(ptr_callASM);                                                       // Call SendMonToPC ASM
    compare(var_box_return, 2);                                              // Compare the resulting return to #2
    virtualgotoif(COND_EQUALS, jumpBoxFull.add_reference(2));                // If the return value was #2, jump to the box full message
    addvar(var_script_ptr_low, dexAsmStart.add_reference(3, &mainAsmStart)); // add to the CallASM offset so that it points to PTR_DEX_START instead
    setvar(var_dex_seen_caught, 2);                                          // set the seen caught variable to 2, so that the Pokemon is set to "seen"
    call(ptr_callASM);                                                       // call "PTR_DEX_START"
    addvar(var_dex_seen_caught, 1); // add 1 to the seen caught variable so that the Pokemon will be "Caught"
    call(ptr_callASM);                                                       // Call "PTR_DEX_START" again
    subvar(var_script_ptr_low, dexAsmStart.add_reference(3, &mainAsmStart)); // subtract from the CallASM offset so that it points to CALL_ASM again
    subvar(var_script_ptr_low, mainAsmStart.add_reference(3, &readFlashStart));
    jumpPkmnCollected.set_start();                           // Set the jump destination for if the Pokemon has already been collected
    addvar(var_pkmn_offset, POKEMON_SIZE);                   // Add the size of one Pokmeon to the Pokemon offset
    addvar(var_index, 1);                                    // Add one to the index
    addvar(var_call_check_flag, rev_endian(1));              // Add one to the flag index
    compare(var_index, MAX_PKMN_IN_BOX);                     // Compare the index to 30
    virtualgotoif(COND_LESSTHAN, jumpLoop.add_reference(2)); // if index is less than six, jump to the start of the loop
    setflag(curr_rom.all_collected_flag);                    // Set the "all collected" flag
    fanfare(0xA4);                                           // Play the received fanfare
    virtualmsgbox(textReceived.add_reference(1));            // Display the recieved text
    waitfanfare();                                           // Wait for the fanfare
    waitmsg();                                               // Wait for the text to finish
    waitkeypress();                                          // Wait for the player to press A/B
    jumpAllCollected.set_start();                            // Set the destination for if all the Pokemon have already been collected
    virtualmsgbox(textThank.add_reference(1));               // Display the thank test
    waitmsg();                                               // Wait for the message
    waitkeypress();                                          // Wait for the player to press A/B
    release();                                               // Release the player
    killscript();                                            // Erase RAMscript
    jumpBoxFull.set_start();                                 // Set the destination for if the box is full
    virtualmsgbox(textPCFull.add_reference(1));              // Display the full box message
    waitmsg();                                               // Wait for the message
    waitkeypress();                                          // Wait for the player to presse A/B
    release();                                               // Release the player
    end();                                                   // End the script

    textGreet.insert_text(mg_script);
    textThank.insert_text(mg_script);
    textPCFull.insert_text(mg_script);
    textReceived.insert_text(mg_script);
    textTest.insert_text(mg_script);
    four_align(); // Align the code so that it is byte aligned

    readFlashStart.set_start();
    push(rlist_lr); // save the load register to the stack
    mov1(r0, 30);   // set r0 to 30 (the sector ID for eReader data)
    ldr3(r1, flashBuffer_ptr.add_reference());
    ldr3(r2, readFlashSector_ptr.add_reference()); // set r2 to the location of "readFlashSector" plus one, since it is thumb code
    mov3(r3, r15);                                 // move r15 (the program counter) to r3
    add2(r3, 5);                                   // add 5 to r3 to compensate for the four following bytes, plus to tell the system to read as thumb code
    mov3(r14, r3);                                 // move r3 into r14 (the load register)
    bx(r2);                                        // jump to the pointer stored in r2 (readFlashSector)
    pop(rlist_r0);                                 // remove r0 from the stack and put it into r0
    bx(r0);
    //
    mainAsmStart.set_start();                      // Set the memory pointer location for ASM start
    push(rlist_lr);                                // save the load register to the stack
    ldr3(r3, curr_pkmn_index_ptr.add_reference()); // set r3 to the pointer to the pokemon index variable
    ldr1(r3, r3, 0);                               // set r3 to the value in memory r3 points to
    add5(r0, pkmnStruct.add_reference());          // set r0 to a pointer to the start of the Pokemon struct.
    ldr1(r0, r0, 0);
    add3(r0, r0, r3);                                   // add r3 to r0, giving it the correct offset for the current index
    ldr3(r1, sendMonToPC_ptr.add_reference());          // set r1 to the location of "SendMonToPC" plus one, since it is thumb code
    mov3(r2, r15);                                      // move r15 (the program counter) to r2
    add2(r2, 5);                                        // add 5 to r2 to compensate for the four following bytes, plus to tell the system to read as thumb code
    mov3(r14, r2);                                      // move r2 into r14 (the load register)
    bx(r1);                                             // jump to the pointer stored in r1 (SendMonToPC)
    ldr3(r2, returned_box_success_ptr.add_reference()); // load variable 0x8006's pointer into r2
    str1(r0, r2, 0);                                    // put the value of r0 into the memory location pointed at by r2, plus 0
    pop(rlist_r0);                                      // remove r0 from the stack and put it into r0
    bx(r0);                                             // jump to r0 (return to where the function was called)
                                                        //
    dexAsmStart.set_start();                            // Note the location where the Dex ASM starts
    push(rlist_lr);                                     // save the load register to the stack
    ldr3(r0, currPkmnIndex_ptr.add_reference());        // load the pointer to the index variable into r0
    ldr1(r0, r0, 0);                                    // load the value at r0's pointer
    mov1(r3, 0xFF);                                     // load 0xFF into r3
    and1(r0, r3);                                       // AND r0 and r3, which will give us just the least significant byte

    add5(r1, dexStruct.add_reference()); // set r1 to the value stored X bytes ahead
    ldr1(r1, r1, 0);
    add3(r0, r0, r1);                             // add r0 and r1, which is the current index and dex_struct respectivly
    ldr1(r0, r0, 0);                              // load the value at the memory location stored in r0
    and1(r0, r3);                                 // truncate to just the least significant byte, which is the current dex number
    ldr3(r1, dexSeenCaught_ptr.add_reference());  // load the dex_seen_caught variable's pointer into r1
    ldr1(r1, r1, 0);                              // load the value of memory pointed at by r1
    and1(r1, r3);                                 // AND r1 and r3, which will keep only the least significant byte
    ldr3(r2, setPokedexFlag_ptr.add_reference()); // load the GetSetPokedexFlag function location into r2
    mov3(r3, r15);                                // move r15 (the program counter) to r3
    add2(r3, 5);                                  // add 5 to r3 to compensate for the four following bytes, as well as to tell it to read as THUMB code
    mov3(r14, r3);                                // move r3 into r14 (the load register)
    bx(r2);                                       // jump to the pointer stored in r2 (GetSetPokedexFlag)
    pop(rlist_r0);                                // remove r0 from the stack and put it into r0
    bx(r0);                                       // jump to r0 (return to where the function was called)

    //
    //
    add_padding();                                   // add padding so that we are byte aligned again
    add_word(sendMonToPC_ptr.place_word());          // the location of "SendMonToPC", plus one (so it is interpreted as thumb code)
    add_word(returned_box_success_ptr.place_word()); // the location of variable "0x8006" (the return value)
    add_word(curr_pkmn_index_ptr.place_word());      // the location of variable "0x8008" (the pokemon offset)
    add_word(setPokedexFlag_ptr.place_word());       // the location of GetSetPokedexFlag, plus one (so it is interpreted as thumb code)
    add_word(dexSeenCaught_ptr.place_word());        // the location of the DEX_SEEN_CAUGHT variable
    add_word(currPkmnIndex_ptr.place_word());        // the location of the INDEX variable
    add_word(flashBuffer_ptr.place_word());
    add_word(readFlashSector_ptr.place_word());
    add_word(pkmnStruct.place_word());
    add_word(dexStruct.place_word());

    four_align(); // make the offset a multiple of 4

    for (unsigned int i = 0; i < asm_variable_list.size(); i++) // Fill all the refrences for script variables
    {
        asm_variable_list[i]->fill_refrences(mg_script);
    }

    if (curr_index > MG_SCRIPT_SIZE) // Throw an error if the script is too large
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

u32 mystery_gift_script::calc_checksum32()
{
    u16 i;
    u32 checksum = 0;

    for (i = 0; i < MG_SCRIPT_SIZE; i++)
    {
        checksum += mg_script[i];
    }

    return checksum;
}

u16 mystery_gift_script::calc_crc16() // Implementation taken from PokeEmerald Decomp
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
};

void mystery_gift_script::add_asm(u16 command)
{
    mg_script[curr_index] = command >> 0;
    mg_script[curr_index + 1] = command >> 8;
    curr_index += 2;
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

void mystery_gift_script::checkflag(u16 flag_id)
{
    value_buffer[0] = 0x2B;
    value_buffer[1] = flag_id >> 0;
    value_buffer[2] = flag_id >> 8;
    add_command(3);
}

void mystery_gift_script::virtualgotoif(u8 condition, u32 location)
{
    value_buffer[0] = 0xBB;
    value_buffer[1] = condition;
    value_buffer[2] = (VIRTUAL_ADDRESS >> 0) & 0xFF;
    value_buffer[3] = (VIRTUAL_ADDRESS >> 8) & 0xFF;
    value_buffer[4] = (VIRTUAL_ADDRESS >> 16) & 0xFF;
    value_buffer[5] = (VIRTUAL_ADDRESS >> 24) & 0xFF;
    add_command(6);
}

void mystery_gift_script::virtualmsgbox(u32 location)
{
    value_buffer[0] = 0xBD;
    value_buffer[1] = (VIRTUAL_ADDRESS >> 0) & 0xFF;
    value_buffer[2] = (VIRTUAL_ADDRESS >> 8) & 0xFF;
    value_buffer[3] = (VIRTUAL_ADDRESS >> 16) & 0xFF;
    value_buffer[4] = (VIRTUAL_ADDRESS >> 24) & 0xFF;
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

void mystery_gift_script::subvar(u16 var_id, u16 value)
{
    value_buffer[0] = 0x18;
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

void mystery_gift_script::special(u16 special_id)
{
    value_buffer[0] = 0x25;
    value_buffer[1] = special_id >> 0;
    value_buffer[2] = special_id >> 8;
    add_command(3);
}

void mystery_gift_script::callstd(u8 function_index)
{
    value_buffer[0] = 0x09;
    value_buffer[1] = function_index;
    add_command(2);
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

void mystery_gift_script::killscript()
{
    value_buffer[0] = 0x0D;
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
/**
 * @brief MOV (1) (Move) moves a large immediate value to a register.
 *
 * @param rd Is the destination register for the operation.
 * @param immed_8 Is an 8-bit immediate value, in the range 0 to 255, to move into <Rd>.
 */
void mystery_gift_script::mov1(u8 rd, u8 immed_8)
{
    add_asm(0b00100 << 11 | rd << 8 | immed_8);
}
/**
 * @brief AND (Logical AND) performs a bitwise AND of the values in two registers.
 *
 * @param rd Specifies the register containing the first operand, and is also the destination register.
 * @param rm Specifies the register containing the second operand.
 */
void mystery_gift_script::and1(u8 rd, u8 rm)
{
    add_asm(0b0100000000 << 6 | rm << 3 | rd);
}
/**
 * @brief LDR (2) loads 32-bit memory data into a general-purpose register. The addressing mode is useful for pointer+large offset arithmetic and for accessing a single element of an array.
 *
 * @param rd Is the destination register for the word loaded from memory.
 * @param rn Is the register containing the first value used in forming the memory address.
 * @param rm Is the register containing the second value used in forming the memory address.
 */
void mystery_gift_script::ldr2(u8 rd, u8 rn, u8 rm)
{
    add_asm(0b0101100 << 9 | rm << 6 | rm << 3 | rd);
}

void mystery_gift_script::add_word(u32 word)
{
    add_asm(word >> 0);
    add_asm(word >> 16);
}

void mystery_gift_script::four_align()
{
    //    while(curr_index % 4 != 0)
    for (int i = 0; i < curr_index % 4; i++)
    {
        mg_script[curr_index] = 0xAA;
        curr_index++;
        four_align_value++;
    }
}

void mystery_gift_script::add_padding()
{
    if (curr_index % 4 != 0)
    {
        add_asm(0x0000);
    }
}
