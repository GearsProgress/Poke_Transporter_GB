#include "z80_asm.h"
#include <stdexcept>
#include <string>

z80_asm_handler::z80_asm_handler(int *nIndex_ptr, unsigned char *nArray_ptr)
{
    index_ptr = nIndex_ptr;
    array_ptr = nArray_ptr;
}

void z80_asm_handler::add_byte(u8 value)
{
    array_ptr[(*index_ptr)++] = value;
}

void z80_asm_handler::throw_error(std::string message)
{

    //throw std::runtime_error(message);
    while (true)
    {
    }
}

// Taken from the Game BoyTM CPU Manual (http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf) and GBops (https://izik1.github.io/gbops/)

void z80_asm_handler::LD(int destination, int source)
{
    // destination is a 16 bit register, source is u16
    if (TYPE(destination) == T_16BIT_REG && TYPE(source) == T_U16)
    { // 0x01, 0x11, 0x21, 0x31
        add_byte(0b00000001 | (destination << 4));
        add_byte(source >> 0);
        add_byte(source >> 8);
        return;
    }

    // destination is a 16 bit pointer, source is A
    else if (TYPE(destination) == T_16BIT_PTR && source == A)
    { // 0x02, 0x12, 0x22, 0x32
        add_byte(0b00000010 | (destination << 4));
        return;
    }

    // destination is a register, source is u8
    else if (TYPE(destination) == T_8BIT_REG && TYPE(source) == T_U8)
    { // 0x06, 0x0E, 0x16, 0x1E, 0x26, 0x2E, 0x36, 0x3E
        add_byte(0b00000110 | (destination << 3));
        add_byte(source >> 0);
        return;
    }

    // destination is a u16, source is SP
    else if (TYPE(destination) == T_U16 && source == SP)
    { // 0x08
        add_byte(0x08);
        return;
    }

    // destination is A, source is a 16 bit pointer
    else if (destination == A && TYPE(source) == T_16BIT_PTR)
    { // 0x0A, 0x1A, 0x2A, 0x3A
        add_byte(0b00001010 | (source << 4));
        return;
    }

    // destination and source are 8 bit registers, both cannot be HL_PTR
    else if ((TYPE(destination) == T_8BIT_REG) && (TYPE(source) == T_8BIT_REG) && !(destination == HL_PTR && source == HL_PTR))
    { // 0x40 - 0x7F, minus 0x76
        add_byte(0b01000000 | (destination << 3) | (source << 0));
        return;
    }

    else if ((TYPE(destination) == T_U16) && source == A)
    {
        add_byte(0xEA);
        add_byte(destination >> 0);
        add_byte(destination >> 8);
        return;
    }
    else if ((destination == A && TYPE(source) == T_U16))
    {
        add_byte(0xFA);
        add_byte(source >> 0);
        add_byte(source >> 8);
        return;
    }
    else if ((destination == SP && source == HL))
    {
        add_byte(0xF9);
        return;
    }
    else
    {
        throw_error("Invalid Z80 LD command: " + std::to_string(source) + ", " + std::to_string(destination));
    }
}
void z80_asm_handler::HALT()
{
    add_byte(0x76);
    return;
}
void z80_asm_handler::ADD(int destination, int source)
{
    if (destination == A && TYPE(source) == T_8BIT_REG)
    { // 0x80 - 0x87
        add_byte(0b10000000 | (source << 0));
        return;
    }
    else if (destination == HL && TYPE(source) == T_16BIT_REG)
    { // 0x09, 0x19, 0x29, 0x39
        add_byte(0b00001001 | (source << 4));
        return;
    }
    else if (destination == A && TYPE(source) == T_U8)
    {
        add_byte(0xC6);
        add_byte(source);
        return;
    }
    else if (destination == SP && TYPE(source) == T_I8)
    {
        add_byte(0xE8);
        add_byte(source);
        return;
    }
    else
    {
        throw_error("Invalid Z80 ADD command: " + std::to_string(source) + ", " + std::to_string(destination));
    }
}
void z80_asm_handler::ADC(int destination, int source)
{
    if (destination == A && TYPE(source) == T_8BIT_REG)
    { // 0x88 - 0x8F
        add_byte(0b10001000 | (source << 0));
        return;
    }
    else if (destination == A && TYPE(source) == T_U8)
    {
        add_byte(0xCE);
        add_byte(source);
        return;
    }
    else
    {
        throw_error("Invalid Z80 ADC command: " + std::to_string(source) + ", " + std::to_string(destination));
    }
}
void z80_asm_handler::SUB(int destination, int source)
{
    if (destination == A && TYPE(source) == T_8BIT_REG)
    { // 0x90 - 0x97
        add_byte(0b10010000 | (source << 0));
        return;
    }
    else if (destination == A && TYPE(source) == T_U8)
    {
        add_byte(0xD6);
        add_byte(source);
        return;
    }
    else
    {
        throw_error("Invalid Z80 SUB command: " + std::to_string(source) + ", " + std::to_string(destination));
    }
}
void z80_asm_handler::SBC(int destination, int source)
{
    if (destination == A && TYPE(source) == T_8BIT_REG)
    { // 0x98 - 0x9F
        add_byte(0b10011000 | (source << 0));
        return;
    }
    else if (destination == A && TYPE(source) == T_U8)
    {
        add_byte(0xDE);
        add_byte(source);
        return;
    }
    else
    {
        throw_error("Invalid Z80 SBC command: " + std::to_string(source) + ", " + std::to_string(destination));
    }
}
void z80_asm_handler::AND(int destination, int source)
{
    if (destination == A && TYPE(source) == T_8BIT_REG)
    { // 0xA0 - 0xA7
        add_byte(0b10100000 | (source << 0));
        return;
    }
    else if (destination == A && TYPE(source) == T_U8)
    {
        add_byte(0xE6);
        add_byte(source);
        return;
    }
    else
    {
        throw_error("Invalid Z80 AND command: " + std::to_string(source) + ", " + std::to_string(destination));
    }
}
void z80_asm_handler::XOR(int destination, int source)
{
    if (destination == A && TYPE(source) == T_8BIT_REG)
    { // 0xA8 - 0xAF
        add_byte(0b10101000 | (source << 0));
        return;
    }
    else if (destination == A && TYPE(source) == T_U8)
    {
        add_byte(0xEE);
        add_byte(source);
        return;
    }
    else
    {
        throw_error("Invalid Z80 XOR command: " + std::to_string(source) + ", " + std::to_string(destination));
    }
}
void z80_asm_handler::OR(int destination, int source)
{
    if (destination == A && TYPE(source) == T_8BIT_REG)
    { // 0xB0 - 0xB7
        add_byte(0b10110000 | (source << 0));
        return;
    }
    else if (destination == A && TYPE(source) == T_U8)
    {
        add_byte(0xF6);
        add_byte(source);
        return;
    }
    else
    {
        throw_error("Invalid Z80 OR command: " + std::to_string(source) + ", " + std::to_string(destination));
    }
}
void z80_asm_handler::CP(int destination, int source)
{
    if (destination == A && TYPE(source) == T_8BIT_REG)
    { // 0xB8 - 0xBF
        add_byte(0b10111000 | (source << 0));
        return;
    }
    else if (destination == A && TYPE(source) == T_U8)
    {
        add_byte(0xFE);
        add_byte(source);
        return;
    }
    else
    {
        throw_error("Invalid Z80 CP command: " + std::to_string(source) + ", " + std::to_string(destination));
    }
}
void z80_asm_handler::NOP()
{
    add_byte(0x00);
    return;
}
void z80_asm_handler::STOP()
{
    add_byte(0x10);
    return;
}
void z80_asm_handler::INC(int reg)
{
    if (TYPE(reg) == T_16BIT_REG)
    { // 0x03, 0x13, 0x23, 0x33
        add_byte(0b00000011 | (reg << 4));
        return;
    }
    else if (TYPE(reg) == T_8BIT_REG)
    { // 0x04, 0x0C, 0x14, 0x1C, 0x24, 0x2C, 0x34, 0x3C
        add_byte(0b00000100 | (reg << 3));
        return;
    }
    else
    {
        throw_error("Invalid Z80 INC command: " + std::to_string(reg));
    }
}
void z80_asm_handler::DEC(int reg)
{
    if (TYPE(reg) == T_16BIT_REG)
    { // 0x0B, 0x1B, 0x2B, 0x3B
        add_byte(0b00001011 | (reg << 4));
        return;
    }
    else if (TYPE(reg) == T_8BIT_REG)
    { // 0x05, 0x0D, 0x15, 0x1D, 0x25, 0x2D, 0x35, 0x3D
        add_byte(0b00000101 | (reg << 3));
        return;
    }
    else
    {
        throw_error("Invalid Z80 DEC command: " + std::to_string(reg));
    }
}
void z80_asm_handler::RLC(int reg)
{
    ROT(reg, 0x00);
}
void z80_asm_handler::RRC(int reg)
{
    ROT(reg, 0x01);
}
void z80_asm_handler::RL(int reg)
{
    ROT(reg, 0x02);
}
void z80_asm_handler::RR(int reg)
{
    ROT(reg, 0x03);
}
void z80_asm_handler::ROT(int reg, int info)
{ // 0x07, 0x0F, 0x17, 0x1F
    if (reg == A)
    {
        add_byte(0b00000111 | (info << 3));
        return;
    }
    else if (TYPE(reg) == T_8BIT_REG)
    {
        add_byte(0xCB);
        add_byte(0b00000000 | info << 3 | reg << 0);
    }
    else
    {
        throw_error("Invalid Z80 ROT command: " + std::to_string(reg));
    }
}
void z80_asm_handler::JR(int distance)
{
    if (TYPE(distance) == T_I8)
    {
        add_byte(0x18);
        add_byte(distance);
        return;
    }
    else
    {
        throw_error("Invalid Z80 JR command: " + std::to_string(distance));
    }
}
void z80_asm_handler::JR(int flag, int distance)
{
    if (TYPE(flag) == T_FLAG && TYPE(distance) == T_I8)
    {
        add_byte(0x20 | flag << 3);
        add_byte(distance);
        return;
    }
    else
    {
        throw_error("Invalid Z80 JR command: " + std::to_string(flag) + ", " + std::to_string(distance));
    }
}
void z80_asm_handler::DDA()
{
    add_byte(0x27);
};
void z80_asm_handler::CPL()
{
    add_byte(0x2F);
};
void z80_asm_handler::SCF()
{
    add_byte(0x37);
};
void z80_asm_handler::CCF()
{
    add_byte(0x3F);
};
void z80_asm_handler::RET()
{
    add_byte(0xC9);
};
void z80_asm_handler::RET(int flag)
{
    if (TYPE(flag) == T_FLAG)
    { // 0xC0, 0xC8, 0xD0, 0xD8
        add_byte(0b11000000 | (flag << 3));
    }
    else
    {
        throw_error("Invalid Z80 RET command: " + std::to_string(flag));
    }
};
void z80_asm_handler::RETI()
{
    add_byte(0xD9);
};
void z80_asm_handler::PUSH(int source)
{
    if (TYPE(source) == T_16BIT_REG)
    {
        add_byte(0b11000001 | (source << 4));
    }
    else
    {
        throw_error("Invalid Z80 PUSH command: " + std::to_string(source));
    }
}
void z80_asm_handler::POP(int destination)
{
    if (TYPE(destination) == T_16BIT_REG)
    {
        add_byte(0b11000101 | (destination << 4));
    }
    else
    {
        throw_error("Invalid Z80 PUSH command: " + std::to_string(destination));
    }
}
void z80_asm_handler::JP(int destination)
{
    if (TYPE(destination) == T_U16)
    {
        add_byte(0xC3);
        add_byte(destination >> 0);
        add_byte(destination >> 8);
        return;
    }
    else if (destination == HL)
    {
        add_byte(0xE9);
        return;
    }
    else
    {
        throw_error("Invalid Z80 JP command: " + std::to_string(destination));
    }
}
void z80_asm_handler::JP(int flag, int destination)
{
    if (TYPE(flag) == T_FLAG && TYPE(destination) == T_U16)
    { // 0xC2, 0xCA, 0xD2, 0xDA
        add_byte(0b11000010 | flag << 3);
        add_byte(destination >> 0);
        add_byte(destination >> 8);
        return;
    }
    else
    {
        throw_error("Invalid Z80 JP command: " + std::to_string(flag) + ", " + std::to_string(destination));
    }
}
void z80_asm_handler::CALL(int destination)
{
    if (TYPE(destination) == T_U16)
    {
        add_byte(0xCD);
        add_byte(destination >> 0);
        add_byte(destination >> 8);
        return;
    }
    else
    {
        throw_error("Invalid Z80 CALL command: " + std::to_string(destination));
    }
}
void z80_asm_handler::CALL(int flag, int destination)
{
    if (TYPE(flag) == T_FLAG && TYPE(destination) == T_U16)
    { // 0xC4, 0xCC, 0xD4, 0xDC
        add_byte(0b11000100 | flag << 3);
        add_byte(destination >> 0);
        add_byte(destination >> 8);
        return;
    }
    else
    {
        throw_error("Invalid Z80 CALL command: " + std::to_string(flag) + ", " + std::to_string(destination));
    }
}
void z80_asm_handler::RST(int value)
{
    if ((value % 8) != 0 && ((value & 0xFF) >= 0) && ((value & 0xFF) <= 0x38))
    { // 0xC7, 0xCF, 0xD7, 0xDF, 0xE7, 0xEF, 0xF7, 0xFF
        add_byte(0b11000111 | value);
    }
    else
    {
        throw_error("Invalid Z80 RST command: " + std::to_string(value));
    }
}
void z80_asm_handler::LDH(int source, int destination)
{
    if (TYPE(source) == T_U8 && destination == A)
    {
        add_byte(0xE0);
        add_byte(source);
        return;
    }
    else if (source == C && destination == A)
    {
        add_byte(0xE2);
        return;
    }
    else if (source == A && TYPE(destination) == T_U8)
    {
        add_byte(0xF0);
        add_byte(destination);
        return;
    }
    else if (source == A && destination == C)
    {
        add_byte(0xE2);
        return;
    }
    else
    {
        throw_error("Invalid Z80 LDH command: " + std::to_string(source) + ", " + std::to_string(destination));
    }
}
void z80_asm_handler::DI()
{
    add_byte(0xF3);
}
void z80_asm_handler::EI()
{
    add_byte(0xFB);
}
void z80_asm_handler::LDHL(int offset)
{
    if (TYPE(offset) == T_I8)
    {
        add_byte(0xF8);
        add_byte(offset);
        return;
    }
    else
    {
        throw_error("Invalid Z80 LDHL command: " + std::to_string(offset));
    }
}
void z80_asm_handler::SLA(int reg)
{
    if (TYPE(reg) == T_8BIT_REG)
    {
        add_byte(0xCB);
        add_byte(0b00100000 | reg);
    }
    else
    {
        throw_error("Invalid Z80 SLA command: " + std::to_string(reg));
    }
}
void z80_asm_handler::SRA(int reg)
{
    if (TYPE(reg) == T_8BIT_REG)
    {
        add_byte(0xCB);
        add_byte(0b00101000 | reg);
    }
    else
    {
        throw_error("Invalid Z80 SRA command: " + std::to_string(reg));
    }
}
void z80_asm_handler::SWAP(int reg)
{
    if (TYPE(reg) == T_8BIT_REG)
    {
        add_byte(0xCB);
        add_byte(0b00110000 | reg);
    }
    else
    {
        throw_error("Invalid Z80 SWAP command: " + std::to_string(reg));
    }
}
void z80_asm_handler::SRL(int reg)
{
    if (TYPE(reg) == T_8BIT_REG)
    {
        add_byte(0xCB);
        add_byte(0b00111000 | reg);
    }
    else
    {
        throw_error("Invalid Z80 SRL command: " + std::to_string(reg));
    }
}
void z80_asm_handler::BIT(int bit, int reg)
{
    if (TYPE(bit) == T_BIT && TYPE(reg) == T_8BIT_REG && ((bit & 0xFF) >= 0) && ((bit & 0xFF) <= 7))
    {
        add_byte(0xCB);
        add_byte(0b01000000 | bit << 3 | reg);
    }
    else
    {
        throw_error("Invalid Z80 BIT command: " + std::to_string(reg));
    }
}
void z80_asm_handler::RES(int bit, int reg)
{
    if (TYPE(bit) == T_BIT && TYPE(reg) == T_8BIT_REG && ((bit & 0xFF) >= 0) && ((bit & 0xFF) <= 7))
    {
        add_byte(0xCB);
        add_byte(0b10000000 | bit << 3 | reg);
    }
    else
    {
        throw_error("Invalid Z80 RES command: " + std::to_string(reg));
    }
}
void z80_asm_handler::SET(int bit, int reg)
{
    if (TYPE(bit) == T_BIT && TYPE(reg) == T_8BIT_REG && ((bit & 0xFF) >= 0) && ((bit & 0xFF) <= 7))
    {
        add_byte(0xCB);
        add_byte(0b11000000 | bit << 3 | reg);
    }
    else
    {
        throw_error("Invalid Z80 SET command: " + std::to_string(reg));
    }
}