#ifndef MYSTERY_GIFT_BUILDER_H
#define MYSTERY_GIFT_BUILDER_H

#include <tonc.h>
#include <string>
#include <map>
#include <vector>
#include "pokemon_party.h"
#include "debug_mode.h"
#include "save_data_manager.h"
#include "script_var.h"
#include "pokemon_data.h"

#define VIR_ADDRESS 0x08000000
#define MG_SCRIPT_SIZE 0x3E8
#define NPC_LOCATION_OFFSET 0x4
#define READ_AS_THUMB 0x1

#define VAR_ID_START 0x8000        // This one should also stay consistant
#define VIRTUAL_ADDRESS 0x08000000 // This will also stay constant

#define TEXT_KANTO 0
#define TEXT_HOENN 1

#define COND_LESSTHAN 0
#define COND_EQUALS 1
#define COND_GREATERTHAN 2
#define COND_LESSEQUALTHAN 3
#define COND_GREATEREQUALTHAN 4
#define COND_NOTEQUAL 5
#define COND_FLAGTRUE 1
#define COND_FLAGFALSE 5

#define r0 0b0000
#define r1 0b0001
#define r2 0b0010
#define r3 0b0011
#define r4 0b0100
#define r5 0b0101
#define r6 0b0110
#define r7 0b0111
#define r8 0b1000
#define r9 0b1001
#define r10 0b1010
#define r11 0b1011
#define r12 0b1100
#define r13 0b1101
#define r14 0b1110
#define r15 0b1111

#define rlist_r0 0b000000001
#define rlist_r1 0b000000010
#define rlist_r2 0b000000101
#define rlist_r3 0b000001001
#define rlist_r4 0b000010001
#define rlist_r5 0b000100001
#define rlist_r6 0b001000001
#define rlist_r7 0b010000001
#define rlist_lr 0b100000000

#define MOVEMENT_ACTION_FACE_DOWN curr_rom.is_hoenn() ? 0x0 : 0x0
#define MOVEMENT_ACTION_FACE_UP curr_rom.is_hoenn() ? 0x1 : 0x1
#define MOVEMENT_ACTION_FACE_LEFT curr_rom.is_hoenn() ? 0x2 : 0x2
#define MOVEMENT_ACTION_FACE_RIGHT curr_rom.is_hoenn() ? 0x3 : 0x3
#define MOVEMENT_ACTION_WALK_SLOW_DOWN curr_rom.is_hoenn() ? 0x4 : 0xC
#define MOVEMENT_ACTION_WALK_SLOW_UP curr_rom.is_hoenn() ? 0x5 : 0xD
#define MOVEMENT_ACTION_WALK_SLOW_LEFT curr_rom.is_hoenn() ? 0x6 : 0xE
#define MOVEMENT_ACTION_WALK_SLOW_RIGHT curr_rom.is_hoenn() ? 0x7 : 0xF
#define MOVEMENT_ACTION_WALK_NORMAL_DOWN curr_rom.is_hoenn() ? 0x8 : 0x10
#define MOVEMENT_ACTION_WALK_NORMAL_UP curr_rom.is_hoenn() ? 0x9 : 0x11
#define MOVEMENT_ACTION_WALK_NORMAL_LEFT curr_rom.is_hoenn() ? 0xA : 0x12
#define MOVEMENT_ACTION_WALK_NORMAL_RIGHT curr_rom.is_hoenn() ? 0xB : 0x13
#define MOVEMENT_ACTION_JUMP_2_DOWN curr_rom.is_hoenn() ? 0xC : 0x14
#define MOVEMENT_ACTION_JUMP_2_UP curr_rom.is_hoenn() ? 0xD : 0x15
#define MOVEMENT_ACTION_JUMP_2_LEFT curr_rom.is_hoenn() ? 0xE : 0x16
#define MOVEMENT_ACTION_JUMP_2_RIGHT curr_rom.is_hoenn() ? 0xF : 0x17
#define MOVEMENT_ACTION_DELAY_1 curr_rom.is_hoenn() ? 0x10 : 0x18
#define MOVEMENT_ACTION_DELAY_2 curr_rom.is_hoenn() ? 0x11 : 0x19
#define MOVEMENT_ACTION_DELAY_4 curr_rom.is_hoenn() ? 0x12 : 0x1A
#define MOVEMENT_ACTION_DELAY_8 curr_rom.is_hoenn() ? 0x13 : 0x1B
#define MOVEMENT_ACTION_DELAY_16 curr_rom.is_hoenn() ? 0x14 : 0x1C
#define MOVEMENT_ACTION_WALK_FAST_DOWN curr_rom.is_hoenn() ? 0x15 : 0x1D
#define MOVEMENT_ACTION_WALK_FAST_UP curr_rom.is_hoenn() ? 0x16 : 0x1E
#define MOVEMENT_ACTION_WALK_FAST_LEFT curr_rom.is_hoenn() ? 0x17 : 0x1F
#define MOVEMENT_ACTION_WALK_FAST_RIGHT curr_rom.is_hoenn() ? 0x18 : 0x20
#define MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_DOWN curr_rom.is_hoenn() ? 0x19 : 0x21
#define MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_UP curr_rom.is_hoenn() ? 0x1A : 0x22
#define MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_LEFT curr_rom.is_hoenn() ? 0x1B : 0x23
#define MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_RIGHT curr_rom.is_hoenn() ? 0x1C : 0x24
#define MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_DOWN curr_rom.is_hoenn() ? 0x1D : 0x25
#define MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_UP curr_rom.is_hoenn() ? 0x1E : 0x26
#define MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_LEFT curr_rom.is_hoenn() ? 0x1F : 0x27
#define MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_RIGHT curr_rom.is_hoenn() ? 0x20 : 0x28
#define MOVEMENT_ACTION_WALK_IN_PLACE_FAST_DOWN curr_rom.is_hoenn() ? 0x21 : 0x29
#define MOVEMENT_ACTION_WALK_IN_PLACE_FAST_UP curr_rom.is_hoenn() ? 0x22 : 0x2A
#define MOVEMENT_ACTION_WALK_IN_PLACE_FAST_LEFT curr_rom.is_hoenn() ? 0x23 : 0x2B
#define MOVEMENT_ACTION_WALK_IN_PLACE_FAST_RIGHT curr_rom.is_hoenn() ? 0x24 : 0x2C
#define MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_DOWN curr_rom.is_hoenn() ? 0x25 : 0x2D
#define MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_UP curr_rom.is_hoenn() ? 0x26 : 0x2E
#define MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_LEFT curr_rom.is_hoenn() ? 0x27 : 0x2F
#define MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_RIGHT curr_rom.is_hoenn() ? 0x28 : 0x30
#define MOVEMENT_ACTION_RIDE_WATER_CURRENT_DOWN curr_rom.is_hoenn() ? 0x29 : 0x31
#define MOVEMENT_ACTION_RIDE_WATER_CURRENT_UP curr_rom.is_hoenn() ? 0x2A : 0x32
#define MOVEMENT_ACTION_RIDE_WATER_CURRENT_LEFT curr_rom.is_hoenn() ? 0x2B : 0x33
#define MOVEMENT_ACTION_RIDE_WATER_CURRENT_RIGHT curr_rom.is_hoenn() ? 0x2C : 0x34
#define MOVEMENT_ACTION_WALK_FASTER_DOWN curr_rom.is_hoenn() ? 0x2D : 0x35
#define MOVEMENT_ACTION_WALK_FASTER_UP curr_rom.is_hoenn() ? 0x2E : 0x36
#define MOVEMENT_ACTION_WALK_FASTER_LEFT curr_rom.is_hoenn() ? 0x2F : 0x37
#define MOVEMENT_ACTION_WALK_FASTER_RIGHT curr_rom.is_hoenn() ? 0x30 : 0x38
#define MOVEMENT_ACTION_SLIDE_DOWN curr_rom.is_hoenn() ? 0x31 : 0x39
#define MOVEMENT_ACTION_SLIDE_UP curr_rom.is_hoenn() ? 0x32 : 0x3A
#define MOVEMENT_ACTION_SLIDE_LEFT curr_rom.is_hoenn() ? 0x33 : 0x3B
#define MOVEMENT_ACTION_SLIDE_RIGHT curr_rom.is_hoenn() ? 0x34 : 0x3C
#define MOVEMENT_ACTION_PLAYER_RUN_DOWN curr_rom.is_hoenn() ? 0x35 : 0x3D
#define MOVEMENT_ACTION_PLAYER_RUN_UP curr_rom.is_hoenn() ? 0x36 : 0x3E
#define MOVEMENT_ACTION_PLAYER_RUN_LEFT curr_rom.is_hoenn() ? 0x37 : 0x3F
#define MOVEMENT_ACTION_PLAYER_RUN_RIGHT curr_rom.is_hoenn() ? 0x38 : 0x40
#define MOVEMENT_ACTION_START_ANIM_IN_DIRECTION curr_rom.is_hoenn() ? 0x39 : 0x45
#define MOVEMENT_ACTION_JUMP_SPECIAL_DOWN curr_rom.is_hoenn() ? 0x3A : 0x46
#define MOVEMENT_ACTION_JUMP_SPECIAL_UP curr_rom.is_hoenn() ? 0x3B : 0x47
#define MOVEMENT_ACTION_JUMP_SPECIAL_LEFT curr_rom.is_hoenn() ? 0x3C : 0x48
#define MOVEMENT_ACTION_JUMP_SPECIAL_RIGHT curr_rom.is_hoenn() ? 0x3D : 0x49
#define MOVEMENT_ACTION_FACE_PLAYER curr_rom.is_hoenn() ? 0x3E : 0x4A
#define MOVEMENT_ACTION_FACE_AWAY_PLAYER curr_rom.is_hoenn() ? 0x3F : 0x4B
#define MOVEMENT_ACTION_LOCK_FACING_DIRECTION curr_rom.is_hoenn() ? 0x40 : 0x4C
#define MOVEMENT_ACTION_UNLOCK_FACING_DIRECTION curr_rom.is_hoenn() ? 0x41 : 0x4D
#define MOVEMENT_ACTION_JUMP_DOWN curr_rom.is_hoenn() ? 0x42 : 0x4E
#define MOVEMENT_ACTION_JUMP_UP curr_rom.is_hoenn() ? 0x43 : 0x4F
#define MOVEMENT_ACTION_JUMP_LEFT curr_rom.is_hoenn() ? 0x44 : 0x50
#define MOVEMENT_ACTION_JUMP_RIGHT curr_rom.is_hoenn() ? 0x45 : 0x51
#define MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN curr_rom.is_hoenn() ? 0x46 : 0x52
#define MOVEMENT_ACTION_JUMP_IN_PLACE_UP curr_rom.is_hoenn() ? 0x47 : 0x53
#define MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT curr_rom.is_hoenn() ? 0x48 : 0x54
#define MOVEMENT_ACTION_JUMP_IN_PLACE_RIGHT curr_rom.is_hoenn() ? 0x49 : 0x55
#define MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN_UP curr_rom.is_hoenn() ? 0x4A : 0x56
#define MOVEMENT_ACTION_JUMP_IN_PLACE_UP_DOWN curr_rom.is_hoenn() ? 0x4B : 0x57
#define MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT_RIGHT curr_rom.is_hoenn() ? 0x4C : 0x58
#define MOVEMENT_ACTION_JUMP_IN_PLACE_RIGHT_LEFT curr_rom.is_hoenn() ? 0x4D : 0x59
#define MOVEMENT_ACTION_FACE_ORIGINAL_DIRECTION curr_rom.is_hoenn() ? 0x4E : 0x5A
#define MOVEMENT_ACTION_NURSE_JOY_BOW_DOWN curr_rom.is_hoenn() ? 0x4F : 0x5B
#define MOVEMENT_ACTION_ENABLE_JUMP_LANDING_GROUND_EFFECT curr_rom.is_hoenn() ? 0x50 : 0x5C
#define MOVEMENT_ACTION_DISABLE_JUMP_LANDING_GROUND_EFFECT curr_rom.is_hoenn() ? 0x51 : 0x5D
#define MOVEMENT_ACTION_DISABLE_ANIMATION curr_rom.is_hoenn() ? 0x52 : 0x5E
#define MOVEMENT_ACTION_RESTORE_ANIMATION curr_rom.is_hoenn() ? 0x53 : 0x5F
#define MOVEMENT_ACTION_SET_INVISIBLE curr_rom.is_hoenn() ? 0x54 : 0x60
#define MOVEMENT_ACTION_SET_VISIBLE curr_rom.is_hoenn() ? 0x55 : 0x61
#define MOVEMENT_ACTION_EMOTE_EXCLAMATION_MARK curr_rom.is_hoenn() ? 0x56 : 0x62
#define MOVEMENT_ACTION_EMOTE_QUESTION_MARK curr_rom.is_hoenn() ? 0x57 : 0x63
#define MOVEMENT_ACTION_EMOTE_HEART curr_rom.is_hoenn() ? 0x58 : 0xFF
#define MOVEMENT_ACTION_REVEAL_TRAINER curr_rom.is_hoenn() ? 0x59 : 0x67
#define MOVEMENT_ACTION_ROCK_SMASH_BREAK curr_rom.is_hoenn() ? 0x5A : 0x68
#define MOVEMENT_ACTION_CUT_TREE curr_rom.is_hoenn() ? 0x5B : 0x69
#define MOVEMENT_ACTION_SET_FIXED_PRIORITY curr_rom.is_hoenn() ? 0x5C : 0x6A
#define MOVEMENT_ACTION_CLEAR_FIXED_PRIORITY curr_rom.is_hoenn() ? 0x5D : 0x6B
#define MOVEMENT_ACTION_INIT_AFFINE_ANIM curr_rom.is_hoenn() ? 0x5E : 0x6C
#define MOVEMENT_ACTION_CLEAR_AFFINE_ANIM curr_rom.is_hoenn() ? 0x5F : 0x6D
#define MOVEMENT_ACTION_HIDE_REFLECTION curr_rom.is_hoenn() ? 0x60 : 0xFF
#define MOVEMENT_ACTION_SHOW_REFLECTION curr_rom.is_hoenn() ? 0x61 : 0xFF
#define MOVEMENT_ACTION_WALK_DOWN_START_AFFINE curr_rom.is_hoenn() ? 0x62 : 0x6E
#define MOVEMENT_ACTION_WALK_DOWN_AFFINE curr_rom.is_hoenn() ? 0x63 : 0x6F
#define MOVEMENT_ACTION_ACRO_WHEELIE_FACE_DOWN curr_rom.is_hoenn() ? 0x64 : 0x70
#define MOVEMENT_ACTION_ACRO_WHEELIE_FACE_UP curr_rom.is_hoenn() ? 0x65 : 0x71
#define MOVEMENT_ACTION_ACRO_WHEELIE_FACE_LEFT curr_rom.is_hoenn() ? 0x66 : 0x72
#define MOVEMENT_ACTION_ACRO_WHEELIE_FACE_RIGHT curr_rom.is_hoenn() ? 0x67 : 0x73
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_DOWN curr_rom.is_hoenn() ? 0x68 : 0x74
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_UP curr_rom.is_hoenn() ? 0x69 : 0x75
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_LEFT curr_rom.is_hoenn() ? 0x6A : 0x76
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_RIGHT curr_rom.is_hoenn() ? 0x6B : 0x77
#define MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_DOWN curr_rom.is_hoenn() ? 0x6C : 0x78
#define MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_UP curr_rom.is_hoenn() ? 0x6D : 0x79
#define MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_LEFT curr_rom.is_hoenn() ? 0x6E : 0x7A
#define MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_RIGHT curr_rom.is_hoenn() ? 0x6F : 0x7B
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_DOWN curr_rom.is_hoenn() ? 0x70 : 0x7C
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_UP curr_rom.is_hoenn() ? 0x71 : 0x7D
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_LEFT curr_rom.is_hoenn() ? 0x72 : 0x7E
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_RIGHT curr_rom.is_hoenn() ? 0x73 : 0x7F
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_DOWN curr_rom.is_hoenn() ? 0x74 : 0x80
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_UP curr_rom.is_hoenn() ? 0x75 : 0x81
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_LEFT curr_rom.is_hoenn() ? 0x76 : 0x82
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_RIGHT curr_rom.is_hoenn() ? 0x77 : 0x83
#define MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_DOWN curr_rom.is_hoenn() ? 0x78 : 0x84
#define MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_UP curr_rom.is_hoenn() ? 0x79 : 0x85
#define MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_LEFT curr_rom.is_hoenn() ? 0x7A : 0x86
#define MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_RIGHT curr_rom.is_hoenn() ? 0x7B : 0x87
#define MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_DOWN curr_rom.is_hoenn() ? 0x7C : 0x88
#define MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_UP curr_rom.is_hoenn() ? 0x7D : 0x89
#define MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_LEFT curr_rom.is_hoenn() ? 0x7E : 0x8A
#define MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_RIGHT curr_rom.is_hoenn() ? 0x7F : 0x8B
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_DOWN curr_rom.is_hoenn() ? 0x80 : 0x8C
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_UP curr_rom.is_hoenn() ? 0x81 : 0x8D
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_LEFT curr_rom.is_hoenn() ? 0x82 : 0x8E
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_RIGHT curr_rom.is_hoenn() ? 0x83 : 0x8F
#define MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_DOWN curr_rom.is_hoenn() ? 0x84 : 0x90
#define MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_UP curr_rom.is_hoenn() ? 0x85 : 0x91
#define MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_LEFT curr_rom.is_hoenn() ? 0x86 : 0x92
#define MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_RIGHT curr_rom.is_hoenn() ? 0x87 : 0x93
#define MOVEMENT_ACTION_ACRO_END_WHEELIE_MOVE_DOWN curr_rom.is_hoenn() ? 0x88 : 0xFF
#define MOVEMENT_ACTION_ACRO_END_WHEELIE_MOVE_UP curr_rom.is_hoenn() ? 0x89 : 0xFF
#define MOVEMENT_ACTION_ACRO_END_WHEELIE_MOVE_LEFT curr_rom.is_hoenn() ? 0x8A : 0xFF
#define MOVEMENT_ACTION_ACRO_END_WHEELIE_MOVE_RIGHT curr_rom.is_hoenn() ? 0x8B : 0xFF
#define MOVEMENT_ACTION_WALK_NORMAL_DIAGONAL_UP_LEFT curr_rom.is_hoenn() ? 0x8C : 0xFF
#define MOVEMENT_ACTION_WALK_NORMAL_DIAGONAL_UP_RIGHT curr_rom.is_hoenn() ? 0x8D : 0xFF
#define MOVEMENT_ACTION_WALK_NORMAL_DIAGONAL_DOWN_LEFT curr_rom.is_hoenn() ? 0x8E : 0xFF
#define MOVEMENT_ACTION_WALK_NORMAL_DIAGONAL_DOWN_RIGHT curr_rom.is_hoenn() ? 0x8F : 0xFF
#define MOVEMENT_ACTION_WALK_SLOW_DIAGONAL_UP_LEFT curr_rom.is_hoenn() ? 0x90 : 0xFF
#define MOVEMENT_ACTION_WALK_SLOW_DIAGONAL_UP_RIGHT curr_rom.is_hoenn() ? 0x91 : 0xFF
#define MOVEMENT_ACTION_WALK_SLOW_DIAGONAL_DOWN_LEFT curr_rom.is_hoenn() ? 0x92 : 0xFF
#define MOVEMENT_ACTION_WALK_SLOW_DIAGONAL_DOWN_RIGHT curr_rom.is_hoenn() ? 0x93 : 0xFF
#define MOVEMENT_ACTION_LOCK_ANIM curr_rom.is_hoenn() ? 0x94 : 0xFF
#define MOVEMENT_ACTION_UNLOCK_ANIM curr_rom.is_hoenn() ? 0x95 : 0xFF
#define MOVEMENT_ACTION_WALK_LEFT_AFFINE curr_rom.is_hoenn() ? 0x96 : 0xFF
#define MOVEMENT_ACTION_WALK_RIGHT_AFFINE curr_rom.is_hoenn() ? 0x97 : 0xFF
#define MOVEMENT_ACTION_LEVITATE curr_rom.is_hoenn() ? 0x98 : 0xFF
#define MOVEMENT_ACTION_STOP_LEVITATE curr_rom.is_hoenn() ? 0x99 : 0xFF
#define MOVEMENT_ACTION_STOP_LEVITATE_AT_TOP curr_rom.is_hoenn() ? 0x9A : 0xFF
#define MOVEMENT_ACTION_FIGURE_8 curr_rom.is_hoenn() ? 0x9B : 0xFF
#define MOVEMENT_ACTION_FLY_UP curr_rom.is_hoenn() ? 0x9C : 0xA4
#define MOVEMENT_ACTION_FLY_DOWN curr_rom.is_hoenn() ? 0x9D : 0xA5
#define MOVEMENT_ACTION_FACE_DOWN_FAST curr_rom.is_hoenn() ? 0xFF : 0x4
#define MOVEMENT_ACTION_FACE_UP_FAST curr_rom.is_hoenn() ? 0xFF : 0x5
#define MOVEMENT_ACTION_FACE_LEFT_FAST curr_rom.is_hoenn() ? 0xFF : 0x6
#define MOVEMENT_ACTION_FACE_RIGHT_FAST curr_rom.is_hoenn() ? 0xFF : 0x7
#define MOVEMENT_ACTION_WALK_SLOWER_DOWN curr_rom.is_hoenn() ? 0xFF : 0x8
#define MOVEMENT_ACTION_WALK_SLOWER_UP curr_rom.is_hoenn() ? 0xFF : 0x9
#define MOVEMENT_ACTION_WALK_SLOWER_LEFT curr_rom.is_hoenn() ? 0xFF : 0xA
#define MOVEMENT_ACTION_WALK_SLOWER_RIGHT curr_rom.is_hoenn() ? 0xFF : 0xB
#define MOVEMENT_ACTION_PLAYER_RUN_DOWN_SLOW curr_rom.is_hoenn() ? 0xFF : 0x41
#define MOVEMENT_ACTION_PLAYER_RUN_UP_SLOW curr_rom.is_hoenn() ? 0xFF : 0x42
#define MOVEMENT_ACTION_PLAYER_RUN_LEFT_SLOW curr_rom.is_hoenn() ? 0xFF : 0x43
#define MOVEMENT_ACTION_PLAYER_RUN_RIGHT_SLOW curr_rom.is_hoenn() ? 0xFF : 0x44
#define MOVEMENT_ACTION_EMOTE_X curr_rom.is_hoenn() ? 0xFF : 0x64
#define MOVEMENT_ACTION_EMOTE_DOUBLE_EXCL_MARK curr_rom.is_hoenn() ? 0xFF : 0x65
#define MOVEMENT_ACTION_EMOTE_SMILE curr_rom.is_hoenn() ? 0xFF : 0x66
#define MOVEMENT_ACTION_SPIN_DOWN curr_rom.is_hoenn() ? 0xFF : 0x94
#define MOVEMENT_ACTION_SPIN_UP curr_rom.is_hoenn() ? 0xFF : 0x95
#define MOVEMENT_ACTION_SPIN_LEFT curr_rom.is_hoenn() ? 0xFF : 0x96
#define MOVEMENT_ACTION_SPIN_RIGHT curr_rom.is_hoenn() ? 0xFF : 0x97
#define MOVEMENT_ACTION_RAISE_HAND_AND_STOP curr_rom.is_hoenn() ? 0xFF : 0x98
#define MOVEMENT_ACTION_RAISE_HAND_AND_JUMP curr_rom.is_hoenn() ? 0xFF : 0x99
#define MOVEMENT_ACTION_RAISE_HAND_AND_SWIM curr_rom.is_hoenn() ? 0xFF : 0x9A
#define MOVEMENT_ACTION_WALK_SLOWEST_DOWN curr_rom.is_hoenn() ? 0xFF : 0x9B
#define MOVEMENT_ACTION_WALK_SLOWEST_UP curr_rom.is_hoenn() ? 0xFF : 0x9C
#define MOVEMENT_ACTION_WALK_SLOWEST_LEFT curr_rom.is_hoenn() ? 0xFF : 0x9D
#define MOVEMENT_ACTION_WALK_SLOWEST_RIGHT curr_rom.is_hoenn() ? 0xFF : 0x9E
#define MOVEMENT_ACTION_SHAKE_HEAD_OR_WALK_IN_PLACE curr_rom.is_hoenn() ? 0xFF : 0x9F
#define MOVEMENT_ACTION_GLIDE_DOWN curr_rom.is_hoenn() ? 0xFF : 0xA0
#define MOVEMENT_ACTION_GLIDE_UP curr_rom.is_hoenn() ? 0xFF : 0xA1
#define MOVEMENT_ACTION_GLIDE_LEFT curr_rom.is_hoenn() ? 0xFF : 0xA2
#define MOVEMENT_ACTION_GLIDE_RIGHT curr_rom.is_hoenn() ? 0xFF : 0xA3
#define MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_DOWN curr_rom.is_hoenn() ? 0xFF : 0xA6
#define MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_UP curr_rom.is_hoenn() ? 0xFF : 0xA7
#define MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_LEFT curr_rom.is_hoenn() ? 0xFF : 0xA8
#define MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_RIGHT curr_rom.is_hoenn() ? 0xFF : 0xA9

#define CPU_SET_16BIT     0x00000000
#define CPU_SET_32BIT     0x04000000
class mystery_gift_script
{
    int curr_mg_index;
    int curr_section30_index;
    u8 mg_script[MG_SCRIPT_SIZE] = {};
    u8 save_section_30[0x1000] = {};
    u8 value_buffer[9];
    u8 four_align_value = 0;

public:
    mystery_gift_script();
    void build_script(Pokemon_Party &incoming_box_data);
    u8 get_script_value_at(int index);
    u8 get_section30_value_at(int index);
    u32 calc_checksum32();
    u16 calc_crc16();

private:
    void add_command(int len);
    u16 rev_endian(u16 num);
    void add_asm(u16 command);
    void init_npc_location(u8 bank, u8 map, u8 npc);
    void add_word(u32 word);
    
    // Scripting commands
    void setvirtualaddress(u32 location);
    void lock();
    void faceplayer();
    void checkflag(u16 flag_id);
    void virtualgotoif(u8 condition, u32 location);
    void virtualmsgbox(u32 location);
    void waitmsg();
    void waitkeypress();
    void setvar(u16 var_id, u16 value);
    void copybyte(u32 destination, u32 source);
    void addvar(u16 var_id, u16 value);
    void subvar(u16 var_id, u16 value);
    void call(u32 script_ptr);
    void compare(u16 var_id, u16 value);
    void setflag(u16 flag_id);
    void fanfare(u16 fanfare_number);
    void waitfanfare();
    void special(u16 special_id);
    void callstd(u8 function_index);
    void release();
    void end();
    void killscript();
    void spritebehave(u16 objectID, u8 behaviorType);
    void spriteface(u16 npc, u8 direction);
    void waitmovement(u16 npc);
    void doanimation(u16 animation);
    void applymovement(u16 npc, u32 movements);
    void callASM(u32 script_ptr);
    void loadpointer(u8 destinationBank, u32 value);
    void setMapLayoutIndex(u16 footer);
    void fadeScreen(u8 effect);
    void setMetaTile(u16 x, u16 y, u16 metaTileId, u16 impassible);
    void playse(u16 soundId);
    void writebytetooffset(u8 byte, u32 offset);
    void waitse();

    void msgboxMacro(u32 location);
    void changeSpriteMacro(u8 npcId, u32 spriteTablePtr);
    void changePaletteMacro(u8 npcId, u8 palNum);

    // ASM commands
    void push(u16 register_list);
    void ldr3(u8 rd, u8 immed_8);
    void ldr1(u8 rd, u8 rn, u8 immed_5);
    void add5(u8 rd, u8 immed_8);
    void add3(u8 rm, u8 rn, u8 rd);
    void mov3(u8 rm, u8 rd);
    void add2(u8 rd, u8 immed_8);
    void bx(u8 rm);
    void str1(u8 immed_5, u8 rn, u8 rd);
    void pop(u16 register_list);
    void mov1(u8 rd, u8 immed_8);
    void and1(u8 rd, u8 rm);
    void ldr2(u8 rd, u8 rn, u8 rm);
    void strh(u8 rd, u8 rn, u8 immed_5);
    void swi(u8 immed_8);
};

#endif
