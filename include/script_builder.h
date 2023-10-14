#ifndef SCRIPT_BUILDER_H
#define SCRIPT_BUILDER_H

#include <tonc.h>
#include <string>
#include <map>
#include "pokemon_party.h"
#include "debug_mode.h"

#define VIR_ADDRESS 0x08000000
#define MG_SCRIPT_SIZE 0x3E8
#define NPC_LOCATION_OFFSET 0x4
#define READ_AS_THUMB 0x1

#define GAMECODE (DEBUG_MODE ? LEAFGREEN : ((*(vu32 *)(0x80000AC)) & 0xFFFFFF))
#define RUBY 0x565841
#define SAPPHIRE 0x505841
#define FIRERED 0x525042
#define LEAFGREEN 0x475042
#define EMERALD 0x455042

#define LOC_SENDMONTOPC         ((GAMECODE == RUBY || GAMECODE == SAPPHIRE) ? 0x01 : ((GAMECODE == FIRERED || GAMECODE == LEAFGREEN) ? 0x08040BA4 : 0x0806B490)) // 94 is where the script jumps to in normal gameplay
#define LOC_GSPECIALVAR_0x8000  ((GAMECODE == RUBY || GAMECODE == SAPPHIRE) ? 0x01 : ((GAMECODE == FIRERED || GAMECODE == LEAFGREEN) ? 0x020370B8 : 0x020375D8))
#define LOC_GSAVEBLOCK1PTR      ((GAMECODE == RUBY || GAMECODE == SAPPHIRE) ? 0x01 : ((GAMECODE == FIRERED || GAMECODE == LEAFGREEN) ? 0x03005008 : 0x03005D8C))
#define OFFSET_RAMSCRIPT        ((GAMECODE == RUBY || GAMECODE == SAPPHIRE) ? 0x01 : ((GAMECODE == FIRERED || GAMECODE == LEAFGREEN) ?     0x361C :     0x3728))
// Source: https://github.com/pret/pokeemerald/blob/master/include/global.h#L1012
#define OFFSET_FLAGS ((GAMECODE == RUBY || GAMECODE == SAPPHIRE) ? 0x01 : ((GAMECODE == FIRERED || GAMECODE == LEAFGREEN) ? 0x0EE0 : 0x1270))
// Flag offset as found within the SaveBlock1 struct in global.h
#define PC_MAKER ((GAMECODE == RUBY || GAMECODE == SAPPHIRE || GAMECODE == EMERALD) ? "LANETTE" : "BILL")

#define FLAG_ID_START 0x21  // This one stays consistant, at least for FRLG/E. Must also be 8x or 8x+1 to store in one byte
#define VAR_ID_START 0x8000 // This one should also stay consistant

#define VAR_CALLASM (VAR_ID_START + 0x00)
#define VAR_SCRIPT_PTR_LOW (VAR_ID_START + 0x01)
#define VAR_SCRIPT_PTR_HIGH (VAR_ID_START + 0x02)
#define VAR_CALL_RETURN_1 (VAR_ID_START + 0x03)
#define VAR_CALL_CHECK_FLAG (VAR_ID_START + 0x04)
#define VAR_CALL_RETURN_2 (VAR_ID_START + 0x05)
#define VAR_BOX_RETURN (VAR_ID_START + 0x06)
#define VAR_INDEX (VAR_ID_START + 0x07)
#define VAR_PKMN_OFFSET (VAR_ID_START + 0x08)

#define PTR_CALLASM (LOC_GSPECIALVAR_0x8000 + 0x00)
#define PTR_SCRIPT_PTR_LOW (LOC_GSPECIALVAR_0x8000 + 0x02)
#define PTR_SCRIPT_PTR_HIGH (LOC_GSPECIALVAR_0x8000 + 0x04)
#define PTR_CALL_RETURN_1 (LOC_GSPECIALVAR_0x8000 + 0x06)
#define PTR_CALL_CHECK_FLAG (LOC_GSPECIALVAR_0x8000 + 0x08)
#define PTR_CALL_RETURN_2 (LOC_GSPECIALVAR_0x8000 + 0x0A)
#define PTR_BOX_RETURN (LOC_GSPECIALVAR_0x8000 + 0x0C)
#define PTR_INDEX (LOC_GSPECIALVAR_0x8000 + 0x0E)
#define PTR_PKMN_OFFSET (LOC_GSPECIALVAR_0x8000 + 0x10)

#define PTR_BLOCK_PTR_LOW (LOC_GSAVEBLOCK1PTR + 0x00)
#define PTR_BLOCK_PTR_HIGH (LOC_GSAVEBLOCK1PTR + 0x02)

#define FLAG_PKMN_1 (FLAG_ID_START + 0x0)
#define FLAG_PKMN_2 (FLAG_ID_START + 0x1)
#define FLAG_PKMN_3 (FLAG_ID_START + 0x2)
#define FLAG_PKMN_4 (FLAG_ID_START + 0x3)
#define FLAG_PKMN_5 (FLAG_ID_START + 0x4)
#define FLAG_PKMN_6 (FLAG_ID_START + 0x5)
#define FLAG_ALL_COLLECTED (FLAG_ID_START + 0x6)


#define NUM_JUMPS 4
#define JUMP_ALL_COLLECTED 0
#define JUMP_PKMN_COLLECTED 1
#define JUMP_BOX_FULL 2
#define JUMP_LOOP 3

#define NUM_TEXTBOXES 4
#define TEXT_GREET 0
#define TEXT_THANK 1
#define TEXT_FULL 2
#define TEXT_RECEIVED 3

#define NUM_ASM_OFFSET 4
#define ASM_OFFSET_PKMN_OFFSET 0
#define ASM_OFFSET_PKMN_STRUCT 1
#define ASM_OFFSET_SENDMON_PTR 2
#define ASM_OFFSET_BOX_SUC_PTR 3

#define NUM_RELATIVE_PTR 1
#define REL_PTR_ASM_START 0

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

// Text conversion definitions

class mystery_gift_script
{
    int curr_index;
    u8 mg_script[MG_SCRIPT_SIZE] = {};
    u8 value_buffer[9];
    u32 jumppoint_location[NUM_JUMPS];
    u32 jumppoint_destination[NUM_JUMPS];
    std::string_view textboxes[NUM_TEXTBOXES] =
        {
            ": Hey /*!-PROFESSOR FENNEL told me that these~were for you!-Don't worry about making room_~I'll send them to the PC!",
            ": Thanks for helping out FENNEL!",
            ": It looks like the PC is full_-Come back once you have more room!",
            "/*'S POK%MON were sent to the PC!",
    };
    u32 textbox_location[NUM_TEXTBOXES];
    u32 textbox_destination[NUM_TEXTBOXES];
    u16 asm_offset_location[NUM_ASM_OFFSET];
    u16 asm_offset_destination[NUM_ASM_OFFSET];
    u16 relative_offset_location[NUM_RELATIVE_PTR];
    u16 relative_offset_destination[NUM_RELATIVE_PTR];
    u8 party_data_array[6 * POKEMON_SIZE];
    u8 four_align_value = 0;
    std::string_view pc_maker = PC_MAKER;

public:
    mystery_gift_script();
    void build_script(Pokemon incoming_party_array[]);
    u8 get_script_value_at(int index);
    u16 calc_checksum();

private:
    void add_command(int len);
    u16 rev_endian(u16 num);
    void insert_textboxes();
    u8 convert_char(char convert_char);
    void fill_jumppoint_pointers();
    void fill_textbox_pointers();
    void add_asm(u16 command);
    void fill_asm_pointers();
    void fill_relative_pointers();
    void set_jump_destination(u8 jumppoint_id);
    u8 get_ptr_offset(u8 jumppoint_id);
    void init_npc_location(u8 bank, u8 map, u8 npc);
    void add_word(u32 word);
    void set_asm_offset_destination(u8 asm_offset_id);
    u8 asm_offset_distance(u8 asm_offset_id);
    void four_align();
    void set_ptr_destination(u8 relative_ptr_id);

    // Scripting commands
    void setvirtualaddress(u32 location);
    void lock();
    void faceplayer();
    void checkflag(u8 flag_id);
    void virtualgotoif(u8 condition, u8 location);
    void virtualmsgbox(u8 textbox_id);
    void waitmsg();
    void waitkeypress();
    void setvar(u16 var_id, u16 value);
    void copybyte(u32 destination, u32 source);
    void addvar(u16 var_id, u16 value);
    void call(u32 script_ptr);
    void compare(u16 var_id, u16 value);
    void setflag(u16 flag_id);
    void fanfare(u16 fanfare_number);
    void waitfanfare();
    void release();
    void end();

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

    // Custom scripting/ASM commands
};

#endif
