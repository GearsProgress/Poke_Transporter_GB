#include "payload_builder.h"
#include "gb_rom_values/base_gb_rom_struct.h"
#include "gb_rom_values/eng_gb_rom_values.h"
#include "debug_mode.h"

#include <iostream>
#include <fstream>
#include <iomanip>

byte payload_storage[674] = {};

byte *generate_payload(GB_ROM curr_rom, bool debug)
{
    /*  10 RNG bytes
        8 Preamble bytes
        418 / 441 Party bytes
        7 Preamble bytes
        194 Patch list bytes (last 2 are unused)

        637 / 662 total bytes
        */

    // RNG Seed:
    // at 0x00, 0x0A in length
    // Does not need to be set

    // Preamble
    // At 0x0A, 0x08 in length
    // Must be filled with 0xFD
    for (int i = 0; i < 8; i++)
    {
        payload_storage[0x0A + i] = 0xFD;
    }

    // Rival name
    // At 0x12, 0x0B in length
    // Set to stored name
    for (int i = 0; i < 11; i++)
    {
        payload_storage[0x12 + i] = curr_rom.custom_name[i];
    }

    // Number of Pokemon
    // At 0x1D, 0x01 in length
    // Does not need to be set
    payload_storage[0x1D] = 0x06;

    // Pokemon list
    // At 0x1E, can be up to 0x1A2 / 0x1B9 bytes in length.
    // Calculate the number of Pokemon names that need to be printed,
    // and add them to the list. Then terminate the list.

    int distance = curr_rom.stack_overwrite_location - curr_rom.print_string_start;
    distance /= 20; // Automatically truncated, so it won't overshoot

    for (int i = 0; i < distance; i++)
    {
        payload_storage[0x1E + i] = curr_rom.short_pkmn_name;
    }
    payload_storage[0x1E + distance] = curr_rom.pointer_pkmn_name;
    payload_storage[0x1E + distance + 1] = 0xFF;

    // Patchlist preamble
    // At 0x1B4 / 0x1D7, 0x07 in length
    // Set as five 0xFD and two 0xFF
    for (int i = 0; i < 7; i++)
    {
        payload_storage[0x1B4 + i] = (i < 5 ? 0xFD : 0xFF);
    }

    // Set the entrance vector
    payload_storage[curr_rom.enter_vector_destination] = 0xC3;
    payload_storage[curr_rom.enter_vector_destination + 1] = curr_rom.enter_vector_location & 0xFF;
    payload_storage[curr_rom.enter_vector_destination + 2] = (curr_rom.enter_vector_location >> 8) & 0xFF;

    // Patchlist
    // At 0x1BB / 0x1DE, 0xC2 in length (0xC4, but the last 2 are unused)
    // Fill with custom code

    int offset = 0x1BB;

    /* Write transferring message to screen: */
    // call ClearScreen
    payload_storage[offset++] = 0xCD;
    payload_storage[offset++] = (curr_rom.clearScreen >> 0) & 0xFF;
    payload_storage[offset++] = (curr_rom.clearScreen >> 8) & 0xFF;

    // ld hl, [upper left textbox corner in VRAM]
    payload_storage[offset++] = 0x21;
    payload_storage[offset++] = (curr_rom.textBoarderUppLeft >> 0) & 0xFF;
    payload_storage[offset++] = (curr_rom.textBoarderUppLeft >> 8) & 0xFF;

    // ld b, 3 [height]
    payload_storage[offset++] = 0x06;
    payload_storage[offset++] = (curr_rom.textBoarderWidth >> 0) & 0xFF;

    // ld c, 14 [width]
    payload_storage[offset++] = 0x0E;
    payload_storage[offset++] = (curr_rom.textBoarderHeight >> 0) & 0xFF;

    // call CableClub_TextBoxBoarder
    payload_storage[offset++] = 0xCD;
    payload_storage[offset++] = (curr_rom.CableClub_TextBoxBoarder >> 0) & 0xFF;
    payload_storage[offset++] = (curr_rom.CableClub_TextBoxBoarder >> 8) & 0xFF;

    // ld hl, [transfer string location]
    payload_storage[offset++] = 0x21;
    payload_storage[offset++] = (curr_rom.transferStringLocation >> 0) & 0xFF;
    payload_storage[offset++] = (curr_rom.transferStringLocation >> 8) & 0xFF;

    // ld de, TransferWaitString
    payload_storage[offset++] = 0x11;
    payload_storage[offset++] = (curr_rom.transferWaitString >> 0) & 0xFF;
    payload_storage[offset++] = (curr_rom.transferWaitString >> 8) & 0xFF;

    // call PlaceString
    payload_storage[offset++] = 0xCD;
    payload_storage[offset++] = (curr_rom.placeString >> 0) & 0xFF;
    payload_storage[offset++] = (curr_rom.placeString >> 8) & 0xFF;

    /* Transfer box data: */
    // ld hl, hSerialConnectionStatus
    payload_storage[offset++] = 0x21;
    payload_storage[offset++] = (curr_rom.hSerialConnectionStatus >> 0) & 0xFF;
    payload_storage[offset++] = (curr_rom.hSerialConnectionStatus >> 8) & 0xFF;

    // ld [hl], 0x01 [Make sure GB is the slave, master if debug]
    payload_storage[offset++] = 0x36;
    payload_storage[offset++] = (debug ? 0x02 : 0x01);

    // ld hl, (wBoxDataStart - 1) [data to send]
    payload_storage[offset++] = 0x21;
    payload_storage[offset++] = ((curr_rom.wBoxDataStart - 1) >> 0) & 0xFF;
    payload_storage[offset++] = ((curr_rom.wBoxDataStart - 1) >> 8) & 0xFF;

    // ld [hl], 0xFD [set the start of the data to 0xFD so Serial_ExchangeBytes is happy]
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
    payload_storage[offset++] = 0xCD;
    payload_storage[offset++] = (curr_rom.Serial_ExchangeBytes >> 0) & 0xFF;
    payload_storage[offset++] = (curr_rom.Serial_ExchangeBytes >> 8) & 0xFF;

    /* Recieve the Pokemon to remove */
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

    // ld bc, 0x0028 [size of data]
    payload_storage[offset++] = 0x01;
    payload_storage[offset++] = 0x28;
    payload_storage[offset++] = 0x00;

    // call Serial_ExchangeBytes [Recieve the removal array]
    if (debug)
    {
        offset += 3; // Don't add in the Serial_ExchangeBytes call if in debug
    }
    else
    {
        payload_storage[offset++] = 0xCD;
        payload_storage[offset++] = (curr_rom.Serial_ExchangeBytes >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom.Serial_ExchangeBytes >> 8) & 0xFF;
    }

    /* Remove the transfered Pokemon */
    // ld hl, wRemoveMonFromBox
    payload_storage[offset++] = 0x21;
    payload_storage[offset++] = (curr_rom.wRemoveMonFromBox >> 0) & 0xFF;
    payload_storage[offset++] = (curr_rom.wRemoveMonFromBox >> 8) & 0xFF;

    // ld [hl], [!= 0x00 specifies the current box]
    payload_storage[offset++] = 0x36;
    payload_storage[offset++] = 0x01;

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

    // jr z, 12
    payload_storage[offset++] = 0x28;
    payload_storage[offset++] = 0x0C;

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
    // call _RemovePokemon
    if (DONT_REMOVE_PKMN)
    {
        offset += 3;
    }
    else
    {
        payload_storage[offset++] = 0xCD;
        payload_storage[offset++] = (curr_rom._RemovePokemon >> 0) & 0xFF;
        payload_storage[offset++] = (curr_rom._RemovePokemon >> 8) & 0xFF;
    }

    // jr, -35
    payload_storage[offset++] = 0x18;
    payload_storage[offset++] = 0xDD;

    /* Save the current box */
    // ld hl, SaveSAVtoSRAM1
    payload_storage[offset++] = 0x21;
    payload_storage[offset++] = (curr_rom.SaveSAVtoSRAM1 >> 0) & 0xFF;
    payload_storage[offset++] = (curr_rom.SaveSAVtoSRAM1 >> 8) & 0xFF;

    // ld b, 0x1C [memory bank of SaveSAVtoSRAM1]
    payload_storage[offset++] = 0x06;
    payload_storage[offset++] = (curr_rom.SaveSAVtoSRAM1_memBank >> 0) & 0xFF;

    // call Bankswitch [which will jump to what's loaded in HL]
    payload_storage[offset++] = 0xCD;
    payload_storage[offset++] = (curr_rom.Bankswitch >> 0) & 0xFF;
    payload_storage[offset++] = (curr_rom.Bankswitch >> 8) & 0xFF;

    // jp SoftReset
    payload_storage[offset++] = 0xC3;
    payload_storage[offset++] = (curr_rom.SoftReset >> 0) & 0xFF;
    payload_storage[offset++] = (curr_rom.SoftReset >> 8) & 0xFF;

    // 1 byte to store the current array counter
    // $C650
    offset = 0x1BB + (0xC650 - curr_rom.enter_vector_location);
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

    return payload_storage;
};

int main()
{
    freopen("test_payload.txt", "w", stdout);
    std::cout << std::endl;
    byte *payload = generate_payload(ENG_RED_BLUE, true);
    for (int i = 0; i < 637; i++)
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