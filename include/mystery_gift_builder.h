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

#define FLAG_ID_START 0x21



#define VAR_ID_START 0x8000 // This one should also stay consistant
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

// Text conversion definitions

class mystery_gift_script
{
    int curr_index;
    u8 mg_script[MG_SCRIPT_SIZE] = {};
    u8 value_buffer[9];
    u8 four_align_value = 0;

public:
    mystery_gift_script();
    void build_script(Pokemon_Party &incoming_box_data);
    u8 get_script_value_at(int index);
    u32 calc_checksum32();
    u16 calc_crc16();
    bool validity_array[MAX_PKMN_IN_BOX];
    int dex_array[MAX_PKMN_IN_BOX];

private:
    void add_command(int len);
    u16 rev_endian(u16 num);
    void add_asm(u16 command);
    void init_npc_location(u8 bank, u8 map, u8 npc);
    void add_word(u32 word);
    void four_align();
    void add_padding();

    // Scripting commands
    void setvirtualaddress(u32 location);
    void lock();
    void faceplayer();
    void checkflag(u8 flag_id);
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
};

#endif
