#include <tonc.h>
#include <vector>
#include "mystery_gift_builder.h"
#include "pokemon_party.h"
#include "pokemon_data.h"
#include "rom_data.h"

extern rom_data curr_rom;

// These are static variables
int var_call_check_flag = (VAR_ID_START + 0x04);
int var_call_return_2 = (VAR_ID_START + 0x05);
int var_box_return = (VAR_ID_START + 0x06);
int var_dex_seen_caught = (VAR_ID_START + 0x07);
int var_index = (VAR_ID_START + 0x09);
int var_pkmn_offset = (VAR_ID_START + 0x0A);

// These values will be defined once we recieve the ROM pointers
int ptr_call_check_flag;
int ptr_call_return_2;
int ptr_box_return;
int ptr_dex_seen_caught;
int ptr_index;
int ptr_pkmn_offset;

mystery_gift_script::mystery_gift_script()
{
    curr_mg_index = NPC_LOCATION_OFFSET;
    curr_section30_index = 0;

    ptr_call_check_flag = (curr_rom.loc_gSpecialVar_0x8000 + 0x08);
    ptr_call_return_2 = (curr_rom.loc_gSpecialVar_0x8000 + 0x0A);
    ptr_box_return = (curr_rom.loc_gSpecialVar_0x8000 + 0x0C);
    ptr_dex_seen_caught = (curr_rom.loc_gSpecialVar_0x8000 + 0x0E);
    ptr_index = (curr_rom.loc_gSpecialVar_0x8000 + 0x12);
    ptr_pkmn_offset = (curr_rom.loc_gSpecialVar_0x8000 + 0x14);
}

void mystery_gift_script::build_script(Pokemon_Party &incoming_box_data)
{
    std::vector<script_var *> mg_variable_list;
    std::vector<script_var *> sec30_variable_list;

    asm_var sendMonToPC_ptr(curr_rom.loc_sendMonToPC + READ_AS_THUMB, sec30_variable_list, &curr_section30_index);
    asm_var returned_box_success_ptr(ptr_box_return, sec30_variable_list, &curr_section30_index);
    asm_var curr_pkmn_index_ptr(ptr_pkmn_offset, sec30_variable_list, &curr_section30_index);
    asm_var setPokedexFlag_ptr(curr_rom.loc_setPokedexFlag + READ_AS_THUMB, sec30_variable_list, &curr_section30_index);
    asm_var dexSeenCaught_ptr(ptr_dex_seen_caught, sec30_variable_list, &curr_section30_index);
    asm_var currPkmnIndex_ptr(ptr_index, sec30_variable_list, &curr_section30_index);
    asm_var pkmnStruct(curr_rom.loc_gSaveDataBuffer, sec30_variable_list, &curr_section30_index);
    asm_var dexStruct(curr_rom.loc_gSaveDataBuffer + (MAX_PKMN_IN_BOX * POKEMON_SIZE), sec30_variable_list, &curr_section30_index);
    asm_var flashBuffer_ptr(curr_rom.loc_gSaveDataBuffer, sec30_variable_list, &curr_section30_index);
    asm_var readFlashSector_ptr(curr_rom.loc_readFlashSector + READ_AS_THUMB, sec30_variable_list, &curr_section30_index);
    asm_var m4aMPlayStop_ptr(0x081dd988 + READ_AS_THUMB, sec30_variable_list, &curr_section30_index);
    asm_var gMPlayInfo_BGM_ptr(0x03007300, sec30_variable_list, &curr_section30_index);
    asm_var gMPlayInfo_SE2_ptr(0x03007380, sec30_variable_list, &curr_section30_index);
    asm_var MPlayStart_ptr(0x081dd8a4 + READ_AS_THUMB, sec30_variable_list, &curr_section30_index);
    asm_var CreateFanfareTask_ptr(0x08071d00 + READ_AS_THUMB, sec30_variable_list, &curr_section30_index);
    asm_var sFanfareCounter_ptr(0x03000fc6, sec30_variable_list, &curr_section30_index);

    asm_var mainAsmStart(sec30_variable_list, &curr_section30_index);
    asm_var dexAsmStart(sec30_variable_list, &curr_section30_index);
    asm_var customSoundASM(sec30_variable_list, &curr_section30_index);

    xse_var jumpLoop(mg_variable_list, &curr_mg_index);
    xse_var jumpBoxFull(mg_variable_list, &curr_mg_index);
    xse_var jumpPkmnCollected(mg_variable_list, &curr_mg_index);
    xse_var jumpAllCollected(mg_variable_list, &curr_mg_index);

    textbox_var textGreet(sec30_variable_list, &curr_section30_index);
    textbox_var textReceived(sec30_variable_list, &curr_section30_index);
    textbox_var textPCFull(sec30_variable_list, &curr_section30_index);
    textbox_var textThank(sec30_variable_list, &curr_section30_index);
    textbox_var textTest(sec30_variable_list, &curr_section30_index);
    textbox_var textYouMustBe(sec30_variable_list, &curr_section30_index);
    textbox_var textIAm(sec30_variable_list, &curr_section30_index);
    textbox_var textWeHere(sec30_variable_list, &curr_section30_index);
    textbox_var textMoveBox(sec30_variable_list, &curr_section30_index);
    textbox_var textPCConvo(sec30_variable_list, &curr_section30_index);
    textbox_var textPCThanks(sec30_variable_list, &curr_section30_index);
    textbox_var textLookerFull(sec30_variable_list, &curr_section30_index);

    movement_var movementSlowSpin(sec30_variable_list, &curr_section30_index);
    movement_var movementFastSpin(sec30_variable_list, &curr_section30_index);
    movement_var movementExclaim(sec30_variable_list, &curr_section30_index);
    movement_var movementToBoxes(sec30_variable_list, &curr_section30_index);
    movement_var movementWalkBack(sec30_variable_list, &curr_section30_index);
    movement_var movementLookDown(sec30_variable_list, &curr_section30_index);

    sprite_var spriteLooker(sec30_variable_list, &curr_section30_index);

    music_var songLooker(sec30_variable_list, &curr_section30_index);

    // Ş = Wait for button and scroll text
    // ȼ = Wait for button and clear text
    // Ȇ = Escape character
    //      À = Change text color
    //          Ç = Red
    //          É = Green
    //          Ë = Blue
    // Ʋ = Variable escape sequence
    //      À = Player name
    // Ň = New line
    // ƞ = string terminator
    textGreet.set_text(u"I may not look like much now,Ňbut when I was younger…");
    textReceived.set_text(u"ȆÀÁƲÀ’S POKÉMON were sent to theŇPC!");
    textYouMustBe.set_text(u"Ah! You must be ƲÀ!ŇI was told you’d be coming.ȼOh! I still wear my disguise! Pardon!ŇOr, rather, let me introduce myself.");
    textIAm.set_text(u"ȆÀËI am a globe-trotting elite of theŇInternational Police.ȼMy name…ŞAh, no, I shall inform you of myŇcode name only.ȼMy code name, it is LOOKER.ŇIt is how I am called!");
    textWeHere.set_text(u"ȆÀËLOOKER: I am here in Kanto to findŇthe leader Giovanni.ȼHowever, in the meantime, I amŇhelping my friend Professor Jazmine.ȼThis is why you are here, no?ȼI shall contact her and tell herŇyou are ready.ŞCome! Allons y!");
    textMoveBox.set_text(u"ȆÀËOh, of course, I have to moveŇthe boxes. Silly me!");
    textPCConvo.set_text(u"ȆÀÉJAZ: Ah, LOOKER! Good to hear fromŇyou! I take it ƲÀ has arrived?ȼȆÀËLOOKER: Indeed! They’re here andŇready to receive their POKÉMON!ȼȆÀÉJAZ: Excellent! I’ll be sending themŇover momentarily… stand by!ȼDon’t worry ƲÀ,Ňyou won’t have to do a thing!");
    textPCThanks.set_text(u"ȆÀÉJAZ: It looks like everything wasŇsent to your PC successfully!ȼThanks again for your help ƲÀ!ŇSee you around, LOOKER!");
    textThank.set_text(u"ȆÀËThanks for stopping by, ƲÀ!ȼIf you’ll excuse me, I need toŇreturn to my disguise.ŞUntil our paths cross again!");
    textPCFull.set_text(u"ȆÀÉJAZ: Hm, it seems like the PC is full!ȼGo make some room, and I can sendŇover the rest of your POKÉMON.");
    textLookerFull.set_text(u"ȆÀËLOOKER: Speak to me again afterŇyou’ve made room, ƲÀ!ȼIn the meantime, I will return toŇmy disguise.");

    const int movementSlowSpinArray[16] = {
        MOVEMENT_ACTION_FACE_LEFT,
        MOVEMENT_ACTION_DELAY_8,
        MOVEMENT_ACTION_FACE_UP,
        MOVEMENT_ACTION_DELAY_8,
        MOVEMENT_ACTION_FACE_RIGHT,
        MOVEMENT_ACTION_DELAY_8,
        MOVEMENT_ACTION_FACE_DOWN,
        MOVEMENT_ACTION_DELAY_8,
        MOVEMENT_ACTION_FACE_LEFT,
        MOVEMENT_ACTION_DELAY_8,
        MOVEMENT_ACTION_FACE_UP,
        MOVEMENT_ACTION_DELAY_8,
        MOVEMENT_ACTION_FACE_RIGHT,
        MOVEMENT_ACTION_DELAY_8,
        MOVEMENT_ACTION_FACE_DOWN,
        MOVEMENT_ACTION_DELAY_8,
    };
    movementSlowSpin.set_movement(movementSlowSpinArray, 16);

    const int movementFastSpinArray[30] = {
        MOVEMENT_ACTION_FACE_LEFT,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_UP,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_RIGHT,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_DOWN,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_LEFT,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_UP,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_RIGHT,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_DOWN,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_LEFT,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_UP,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_RIGHT,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_DOWN,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_LEFT,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_UP,
        MOVEMENT_ACTION_DELAY_4,
        MOVEMENT_ACTION_FACE_RIGHT,
        MOVEMENT_ACTION_DELAY_4,
    };
    movementFastSpin.set_movement(movementFastSpinArray, 30);

    const int movementExclaimArray[1] = {MOVEMENT_ACTION_EMOTE_EXCLAMATION_MARK};
    movementExclaim.set_movement(movementExclaimArray, 1);

    const int movementToBoxesArray[3] = {MOVEMENT_ACTION_WALK_FAST_UP, MOVEMENT_ACTION_WALK_FAST_UP, MOVEMENT_ACTION_EMOTE_EXCLAMATION_MARK};
    movementToBoxes.set_movement(movementToBoxesArray, 3);

    const int movementWalkBackArray[2] = {MOVEMENT_ACTION_WALK_FAST_DOWN, MOVEMENT_ACTION_WALK_FAST_DOWN};
    movementWalkBack.set_movement(movementWalkBackArray, 2);

    const int movementLookDownArray[1] = {MOVEMENT_ACTION_FACE_DOWN};
    movementLookDown.set_movement(movementLookDownArray, 1);

    //                                      v Instrument
    songLooker.add_track({0xBC, 0x00, 0xBB, 0x38, 0xBD, 0x38, 0xBE, 0x64, 0xBF, 0x30, 0xD4, 0x37, 0x64, 0x86, 0x3C, 0x86, 0x40, 0x86, 0x43, 0x86, 0x48, 0x86, 0x4C, 0x86, 0xE0, 0x4F, 0x92, 0x4C, 0x92, 0xD4, 0x38, 0x86, 0x3C, 0x86, 0x3F, 0x86, 0x44, 0x86, 0x48, 0x86, 0x4B, 0x86, 0xE0, 0x50, 0x92, 0x4B, 0x92, 0xD4, 0x3A, 0x86, 0x3E, 0x86, 0x41, 0x86, 0x46, 0x86, 0x4A, 0x86, 0x4D, 0x86, 0xE0, 0x52, 0x8C, 0x86, 0xD4, 0x86, 0xD4, 0x86, 0xD4, 0x86, 0xF2, 0x54, 0xA8, 0xAF, 0x83, 0xB1});
    songLooker.add_track({0xBC, 0x00, 0xBD, 0x3C, 0xBE, 0x5A, 0xBF, 0x50, 0x92, 0xD4, 0x24, 0x64, 0x86, 0x28, 0x86, 0x2B, 0x86, 0xE0, 0x28, 0x92, 0x24, 0x9C, 0xD4, 0x86, 0x27, 0x86, 0x2C, 0x86, 0xE0, 0x27, 0x92, 0x24, 0x9C, 0xD4, 0x26, 0x86, 0x29, 0x86, 0x2E, 0x86, 0xE0, 0x35, 0x8C, 0x86, 0xD4, 0x32, 0x86, 0xD4, 0x86, 0xD4, 0x86, 0xF0, 0x30, 0xA8, 0xAF, 0x83, 0xB1});
    songLooker.add_track({0xBC, 0x00, 0xBD, 0x40, 0xBE, 0x5A, 0xBF, 0x61, 0xD4, 0x28, 0x64, 0x86, 0x2B, 0x86, 0x30, 0x86, 0x34, 0x86, 0x37, 0x86, 0x3C, 0x86, 0xE0, 0x40, 0x93, 0x3C, 0x58, 0x91, 0xD4, 0x27, 0x64, 0x86, 0x2C, 0x86, 0x30, 0x86, 0x33, 0x86, 0x38, 0x86, 0x3C, 0x86, 0xE0, 0x3F, 0x92, 0x3C, 0x92, 0xD4, 0x29, 0x86, 0x2E, 0x86, 0x32, 0x86, 0x35, 0x86, 0x3A, 0x86, 0x3E, 0x86, 0xDA, 0x41, 0x8C, 0x86, 0xD4, 0x86, 0xD4, 0x86, 0xD4, 0x86, 0xF2, 0x40, 0xA8, 0xAF, 0x83, 0xB1});
    songLooker.add_track({0xBC, 0x00, 0xBD, 0x40, 0xBE, 0x5A, 0xBF, 0x20, 0x86, 0xD4, 0x28, 0x64, 0x86, 0x2B, 0x86, 0x30, 0x86, 0x34, 0x86, 0x37, 0x86, 0xE0, 0x3C, 0x92, 0x3C, 0x58, 0x98, 0xD4, 0x27, 0x64, 0x86, 0x2C, 0x86, 0x30, 0x86, 0x33, 0x86, 0x38, 0x86, 0xE0, 0x3C, 0x92, 0x38, 0x98, 0xD4, 0x29, 0x86, 0x2E, 0x86, 0x32, 0x86, 0x35, 0x86, 0x3A, 0x86, 0xE0, 0x3E, 0x8C, 0x86, 0xE0, 0x92, 0xF2, 0x3C, 0xA8, 0xAF, 0x83, 0xB1});
    songLooker.add_track({0xBC, 0x00, 0xBD, 0x40, 0xBE, 0x5A, 0xBF, 0x40, 0xD4, 0x2B, 0x64, 0x86, 0x30, 0x86, 0x34, 0x86, 0x37, 0x86, 0x3C, 0x86, 0x40, 0x86, 0xE0, 0x43, 0x92, 0x40, 0x92, 0xD4, 0x2C, 0x86, 0x30, 0x86, 0x33, 0x86, 0x38, 0x86, 0x3C, 0x86, 0x3F, 0x86, 0xE0, 0x44, 0x92, 0x3F, 0x92, 0xD4, 0x2E, 0x86, 0x32, 0x86, 0x35, 0x86, 0x3A, 0x86, 0x3E, 0x86, 0x41, 0x86, 0xE0, 0x46, 0x8C, 0x86, 0xD4, 0x86, 0xD4, 0x86, 0xD4, 0x86, 0xF2, 0x48, 0xA8, 0xAF, 0x83, 0xB1, 0xD7, 0x6B});



    int dex_nums[MAX_PKMN_IN_BOX] = {};

    for (int i = 0; i < MAX_PKMN_IN_BOX; i++) // Add in the Pokemon data
    {
        Pokemon curr_pkmn = incoming_box_data.get_converted_pkmn(i);
        if (curr_pkmn.get_validity())
        {
            for (int curr_byte = 0; curr_byte < POKEMON_SIZE; curr_byte++)
            {
                save_section_30[curr_section30_index] = curr_pkmn.get_gen_3_data(curr_byte);
                curr_section30_index++;
            }
            dex_nums[i] = curr_pkmn.get_dex_number();
        }
        else
        {
            curr_section30_index += POKEMON_SIZE;
        }
    }

    for (int i = 0; i < MAX_PKMN_IN_BOX; i++) // Add in the dex numbers
    {
        save_section_30[curr_section30_index] = dex_nums[i];
        curr_section30_index++;
    }

    // insert text
    textThank.insert_text(save_section_30);
    textYouMustBe.insert_text(save_section_30);
    // textPCFull.insert_text(save_section_30);
    textReceived.insert_text(save_section_30);
    textGreet.insert_text(save_section_30);
    textIAm.insert_text(save_section_30);
    textWeHere.insert_text(save_section_30);
    //textMoveBox.insert_text(save_section_30);
    //textPCConvo.insert_text(save_section_30);
    //textPCThanks.insert_text(save_section_30);
    // textLookerFull.insert_text(save_section_30);

    movementSlowSpin.insert_movement(save_section_30);
    movementFastSpin.insert_movement(save_section_30);
    movementExclaim.insert_movement(save_section_30);
    movementToBoxes.insert_movement(save_section_30);
    movementWalkBack.insert_movement(save_section_30);
    movementLookDown.insert_movement(save_section_30);

    while (curr_section30_index % 4 != 0)
    {
        curr_section30_index++; // Align the code so that it is byte aligned
    }

    songLooker.insert_music_data(save_section_30, 0, 0, 0, 0x084950ec);

    asm_var customSong(songLooker.get_loc_in_sec30(), sec30_variable_list, &curr_section30_index);
    asm_var customSongDuration(388, sec30_variable_list, &curr_section30_index);



    while (curr_section30_index % 4 != 0)
    {
        curr_section30_index++; // Align the code so that it is byte aligned
    }

#include "mario.h"
    spriteLooker.insert_sprite_data(save_section_30, marioTiles, 256);

    mainAsmStart.set_start();                           // Set the memory pointer location for ASM start
    push(rlist_lr);                                     // save the load register to the stack
    ldr3(r3, curr_pkmn_index_ptr.add_reference());      // set r3 to the pointer to the pokemon index variable
    ldr1(r3, r3, 0);                                    // set r3 to the value in memory r3 points to
    add5(r0, pkmnStruct.add_reference());               // set r0 to a pointer to the start of the Pokemon struct.
    ldr1(r0, r0, 0);                                    // set r0 to the value in memory r0 points to
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
    while (curr_section30_index % 4 != 0)
    {
        curr_section30_index++; // Align the code so that it is byte aligned
    }

    add_word(curr_pkmn_index_ptr.place_word());      // the location of variable "0x8008" (the pokemon offset)
    add_word(pkmnStruct.place_word());               // the location of the Pokemon Struct
    add_word(sendMonToPC_ptr.place_word());          // the location of "SendMonToPC", plus one (so it is interpreted as thumb code)
    add_word(returned_box_success_ptr.place_word()); // the location of variable "0x8006" (the return value)

    dexAsmStart.set_start();                      // Note the location where the Dex ASM starts
    push(rlist_lr);                               // save the load register to the stack
    ldr3(r0, currPkmnIndex_ptr.add_reference());  // load the pointer to the index variable into r0
    ldr1(r0, r0, 0);                              // load the value at r0's pointer
    mov1(r3, 0xFF);                               // load 0xFF into r3
    and1(r0, r3);                                 // AND r0 and r3, which will give us just the least significant byte
    add5(r1, dexStruct.add_reference());          // set r1 to the value stored X bytes ahead
    ldr1(r1, r1, 0);                              // loda the value at the memory location stored in r1
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
    while (curr_section30_index % 4 != 0)
    {
        curr_section30_index++; // Align the code so that it is byte aligned
    }
    add_word(currPkmnIndex_ptr.place_word());  // the location of the INDEX variable
    add_word(dexStruct.place_word());          // the location of the dex struct
    add_word(dexSeenCaught_ptr.place_word());  // the location of the DEX_SEEN_CAUGHT variable
    add_word(setPokedexFlag_ptr.place_word()); // the location of GetSetPokedexFlag, plus one (so it is interpreted as thumb code)

    customSoundASM.set_start(); // Note the location where the custom sound ASM starts
    push(rlist_lr);             // save the load register to the stack

    ldr3(r0, gMPlayInfo_BGM_ptr.add_reference()); // load the gMPlayInfo_BGM function location into r0
    ldr3(r2, m4aMPlayStop_ptr.add_reference());   // load the m4aMPlayStop location into r2
    mov3(r3, r15);                                // move r15 (the program counter) to r3
    add2(r3, 5);                                  // add 5 to r3 to compensate for the four following bytes, as well as to tell it to read as THUMB code
    mov3(r14, r3);                                // move r3 into r14 (the load register)
    bx(r2);                                       // jump to the pointer stored in r2 (m4aMPlayStop)

    ldr3(r0, sFanfareCounter_ptr.add_reference()); // load the sFanfareCounter_ptr function location into r0
    ldr3(r1, customSongDuration.add_reference());  // load the custom song duration into r1
    strh(r1, r0, 0);                               // Load the value into memory

    ldr3(r0, gMPlayInfo_SE2_ptr.add_reference()); // load the gMPlayInfo_SE2 function location into r0
    ldr3(r1, customSong.add_reference());         // load the custom song location into r1
    ldr3(r2, MPlayStart_ptr.add_reference());     // load the m4aMPlayStop location into r2
    mov3(r3, r15);                                // move r15 (the program counter) to r3
    add2(r3, 5);                                  // add 5 to r3 to compensate for the four following bytes, as well as to tell it to read as THUMB code
    mov3(r14, r3);                                // move r3 into r14 (the load register)
    bx(r2);                                       // jump to the pointer stored in r2 (MPlayStart)

    ldr3(r2, CreateFanfareTask_ptr.add_reference()); // load the m4aMPlayStop location into r2
    mov3(r3, r15);                                   // move r15 (the program counter) to r3
    add2(r3, 5);                                     // add 5 to r3 to compensate for the four following bytes, as well as to tell it to read as THUMB code
    mov3(r14, r3);                                   // move r3 into r14 (the load register)
    bx(r2);                                          // jump to the pointer stored in r2 (MPlayStart)

    pop(rlist_r0); // remove r0 from the stack and put it into r0
    bx(r0);        // jump to r0 (return to where the function was called)
    while (curr_section30_index % 4 != 0)
    {
        curr_section30_index++; // Align the code so that it is byte aligned
    }
    add_word(m4aMPlayStop_ptr.place_word());   // the location of the INDEX variable
    add_word(gMPlayInfo_BGM_ptr.place_word()); // the location of the dex struct
    add_word(gMPlayInfo_SE2_ptr.place_word());
    add_word(MPlayStart_ptr.place_word());
    add_word(CreateFanfareTask_ptr.place_word());
    add_word(sFanfareCounter_ptr.place_word());
    add_word(customSong.place_word());
    add_word(customSongDuration.place_word());

    // The start of the Mystery Gift Script

    // Located at 0x?8A8 in the .sav
    init_npc_location(curr_rom.map_bank, curr_rom.map_id, curr_rom.npc_id); // Set the location of the NPC
    setvirtualaddress(VIRTUAL_ADDRESS);                                     // Set virtual address
    callASM(curr_rom.loc_loadSaveSection30 + READ_AS_THUMB);                // Load save section 30 into saveDataBuffer
    lock();                                                                 // Lock the player
    faceplayer();                                                           // Have the NPC face the player
    msgboxMacro(textGreet.get_loc_in_sec30());                              // Start the dialouge
    applymovement(curr_rom.npc_id, movementExclaim.get_loc_in_sec30());
    playse(0x15);
    waitse();
    waitmovement(curr_rom.npc_id);
    msgboxMacro(textYouMustBe.get_loc_in_sec30());
    applymovement(curr_rom.npc_id, movementSlowSpin.get_loc_in_sec30());
    waitmovement(curr_rom.npc_id);
    applymovement(curr_rom.npc_id, movementFastSpin.get_loc_in_sec30());
    waitmovement(curr_rom.npc_id);
    changeSpriteMacro(1, spriteLooker.get_loc_in_sec30());
    copyPaletteMacro(0xA, marioPal);
    changePaletteMacro(curr_rom.npc_id, 0xA);
    applymovement(curr_rom.npc_id, movementLookDown.get_loc_in_sec30());
    callASM(customSoundASM.get_loc_in_sec30());
    waitfanfare();
    msgboxMacro(textIAm.get_loc_in_sec30());
    changeSpriteMacro(1, 0x083a0b08);
    changePaletteMacro(curr_rom.npc_id, 0x3);
    applymovement(curr_rom.npc_id, movementFastSpin.get_loc_in_sec30());
    waitmovement(curr_rom.npc_id);
    applymovement(curr_rom.npc_id, movementSlowSpin.get_loc_in_sec30());
    waitmovement(curr_rom.npc_id);
    faceplayer();
    msgboxMacro(textWeHere.get_loc_in_sec30());
    applymovement(curr_rom.npc_id, movementToBoxes.get_loc_in_sec30());
    waitmovement(curr_rom.npc_id);
    playse(0x15);
    waitse();
    msgboxMacro(textMoveBox.get_loc_in_sec30());
    fadeScreen(1);
    // Place the PC
    setMetaTile(4, 1, 98, 0);
    // Place the boxes
    setMetaTile(2, 1, 385, 1);
    setMetaTile(2, 2, 386, 0);
    special(0x8E);
    playse(0xC);
    waitse();
    fadeScreen(0);
    setMetaTile(4, 1, 99, 0);
    special(0x8E);
    playse(0x2);
    waitse();
    msgboxMacro(textPCConvo.get_loc_in_sec30());

    // -- POKEMON INJECTION START--
    setvar(var_index, 0);                                                        // set the index to 0
    setvar(var_pkmn_offset, 0);                                                  // Set the Pokemon struct offset to 0
    setvar(var_call_check_flag, rev_endian(0x2B00));                             // Set the variable to 0x2B. 0x2B = CHECK FLAG
    addvar(var_call_check_flag, rev_endian(curr_rom.pkmn_collected_flag_start)); // Add the starting flag ID (plus one to ignore the is collected flag) to the check flag ASM variable
    setvar(var_call_return_2, rev_endian(0x0003));                               // Set the variable to 0x03. 0x03 = RETURN
    jumpLoop.set_start();                                                        // Set the jump destination for the JUMP_LOOP
    call(ptr_call_check_flag);                                                   // Call the check flag ASM
    virtualgotoif(COND_FLAGFALSE, jumpPkmnCollected.add_reference(2));           // If the "pokemon collected" flag is false, jump to the end of the loop
    callASM(mainAsmStart.get_loc_in_sec30());                                    // Call SendMonToPC ASM
    compare(var_box_return, 2);                                                  // Compare the resulting return to #2
    virtualgotoif(COND_EQUALS, jumpBoxFull.add_reference(2));                    // If the return value was #2, jump to the box full message
    setvar(var_dex_seen_caught, 2);                                              // set the seen caught variable to 2, so that the Pokemon is set to "seen"
    callASM(dexAsmStart.get_loc_in_sec30());                                     // call "PTR_DEX_START"
    addvar(var_dex_seen_caught, 1);                                              // add 1 to the seen caught variable so that the Pokemon will be "Caught"
    callASM(dexAsmStart.get_loc_in_sec30());                                     // Call "PTR_DEX_START" again
    jumpPkmnCollected.set_start();                                               // Set the jump destination for if the Pokemon has already been collected
    addvar(var_pkmn_offset, POKEMON_SIZE);                                       // Add the size of one Pokmeon to the Pokemon offset
    addvar(var_index, 1);                                                        // Add one to the index
    addvar(var_call_check_flag, rev_endian(1));                                  // Add one to the flag index
    compare(var_index, MAX_PKMN_IN_BOX);                                         // Compare the index to 30
    virtualgotoif(COND_LESSTHAN, jumpLoop.add_reference(2));                     // if index is less than six, jump to the start of the loop
    setflag(curr_rom.all_collected_flag);                                        // Set the "all collected" flag
    fanfare(0x100);                                                              // Play the received fanfare
    msgboxMacro(textReceived.get_loc_in_sec30());                                // Display the recieved text
    waitfanfare();                                                               // Wait for the fanfare

    // -- POKEMON INJECTION END --
    jumpAllCollected.set_start();                 // Set the destination for if all the Pokemon have already been collected
    msgboxMacro(textPCThanks.get_loc_in_sec30()); // Display the thank text
    setMetaTile(4, 1, 98, 0);
    special(0x8E);
    playse(0x3);
    waitse();
    fadeScreen(1);
    // Place the PC
    setMetaTile(4, 1, 385, 1);
    // Place the boxes
    setMetaTile(2, 1, 272, 1);
    setMetaTile(2, 2, 273, 0);
    special(0x8E);
    playse(0xC);
    waitse();
    fadeScreen(0);
    applymovement(curr_rom.npc_id, movementWalkBack.get_loc_in_sec30());
    waitmovement(curr_rom.npc_id);
    faceplayer();
    msgboxMacro(textThank.get_loc_in_sec30());
    release();    // Release the player
    killscript(); // Erase RAMscript

    // -- BOX IS FULL TEXT --
    jumpBoxFull.set_start();                    // Set the destination for if the box is full
    msgboxMacro(textPCFull.get_loc_in_sec30()); // Display the thank text
    setMetaTile(4, 1, 98, 0);
    special(0x8E);
    playse(0x3);
    waitse();
    fadeScreen(1);
    // Place the PC
    setMetaTile(4, 1, 385, 1);
    // Place the boxes
    setMetaTile(2, 1, 272, 1);
    setMetaTile(2, 2, 273, 0);
    special(0x8E);
    playse(0xC);
    waitse();
    fadeScreen(0);
    applymovement(curr_rom.npc_id, movementWalkBack.get_loc_in_sec30());
    waitmovement(curr_rom.npc_id);
    faceplayer();
    msgboxMacro(textLookerFull.get_loc_in_sec30());
    release(); // Release the player
    end();     // End the script

    for (unsigned int i = 0; i < mg_variable_list.size(); i++) // Fill all the refrences for script variables in the mg
    {
        mg_variable_list[i]->fill_refrences(mg_script);
    }

    for (unsigned int i = 0; i < sec30_variable_list.size(); i++) // Fill all the refrences for script variables in save section 30
    {
        sec30_variable_list[i]->fill_refrences(save_section_30);
    }

    if (curr_mg_index > MG_SCRIPT_SIZE) // Throw an error if the script is too large
    {
        tte_erase_screen();
        int val = (curr_mg_index - MG_SCRIPT_SIZE) - four_align_value;
        tte_write("MG Script exceeded by ");
        tte_write(std::to_string(val).c_str());
        tte_write(" bytes");
        while (true)
        {
        }
    }

    if (curr_section30_index > 0x4096) // Throw an error if the script is too large
    {
        tte_erase_screen();
        int val = (curr_section30_index - 0x4096) - four_align_value;
        tte_write("S30 Script exceeded by ");
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

u8 mystery_gift_script::get_section30_value_at(int i)
{
    return save_section_30[i];
}

u16 mystery_gift_script::rev_endian(u16 num)
{
    return ((num & 0xFF) << 8) | (num >> 8);
}

void mystery_gift_script::add_command(int len)
{
    for (int i = 0; i < len; i++)
    {
        mg_script[curr_mg_index] = value_buffer[i];
        curr_mg_index++;
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
    save_section_30[curr_section30_index] = command >> 0;
    save_section_30[curr_section30_index + 1] = command >> 8;
    curr_section30_index += 2;
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

void mystery_gift_script::loadpointer(u8 destinationBank, u32 value)
{
    value_buffer[0] = 0x0F;
    value_buffer[1] = destinationBank;
    value_buffer[2] = value >> 0;
    value_buffer[3] = value >> 8;
    value_buffer[4] = value >> 16;
    value_buffer[5] = value >> 24;
    add_command(6);
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

void mystery_gift_script::spritebehave(u16 objectID, u8 behaviorType)
{
    value_buffer[0] = 0x65;
    value_buffer[1] = objectID >> 0;
    value_buffer[2] = objectID >> 8;
    value_buffer[3] = behaviorType;
    add_command(4);
}

void mystery_gift_script::spriteface(u16 npc, u8 direction)
{
    value_buffer[0] = 0x5B;
    value_buffer[1] = npc >> 0;
    value_buffer[2] = npc >> 8;
    value_buffer[3] = direction;
    add_command(4);
}

void mystery_gift_script::waitmovement(u16 npc)
{
    value_buffer[0] = 0x51;
    value_buffer[1] = npc >> 0;
    value_buffer[2] = npc >> 8;
    add_command(3);
}

void mystery_gift_script::doanimation(u16 animation)
{
    value_buffer[0] = 0x9C;
    value_buffer[1] = animation >> 0;
    value_buffer[2] = animation >> 8;
    add_command(3);
}

void mystery_gift_script::applymovement(u16 npc, u32 movements)
{
    value_buffer[0] = 0x4F;
    value_buffer[1] = npc >> 0;
    value_buffer[2] = npc >> 8;
    value_buffer[3] = movements >> 0;
    value_buffer[4] = movements >> 8;
    value_buffer[5] = movements >> 16;
    value_buffer[6] = movements >> 24;
    add_command(7);
}

void mystery_gift_script::callASM(u32 script_ptr)
{
    value_buffer[0] = 0x23;
    value_buffer[1] = script_ptr >> 0;
    value_buffer[2] = script_ptr >> 8;
    value_buffer[3] = script_ptr >> 16;
    value_buffer[4] = script_ptr >> 24;
    add_command(5);
}

void mystery_gift_script::setMapLayoutIndex(u16 footer)
{
    value_buffer[0] = 0xA7;
    value_buffer[1] = footer >> 0;
    value_buffer[2] = footer >> 8;
    add_command(3);
}

void mystery_gift_script::fadeScreen(u8 effect)
{
    value_buffer[0] = 0x97;
    value_buffer[1] = effect >> 0;
    add_command(2);
}

void mystery_gift_script::setMetaTile(u16 x, u16 y, u16 metaTileId, u16 impassible)
{
    value_buffer[0] = 0xA2;
    value_buffer[1] = x >> 0;
    value_buffer[2] = x >> 8;
    value_buffer[3] = y >> 0;
    value_buffer[4] = y >> 8;
    value_buffer[5] = metaTileId >> 0;
    value_buffer[6] = metaTileId >> 8;
    value_buffer[7] = impassible >> 0;
    value_buffer[8] = impassible >> 8;
    add_command(9);
}

void mystery_gift_script::playse(u16 soundId)
{
    value_buffer[0] = 0x2F;
    value_buffer[1] = soundId >> 0;
    value_buffer[2] = soundId >> 8;
    add_command(3);
}

void mystery_gift_script::waitse()
{
    value_buffer[0] = 0x30;
    add_command(1);
}

void mystery_gift_script::writebytetooffset(u8 byte, u32 offset)
{
    value_buffer[0] = 0x11;
    value_buffer[1] = byte;
    value_buffer[2] = offset >> 0;
    value_buffer[3] = offset >> 8;
    value_buffer[4] = offset >> 16;
    value_buffer[5] = offset >> 24;
    add_command(6);
}

void mystery_gift_script::init_npc_location(u8 bank, u8 map, u8 npc)
{
    mg_script[0] = 0x33; // File ID?
    mg_script[1] = bank;
    mg_script[2] = map;
    mg_script[3] = npc;
}

void mystery_gift_script::msgboxMacro(u32 location)
{
    loadpointer(0, location);
    callstd(4);
}

void mystery_gift_script::changeSpriteMacro(u8 npcId, u32 spriteTablePtr)
{
    writebytetooffset(spriteTablePtr >> 0, 0x0202063c + (0x44 * npcId) + 0xC + 0);
    writebytetooffset(spriteTablePtr >> 8, 0x0202063c + (0x44 * npcId) + 0xC + 1);
    writebytetooffset(spriteTablePtr >> 16, 0x0202063c + (0x44 * npcId) + 0xC + 2);
    writebytetooffset(spriteTablePtr >> 24, 0x0202063c + (0x44 * npcId) + 0xC + 3);
}

void mystery_gift_script::copyPaletteMacro(u8 palNum, const unsigned short palette_array[])
{
    for (int i = 0; i < 32; i++)
    {
        writebytetooffset(palette_array[i / 2] >> (8 * (i % 2)), 0x020375f8 + 0x200 + (32 * palNum) + i);
    }
}

void mystery_gift_script::changePaletteMacro(u8 npcId, u8 palNum)
{
    writebytetooffset((palNum << 4) | 0x08, 0x0202063c + (0x44 * npcId) + 0x5);
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
/**
 * @brief STRH (1) (Store Register Halfword) stores 16-bit data from a general-purpose register to memory. The addressing mode is useful for accessing structure (record) fields. With an offset of zero, the address produced is the unaltered value of the base register <Rn>.
 *
 * @param rd Is the register whose least significant halfword is stored to memory.
 * @param rn Is the register containing the base address for the instruction.
 * @param immed_5 Is a 5-bit immediate value that is multiplied by two and added to the value of <Rn> to form the memory address.
 */
void mystery_gift_script::strh(u8 rd, u8 rn, u8 immed_5)
{
    add_asm(0b10000 << 11 | (immed_5 & 0b11111) << 6 | rn << 3 | rd);
}
void mystery_gift_script::add_word(u32 word)
{
    add_asm(word >> 0);
    add_asm(word >> 16);
}

void mystery_gift_script::four_align()
{
    //    while(curr_index % 4 != 0)
    for (int i = 0; i < curr_mg_index % 4; i++)
    {
        mg_script[curr_mg_index] = 0xAA;
        curr_mg_index++;
        four_align_value++;
    }
}

void mystery_gift_script::add_padding()
{
    if (curr_mg_index % 4 != 0)
    {
        add_asm(0x0000);
    }
}
