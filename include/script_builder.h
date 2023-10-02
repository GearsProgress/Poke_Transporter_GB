#ifndef SCRIPT_BUILDER_H
#define SCRIPT_BUILDER_H

#include <tonc.h>
#include <string>
#include <map>

#define VIR_ADDRESS 0x08000000
#define MG_SCRIPT_SIZE 0x3EC

#define NUM_JUMPS 4
#define JUMP_ALL_COLLECTED 0
#define JUMP_PKMN_COLLECTED 1
#define JUMP_BOX_FULL 2
#define JUMP_LOOP 3

#define NUM_TEXTBOXES 3
#define TEXT_GREET 0
#define TEXT_THANK 1
#define TEXT_FULL 2

#define COND_LESSTHAN 0
#define COND_EQUALS 1
#define COND_GREATERTHAN 2
#define COND_LESSEQUALTHAN 3
#define COND_GREATEREQUALTHAN 4
#define COND_NOTEQUAL 5
#define COND_FLAGTRUE 1
#define COND_FLAGFALSE 5

#define VAR_CALLASM 0x8000
#define VAR_SCRIPT_PTR_LOW 0x8001
#define VAR_SCRIPT_PTR_HIGH 0x8002
#define VAR_CALL_RETURN_1 0x8003
#define VAR_CALL_CHECK_FLAG 0x8004
#define VAR_CALL_RETURN_2 0x8005
#define VAR_BOX_RETURN 0x8006
#define VAR_INDEX 0x8007
#define VAR_PKMN_OFFSET 0x8008

#define PTR_CALLASM 0x020375D8
#define PTR_SCRIPT_PTR_LOW 0x020375DA
#define PTR_SCRIPT_PTR_HIGH 0x020375DC
#define PTR_CALL_RETURN_1 0x020375DE
#define PTR_CALL_CHECK_FLAG 0x020375E0
#define PTR_CALL_RETURN_2 0x020375E2
#define PTR_BOX_RETURN 0x020375E4
#define PTR_INDEX 0x020375E6
#define PTR_PKMN_OFFSET 0x020375E8
#define PTR_BLOCK_PTR_LOW 0x03005D8C
#define PTR_BLOCK_PTR_HIGH 0x03005D8E

#define FLAG_ALL_COLLECTED 0x26

#define TEXTBOX 0xF1

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
            "test!",
            "test 2",
            "test 3",
    };
    u32 textbox_location[NUM_TEXTBOXES];
    u32 textbox_destination[NUM_TEXTBOXES];

public:
    mystery_gift_script();
    void build_script();
    u8 get_script_value_at(int index);
    u16 calc_checksum();

private:
    void set_script();
    void add_command(int len);
    u16 rev_endian(u16 num);
    void insert_textboxes();
    u8 convert_char(char convert_char);
    void fill_jumppoint_pointers();
    void fill_textbox_pointers();

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
    void release();
    void end();

    // Custom scripting commands
    void set_jump_destination(u8 jumppoint_id);
};

#endif
