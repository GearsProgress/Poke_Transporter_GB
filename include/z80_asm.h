#ifndef Z80_ASM_H
#define Z80_ASM_H

#include <string>
#include <stdarg.h>
#include <vector>

/*
All registers are above 16 to not confuse them with u8 or u16
u8 registers have a 0x0, while u16 have 0x1
u16 values pointing to a byte have 0x2, sans HL_PTR
*/

#define T_U8 0x00000000
#define T_I8 0x01000000
#define T_U16 0x02000000
#define T_8BIT_REG 0x03000000
#define T_16BIT_REG 0x04000000
#define T_16BIT_PTR 0x05000000
#define T_BIT 0x06000000
#define T_FLAG 0x07000000

#define B (0x00 | T_8BIT_REG)
#define C (0x01 | T_8BIT_REG)
#define D (0x02 | T_8BIT_REG)
#define E (0x03 | T_8BIT_REG)
#define H (0x04 | T_8BIT_REG)
#define L (0x05 | T_8BIT_REG)
#define HL_PTR (0x06 | T_8BIT_REG)
#define A (0x07 | T_8BIT_REG)

#define BC (0x00 | T_16BIT_REG)
#define DE (0x01 | T_16BIT_REG)
#define HL (0x02 | T_16BIT_REG)
#define SP (0x03 | T_16BIT_REG)
#define AF (0x03 | T_16BIT_REG) // AF is only used instead of SP in the PUSH commands

#define BC_PTR (0x00 | T_16BIT_PTR)
#define DE_PTR (0x01 | T_16BIT_PTR)
#define HLI_PTR (0x02 | T_16BIT_PTR)
#define HLD_PTR (0x03 | T_16BIT_PTR)

#define NZ_F (0x00 | T_FLAG)
#define Z_F (0x01 | T_FLAG)
#define NC_F (0x02 | T_FLAG)
#define C_F (0x03 | T_FLAG)

#define TYPE(a) (a & 0xFF000000)

typedef unsigned char u8;   // Issues with including Tonc again with the test payload script
typedef unsigned char byte; // Issues with including Tonc again with the test payload script
typedef unsigned short u16; // Issues with including Tonc again with the test payload script

class z80_asm_handler
{
public:
    int index;
    int memory_offset;
    std::vector<byte> data_vector;

    z80_asm_handler(int data_size, int mem_offset);
    void add_byte(u8 value);
    void add_bytes(int num_bytes, ...);
    void generate_patchlist(z80_asm_handler *bytes_to_patch);
    void LD(int destination, int source);
    void HALT();
    void ADD(int destination, int source);
    void ADC(int destination, int source);
    void SUB(int destination, int source);
    void SBC(int destination, int source);
    void AND(int destination, int source);
    void XOR(int destination, int source);
    void OR(int destination, int source);
    void CP(int destination, int source);
    void NOP();
    void STOP();
    void INC(int reg);
    void DEC(int reg);
    void RLC(int reg);
    void RRC(int reg);
    void RL(int reg);
    void RR(int reg);
    void JR(int distance);
    void JR(int flag, int distance);
    void DDA();
    void CPL();
    void SCF();
    void CCF();
    void RET();
    void RET(int flag);
    void RETI();
    void PUSH(int source);
    void POP(int destination);
    void JP(int destination);
    void JP(int flag, int destination);
    void CALL(int destination);
    void CALL(int flag, int destination);
    void RST(int value);
    void LDH(int source, int destination);
    void DI();
    void EI();
    void LDHL(int offset);
    void SLA(int reg);
    void SRA(int reg);
    void SWAP(int reg);
    void SRL(int reg);
    void BIT(int bit, int reg);
    void RES(int bit, int reg);
    void SET(int bit, int reg);

private:
    void ROT(int reg, int info);
    void throw_error(std::string message);
};

class z80_variable
{
public:
    std::vector<byte> data;
    int size;
    z80_variable(std::vector<z80_variable*> *var_vec, int data_size, ...);
    z80_variable(std::vector<z80_variable*> *var_vec);
    void load_data(int data_size, byte array_data[]);
    int place_ptr(z80_asm_handler *z80_instance);
    void insert_variable(z80_asm_handler *var);
    void update_ptrs();

private:
    std::vector<int> ptr_locations;
    std::vector<z80_asm_handler *> asm_handlers;
    int var_mem_location;
};

class z80_jump
{
public:
    z80_jump(std::vector<z80_jump*> *jump_vec);
    int place_relative_jump(z80_asm_handler *z80_instance);
    int place_direct_jump(z80_asm_handler *z80_instance);
    int place_pointer(z80_asm_handler *z80_instance);
    void set_start(z80_asm_handler *var);
    void update_jumps();

private:
    std::vector<int> ptr_locations;
    std::vector<z80_asm_handler *> asm_handlers;
    std::vector<bool> jump_types;
    int jump_mem_location;
};

#endif