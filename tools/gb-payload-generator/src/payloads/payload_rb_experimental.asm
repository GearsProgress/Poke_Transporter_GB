INCLUDE "../../include/constants/charmap.asm"
INCLUDE "../../include/constants/serial_constants.asm"
INCLUDE "../../include/constants/symbols.asm"
INCLUDE "../../include/payload/species.asm"
INCLUDE "../../include/payload/payload.asm"
INCLUDE "../../include/payload/patches.asm"
INCLUDE "../../include/payload/settings.asm"

SECTION "Universal payload non-JP R/B", ROM0

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

LOAD "serialPatch", WRAM0[wSerialEnemyMonsPatchList - 1]
SerialPatchPreamble:
	ds 5, SERIAL_PREAMBLE_BYTE
	ds 2, SERIAL_PATCH_LIST_PART_TERMINATOR
.end
SerialPatchList:
	ld bc, 0x0168
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
	ld bc, PRINTWAITINGTEXT_SEARCH
	call .findPointerAndPatch
.callPrintWaitingText
	call .callPrintWaitingText

	ld hl, SERIAL_EXCHANGEBYTES_OFFSET
	ld de, .callSerial_ExchangeBytes + 3
	ld bc, SERIAL_EXCHANGEBYTES_SEARCH
	call .findPointerAndPatch
.sendChecksum
	ld hl, 0x14E ; cartridge checksum
	ld a, [hli]
	ld b, [hl]
	
	ld hl, SerialPatchPreamble + 3 ; prepare to send cartridge checksum
	ld [hli], a
	ld [hl], b
	inc hl
	add a, b
	res 7, a
	ld [hl], a	; place checksum
	ld hl, SerialPatchPreamble + 2
	ld de, wSerialPartyMonsPatchList + 2
	push hl
	push hl
	push de
	ld bc, 0x5
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
	pop de
	ld c, 0xC0
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
	and a, a
	jr z, .sendChecksum
	inc a
	jp z, Start
	jp hl
.callSerial_ExchangeBytes
	ld a, 1
	jp .callSerial_ExchangeBytes
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