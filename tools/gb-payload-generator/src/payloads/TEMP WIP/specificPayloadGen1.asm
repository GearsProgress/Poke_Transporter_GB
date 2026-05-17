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


SECTION "Main", ROM0
Main:
LOAD "Payload", WRAM0[0xC508]
Payload:
	ld b, LoadCurrentBoxDataBank
	ld hl, LoadCurrentBoxData
	call BankSwitch
.loopTransfer
	ld hl, 0xC6DC ; perfect place to store incoming packets. TODO: on first pass, this will interpret the generic payload as part of an incoming packet. Check if this interferes with anything.
.skipPreamble
	ld a, [hli]
	cp SERIAL_PREAMBLE_BYTE
	jr z, .skipPreamble ; standard sanity check
	ld [0xC6DC], a ; copy the first non-preamble byte to the very start of the received packet. This is to prevent a 0xFD from occupying the first byte, which is important in case we run into a command failure.
	push hl
	ld hl, .commandTable
	cp a, 4 ; PLACEHOLDER: LOOK INTO REPLACING WITH PROPER TABLE_SIZE DEFINITION
	call c, CallFunctionInTable ; if command not in table, send data to PTGB instead. Afterwards, request another packet from PTGB.
	pop hl ; hl should now point to the pointer that PTGB wants us to read data from.
	ld a, [hli]
	ld h, [hl]
	ld l, a
	ld de, 0xC6D2 
	push de
	inc bc ; Serial_ExchangeBytes exits with bc = 0x0000, and CallFunctionInTable preserves bc. With this inc, bc = 0x0001
	ld a, c
	ldh [hSerialConnectionStatus], a ; is this needed?
.loop
	ld a, [hli]
	rra ; c flag is always 0 here, except if a failure state was detected in a command we ran this cycle. Failure state means 1st data byte > 0x80
	push af ; store new c flag for later
	inc de
	ld [de], a
	add a, b 
	ld b, a ; calculates checksum
	pop af
	ld a, c ; stores LSB bytes that were extracted using rra
	adc a, a ; shifts a left, then adds the current carry flag to a. If shifted for a total of 8 times, a will overflow and we escape the loop.
	ld c, a
	jr nc, .loop
	
	add a, c
	add a, h
	add a, l
	res 7, a ; ensure that the checksum is never equal to 0xFE
	ld [de], a ; load in the checksum
	inc de ; de now points to 0xC6DC, where the next packet will arrive.
	
	pop hl
	ld a, c
	and 0x0F ; extract the lower nybble.
	ld [hld], a ; 4 LSB get stored here.
	xor c ; I love xor magic, this stores the higher nybble in a.
	swap a
	ld [hld], a ; 4 MSB get stored here, hl now points to 0xC6D0, where the next packet will be sent from.
	
	ld bc, PACKET_SIZE
	call Serial_ExchangeBytes
	jr .loopTransfer
.commandTable
	dw TransferPokemon
	dw Start ; R/B don't have CGB specific logic, so reset without caring for register states.
	dw OpenSRAM
	dw CloseSRAM
ReadAdditionalCommandByte: ; fetch the current command pointer within the stack, read the command byte at the current pointer, then increment the pointer. Only run this if we are executing a command and don't have additional stuff placed on the stack.
	ld hl, sp + 0x0C ; this should reset the carry flag, hl points to the part of the stack that points to directly after the current command byte.
	ld a, [hl] 
	inc [hl] ; since we are reading an additional command byte, increment the pointer.
	inc hl
	ld h, [hl]
	ld l, a
	ld a, [hl]
	ret ; hl contains a pointer to the next command byte, while a contains the current command byte.
TransferPokemon:
	ld hl, 0xC610
	ld d, h
	ld e, l
	push de
	push de
	ld bc, 0x1F
	call Serial_ExchangeBytes
	pop hl
.skipPreamble
	ld a, [hli]
	cp a, SERIAL_PREAMBLE_BYTE
	jr z, .skipPreamble
.checksumPacket
	add a, c ; due to Serial_ExchangeBytes, bc = 0000 when we enter
	ld c, a
	ld a, [hli]
	cp a, 0xFF
	jr nz, .checksumPacket

	ld a, c
	sub [hl] ; if the checksum matches, set z flag.
	scf ; in case the checksum, set the carry flag so we can communicate this failure state.
	ret nz 
	
	inc a
	ld [wRemoveMonFromBox], a ; a non-zer value in this address indicates we'll be removing stuff from the current active box.
.removalLoop
	pop hl
	ld a, [hli]
	cp a, 0xFF
	jr z, .saveBox
	push hl
	ld hl, wBoxCount
	cp a, [hl]
	ld [wWhichPokemon], a
	call nc, RemovePokemon
	jr .removalLoop	
.saveBox
	ld b, SaveCurrentBoxDataBank
	ld hl, SaveCurrentBoxData ; resets carry flag
	jp BankSwitch ; preserves flags
OpenSRAM: ; it is deeply funny that R/B do not have their own dedicated openSRAM or closeSRAM routines
	call ReadAdditionalCommandByte ; inelegant solution to the constraints of CallFunctionInTable
	ld h, 0xA
	ld [hl], h
	ld h, 0x40
	ld [hl], a
	ret
CloseSRAM:
	ld h, 0
	ld [hl], a
	ret
ENDL
