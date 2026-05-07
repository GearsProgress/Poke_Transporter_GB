INCLUDE "../../include/constants/charmap.asm"
INCLUDE "../../include/macros/const.asm"
INCLUDE "../../include/constants/serial_constants.asm"
INCLUDE "../../include/constants/pokemon_constants.asm"
INCLUDE "../../include/constants/symbols.asm"
INCLUDE "../../include/constants/hardware.inc"
INCLUDE "../../include/payload/payload.asm"
INCLUDE "../../include/payload/patches.asm"
INCLUDE "../../include/payload/settings.asm"

SECTION "Payload", ROM0
Payload:
LOAD "RNGSeed", WRAM0[wSerialOtherGameboyRandomNumberListBlock - 1]
RNGSeed:
.end
ds RNGSIZE_GEN2 - (RNGSeed.end - RNGSeed) - 7, 0 ; 7 bytes of preamble that need to be deducted.
ENDL

PartyDataPreamble:
	ds 6, SERIAL_PREAMBLE_BYTE
.end

PartyData:
	db RIVAL_NAME
	ds 6 - STRLEN(RIVAL_NAME), '<NEXT>' ; This setup is universal, so take JP name size into account.
	ds 5, '<NEXT>' ; on JP, this becomes part of party data. On other versions, this becomes part of the name.
.partyCount
	db '<NEXT>'
.partyList
	ds 7, '<NEXT>'
.tid
	ds 2, '<NEXT>'
.partyData
	db 1
	db '<LINE>'
	ds 171, '<NEXT>'
	ds 34, 'A'
	dw SerialPatchListPayload + 0x100
	db '<NEXT>'
	ds 10, 'A'
	dw SerialPatchListPayload
	db 1
	db '@'
	db '<KOR_LINE>'
	ds 69, 	'<KOR_NEXT>'
	db '<KOR_LF>'
	ds 14, 'A'
	dw SerialPatchListKoreanPayload
	db '@'
.end
ds LINKDATASIZE_GEN2 - (PartyData.end - PartyDataPreamble), 0

LOAD "serialPatch", WRAM0[wSerialEnemyMonsPatchList_GS]
SerialPatchPreamble:
	ds 5, SERIAL_PREAMBLE_BYTE
	ds 2, SERIAL_PATCH_LIST_PART_TERMINATOR
.end

SerialPatchListKoreanPayload:
	ds 3, 0
	call ClearScreen_KOR ; KOR has some weirdness in how stuff is displayed. This function provides a full reset of the screen.
.end

SerialPatchListPayload: ; on GS: this gets loaded in 0xC5D0. On C: this gets loaded in 0xC6D0. Until we align, we can't rely on jp or call.
	ds 3, 0
	di
	call Bankswitch_GSC + 5 ; jump straight to a ret instruction.
.fetchPC
	dec sp
	dec sp
	pop hl ; since interrupts are disabled, we can retrieve the return pointer of the previous call, effectively retrieving a relative address.
	ei
	ld bc, wTileMap - .fetchPC
	push hl ; store relative address for later
	add hl, bc ; if GS: hl = 0xC3A0. If C: hl = 0xC4A0.
	ld bc, wSerialPartyMonsPatchList - wTileMap
.clearScreenLoop ; replace all tiles on screen with blank tiles.
	ld a, 0x7F
	ld [hli], a
	dec bc
	ld a, b
	or c
	jr nz, .clearScreenLoop
	ld bc, wMusicFadeID - wSerialPartyMonsPatchList
	add hl, bc ; if GS: hl = 0xC1A9. If C: hl = 0xC2A9.
	xor a
	ld [hld], a
	ld [hld], a
	inc a
	ld [hl], a ; This disables music from playing
	ld hl, PlaceWaitingText
	rst FarCall ; call 01:4000
	pop hl
	ld bc, .end - .fetchPC
	add hl, bc ; hl now points to the first byte of SerialPatchListAligned
	ld de, SerialPatchListAligned
	ld bc, SerialPatchListAligned.end - SerialPatchListAligned
	push de
.alignPayload ; copy remainder of payload to safer location, then jump towards it.
	ld a, [hli]
	ld [de], a
	inc de
	dec c
	ret z
	jr .alignPayload
.end
ENDL
LOAD "serialPatchAligned", WRAM0[SerialPatchAlignedAddress]
SerialPatchListAligned:
	ld a, HIGH(SerialPatchListPayload.end)
	sub a, h ; sneaky hack. If we're on GS, this will set the z flag, allowing us to easily determine which version we're running.
	push af
	ld hl, SerialInterrupt + 1 ; retrieve a pointer to Serial.
	ld a, [hli]
	ld h, [hl]
	ld l, a
	ld c, SerialOffset_GS ; if we're on GS, there is a 0x66 byte offset between Serial and Serial_ExchangeBytes.
	jr z, .done
	ld c, SerialOffset_C ; if we're on C, the offset is 0x70 bytes instead.
.done
	add hl, bc
	call .patchPointer
.sendChecksum
	ld hl, 0x14E ; locate cartridge checksum
	ld a, [hli]
	ld b, [hl]
	ld hl, SerialPatchPreamble + 0x102 ; prepare to send cartridge checksum
	ld [hli], a
	ld [hl], b
	inc hl
	add a, b
	res 7, a
	ld [hl], a	; place checksum
	ld l, LOW(SerialPatchPreamble) ; send checksum data from this address
	ld a, SERIAL_PREAMBLE_BYTE ; we can't be sure that the first two bytes contain a preamble, so manually add it.
	ld [hli], a
	ld [hld], a
	ld de, SpecificPayloadAddress ; receive payload at this address
	push hl
	push de
	ld bc, CHECKSUMPACKET_SIZE
	call .callSerial_ExchangeBytes ; send checksum to PTGB, bc = 0000 on exit
	pop de
	pop hl
	push de
	ld c, PATCHLIST_SIZE ; serial patch list size
	push bc
	call .callSerial_ExchangeBytes ; receive specific payload from PTGB
	pop bc
	pop hl
	push hl
	push hl
	pop de
.findNotPreamble ; we can't be sure if the payload arrived in the exact desired position. Because of this, let's align the payload.
	ld a, [hli]
	cp SERIAL_PREAMBLE_BYTE
	jr z, .findNotPreamble
.alignPayload ; now that we have found the first non-preamble value, let's align it properly.
	ld [de], a
	inc de
	dec c ; we're only aligning stuff within the 0xC500 space
	ld a, [hli]
	jr nz, .alignPayload
	pop hl
	ld a, [hl] ; check first non-preamble byte of payload. If 00, resend checksum (incorrect calculated checksum). If FF, an error has occured (correct calculated checksum, but the cartridge checksum is not recognized), so safely reset instead. If any other values, jump to new payload!
	and a, a
	jr z, .sendChecksum
	push hl ; What I wouldn't give for a conditional jp hl
	inc a
	ret nz
	pop af ; hCGB has a version-specific address, so retrieve the z flag we used earlier.
	ldh a, [hCGB_GS]
	jr z, .notCrystal
	ldh a, [hCGB_C]
.notCrystal
	add a, BOOTUP_A_CGB - 1
	rst NULL
.patchPointer ; searches for specific opcodes from a certain offset and places the resulting pointer at a specific location
; b = first opcode to search for
; c = second opcode to search for
; de = address to write pointer to
; hl = offset to start searching from
; return destination pointer in hl, made to minimize amount of M-cycles taken
	ld de, .callPatchedPointer + 1
	ld a, l
	ld [de], a
	inc de
	ld a, h
	ld [de], a
	ret
.callSerial_ExchangeBytes
	ld a, IE_SERIAL
	ldh [rIE], a
.callPatchedPointer
	jp .callPatchedPointer
.end
ds PATCHLIST_GEN2 - (SerialPatchListAligned.end - SerialPatchListAligned) - (SerialPatchListPayload.end - SerialPatchListPayload) - (SerialPatchListKoreanPayload.end - SerialPatchListKoreanPayload) - (SerialPatchPreamble.end - SerialPatchPreamble), 0
ENDL