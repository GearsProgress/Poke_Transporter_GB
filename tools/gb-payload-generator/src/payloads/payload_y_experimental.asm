INCLUDE "../../include/constants/charmap.asm"
INCLUDE "../../include/constants/serial_constants.asm"
INCLUDE "../../include/constants/symbols.asm"
INCLUDE "../../include/constants/hardware.inc"
INCLUDE "../../include/payload/species.asm"
INCLUDE "../../include/payload/payload.asm"
INCLUDE "../../include/payload/patches.asm"
INCLUDE "../../include/payload/settings.asm"

SECTION "Universal payload non-JP Y", ROM0

; RNG Seed
; 10 Bytes
; Location of the entrance vector

LOAD "RNGSeed", WRAM0[wSerialOtherGameboyRandomNumberListBlock - 1]
RNGSeed:
	ds 5
	jp SerialPatchList
.end
ds RNGSEED_SIZE - (RNGSeed.end - RNGSeed), 0
ENDL

; Payload, consisting of preamble, rival name and actual party data

; Preamble (offset 0x00)
; 0x07 in length 
; must be filled with 0xFD, one 0xFD will be consumed and fail to transfer.

; Rival name (offset 0x07) 
; 0x0B in lenth
; Set to the stored name

; Party Data (offset 0x12)
; Can be up to 0x1A8 bytes in length.
; First byte determines number of pokémon (arbitrary value)
; Following values determine party data, the main part we care about is the pokémon list.
; Since we disrupt the stack with the party list, the party list itself does not need to be terminated.

LOAD "PAYLOAD", WRAMX[wSerialEnemyDataBlock - 1]
PartyPreamble:
	ds 7, SERIAL_PREAMBLE_BYTE
.end
RivalName:
	db RIVAL_NAME
	ds 11 - STRLEN(RIVAL_NAME), CHARVAL("@")
PartyData:
	db 0x06
.partyList
	ds 0x160, shortMon
	db pointerMon
.end
ds PAYLOAD_SIZE - (PartyData.end - PartyPreamble), 0
ENDL

; SerialPatchPreamble (offset 0x1B4)
; 0x07 in length
; Set as five 0xFD and two 0xFF, prevents patchlist from modifying anything on the party list.

; SerialPatchList (offset 0x1BB)
; At 0x1BB / 0x1DE, 0xC2 in length (0xC4, but the last 2 are unused)
; Fill with custom code

; FD FD FD FD FF FF 00 00 00 00 00 00 00 00 00 00
; 00 00 00 01 68 01 00 00 00 21 A0 C3 3E 7F 22 0B
; 78 B1 20 F8 21 ED 49 11 04 C6 00 00 00 01 6B 21
; CD 75 C6 CD 03 C6 21 F1 0B 11 71 C6 06 E0 00 00
; 00 0E AB CD 75 C6 21 4E 01 2A 46 21 D2 C5 22 70
; 23 F5 00 00 00 F1 80 CB BF 77 21 D1 C5 11 0A C5
; E5 E5 D5 01 05 00 00 00 00 CD 6E C6 D1 E1 01 FF
; 00 CD 6E C6 E1 23 E5 E5 0E C0 00 00 00 E5 D1 2A
; FE FD 28 FB 12 13 2A 0D C2 54 C6 E1 7E F5 00 00
; 00 F1 A7 28 B1 3C C0 F0 FE C6 10 C3 00 01 3E 01
; C3 6E C6 00 00 2A B8 20 FC 7E B9 20 F8 2B 7D 12
; 13 7C 12 C9

; FD FD 8C 84 96 FF|00 00 00 00 00 00 00 00 00 00
; 00 00 00[00]00 00 8C 84 96 00 00 00 00 00 00 00
; 00 00 00 00 00 00 00 00 00 00 8C 84 96 00 00 00
; 00 00 00 00 00 00 00 00 00 00 00 00 00 00 8C 84
; 96 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
; 00 00 8C 84 96 00 00 00 00 00 00 00 00 00 00 00
; 00 00 00 00 00 00 8C 84 96 00 00 00 00 00 00 00
; 00 00 00 00 00 00 00 00 00 00 8C 84 96 00 00 00
; 00 00 00 00 00 00 00 00 00 00 00 00 00 00 8C 84
; 96 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
; 00 00 8C 84 96 00 00 00 00 00 00 00 00 00 00 00
; 00 00 00 00 00 00 8C 84 96 00 00 00 00 00 00 00
; 00 00 00 00 00 00 00 00 19 19 8C 84 96 19 19 19

; 27 bytes lost -> adc h ; add h; sub a [hl]

LOAD "serialPatch", WRAM0[wSerialEnemyMonsPatchList - 1]
SerialPatchPreamble:
	ds 5, SERIAL_PREAMBLE_BYTE
	ds 2, SERIAL_PATCH_LIST_PART_TERMINATOR
.end
SerialPatchList:
	ds 13, 0 ; start from 0xC5E4
	ld bc, 0x0168
	ds 3, 0
	ld hl, 0xC3A0
.clearScreenLoop
	ld a, 0x7F
	ld [hli], a
	dec bc
	ld a, b
	or c
	jr nz, .clearScreenLoop
	ld hl, PRINTWAITINGTEXT_OFFSET
	ld de, .callPrintWaitingText + 1
	ds 3, 0
	ld bc, PRINTWAITINGTEXT_SEARCH
	call .findPointerAndPatch
.callPrintWaitingText
	call .callPrintWaitingText

	ld hl, SERIAL_EXCHANGEBYTES_OFFSET
	ld de, .callSerial_ExchangeBytes + 3
	ld b, HIGH(SERIAL_EXCHANGEBYTES_SEARCH)
	ds 3, 0
	ld c, LOW(SERIAL_EXCHANGEBYTES_SEARCH)
	call .findPointerAndPatch
.sendChecksum
	ld hl, 0x14E ; cartridge checksum
	ld a, [hli]
	ld b, [hl]
	
	ld hl, SerialPatchPreamble + 3 ; prepare to send cartridge checksum
	ld [hli], a
	ld [hl], b
	inc hl
	push af
	ds 3, 0
	pop af
	add a, b
	res 7, a
	ld [hl], a	; place checksum
	ld hl, SerialPatchPreamble + 2
	ld de, wSerialPartyMonsPatchList + 2
	push hl
	push hl
	push de
	ld bc, 0x5
	ds 3, 0
	call .callSerial_ExchangeBytes
	pop de
	pop hl
	ld bc, 0xFF ; placeholder, exact size to be determined
	call .callSerial_ExchangeBytes
	; to do: add verification that the payload is correctly processed
	pop hl
	inc hl
	push hl
	push hl
	ld c, 0xC0
	ds 3, 0
	push hl
	pop de
.findNotPreamble
	ld a, [hli]
	cp SERIAL_PREAMBLE_BYTE
	jr z, .findNotPreamble
.alignPayload
	ld [de], a
	inc de
	ld a, [hli]
	dec c
	jp nz, .alignPayload
	pop hl
	ld a, [hl]
	push af
	ds 3, 0
	pop af
	and a, a
	jr z, .sendChecksum
	inc a
	ret nz
	ldh a, [hOnCGB]
	add a, BOOTUP_A_CGB - 1
	jp Start
.callSerial_ExchangeBytes
	ld a, 1
	jp .callSerial_ExchangeBytes
	ds 2, 0 ; first byte of 3 gets overwritten by RAMPatch
.findPointerAndPatch
; b = first opcode to search for
; c = second opcode to search for
; de = address to write pointer to
; hl = offset to start searching from
; return destination pointer in hl, made to minimize amount of M-cycles taken
	ld a, [hli]
	cp b
	jr nz, .findPointerAndPatch
	ld a, [hl]
	cp c
	jr nz, .findPointerAndPatch
	dec hl
	ld a, l
	ld [de], a
	inc de
	ld a, h
	ld [de], a
	ret
.end
ds PATCHLIST_SIZE - (SerialPatchList.end - SerialPatchPreamble), 0
ENDL