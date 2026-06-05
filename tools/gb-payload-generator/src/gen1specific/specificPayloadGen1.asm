INCLUDE "include/macros/const.asm"
INCLUDE "include/macros/coords.asm"
INCLUDE "include/constants/serial_constants.asm"
INCLUDE "include/constants/charmap.asm"
INCLUDE "include/payload/payload.asm"
INCLUDE "include/payload/patches.asm"
INCLUDE "include/payload/settings.asm"

SECTION "Main", ROM0
Main:
	db 0xFD
LOAD "Payload", WRAM0[0xC700]
Payload:
.loopTransfer
	ld hl, 0xC5DC ; perfect place to store incoming packets. TODO: on first pass, this will interpret the generic payload as part of an incoming packet. Check if this interferes with anything.
.skipPreamble
	ld a, [hli]
	cp SERIAL_PREAMBLE_BYTE
	jr z, .skipPreamble ; standard sanity check. If current byte does not match preamble, then we've loaded the counter in register a.
	ld [0xC5DC], a
	push af
	ld a, [hli] ; load command byte
	ld b, [hl] ; load argument byte 1
	inc hl
	ld c, [hl] ; load argument byte 2
	inc hl
	push hl
	ld hl, .commandTable
	cp a, (.end - .commandTable) / 2 ; number of valid commands.
	call c, CallFunctionInTable ; if command not in table, send data to PTGB instead. Afterwards, request another packet from PTGB.
	pop hl ; hl should now point to the pointer that PTGB wants us to read data from.
	ld a, [hli]
	ld h, [hl]
	ld l, a
	ld de, 0xC5D3
	pop bc
	push de
	ld c, 1
.loop
	ld a, [hli]
	rra ; c flag is always 0 here, except if a failure state was detected in a command we ran this cycle. Failure state means 1st data byte > 0x80
	push af ; store new c flag for later
	inc de
	ld [de], a
	add a, b 
	ld b, a ; calculates checksum
	pop af
	ld a, c ; register c stores LSB bytes that were extracted using rra
	adc a, a ; shifts a left, then adds the current carry flag to a. If shifted for a total of 8 times, a will overflow and we escape the loop.
	ld c, a
	jr nc, .loop
	
	add a, b
	add a, h
	add a, l
	res 7, a ; ensure that the checksum is never equal to 0xFE
	inc de
	pop hl
	ld [hld], a
	ld a, c
	and 0x0F ; extract the lower nybble.
	ld [hld], a ; 4 LSB get stored here.
	xor c ; I love xor magic, this stores the higher nybble in a.
	ld [hld], a ; 4 MSB get stored here, hl now points to 0xC5D0, where the next packet will be sent from.
	ld a, [de] 
	ld [hl], a ; write counter
	ld c, PACKET_SIZE
	call .changeInterruptsAndCommunicate
	jr .loopTransfer
.changeInterruptsAndCommunicate
	ld b, 0
	call 0xC690 ; leftover from the universal payload, only allow serial interrupt and call Serial_ExchangeBytes
	ld a, IE_SERIAL | IE_TIMER | IE_VBLANK ; enable vblank interrupt so that a sound effect can play
	ldh [rIE], a
	ret
.commandTable
	dw ReloadCurrentBox
	dw TransferPokemon
	dw SoftReset
	dw ModifySRAMAccess
	dw RunSecondaryPayload
.end
VerifySecondaryPayload: ; checks if payload matches expected size and passes verification.
	ld c, b
	ld de, 0xC800
	ld hl, 0xC5D0
	push de
	call Payload.changeInterruptsAndCommunicate
	pop hl
	push hl
.skipPreambleAndFF
	ld a, [hli]
	inc a
	jr nz, .skipPreambleAndFF
	ld c, [hl] ; c now equals the size of the payload's data
	inc hl
	pop de
	push de
.checksumLoop	
	ld a, [hli]
	ld [de], a
	inc de
	add a, b
	ld b, a
	dec c
	jr nz, .checksumLoop ; calculates checksum and aligns payload at the same time
	pop hl
	and a
	ret z
	pop hl
	call ReplaceTextBox.writeCommunicating
	scf
	ret
ReloadCurrentBox:
	call ReplaceTextBox
	ld hl, LoadCurrentBoxData ; always resets carry flag at the end
.bankswitch
	ld b, LoadCurrentBoxDataBank
	jp Bankswitch ; preserves carry flag on return
TransferPokemon: ; possible usecase: use second argument byte to change box?
	ld a, c
	ld [wCurrentMenuItem], a
	push bc
	ld de, ReplaceTextBox.transferringText
	call ReplaceTextBox.writeOwnString
	ld hl, ChangeCurrentBox
	call ReloadCurrentBox.bankswitch
	pop bc
	call VerifySecondaryPayload
	inc a
	ld [wRemoveMonFromBox], a ; a non-zero value in this address indicates we'll be removing stuff from the current active box.
.removalLoop ; implementation of Gears' removal loop
	ld a, [hli]
	cp a, 0xFF
	jr z, .saveBox ; possible to optimize this jr out?
	push hl
	ld hl, wBoxCount
	cp a, [hl]
	ld [wWhichPokemon], a
	call nc, RemovePokemon ; funny thing here, RemovePokemon is located in bank 00 and just contains a jpfar to _RemovePokemon
	pop hl
	jr .removalLoop	
.saveBox
	ld hl, SaveCurrentBoxData ; resets carry flag
	call ReloadCurrentBox.bankswitch
	jr ReplaceTextBox.writeCommunicating
ModifySRAMAccess: ; opens SRAM bank to the bank described in argument byte 1.
	ld h, b
	ld [hl], h
	ld h, 0x40
	ld [hl], c
;	and a ; reset carry flag, should not be needed due to how CallFunctionInTable works
	ret
RunSecondaryPayload: ; loads new payload of size b, aligns it, verifies it, then executes it.
	call VerifySecondaryPayload
	jp hl
ReplaceTextBox:
	call ClearScreen
	hlcoord 2, 10
	ld bc, 1 << 8 | 14
	call CableClub_TextBoxBorder
.writeCommunicating
	ld de, .communicatingText
.writeOwnString
	hlcoord 3, 11
	jp PlaceString
.communicatingText:
	db "COMMUNICATING!@"
.transferringText:
	db "TRANSFERRING! @"
.end
ds 255 - (ReplaceTextBox.end - Payload), 0
ENDL
