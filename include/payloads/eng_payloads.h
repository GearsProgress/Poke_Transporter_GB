#include <tonc.h>

#include "payloads/base_payload_struct.h"
#include "pokemon_data.h"

const struct PAYLOAD ENG_RED_BLUE = {
    .language = ENG_ID,
    .version = RED_BLUE_ID,
    .payload_array = {

        // RNG Seed
        0, 0, 0, 0, 0, 0xCD, 0x87, 0xD8, 184, 165,

        // Preamble
        253, 253, 253, 253, 253, 253, 253, 253,

        // Party (bootstrap)
        //// Rival name
        248, 0, 54, 253, 1, 62, 88, 197, 195, 214, 197,
        // num of Pokemon
        6,
        // Pokemon list
        0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 252, 0xE3, 0xE3, 255,
        // Code
        33, 160, 195, 1, 136, 1, 62, 0, 205, 224, 54, 17, 24, 218, 33, 89, 196, 205, 85, 25, 195, 21, 218, 139, 142, 128, 131, 136, 141, 134, 232, 232, 232, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 64, 0, 0,

        // Patchlist preamble
        253, 253, 253, 253, 253, 255, 255,

        // Patchlist (code storage)
        // Test string: 62, 99, 245, 33, 160, 195, 1, 136, 1, 205, 224, 54, 17, 255, 197, 33, 87, 196, 205, 85, 25, 118, 118, 118, 118, 118, 118, 118, 241, 60, 14, 108, 185, 194, 216, 197, 62, 99, 195, 216, 197, 127, 0x8E, 0x8C, 0x86, 127, 0x92, 0x8E, 0x91, 0x80, 0xE6, 0xE7, 0xE6, 0xE7, 127, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,

        // Write transferring message to screen
        // call ClearScreen
        0xCD, 0x0F, 0x19,
        // ld hl, $C42E
        0x21, 0x2E, 0xC4,
        // ld b, 3 [height]
        0x06, 0x03,
        // ld c, 14 [width]
        0x0E, 0x0E,
        // call CableClub_TextBoxBoarder
        0xCD, 0xB3, 0x5A,
        // ld hl, $C443
        0x21, 0x43, 0xC4,
        // ld de, TransferWaitString
        0x11, 0x7A, 0xC6,
        // call PlaceString
        0xCD, 0x55, 0x19,

        // Transfer box data
        // ld hl, hSerialConnectionStatus
        0x21, 0xAA, 0xFF,
        // ld [hl], 0x01 [Make sure GB is the slave]
        0x36, 0x01,
        // ld hl, (wBoxDataStart - 1) [data to send]
        0x21, 0x7F, 0xDA,
        // ld [hl], 0xFD [set the start of the data to 0xFD so Serial_ExchangeBytes is happy]
        0x36, 0xFD,
        // ld de, (wBoxDataStart - 3) [location to put stored data]
        0x11, 0x7D, 0xDA,
        // ld bc, (wBoxDataEnd - wBoxDataStart) + 2
        0x01, 0x64, 0x04,
        // call Serial_ExchangeBytes [Send the box data]
        0xCD, 0x6F, 0x21,

        // Recieve the Pokemon to remove
        // ld hl, hSerialConnectionStatus
        0x21, 0xAA, 0xFF,
        // ld [hl], 0x01 [Make sure GB is the slave]
        0x36, 0x01,
        // ld hl, 0xC613 [data to send, garbage data]
        0x21, 0x16, 0x03,
        // ld de, 0xC652 [data to recieve]
        0x11, 0x52, 0xC6,
        // ld bc, 0x001E [size of data]
        0x01, 0x27, 0x00,
        // call Serial_ExchangeBytes [Recieve the removal array]
        0xCD, 0x6F, 0x21,
        //0x00, 0x00, 0x00,

        // Remove the transfered Pokemon
        // ld hl, wRemoveMonFromBox
        0x21, 0x95, 0xCF,
        // ld [hl], [!= 0x00 specifies the current box]
        0x36, 0x01,
        // ld a, [arrayCounter]
        0xFA, 0x51, 0xC6,
        // ld e, a
        0x5F,
        // ld d, 0x00
        0x16, 0x00,
        // ld hl, [removalArray]
        0x21, 0x52, 0xC6,
        // add hl, de
        0x19,
        // inc a
        0x3C,
        // ld [arrayCounter], a
        0xEA, 0x51, 0xC6,
        // ld a, [wBoxCount]
        0xFA, 0x80, 0xDA,
        // ld b, a
        0x47,
        // ld a, [hl]
        0x2A,
        // cp a, 0xFF
        0xFE, 0xFF,
        // jr z, 12
        0x28, 0x0C,
        // cp a, b
        0xB8,
        // jr nc, -26
        0x30, 0xE6,
        // ld hl, wWhichPokemon
        0x21, 0x92, 0xCF,
        // ld [hl], a
        0x77,
        // call _RemovePokemon
        0xCD, 0x68, 0x7B,
        // jr, -35
        0x18, 0xDD,

        // Save the current box
        // ld hl, SaveSAVtoSRAM1
        0x21, 0xE2, 0x77,
        // ld b, 0x1C [memory bank of SaveSAVtoSRAM1]
        0x06, 0x1C,
        // call Bankswitch [which will jump to what's loaded in HL]
        0xCD, 0xD6, 0x35,
        // jp SoftReset
        0xC3, 0x49, 0x1F,

        // 1 byte to store the current array counter
        // $C651
        0x00,

        // 40 byte storage for list of Pokemon to remove
        // $C652
        0xFD, 0xFD, 0xFD, 0xFD, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
        0x13, 0x12, 0x11, 0x10, 0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A,
        0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

        // TransferWaitString
        // $C67A
        // TRANSFERRING..\n
        //  PLEASE WAIT!
        0x93, 0x91, 0x80, 0x8D, 0x92, 0x85, 0x84, 0x91, 0x91, 0x88, 0x8D, 0x86, 0xF2, 0xF2, 0x4E,
        0x7F, 0x8F, 0x8B, 0x84, 0x80, 0x92, 0x84, 0x7F, 0x96, 0x80, 0x88, 0x93, 0xE7, 0x7F, 0x50,

        // This payload works by placing Pokemon ID 0xFC's name in the stack, and causing a return to CD8E,
        // which is part of the RNG seed. From there we can jump anywhere- and we choose to jump to D887,
        // which is the rival's name. This code fixes the stack and jumps to the patchlist, which is where
        // our final code is.
    }};