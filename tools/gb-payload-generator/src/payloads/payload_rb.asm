INCLUDE "../../include/constants/charmap.asm"
INCLUDE "../../include/constants/serial_constants.asm"
INCLUDE "../../include/constants/symbols.asm"
INCLUDE "../../include/payload/species.asm"
INCLUDE "../../include/payload/payload.asm"
INCLUDE "../../include/payload/patches.asm"
INCLUDE "../../include/payload/settings.asm"

DEF packetStartAddress = 0xCFE7
DEF packetSize = 8

SECTION "Payload", ROM0
Payload:
LOAD "RNGSeed", WRAM0[wSerialOtherGameboyRandomNumberListBlock - 1]
RNGSeed:
	ds 5
	jp SerialPatchList
.end
ds RNGSEED_SIZE - (RNGSeed.end - RNGSeed), 0
ENDL


LOAD "PartyData", WRAMX[wSerialEnemyDataBlock - 1]
PartyDataPreamble:
	ds 7, SERIAL_PREAMBLE_BYTE
.end

PartyData:
	db RIVAL_NAME
	ds 11 - STRLEN(RIVAL_NAME), CHARVAL("@")
.partyCount
	db 0x06
.partyList
	ds 0x160, shortMon
	db 0xFC
	db 0xFF
.transferList
	ds 30, SERIAL_PREAMBLE_BYTE
	ds 11, 0xFF
.end
ds PAYLOAD_SIZE - (PartyData.end - PartyDataPreamble), 0
ENDL

LOAD "serialPatch", WRAM0[wSerialEnemyMonsPatchList - 1]
SerialPatchPreamble:
	ds 5, SERIAL_PREAMBLE_BYTE
	ds 2, SERIAL_PATCH_LIST_PART_TERMINATOR
.end

SerialPatchList:
	call ClearScreen
	ld hl, wTileMap + 0x8F
	ld bc, (textBorderHeight  << 8) + textBorderWidth
	call CableClub_TextBoxBorder
	ld l, LOW(0x44)
	ld de, .waitString
	call PlaceString
	
.sendPacketLoop
	ld hl, 0xCFFD
	ld a, [hli]
	ld d, [hl]
	ld e, a
	ld hl, packetStartAddress
	ld c, 0
.packet_loop
	ld b, 0
	ld a, [de]
	add a, c
	ld c, a
	ld a, [de]
	inc de
	cp a, SERIAL_NO_DATA_BYTE
	jr nz, .feBypass
	dec a
	inc b
.feBypass
	ld [hli], a
	ld [hl], b
	inc hl
	ld a, LOW(packetStartAddress + 2 * packetSize)
	cp a, l
	jr nz, .packet_loop
	ld a, c
	res 7, a
	ld [hli], a
	ld a, d
	ld [hli], a
	ld a, e
	ld [hli], a
	
	ld a, 1
	ldh [0xFFAA], a
	ld hl, 0xCFE5
	ld [hl], SERIAL_PREAMBLE_BYTE
	inc hl
	ld [hl], 0
	dec hl
	ld de, 0xCFFA
	ld bc, 0x15
	call Serial_ExchangeBytes
	ld a, [0xCFFE]
	inc a
	jr nz, .sendPacketLoop
	
	inc a
	ldh [0xFFAA], a
	ld [wRemoveMonFromBox], a
	ld hl, 0x316
	ld de, PartyData.transferList
	ld bc, 0x1E
	call Serial_ExchangeBytes
	ld hl, PartyData.transferList
.removeArrayLoop
	ld a, [wBoxCount]
	ld b, a
	ld a, [hli]
	cp a, 0xFF
	jr z, .saveBox
	cp a, b
	jr nc, .removeArrayLoop
	
	ld [wWhichPokemon], a
	push hl
	call RemovePokemon
	pop hl
	jr .removeArrayLoop
.saveBox
	ld b, SaveCurrentBoxDataBank
	ld hl, SaveCurrentBoxData
	call Bankswitch
	jp SoftReset
.waitString
	db "SENDING DATA@"
.end
ds PATCHLIST_SIZE - (SerialPatchList.end - SerialPatchPreamble), 0
	