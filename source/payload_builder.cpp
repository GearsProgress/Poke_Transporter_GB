#include "payload_builder.h"
#include "gb_rom_values/base_gb_rom_struct.h"
#include "gb_rom_values/eng_gb_rom_values.h"
#include "debug_mode.h"
#include "z80_asm.h"

#include <iostream>
#include <fstream>
#include <iomanip>

#define DATA_LOC (SHOW_DATA_PACKETS ? curr_rom.transferStringLocation : curr_rom.wEnemyMonSpecies)
#define PACKET_SIZE (1 + 8 + 1 + 1 + 2) // 0xFD, 8 data bytes, the checksum, the flag bytes, and two location bytes

byte out_array[PAYLOAD_SIZE] = {};

byte *generate_payload(GB_ROM curr_rom, int type, bool debug)
{
    /*  10 RNG bytes
        8 Preamble bytes
        418 / 441 Party bytes
        7 Preamble bytes
        194 Patch list bytes (last 2 are unused)

        637 / 660 total bytes
        */

    if ((curr_rom.generation == 1 && curr_rom.method == METHOD_NEWLINE))
    {
        std::vector<z80_jump *> jump_vector;
        std::vector<z80_variable *> var_vector;

        z80_asm_handler z80_rng_seed(0x0A, curr_rom.wSerialOtherGameboyRandomNumberListBlock + 8);
        z80_asm_handler z80_payload(0x1AA, curr_rom.wSerialEnemyDataBlock);
        z80_asm_handler z80_patchlist(0xEC, curr_rom.wSerialEnemyMonsPatchList);

        z80_jump asm_start(&jump_vector);
        z80_jump save_box(&jump_vector);
        z80_jump remove_array_loop(&jump_vector);
        z80_jump packet_loop(&jump_vector);
        z80_jump fe_bypass(&jump_vector);
        z80_jump send_packet_loop(&jump_vector);

        z80_variable array_counter(&var_vector, 1, 0x00); // 1 byte to store the current array counter
        z80_variable removal_array(&var_vector);          // 40 byte storage for list of Pokemon to remove, plus a permanent array terminator

        byte removal_array_data[41];
        for (int i = 0; i < 41; i++)
        {
            if (debug)
            {
                removal_array_data[i] = (i < 30 ? (29 - i) : 0xFF);
            }
            else
            {
                removal_array_data[i] = (i < 30 ? 0xFD : 0xFF);
            }
        }
        removal_array.load_data(41, removal_array_data);
        z80_variable transfer_wait_string(&var_vector, 13, // SENDING DATA
                                          0x92, 0x84, 0x8D, 0x83, 0x88, 0x8D, 0x86, 0x7F, 0x83, 0x80, 0x93, 0x80, 0x50);
        z80_variable custom_name(&var_vector, 11, // FENNEL
                                 0x85, 0x84, 0x8D, 0x8D, 0x84, 0x8B, 0x50, 0x50, 0x50, 0x50, 0x50);

        // RNG Seed
        // Location of the entrance vector
        z80_rng_seed.index = 5; // Set the entrance vector
        z80_rng_seed.JP(asm_start.place_direct_jump(&z80_rng_seed) | T_U16);

        // Preamble
        // At 0x00, 0x07 in length
        // Must be filled with 0xFD
        for (int i = 0; i < 7; i++)
        {
            z80_payload.add_byte(0xFD);
        }

        // Rival name
        // At 0x07, 0x0B in length
        // Set to stored name
        z80_payload.index = 0x07;
        custom_name.insert_variable(&z80_payload);

        // Number of Pokemon
        // At 0x12, 0x01 in length
        // Does not need to be set
        z80_payload.index = 0x12;
        z80_payload.add_byte(0x06);

        // Pokemon list
        // At 0x13, can be up to 0x1A2 / 0x1B9 bytes in length.
        // Calculate the number of Pokemon names that need to be printed,
        // and add them to the list. Then terminate the list.
        z80_payload.index = 0x13;
        int distance = curr_rom.stack_overwrite_location - curr_rom.print_string_start;
        distance /= 20; // Automatically truncated, so it won't overshoot

        for (int i = 0; i < distance; i++)
        {
            z80_payload.add_byte(curr_rom.short_pkmn_name);
        }
        z80_payload.add_byte(curr_rom.pointer_pkmn_name);
        z80_payload.add_byte(0xFF);

        // Patchlist preamble
        // At 0x1B4 / 0x1D7, 0x07 in length
        // Set as five 0xFD and two 0xFF

        for (int i = 0; i < 7; i++)
        {
            z80_patchlist.add_byte(i < 5 ? 0xFD : 0xFF);
        }

        // Patchlist
        // At 0x1BB / 0x1DE, 0xC2 in length (0xC4, but the last 2 are unused)
        // Fill with custom code
        asm_start.set_start(&z80_patchlist);

        /* Write transferring message to screen: */
        // call ClearScreen
        z80_patchlist.CALL(curr_rom.clearScreen | T_U16);
        z80_patchlist.LD(HL, curr_rom.textBorderUppLeft | T_U16);
        z80_patchlist.LD(C, curr_rom.textBorderWidth | T_U8);
        z80_patchlist.LD(B, curr_rom.textBorderHeight | T_U8);
        z80_patchlist.CALL(curr_rom.CableClub_TextBoxBorder | T_U16);
        z80_patchlist.LD(HL, curr_rom.transferStringLocation | T_U16);
        z80_patchlist.LD(DE, transfer_wait_string.place_ptr(&z80_patchlist) | T_U16);
        z80_patchlist.CALL(curr_rom.placeString | T_U16);

        /* Build the packet */
        //      HL is the current data pointer
        //      DE is the destination pointer
        //      A is the checksum
        //      B is the 0xFE flag byte
        //      C is the counter
        send_packet_loop.set_start(&z80_patchlist);

        // Theoretically this could be changed to just take the direct address instead of adding the offset to it, if space is needed
        z80_patchlist.LD(HL, (DATA_LOC + PACKET_SIZE + 3) | T_U16);
        z80_patchlist.LD(E, HL_PTR);
        z80_patchlist.INC(HL);
        z80_patchlist.LD(D, HL_PTR);
        z80_patchlist.LD(HL, curr_rom.wBoxDataStart | T_U16);
        z80_patchlist.ADD(HL, DE);

        z80_patchlist.LD(DE, (DATA_LOC + 1) | T_U16); // Enemy Pokemon data, should be unused
        z80_patchlist.XOR(A, A);                      // Clear the register
        z80_patchlist.LD(B, A);                       // Clear B as well
        z80_patchlist.LD(C, A);                       // Clear C as well
        z80_patchlist.PUSH(AF);
        packet_loop.set_start(&z80_patchlist);
        z80_patchlist.SLA(B); // Shift flag over
        z80_patchlist.POP(AF);
        z80_patchlist.ADD(A, HL_PTR); // Add the current data to the checksum
        z80_patchlist.PUSH(AF);
        z80_patchlist.LD(A, 0xFE);
        z80_patchlist.CP(A, HL_PTR);  // Compare the current data to 0xFE
        z80_patchlist.LD(A, HLI_PTR); // Load HL's data into A for modification (if need be)

        // If HL's data is 0xFE
        z80_patchlist.JR(NZ_F, fe_bypass.place_relative_jump(&z80_patchlist) | T_I8);
        z80_patchlist.DEC(A);
        z80_patchlist.INC(B); // Set flag
        fe_bypass.set_start(&z80_patchlist);

        z80_patchlist.LD(DE_PTR, A);
        z80_patchlist.INC(DE);
        z80_patchlist.INC(C);
        z80_patchlist.LD(A, 0x07);
        z80_patchlist.CP(A, C);
        z80_patchlist.JR(NC_F, packet_loop.place_relative_jump(&z80_patchlist) | T_I8);
        z80_patchlist.POP(AF);
        z80_patchlist.LD(DE_PTR, A);
        z80_patchlist.INC(DE);
        z80_patchlist.LD(A, B);
        z80_patchlist.LD(DE_PTR, A);
        z80_patchlist.INC(DE);
        z80_patchlist.LD(A, H);
        z80_patchlist.LD(DE_PTR, A);
        z80_patchlist.INC(DE);
        z80_patchlist.LD(A, L);
        z80_patchlist.LD(DE_PTR, A);

        // z80_patchlist.LD(HL, curr_rom.garbageDataLocation | T_U16);

        /* Transfer box data packet: */
        z80_patchlist.LD(HL, curr_rom.hSerialConnectionStatus | T_U16); // Can be shortened since it is 0xFFxx
        z80_patchlist.LD(HL_PTR, (debug ? 0x02 : 0x01) | T_U8);         // Make sure GB is the slave, master if debug
        z80_patchlist.LD(HL, DATA_LOC | T_U16);
        z80_patchlist.LD(HL_PTR, 0xFD | T_U8);                  // set the start of the data to 0xFD so Serial_ExchangeBytes is happy
        z80_patchlist.LD(DE, (DATA_LOC + PACKET_SIZE) | T_U16); // location to put stored data
        z80_patchlist.LD(BC, PACKET_SIZE | T_U16);
        if (debug) // Don't call serialExchangeBytes if debug is enabled
        {
            z80_patchlist.index += 3;
        }
        else
        {
            z80_patchlist.CALL(curr_rom.Serial_ExchangeBytes | T_U16);
        }

        z80_patchlist.LD(A, (DATA_LOC + PACKET_SIZE + 3 + 1) | T_U16);
        z80_patchlist.CP(A, 0xFF);
        z80_patchlist.JR(NZ_F, send_packet_loop.place_relative_jump(&z80_patchlist) | T_I8);

        /* Recieve the Pokemon to remove */
        z80_patchlist.LD(HL, curr_rom.hSerialConnectionStatus | T_U16); // This can also be shortened
        z80_patchlist.LD(HL_PTR, (debug ? 0x02 : 0x01) | T_U8);         // Make sure GB is the slave, master if debug
        z80_patchlist.LD(HL, curr_rom.garbageDataLocation | T_U16);
        z80_patchlist.LD(DE, removal_array.place_ptr(&z80_patchlist) | T_U16);
        z80_patchlist.LD(BC, 0x001E | T_U16); // Preamble does *not* count
        if (debug)                            // Don't add in the Serial_ExchangeBytes call if in debug
        {
            z80_patchlist.index += 3;
        }
        else
        {
            z80_patchlist.CALL(curr_rom.Serial_ExchangeBytes | T_U16);
        }

        /* Remove the transfered Pokemon */
        z80_patchlist.LD(HL, curr_rom.wRemoveMonFromBox | T_U16);
        z80_patchlist.LD(HL_PTR, 0x01 | T_U8); // != 0x00 specifies the current box
        remove_array_loop.set_start(&z80_patchlist);
        z80_patchlist.LD(A, array_counter.place_ptr(&z80_patchlist) | T_U16);
        z80_patchlist.LD(E, A);
        z80_patchlist.LD(D, 0x00 | T_U8);
        z80_patchlist.LD(HL, removal_array.place_ptr(&z80_patchlist) | T_U16);
        z80_patchlist.ADD(HL, DE);
        z80_patchlist.INC(A);
        z80_patchlist.LD(array_counter.place_ptr(&z80_patchlist) | T_U16, A);
        z80_patchlist.LD(A, curr_rom.wBoxCount | T_U16);
        z80_patchlist.LD(B, A);
        z80_patchlist.LD(A, HL_PTR);
        z80_patchlist.CP(A, 0xFF | T_U8);
        z80_patchlist.JR(Z_F, save_box.place_relative_jump(&z80_patchlist) | T_I8);
        z80_patchlist.CP(A, B);
        z80_patchlist.JR(NC_F, remove_array_loop.place_relative_jump(&z80_patchlist) | T_I8);
        z80_patchlist.LD(HL, curr_rom.wWhichPokemon | T_U16);
        z80_patchlist.LD(HL_PTR, A);
        if (DONT_REMOVE_PKMN)
        {
            z80_patchlist.index += 3;
        }
        else
        {
            z80_patchlist.CALL(curr_rom._RemovePokemon | T_U16);
        }
        z80_patchlist.JR((remove_array_loop.place_relative_jump(&z80_patchlist) & 0xFF) | T_I8);

        /* Save the current box */
        save_box.set_start(&z80_patchlist);
        z80_patchlist.LD(B, (curr_rom.SaveSAVtoSRAM1 >> 16) | T_U8); // Load ROM Bank
        z80_patchlist.LD(HL, curr_rom.SaveSAVtoSRAM1 | T_U16);
        z80_patchlist.CALL(curr_rom.Bankswitch | T_U16);
        z80_patchlist.LD(B, (curr_rom.SaveSAVtoSRAM1 >> 16) | T_U8); // Load ROM Bank
        z80_patchlist.LD(HL, curr_rom.SaveSAVtoSRAM2 | T_U16);
        z80_patchlist.CALL(curr_rom.Bankswitch | T_U16);
        z80_patchlist.JP(curr_rom.SoftReset | T_U16);

        // z80_patchlist.index += 5;

        array_counter.insert_variable(&z80_patchlist);
        removal_array.insert_variable(&z80_payload);
        transfer_wait_string.insert_variable(&z80_patchlist);

        // This payload works by placing Pokemon ID 0xFC's name in the stack, and causing a return to CD8E,
        // which is part of the RNG seed. From there we can jump anywhere- and we choose to jump to D887,
        // which is the rival's name. This code fixes the stack and jumps to the patchlist, which is where
        // our final code is.

        // Update all the pointers
        for (unsigned int i = 0; i < var_vector.size(); i++)
        {
            var_vector.at(i)->update_ptrs();
        }
        for (unsigned int i = 0; i < jump_vector.size(); i++)
        {
            jump_vector.at(i)->update_jumps();
        }

        // Combine the vectors into the full payload
        std::vector<byte> full_data;
        full_data.reserve(z80_rng_seed.data_vector.size() + z80_payload.data_vector.size() + z80_patchlist.data_vector.size());
        full_data.insert(full_data.end(), z80_rng_seed.data_vector.begin(), z80_rng_seed.data_vector.end());
        full_data.insert(full_data.end(), z80_payload.data_vector.begin(), z80_payload.data_vector.end());
        full_data.insert(full_data.end(), z80_patchlist.data_vector.begin(), z80_patchlist.data_vector.end());

        std::copy(full_data.begin(), full_data.end(), out_array);

        return out_array;
    }

    else if ((curr_rom.generation == 1 && curr_rom.method == METHOD_MEW))
    {
        std::vector<z80_jump *> jump_vector;
        std::vector<z80_variable *> var_vector;

        z80_asm_handler z80_rng_seed(0x0A, curr_rom.wSerialOtherGameboyRandomNumberListBlock + 8);
        z80_asm_handler z80_payload(0x1AA, curr_rom.wSerialEnemyDataBlock);
        z80_asm_handler z80_patchlist(0xEC, curr_rom.wSerialEnemyMonsPatchList);

        z80_jump asm_start(&jump_vector);
        z80_jump save_box(&jump_vector);
        z80_jump remove_array_loop(&jump_vector);
        z80_jump small_hop(&jump_vector);

        z80_variable array_counter(&var_vector, 1, 0x00); // 1 byte to store the current array counter
        z80_variable removal_array(&var_vector);          // 40 byte storage for list of Pokemon to remove, plus a permanent array terminator
        byte removal_array_data[41];
        for (int i = 0; i < 41; i++)
        {
            if (debug)
            {
                removal_array_data[i] = (i < 30 ? (29 - i) : 0xFF);
            }
            else
            {
                removal_array_data[i] = (i < 30 ? 0xFD : 0xFF);
            }
        }
        removal_array.load_data(41, removal_array_data);
        z80_variable transfer_wait_string(&var_vector, 30, // TRANSFERRING..\n
                                                           //  PLEASE WAIT!
                                          0x93, 0x91, 0x80, 0x8D, 0x92, 0x85, 0x84, 0x91, 0x91, 0x88, 0x8D, 0x86, 0xF2, 0xF2, 0x4E,
                                          0x7F, 0x8F, 0x8B, 0x84, 0x80, 0x92, 0x84, 0x7F, 0x96, 0x80, 0x88, 0x93, 0xE7, 0x7F, 0x50);
        z80_variable custom_name(&var_vector, 11, // FENNEL
                                 0x85, 0x84, 0x8D, 0x8D, 0x84, 0x8B, 0x50, 0x50, 0x50, 0x50, 0x50);

        // RNG Seed:
        // at 0x00, 0x0A in length
        // Does not need to be set

        // Preamble
        // At 0x00, 0x07 in length
        // Must be filled with 0xFD
        for (int i = 0; i < 7; i++)
        {
            z80_payload.add_byte(0xFD);
        }

        // Rival name
        // At 0x07, 0x0B in length
        // Set to stored name
        z80_payload.index = 0x07;
        custom_name.insert_variable(&z80_payload);

        // Number of Pokemon
        // At 0x12, 0x01 in length
        // Does not need to be set
        z80_payload.index = 0x12;
        z80_payload.add_byte(0x06);

        // Pokemon list
        // At 0x13, can be up to 0x1A2 / 0x1B9 bytes in length.
        // Calculate the number of Pokemon names that need to be printed,
        // and add them to the list. Then terminate the list.

        int distance = curr_rom.stack_overwrite_location - curr_rom.print_string_start;
        distance /= 20; // Automatically truncated, so it won't overshoot

        z80_payload.index = 0x13;
        for (int i = 0; i < distance; i++)
        {
            z80_payload.add_byte(i != 277 ? curr_rom.short_pkmn_name : 0xC8);
        }
        z80_payload.add_byte(curr_rom.pointer_pkmn_name);
        z80_payload.add_byte(0xFF);

        // Add in the code for reloading the script, keeping in mind the MEWs
        z80_payload.index = 0x194;

        // ld hl, hSerialConnectionStatus
        z80_payload.LD(HL, curr_rom.hSerialConnectionStatus | T_U16);
        z80_payload.LD(HL_PTR, (debug ? 0x02 : 0x01) | T_U8); // Make sure GB is the slave, master if debug
        z80_payload.index += 4;                               // Mew
        z80_payload.LD(HL, curr_rom.garbageDataLocation | T_U16);
        z80_payload.LD(DE, 0xC5D0 | T_U16);                                          // wSerialEnemyMonsPatchList
        z80_payload.JR((small_hop.place_relative_jump(&z80_payload) & 0xFF) | T_I8); // Relative jump, since that's all we have space for

        z80_payload.index -= 47;

        small_hop.set_start(&z80_payload);
        z80_payload.LD(BC, 0x00C2 | T_U16);
        z80_payload.CALL(curr_rom.Serial_ExchangeBytes | T_U16); // Refresh the patch section
        z80_payload.LD(A, (curr_rom.SaveSAVtoSRAM1 >> 16) | T_U8);
        z80_payload.CALL(curr_rom.Bankswitch | T_U16);
        z80_payload.CALL(0x79FC | T_U16); // Call LoadSAV1

        z80_payload.index += 5; // Mew

        z80_payload.CALL(0x7A24 | T_U16);
        z80_payload.JP(asm_start.place_direct_jump(&z80_payload) | T_U16);

        // Patchlist preamble
        // At 0x1B4 0x07 in length
        // Set as five 0xFD and two 0xFF
        for (int i = 0; i < 7; i++)
        {
            z80_patchlist.add_byte(i < 5 ? 0xFD : 0xFF);
        }

        // Patchlist
        // At 0x1BB / 0x1DE, 0xC2 in length (0xC4, but the last 2 are unused)
        // Fill with custom code

        if (type == TRANSFER)
        {
            asm_start.set_start(&z80_patchlist);
            z80_patchlist.LD(A, 0x01 | T_U8);
            z80_patchlist.CALL(curr_rom.Bankswitch | T_U16);

            // Write transferring message to screen:
            z80_patchlist.CALL(curr_rom.clearScreen | T_U16);
            z80_patchlist.LD(HL, curr_rom.textBorderUppLeft | T_U16);
            z80_patchlist.LD(C, curr_rom.textBorderWidth | T_U8);
            z80_patchlist.LD(B, curr_rom.textBorderHeight | T_U8);
            z80_patchlist.CALL(curr_rom.CableClub_TextBoxBorder | T_U16);
            z80_patchlist.LD(HL, curr_rom.transferStringLocation | T_U16);
            z80_patchlist.LD(DE, (transfer_wait_string.place_ptr(&z80_patchlist)) | T_U16);
            z80_patchlist.CALL(curr_rom.placeString | T_U16);

            // Transfer box data:
            z80_patchlist.LD(HL, curr_rom.hSerialConnectionStatus | T_U16); // Can be shortened since it is 0xFFxx
            z80_patchlist.LD(HL_PTR, (debug ? 0x02 : 0x01) | T_U8);         // Make sure GB is the slave, master if debug
            z80_patchlist.LD(HL, (curr_rom.wBoxDataStart - 1) | T_U16);
            z80_patchlist.LD(HL_PTR, 0xFD | T_U8);                                    // set the start of the data to 0xFD so Serial_ExchangeBytes is happy
            z80_patchlist.LD(DE, (curr_rom.wBoxDataStart - (debug ? 2 : 3)) | T_U16); // location to put stored data
            z80_patchlist.LD(BC, ((curr_rom.wBoxDataEnd - curr_rom.wBoxDataStart) + 2) | T_U16);

            if (debug) // Don't call serialExchangeBytes if debug is enabled
            {
                z80_patchlist.index += 3;
            }
            else
            {
                z80_patchlist.CALL(curr_rom.Serial_ExchangeBytes | T_U16);
            }

            // Recieve the Pokemon to remove
            z80_patchlist.LD(HL, curr_rom.hSerialConnectionStatus | T_U16); // This can also be shortened
            z80_patchlist.LD(HL_PTR, (debug ? 0x02 : 0x01) | T_U8);         // Make sure GB is the slave, master if debug
            z80_patchlist.LD(HL, curr_rom.garbageDataLocation | T_U16);
            z80_patchlist.LD(DE, removal_array.place_ptr(&z80_patchlist) | T_U16);
            z80_patchlist.LD(BC, 0x001E | T_U16); // Preamble does *not* count

            if (debug) // Don't add in the Serial_ExchangeBytes call if in debug
            {
                z80_patchlist.index += 3;
            }
            else
            {
                z80_patchlist.CALL(curr_rom.Serial_ExchangeBytes | T_U16);
            }

            // Remove the transfered Pokemon
            z80_patchlist.LD(HL, curr_rom.wRemoveMonFromBox | T_U16);
            z80_patchlist.LD(HL_PTR, 0x01 | T_U8); // != 0x00 specifies the current box
            remove_array_loop.set_start(&z80_patchlist);
            z80_patchlist.LD(A, array_counter.place_ptr(&z80_patchlist) | T_U16);
            z80_patchlist.LD(E, A);
            z80_patchlist.LD(D, 0x00 | T_U8);
            z80_patchlist.LD(HL, removal_array.place_ptr(&z80_patchlist) | T_U16);
            z80_patchlist.ADD(HL, DE);
            z80_patchlist.LD(E, 0xFF | T_U8);
            z80_patchlist.INC(A);
            z80_patchlist.LD(array_counter.place_ptr(&z80_patchlist) | T_U16, A);
            z80_patchlist.LD(A, curr_rom.wBoxCount | T_U16);
            z80_patchlist.LD(B, A);
            z80_patchlist.LD(A, HL_PTR);
            z80_patchlist.CP(A, E);
            z80_patchlist.JR(Z_F, save_box.place_relative_jump(&z80_patchlist) | T_I8);
            z80_patchlist.CP(A, B);
            z80_patchlist.JR(NC_F, remove_array_loop.place_relative_jump(&z80_patchlist) | T_I8);
            z80_patchlist.LD(HL, curr_rom.wWhichPokemon | T_U16);
            z80_patchlist.LD(HL_PTR, A);
            if (DONT_REMOVE_PKMN)
            {
                z80_patchlist.index += 3;
            }
            else
            {
                z80_patchlist.CALL(curr_rom._RemovePokemon | T_U16);
            }
            z80_patchlist.JR(remove_array_loop.place_relative_jump(&z80_patchlist) | T_I8);

            // Save the current box
            save_box.set_start(&z80_patchlist);
            z80_patchlist.LD(A, (curr_rom.SaveSAVtoSRAM1 >> 16) | T_U8); // Load ROM Bank
            z80_patchlist.CALL(curr_rom.Bankswitch | T_U16);
            z80_patchlist.CALL(curr_rom.SaveSAVtoSRAM1 | T_U16);
            z80_patchlist.CALL(curr_rom.SaveSAVtoSRAM2 | T_U16);
            z80_patchlist.JP(curr_rom.SoftReset | T_U16);

            array_counter.insert_variable(&z80_patchlist);
            removal_array.insert_variable(&z80_patchlist);
            transfer_wait_string.insert_variable(&z80_patchlist);

            // This payload works by placing Pokemon ID 0xFC's name in the stack, and causing a return to CD8E,
            // which is part of the RNG seed. From there we can jump anywhere- and we choose to jump to D887,
            // which is the rival's name. This code fixes the stack and jumps to the patchlist, which is where
            // our final code is.

            // Update all the pointers
            for (unsigned int i = 0; i < var_vector.size(); i++)
            {
                var_vector.at(i)->update_ptrs();
            }
            for (unsigned int i = 0; i < jump_vector.size(); i++)
            {
                jump_vector.at(i)->update_jumps();
            }

            // Combine the vectors into the full payload
            std::vector<byte> full_data;
            full_data.reserve(z80_rng_seed.data_vector.size() + z80_payload.data_vector.size() + z80_patchlist.data_vector.size());
            full_data.insert(full_data.end(), z80_rng_seed.data_vector.begin(), z80_rng_seed.data_vector.end());
            full_data.insert(full_data.end(), z80_payload.data_vector.begin(), z80_payload.data_vector.end());
            full_data.insert(full_data.end(), z80_patchlist.data_vector.begin(), z80_patchlist.data_vector.end());

            std::copy(full_data.begin(), full_data.end(), out_array);

            return out_array;
        }
        /*
        else if (type == EVENT)
        {
            // ld a, $03
            payload_storage[offset++] = 0x3A;
            payload_storage[offset++] = 0x03;

            // call OpenSRAM
            payload_storage[offset++] = 0xC3;
            payload_storage[offset++] = (curr_rom.OpenSRAM >> 0) & 0xFF;
            payload_storage[offset++] = (curr_rom.OpenSRAM >> 8) & 0xFF;

            // ld de, $BEB0
            payload_storage[offset++] = 0x11;
            payload_storage[offset++] = 0xB0;
            payload_storage[offset++] = 0xBE;

            // ld bc, $150
            payload_storage[offset++] = 0x01;
            payload_storage[offset++] = 0x50;
            payload_storage[offset++] = 0x01;

            // ld hl, ???
            payload_storage[offset++] = 0x21;
            payload_storage[offset++] = 0x00;
            payload_storage[offset++] = 0x00;

            //  CUSTOM EVENT SCRIPT:
            // Start with the table data
            int init_offset = offset;
            insert_ext_copy_cmd(&offset, 0x11410E, 0xD930, 18); // Copy text pointers
            insert_ext_copy_cmd(&offset, 0x00C120, 0xC140, 10); //
            insert_ext_copy_cmd(&offset, 0x00C220, 0xC240, 16); //
            byte temp[] = {0xD0, 0x0A};
            insert_int_copy_cmd(&offset, 0xD4E9, 2, temp); //
            byte temp1[] = {0x15, 0x05};
            insert_int_copy_cmd(&offset, 0xD517, 2, temp1); //
            byte temp2[] = {0x30, 0xD9};
            insert_int_copy_cmd(&offset, 0xD36B, 2, temp2); //
            byte temp3[] = {0x0B, 0xF0, 0xFF};
            insert_int_copy_cmd(&offset, 0xD5D3, 3, temp3); //
            byte temp4[] = {0x05};
            insert_int_copy_cmd(&offset, 0xD4E0, 1, temp4); //
            byte temp5[] = {0x44, 0xD9, 0x08, 0x21, 0x54, 0xD9, 0xCD, 0x68, 0x31, 0x21, 0xB0, 0xC1, 0x00, 0x00, 0xC3, 0xD2, 0x23, 0x01, 0x00, 0x5E, 0xD8, 0xD8, 0xC9, 0xD8, 0xC9, 0xD8, 0xC9, 0xD8, 0xC9, 0x00, 0x8C, 0xB8, 0xB4, 0xB4, 0xE7, 0x50, 0x08, 0x3E, 0x83, 0xCD, 0x8B, 0x11, 0xCD, 0x3E, 0x37, 0xC3, 0xD2, 0x23};
            insert_int_copy_cmd(&offset, 0xD942, 48, temp5); //
            payload_storage[offset++] = 0xFF;


            // call CloseSRAM
            payload_storage[offset++] = 0xC3;
            payload_storage[offset++] = (curr_rom.CloseSRAM >> 0) & 0xFF;
            payload_storage[offset++] = (curr_rom.CloseSRAM >> 8) & 0xFF;

            // call SoftReset
            payload_storage[offset++] = 0xC3;
            payload_storage[offset++] = (curr_rom.SoftReset >> 0) & 0xFF;
            payload_storage[offset++] = (curr_rom.SoftReset >> 8) & 0xFF;

        }*/
    }

    else if (curr_rom.generation == 2)
    {
        std::vector<z80_jump *> jump_vector;
        std::vector<z80_variable *> var_vector;

        z80_asm_handler z80_rng_seed(0x0A, curr_rom.wSerialOtherGameboyRandomNumberListBlock);
        z80_asm_handler z80_payload(0x1CD, curr_rom.wSerialEnemyDataBlock);      // wOTPartyData
        z80_asm_handler z80_patchlist(0xEC, curr_rom.wSerialEnemyMonsPatchList); // wOTPatchLists

        /*
        Initally the entire wLinkData is copied into the data section at D26B.
        then, CopyBytes is called four times within link.skip_mail:
            1. It copies 0xB bytes from wLinkData to wOTPlayerName (D26B)
            2. It copies 0x8 bytes from where the previous one ended (D280) to wOTPartyCount
            3. It copies 0x2 bytes from where the previous one ended (D276) to wOTPlayerID
            4. It copies 0x1A4 bytes from where the previous one ended (D288) to wOTPartyMons

            8 bytes aren't overwritten when copied over (D278-D28F), which is where the weird offset comes from. These bytes are index 0xE through 0x15 in the original data
            By having 9 bytes of 0xFD, the offset ends up working out correctly.
        */

        z80_jump asm_start(&jump_vector);
        z80_jump save_box(&jump_vector);
        z80_jump remove_array_loop(&jump_vector);
        z80_jump jump_to_party(&jump_vector);
        z80_jump jump_to_payload(&jump_vector);
        z80_jump packet_loop(&jump_vector);
        z80_jump fe_bypass(&jump_vector);
        z80_jump send_packet_loop(&jump_vector);

        z80_variable array_counter(&var_vector, 1, 0x00); // 1 byte to store the current array counter
        z80_variable removal_array(&var_vector);          // 40 byte storage for list of Pokemon to remove, plus a permanent array terminator
        byte removal_array_data[41];
        for (int i = 0; i < 41; i++)
        {
            if (debug)
            {
                removal_array_data[i] = (i < 30 ? (29 - i) : 0xFF);
            }
            else
            {
                removal_array_data[i] = (i < 30 ? 0xFD : 0xFF);
            }
        }
        removal_array.load_data(41, removal_array_data);
        z80_variable transfer_wait_string(&var_vector, 13, // SENDING DATA
                                          0x92, 0x84, 0x8D, 0x83, 0x88, 0x8D, 0x86, 0x7F, 0x83, 0x80, 0x93, 0x80, 0x50);
        z80_variable custom_name(&var_vector, 11, // FENNEL
                                 0x85, 0x84, 0x8D, 0x8D, 0x84, 0x8B, 0x50, 0x50, 0x50, 0x50, 0x50);

        // RNG Seed:
        // at 0x00, 0x0A in length
        // Does not need to be set

        // Preamble
        // At 0x00, 0x09 in length
        // Must be filled with 0xFD
        for (int i = 0; i < 9; i++)
        {
            z80_payload.add_byte(0xFD);
        }

        // Preamble/Rival name
        // At 0x00, 0x1C5 in length
        // Set to stored name
        int distance = curr_rom.stack_overwrite_location - curr_rom.print_string_start;
        int remainder = distance % 40;
        distance /= 40; // Automatically truncated, so it won't overshoot
        distance -= 8;  // There will be 8 extra bytes due to how the copy functions work.

        for (int i = 0; i < distance; i++)
        {
            z80_payload.add_byte(curr_rom.short_pkmn_name);
        }
        for (int i = 0; i < remainder; i++)
        {
            z80_payload.add_byte(0x80);
        }

        z80_payload.index -= 1; // Prep for the direct jump, since it usually has to jump forward one for the ASM call
        jump_to_payload.place_direct_jump(&z80_payload);
        z80_payload.index += 3;
        z80_payload.add_byte(0x50); // String terminator

        // Saving the box overwrites our code, so we need to move it here.
        jump_to_party.set_start(&z80_payload);
        z80_payload.LD(A, curr_rom.SaveBox >> 16 | T_U8);
        z80_payload.RST(0x10); // Bank switch
        z80_payload.CALL(curr_rom.SaveBox | T_U16);

        z80_payload.JP(curr_rom.SoftReset | T_U16);

        // Patchlist preamble
        // At 0x1B4 / 0x1D7, 0x07 in length
        // Set as five 0xFD and two 0xFF

        for (int i = 0; i < 7; i++)
        {
            z80_patchlist.add_byte(i < 5 ? 0xFD : 0xFF);
        }

        // Patchlist
        // At 0x1DE, 194 in length
        // Fill with custom code

        // Write transferring message to screen:
        // call ClearScreen
        jump_to_payload.set_start(&z80_patchlist);
        z80_patchlist.CALL(curr_rom.clearScreen | T_U16);

        z80_patchlist.LD(HL, curr_rom.textBorderUppLeft | T_U16);
        z80_patchlist.LD(C, curr_rom.textBorderWidth | T_U8);
        z80_patchlist.LD(B, curr_rom.textBorderHeight | T_U8);
        z80_patchlist.LD(A, curr_rom.CableClub_TextBoxBorder >> 16 | T_U8);
        z80_patchlist.RST(0x10); // Bank switch
        z80_patchlist.CALL(curr_rom.CableClub_TextBoxBorder | T_U16);
        z80_patchlist.LD(HL, curr_rom.transferStringLocation | T_U16);
        z80_patchlist.LD(DE, transfer_wait_string.place_ptr(&z80_patchlist) | T_U16);

        // call PlaceString
        z80_patchlist.CALL(curr_rom.placeString | T_U16);

        // call OpenSRAM
        z80_patchlist.LD(A, 0x01 | T_U8);
        z80_patchlist.CALL(curr_rom.OpenSRAM | T_U16);

        /* Build the packet */
        //      HL is the current data pointer
        //      DE is the destination pointer
        //      A is the checksum
        //      B is the 0xFE flag byte
        //      C is the counter
        send_packet_loop.set_start(&z80_patchlist);

        // Theoretically this could be changed to just take the direct address instead of adding the offset to it, if space is needed
        z80_patchlist.LD(HL, (DATA_LOC + PACKET_SIZE + 3) | T_U16);
        z80_patchlist.LD(E, HL_PTR);
        z80_patchlist.INC(HL);
        z80_patchlist.LD(D, HL_PTR);
        z80_patchlist.LD(HL, curr_rom.wBoxDataStart | T_U16);
        z80_patchlist.ADD(HL, DE);

        z80_patchlist.LD(DE, (DATA_LOC + 1) | T_U16); // Enemy Pokemon data, should be unused
        z80_patchlist.XOR(A, A);                      // Clear the register
        z80_patchlist.LD(B, A);                       // Clear B as well
        z80_patchlist.LD(C, A);                       // Clear C as well
        z80_patchlist.PUSH(AF);
        packet_loop.set_start(&z80_patchlist);
        z80_patchlist.SLA(B); // Shift flag over
        z80_patchlist.POP(AF);
        z80_patchlist.ADD(A, HL_PTR); // Add the current data to the checksum
        z80_patchlist.PUSH(AF);
        z80_patchlist.LD(A, 0xFE);
        z80_patchlist.CP(A, HL_PTR);  // Compare the current data to 0xFE
        z80_patchlist.LD(A, HLI_PTR); // Load HL's data into A for modification (if need be)

        // If HL's data is 0xFE
        z80_patchlist.JR(NZ_F, fe_bypass.place_relative_jump(&z80_patchlist) | T_I8);
        z80_patchlist.DEC(A);
        z80_patchlist.INC(B); // Set flag
        fe_bypass.set_start(&z80_patchlist);

        z80_patchlist.LD(DE_PTR, A);
        z80_patchlist.INC(DE);
        z80_patchlist.INC(C);
        z80_patchlist.LD(A, 0x07);
        z80_patchlist.CP(A, C);
        z80_patchlist.JR(NC_F, packet_loop.place_relative_jump(&z80_patchlist) | T_I8);
        z80_patchlist.POP(AF);
        z80_patchlist.LD(DE_PTR, A);
        z80_patchlist.INC(DE);
        z80_patchlist.LD(A, B);
        z80_patchlist.LD(DE_PTR, A);
        z80_patchlist.INC(DE);
        z80_patchlist.LD(A, H);
        z80_patchlist.LD(DE_PTR, A);
        z80_patchlist.INC(DE);
        z80_patchlist.LD(A, L);
        z80_patchlist.LD(DE_PTR, A);

        /* Transfer box data packet: */
        z80_patchlist.LD(HL, curr_rom.hSerialConnectionStatus | T_U16); // Can be shortened since it is 0xFFxx
        z80_patchlist.LD(HL_PTR, (debug ? 0x02 : 0x01) | T_U8);         // Make sure GB is the slave, master if debug
        z80_patchlist.LD(HL, DATA_LOC | T_U16);
        z80_patchlist.LD(HL_PTR, 0xFD | T_U8);                  // set the start of the data to 0xFD so Serial_ExchangeBytes is happy
        z80_patchlist.LD(DE, (DATA_LOC + PACKET_SIZE) | T_U16); // location to put stored data
        z80_patchlist.LD(BC, PACKET_SIZE | T_U16);
        if (debug) // Don't call serialExchangeBytes if debug is enabled
        {
            z80_patchlist.index += 3;
        }
        else
        {
            z80_patchlist.CALL(curr_rom.Serial_ExchangeBytes | T_U16);
        }

        z80_patchlist.LD(A, (DATA_LOC + PACKET_SIZE + 3 + 1) | T_U16);
        z80_patchlist.CP(A, 0xFF);
        z80_patchlist.JR(NZ_F, send_packet_loop.place_relative_jump(&z80_patchlist) | T_I8);

        // Recieve the Pokemon to remove
        z80_patchlist.LD(HL, curr_rom.hSerialConnectionStatus | T_U16); // This can also be shortened
        z80_patchlist.LD(HL_PTR, (debug ? 0x02 : 0x01) | T_U8);         // Make sure GB is the slave, master if debug
        z80_patchlist.LD(HL, curr_rom.garbageDataLocation | T_U16);
        z80_patchlist.LD(DE, removal_array.place_ptr(&z80_patchlist) | T_U16);
        z80_patchlist.LD(BC, 0x001E | T_U16); // Preamble does *not* count
        if (debug)                            // Don't add in the Serial_ExchangeBytes call if in debug
        {
            z80_patchlist.index += 3;
        }
        else
        {
            z80_patchlist.CALL(curr_rom.Serial_ExchangeBytes | T_U16);
        }

        // Remove the transfered Pokemon
        z80_patchlist.LD(HL, curr_rom.wRemoveMonFromBox | T_U16);
        z80_patchlist.LD(HL_PTR, 0x01 | T_U8); // != 0x00 specifies the current box
        remove_array_loop.set_start(&z80_patchlist);
        z80_patchlist.LD(A, array_counter.place_ptr(&z80_patchlist) | T_U16);
        z80_patchlist.LD(E, A);
        z80_patchlist.LD(D, 0x00 | T_U8);
        z80_patchlist.LD(HL, removal_array.place_ptr(&z80_patchlist) | T_U16);
        z80_patchlist.ADD(HL, DE);
        z80_patchlist.INC(A);
        z80_patchlist.LD(array_counter.place_ptr(&z80_patchlist) | T_U16, A);
        z80_patchlist.LD(A, curr_rom.wBoxCount | T_U16);
        z80_patchlist.LD(B, A);
        z80_patchlist.LD(A, HL_PTR);
        z80_patchlist.CP(A, 0xFF | T_U8);
        z80_patchlist.JR(Z_F, save_box.place_relative_jump(&z80_patchlist) | T_I8);
        z80_patchlist.CP(A, B);
        z80_patchlist.JR(NC_F, remove_array_loop.place_relative_jump(&z80_patchlist) | T_I8);
        z80_patchlist.LD(HL, curr_rom.wWhichPokemon | T_U16);
        z80_patchlist.LD(HL_PTR, A);
        if (DONT_REMOVE_PKMN)
        {
            z80_patchlist.index += 6;
        }
        else
        {
            z80_patchlist.LD(A, curr_rom._RemovePokemon >> 16 | T_U8);
            z80_patchlist.RST(0x10); // Bank switch
            z80_patchlist.CALL(curr_rom._RemovePokemon | T_U16);
        }
        z80_patchlist.JR(remove_array_loop.place_relative_jump(&z80_patchlist) | T_I8);

        save_box.set_start(&z80_patchlist);
        z80_patchlist.JP(jump_to_party.place_direct_jump(&z80_patchlist) | T_U16); // jp pkmn list (because saving the box overwrites the data)

        array_counter.insert_variable(&z80_patchlist);
        removal_array.insert_variable(&z80_payload);
        transfer_wait_string.insert_variable(&z80_patchlist);

        // This payload works by placing Pokemon ID 0xFC's name in the stack, and causing a return to CD8E,
        // which is part of the RNG seed. From there we can jump anywhere- and we choose to jump to D887,
        // which is the rival's name. This code fixes the stack and jumps to the patchlist, which is where
        // our final code is.

        // Update all the pointers
        for (unsigned int i = 0; i < var_vector.size(); i++)
        {
            var_vector.at(i)->update_ptrs();
        }
        for (unsigned int i = 0; i < jump_vector.size(); i++)
        {
            jump_vector.at(i)->update_jumps();
        }

        // Combine the vectors into the full payload
        std::vector<byte> full_data;
        full_data.reserve(z80_rng_seed.data_vector.size() + z80_payload.data_vector.size() + z80_patchlist.data_vector.size());
        full_data.insert(full_data.end(), z80_rng_seed.data_vector.begin(), z80_rng_seed.data_vector.end());
        full_data.insert(full_data.end(), z80_payload.data_vector.begin(), z80_payload.data_vector.end());
        full_data.insert(full_data.end(), z80_patchlist.data_vector.begin(), z80_patchlist.data_vector.end());

        std::copy(full_data.begin(), full_data.end(), out_array);

        return out_array;

        // This payload works by placing Pokemon ID 0xFC's name in the stack, and causing a return to CD8E,
        // which is part of the RNG seed. From there we can jump anywhere- and we choose to jump to D887,
        // which is the rival's name. This code fixes the stack and jumps to the patchlist, which is where
        // our final code is.
    }
    return nullptr;
};

int test_main() // Rename to "main" to send the payload to test_payload.txt
{
    freopen("test_payload.txt", "w", stdout);
    std::cout << std::endl;
    byte *payload = generate_payload(ENG_GOLD, TRANSFER, true);
    if (true)
    {
        for (int i = 0; i < 0x2A0; i++)
        {

            std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << (unsigned int)payload[i] << ", ";
            if (i % 0x10 == 0xF)
            {
                std::cout << std::endl
                          << "# 0x" << std::hex << i + 1 << std::endl;
            }
        }
        return 0;
    }
    else
    {
        for (int i = 0; i < 0x150; i++)
        {
            std::cout << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << (unsigned int)payload[i + ((0x10 * 28) + 9)] << " ";
            if (i % 0x10 == 0xF)
            {
                std::cout << std::endl;
            }
        }
        return 0;
    }
}