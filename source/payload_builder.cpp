#include "payload_builder.h"
#include "gb_rom_values/base_gb_rom_struct.h"
#include "gb_rom_values/eng_gb_rom_values.h"
#include "debug_mode.h"
#include "z80_asm.h"

#include <iostream>
#include <fstream>
#include <iomanip>

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

        z80_asm_handler z80_rng_seed(0x0A, 0xCD89);
        z80_asm_handler z80_payload(0x1AA, 0xD892);
        z80_asm_handler z80_patchlist(0xEC, 0xC5D0);

        z80_jump asm_start(&jump_vector);
        z80_jump save_box(&jump_vector);
        z80_jump remove_array_loop(&jump_vector);

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

        // RNG Seed
        // Location of the entrance vector
        z80_rng_seed.index = 5; // Set the entrance vector
        z80_rng_seed.JP(asm_start.place_direct_jump(&z80_rng_seed) | T_U16);

        // Preamble
        // At 0x00, 0x08 in length
        // Must be filled with 0xFD
        for (int i = 0; i < 8; i++)
        {
            z80_payload.add_byte(0xFD);
        }

        // Rival name
        // At 0x08, 0x0B in length
        // Set to stored name
        z80_payload.index = 0x08;
        custom_name.insert_variable(&z80_payload);

        // Number of Pokemon
        // At 0x13, 0x01 in length
        // Does not need to be set
        z80_payload.index = 0x13;
        z80_payload.add_byte(0x06);

        // Pokemon list
        // At 0x14, can be up to 0x1A2 / 0x1B9 bytes in length.
        // Calculate the number of Pokemon names that need to be printed,
        // and add them to the list. Then terminate the list.
        z80_payload.index = 0x14;
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
        z80_patchlist.LD(B, curr_rom.textBorderWidth | T_U8);
        z80_patchlist.LD(C, curr_rom.textBorderHeight | T_U8);
        z80_patchlist.CALL(curr_rom.CableClub_TextBoxBorder | T_U16);
        z80_patchlist.LD(HL, curr_rom.transferStringLocation | T_U16);
        z80_patchlist.LD(DE, transfer_wait_string.place_ptr(&z80_patchlist) | T_U16);
        z80_patchlist.CALL(curr_rom.placeString | T_U16);

        /* Transfer box data: */
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
        z80_patchlist.LD(B, curr_rom.SaveSAVtoSRAM1 >> 16); // Load ROM Bank
        z80_patchlist.LD(HL, curr_rom.SaveSAVtoSRAM1 | T_U16);
        z80_patchlist.CALL(curr_rom.Bankswitch | T_U16);
        z80_patchlist.LD(B, curr_rom.SaveSAVtoSRAM1 >> 16); // Load ROM Bank
        z80_patchlist.LD(HL, curr_rom.SaveSAVtoSRAM2 | T_U16);
        z80_patchlist.CALL(curr_rom.Bankswitch | T_U16);
        z80_patchlist.JP(curr_rom.SoftReset | T_U16);

        // z80_patchlist.index += 5;

        array_counter.insert_variable(&z80_patchlist);
        removal_array.insert_variable(&z80_patchlist);
        transfer_wait_string.insert_variable(&z80_patchlist);

        // This payload works by placing Pokemon ID 0xFC's name in the stack, and causing a return to CD8E,
        // which is part of the RNG seed. From there we can jump anywhere- and we choose to jump to D887,
        // which is the rival's name. This code fixes the stack and jumps to the patchlist, which is where
        // our final code is.

        // Update all the pointers
        for (int i = 0; i < var_vector.size(); i++)
        {
            var_vector.at(i)->update_ptrs();
        }
        for (int i = 0; i < jump_vector.size(); i++)
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

        z80_asm_handler z80_rng_seed(0x0A, 0xCD89);
        z80_asm_handler z80_payload(0x1AA, 0xD892);
        z80_asm_handler z80_patchlist(0xEC, 0xC5D0);

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
        // At 0x00, 0x08 in length
        // Must be filled with 0xFD
        for (int i = 0; i < 8; i++)
        {
            z80_payload.add_byte(0xFD);
        }

        // Rival name
        // At 0x08, 0x0B in length
        // Set to stored name
        z80_payload.index = 0x08;
        custom_name.insert_variable(&z80_payload);

        // Number of Pokemon
        // At 0x13, 0x01 in length
        // Does not need to be set
        z80_payload.index = 0x13;
        z80_payload.add_byte(0x06);

        // Pokemon list
        // At 0x14, can be up to 0x1A2 / 0x1B9 bytes in length.
        // Calculate the number of Pokemon names that need to be printed,
        // and add them to the list. Then terminate the list.

        int distance = curr_rom.stack_overwrite_location - curr_rom.print_string_start;
        distance /= 20; // Automatically truncated, so it won't overshoot
        
        z80_payload.index = 0x14;
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
        z80_payload.LD(DE, 0xC5D0 | T_U16);  // wSerialEnemyMonsPatchList
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
            z80_patchlist.LD(B, curr_rom.textBorderWidth | T_U8);
            z80_patchlist.LD(C, curr_rom.textBorderHeight | T_U8);
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
            z80_patchlist.LD(A, curr_rom.SaveSAVtoSRAM1 >> 16); // Load ROM Bank
            z80_patchlist.CALL(curr_rom.Bankswitch | T_U16);
            z80_patchlist.CALL(curr_rom.SaveSAVtoSRAM1 | T_U16);
            z80_patchlist.CALL(curr_rom.SaveSAVtoSRAM2 | T_U16);
            z80_patchlist.JP(curr_rom.SoftReset | T_U16);

            z80_patchlist.index += 4;

            array_counter.insert_variable(&z80_patchlist);
            removal_array.insert_variable(&z80_patchlist);
            transfer_wait_string.insert_variable(&z80_patchlist);

            // This payload works by placing Pokemon ID 0xFC's name in the stack, and causing a return to CD8E,
            // which is part of the RNG seed. From there we can jump anywhere- and we choose to jump to D887,
            // which is the rival's name. This code fixes the stack and jumps to the patchlist, which is where
            // our final code is.

            // Update all the pointers
            for (int i = 0; i < var_vector.size(); i++)
            {
                var_vector.at(i)->update_ptrs();
            }
            for (int i = 0; i < jump_vector.size(); i++)
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
    /*
    else if (curr_rom.generation == 2)
    {

        // RNG Seed:
        // at 0x00, 0x0A in length
        // Does not need to be set

        offset = 0x0A;

        // Preamble
        // At 0x0A, 0x08 in length
        // Must be filled with 0xFD
        for (int i = 0; i < 8; i++)
        {
            payload_storage[offset++] = 0xFD;
        }

        // Rival name
        // At 0x12, 0x1C5 in length
        // Set to stored name
        int distance = curr_rom.stack_overwrite_location - curr_rom.print_string_start;
        int remainder = distance % 40;
        distance /= 40; // Automatically truncated, so it won't overshoot
        distance -= 8;  // Gen 2 does some weird copy paste, so this allows it to ignore that. 8 because of the OT name length

        for (int i = 0; i < distance; i++)
        {
            payload_storage[offset++] = curr_rom.short_pkmn_name;
        }
        for (int i = 0; i < remainder; i++)
        {
            payload_storage[offset++] = 0x80;
        }
        payload_storage[offset++] = curr_rom.enter_vector_location & 0xFF;
        payload_storage[offset++] = (curr_rom.enter_vector_location >> 8) & 0xFF;
        payload_storage[offset++] = 0x50;

        // Opens the PC box and then crashes- only used for debugging
        // write_call(curr_rom.generation, payload_storage, offset, 0x0363D8);

        // Saving the box overwrites our code, so we need to move it here.
        write_call(curr_rom.generation, payload_storage, offset, curr_rom.SaveBox);

        // jp SoftReset
        payload_storage[offset++] = 0xC3;
        payload_storage[offset++] = (curr_rom.SoftReset >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.SoftReset >> 8) & 0xFF;

        // Patchlist preamble
        // At 0x1B4 / 0x1D7, 0x07 in length
        // Set as five 0xFD and two 0xFF

        offset = 0x1D7;

        for (int i = 0; i < 7; i++)
        {
            payload_storage[offset++] = (i < 5 ? 0xFD : 0xFF);
        }

        // Patchlist
        // At 0x1DE, 194 in length
        // Fill with custom code

        // Write transferring message to screen:
        // call ClearScreen
        write_call(curr_rom.generation, payload_storage, offset, curr_rom.clearScreen);

        // ld hl, [upper left textbox corner in VRAM]
        payload_storage[offset++] = 0x21;
        payload_storage[offset++] = (curr_rom.textBorderUppLeft >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.textBorderUppLeft >> 8) & 0xFF;

        // ld b, 3 [height]
        payload_storage[offset++] = 0x06;
        payload_storage[offset++] = (curr_rom.textBorderWidth >> 0) & 0xFF;

        // ld c, 14 [width]
        payload_storage[offset++] = 0x0E;
        payload_storage[offset++] = (curr_rom.textBorderHeight >> 0) & 0xFF;

        // call CableClub_TextBoxBorder
        write_call(curr_rom.generation, payload_storage, offset, curr_rom.CableClub_TextBoxBorder);

        // ld hl, [transfer string location]
        payload_storage[offset++] = 0x21;
        payload_storage[offset++] = (curr_rom.transferStringLocation >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.transferStringLocation >> 8) & 0xFF;

        // ld de, TransferWaitString
        payload_storage[offset++] = 0x11;
        payload_storage[offset++] = (curr_rom.transferWaitString >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.transferWaitString >> 8) & 0xFF;

        // call PlaceString
        write_call(curr_rom.generation, payload_storage, offset, curr_rom.placeString);

        // Transfer box data:
        // ld hl, hSerialConnectionStatus
        payload_storage[offset++] = 0x21;
        payload_storage[offset++] = (curr_rom.hSerialConnectionStatus >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.hSerialConnectionStatus >> 8) & 0xFF;

        // ld [hl], 0x01 [Make sure GB is the slave, master if debug]
        payload_storage[offset++] = 0x36;
        payload_storage[offset++] = (debug ? 0x02 : 0x01);

        // call OpenSRAM
        payload_storage[offset++] = 0x3E;
        payload_storage[offset++] = 0x01;
        write_call(curr_rom.generation, payload_storage, offset, curr_rom.OpenSRAM);

        // ld hl, (wBoxDataStart - 1) [data to send]
        payload_storage[offset++] = 0x21;
        payload_storage[offset++] = ((curr_rom.wBoxDataStart - 1) >> 0) & 0xFF;
        payload_storage[offset++] = ((curr_rom.wBoxDataStart - 1) >> 8) & 0xFF;

        // ld [hl], 0xFD [set the start of the data to 0xFD so Serial_ExchangeBytes is happy]
        // TODO Change me because of save corruption yayyyyyy
        payload_storage[offset++] = 0x36;
        payload_storage[offset++] = 0xFD;

        // ld de, (wBoxDataStart - 3) [location to put stored data]
        payload_storage[offset++] = 0x11;
        payload_storage[offset++] = ((curr_rom.wBoxDataStart - (debug ? 2 : 3)) >> 0) & 0xFF;
        payload_storage[offset++] = ((curr_rom.wBoxDataStart - (debug ? 2 : 3)) >> 8) & 0xFF;

        // ld bc, (wBoxDataEnd - wBoxDataStart) + 2
        payload_storage[offset++] = 0x01;
        payload_storage[offset++] = (((curr_rom.wBoxDataEnd - curr_rom.wBoxDataStart) + 2) >> 0) & 0xFF;
        payload_storage[offset++] = (((curr_rom.wBoxDataEnd - curr_rom.wBoxDataStart) + 2) >> 8) & 0xFF;

        // call Serial_ExchangeBytes [Send the box data]
        write_call(curr_rom.generation, payload_storage, offset, curr_rom.Serial_ExchangeBytes);

        // Recieve the Pokemon to remove
        // ld hl, hSerialConnectionStatus
        payload_storage[offset++] = 0x21;
        payload_storage[offset++] = (curr_rom.hSerialConnectionStatus >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.hSerialConnectionStatus >> 8) & 0xFF;

        // ld [hl], 0x01 [Make sure GB is the slave, master if debug]
        payload_storage[offset++] = 0x36;
        payload_storage[offset++] = (debug ? 0x02 : 0x01);

        // ld hl, 0xC613 [data to send, garbage data]
        payload_storage[offset++] = 0x21;
        payload_storage[offset++] = (curr_rom.garbageDataLocation >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.garbageDataLocation >> 8) & 0xFF;

        // ld de, 0xC651 [data to recieve]
        payload_storage[offset++] = 0x11;
        payload_storage[offset++] = (curr_rom.pkmnTransferArray >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.pkmnTransferArray >> 8) & 0xFF;

        // ld bc, 0x001E [size of data]
        payload_storage[offset++] = 0x01;
        payload_storage[offset++] = 0x1E;
        payload_storage[offset++] = 0x00;

        // call Serial_ExchangeBytes [Recieve the removal array]
        if (debug)
        {
            offset += 3; // Don't add in the Serial_ExchangeBytes call if in debug
        }
        else
        {
            write_call(curr_rom.generation, payload_storage, offset, curr_rom.Serial_ExchangeBytes);
        }

        // Remove the transfered Pokemon
        // ld hl, wRemoveMonFromBox
        payload_storage[offset++] = 0x21;
        payload_storage[offset++] = (curr_rom.wRemoveMonFromBox >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.wRemoveMonFromBox >> 8) & 0xFF;

        // ld [hl], [!= 0x00 specifies the current box]
        payload_storage[offset++] = 0x36;
        payload_storage[offset++] = 0x01;

        // LOOP BEGIN

        // ld a, [arrayCounter]
        payload_storage[offset++] = 0xFA;
        payload_storage[offset++] = (curr_rom.arrayCounter >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.arrayCounter >> 8) & 0xFF;

        // ld e, a
        payload_storage[offset++] = 0x5F;

        // ld d, 0x00
        payload_storage[offset++] = 0x16;
        payload_storage[offset++] = 0x00;

        // ld hl, [removalArray]
        payload_storage[offset++] = 0x21;
        payload_storage[offset++] = (curr_rom.pkmnTransferArray >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.pkmnTransferArray >> 8) & 0xFF;

        // add hl, de
        payload_storage[offset++] = 0x19;

        // inc a
        payload_storage[offset++] = 0x3C;

        // ld [arrayCounter], a
        payload_storage[offset++] = 0xEA;
        payload_storage[offset++] = (curr_rom.arrayCounter >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.arrayCounter >> 8) & 0xFF;

        // ld a, [wBoxCount]
        payload_storage[offset++] = 0xFA;
        payload_storage[offset++] = (curr_rom.wBoxCount >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.wBoxCount >> 8) & 0xFF;

        // ld b, a
        payload_storage[offset++] = 0x47;

        // ld a, [hl]
        payload_storage[offset++] = 0x2A;

        // cp a, 0xFF
        payload_storage[offset++] = 0xFE;
        payload_storage[offset++] = 0xFF;

        // jr z, 15
        payload_storage[offset++] = 0x28;
        payload_storage[offset++] = 0x0F;

        // cp a, b
        payload_storage[offset++] = 0xB8;

        // jr nc, -26
        payload_storage[offset++] = 0x30;
        payload_storage[offset++] = 0xE6;

        // ld hl, wWhichPokemon
        payload_storage[offset++] = 0x21;
        payload_storage[offset++] = (curr_rom.wWhichPokemon >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.wWhichPokemon >> 8) & 0xFF;

        // ld [hl], a
        payload_storage[offset++] = 0x77;

        // call TakePartyItem

        // call _RemovePokemon
        if (DONT_REMOVE_PKMN)
        {
            offset += 6;
        }
        else
        {
            // write_call(curr_rom.generation, payload_storage, offset, 0x046C60);
            write_call(curr_rom.generation, payload_storage, offset, curr_rom._RemovePokemon);
        }

        // jr, -38
        payload_storage[offset++] = 0x18;
        payload_storage[offset++] = 0xDA;
        // LOOP END

        // jp pkmn list (because saving the box overwrites the data)
        payload_storage[offset++] = 0xC3;
        payload_storage[offset++] = (curr_rom.jump_vector_location >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.jump_vector_location >> 8) & 0xFF;

        // 72 total bytes of string/array stuff

        // 1 byte to store the current array counter
        // $C650
        if (offset > (0x1DE + (194 - 72)))
        {
            std::cout << "# Error: Script exceeded by " << offset - (0x1DE + (194 - 72)) << " bytes!" << std::endl;
        }
        offset = (0x1DE + (194 - 72));
        payload_storage[offset++] = 0x00;

        // 40 byte storage for list of Pokemon to remove
        // $C651
        for (int i = 0; i < 40; i++)
        {
            if (debug)
            {
                payload_storage[offset++] = (i < 30 ? (29 - i) : 0xFF);
            }
            else
            {
                payload_storage[offset++] = (i < 30 ? 0xFD : 0xFF);
            }
        }

        // permanent array terminator, just in case
        // $C679
        payload_storage[offset++] = 0xFF;

        // TransferWaitString
        // $C67A
        for (int i = 0; i < 30; i++)
        {
            payload_storage[offset++] = curr_rom.transferString[i];
        }

        // This payload works by placing Pokemon ID 0xFC's name in the stack, and causing a return to CD8E,
        // which is part of the RNG seed. From there we can jump anywhere- and we choose to jump to D887,
        // which is the rival's name. This code fixes the stack and jumps to the patchlist, which is where
        // our final code is.
    }
    */
};

int main() // Rename to "main" to send the payload to test_payload.txt
{
    freopen("test_payload.txt", "w", stdout);
    std::cout << std::endl;
    byte *payload = generate_payload(ENG_YELLOW, TRANSFER, true);
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