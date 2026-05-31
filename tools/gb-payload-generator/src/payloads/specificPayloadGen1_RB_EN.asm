INCLUDE "../../include/constants/charmap.asm"
INCLUDE "../../include/macros/const.asm"
INCLUDE "../../include/constants/serial_constants.asm"
INCLUDE "../../include/constants/pokemon_constants.asm"
INCLUDE "../../include/constants/symbols.asm"
INCLUDE "../../include/constants/hardware.inc"
INCLUDE "../../include/payload/payload.asm"
INCLUDE "../../include/payload/patches.asm"
INCLUDE "../../include/payload/settings.asm"

DEF hSerialConnectionStatus EQU 0xFF02

DEF LoadCurrentBoxDataBank EQU 0x1C
DEF LoadCurrentBoxData EQU 0x7690

DEF BankSwitch EQU 0x35D6
DEF CallFunctionInTable EQU 0x3D97

DEF PACKET_SIZE = 0xC

DEF StopAllSounds = 0x200E
DEF TextCommandProcessor = 0x1B40

DEF wCurrentMenuItem = 0xCC26


SECTION "Main", ROM0
Main:
	db 0xFD
LOAD "Payload", WRAM0[0xC508]
Payload:
.loopTransfer
	ld hl, 0xC5DC ; perfect place to store incoming packets. TODO: on first pass, this will interpret the generic payload as part of an incoming packet. Check if this interferes with anything.
.skipPreamble
	res 7, [hl] ; if current pointer == 0xFD, change so that rra with carry flag doesn't create 0xFE. If command byte, this functionally does nothing.
	ld a, [hli]
	cp SERIAL_PREAMBLE_BYTE - 0x80
	jr z, .skipPreamble ; standard sanity check. If current byte does not match preamble, then we've loaded command byte 1 in register a.
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
	ld de, 0xC5D2 
	push de
	ld bc, 1
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
	
	add a, c
	add a, h
	add a, l
	res 7, a ; ensure that the checksum is never equal to 0xFE
	inc de
	ld [de], a ; load in the checksum
	inc de ; de now points to 0xC5DC, where the next packet will arrive.
	pop hl
	ld a, c
	and 0x0F ; extract the lower nybble.
	ld [hld], a ; 4 LSB get stored here.
	xor c ; I love xor magic, this stores the higher nybble in a.
	swap a
	ld [hld], a ; 4 MSB get stored here, hl now points to 0xC5D0, where the next packet will be sent from.
	ld [hl], SERIAL_PREAMBLE_BYTE
	
	ld bc, PACKET_SIZE
	call Serial_ExchangeBytes
	jr .loopTransfer
.commandTable
	dw ReloadCurrentBox
	dw TransferPokemon
	dw Start ; R/B don't have CGB specific logic, so reset without caring for register states.
	dw OpenSRAM
	dw CloseSRAM
	dw RunSecondaryPayload
.end
VerifySecondaryPayload: ; checks if payload matches expected size and passes verification.
	ld c, b
	ld b, 0
	ld de, 0xC610
	ld hl, 0xC5D0
	push de
	call Serial_ExchangeBytes
	pop hl
	push hl
.skipPreambleAndFF
	ld a, [hli]
	inc a
	jr z, .skipPreambleAndFF
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
	jr z, .checksumLoop
	pop hl
	and a
	ret z
	scf
	pop hl
	ret
ReloadCurrentBox:
	ld hl, LoadCurrentBoxData ; always resets carry flag at the end
.bankSwitch
	ld b, LoadCurrentBoxDataBank
	jp BankSwitch ; preserves carry flag on return
TransferPokemon: ; possible usecase: use second argument byte to change box?
	ld a, c
	ld [wCurrentMenuItem], a
	push bc
	ld a, 0xb ; enable vblank interrupt so that a sound effect can play
	ldh [rIE], a
	ld hl, 0x78CD
	call ReloadCurrentBox.bankSwitch
	ld a, 0x8
	ldh [rIE], a
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
	jr ReloadCurrentBox.bankSwitch
OpenSRAM: ; opens SRAM bank to the bank described in argument byte 1.
	ld h, 0xA
	ld [hl], h
	ld h, 0x40
	ld [hl], b
	and a ; reset carry flag
	ret
CloseSRAM:
	xor a ; reset carry flag
	ld h, a
	ld [hl], a
	ret
RunSecondaryPayload: ; loads new payload of size bc, aligns it, verifies it, then executes it.
	call VerifySecondaryPayload
	jp hl
ENDL
