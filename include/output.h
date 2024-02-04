//Created by StevenChaulk https://github.com/stevenchaulk/arduino-poke-gen2

#include <stdint.h>

#define PLAYER_LENGTH_GEN_I  418	//11+8+(44*6)+(11*6)+(11*6)
#define PLAYER_LENGTH_GEN_II 444	//11+8+2+(48*6)+(11*6)+(11*6)+3


#define PATCH_LIST_LEN_GEN_I 196


//uint8_t INPUT_BLOCK_GEN_I[PLAYER_LENGTH_GEN_I];
//uint8_t INPUT_BLOCK_GEN_II[PLAYER_LENGTH_GEN_II];

/* const uint8_t DATA_BLOCK[PLAYER_LENGTH] PROGMEM = {
0x80, 0x91, 0x83, 0x94, 0x88, 0x8D, 0x8E, 0x50, 0x00, 0x00, 0x00, // name
0x1, 0x24, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // number of pokemon in party (0x00), pokemon ID (0x01 - 0x06), stop byte (0x07)
// 6 pokemon
//spc curr HP   lvl  sts  typ1  typ2  cr    mv1   mv2  mv3  mv4  OT         experience      HP EV     att EV    def EV    speed EV  Speci EV  IV          mvPP  mvPP mvPP mvPP Lvl  max HP     attack    defense   speed     special
0x24, 0x0, 0xD, 0x2, 0x0, 0x0,  0x2,  0xFF, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0,  0x0, 0x0, 0x9,  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46, 0x21, 0x23, 0x0, 0x0, 0x0, 0x2, 0x0, 0xD,  0x0, 0x6, 0x0, 0x6, 0x0, 0x7, 0x0, 0x6,
0x85, 0x0, 0x1, 0x5, 0x1, 0x15, 0x15, 0xFF, 0x96, 0x0, 0x0, 0x0, 0x8, 0x87, 0x0, 0x0, 0x9C, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2D, 0x24, 0x28, 0x0, 0x0, 0x0, 0x5, 0x0, 0x11, 0x0, 0x6, 0x0, 0xB, 0x0, 0xD, 0x0, 0x7,
0x85, 0x0, 0x1, 0x5, 0x1, 0x15, 0x15, 0xFF, 0x96, 0x0, 0x0, 0x0, 0x8, 0x87, 0x0, 0x0, 0x9C, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2D, 0x24, 0x28, 0x0, 0x0, 0x0, 0x5, 0x0, 0x11, 0x0, 0x6, 0x0, 0xB, 0x0, 0xD, 0x0, 0x7,
0x85, 0x0, 0x1, 0x5, 0x1, 0x15, 0x15, 0xFF, 0x96, 0x0, 0x0, 0x0, 0x8, 0x87, 0x0, 0x0, 0x9C, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2D, 0x24, 0x28, 0x0, 0x0, 0x0, 0x5, 0x0, 0x11, 0x0, 0x6, 0x0, 0xB, 0x0, 0xD, 0x0, 0x7,
0x85, 0x0, 0x1, 0x5, 0x1, 0x15, 0x15, 0xFF, 0x96, 0x0, 0x0, 0x0, 0x8, 0x87, 0x0, 0x0, 0x9C, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2D, 0x24, 0x28, 0x0, 0x0, 0x0, 0x5, 0x0, 0x11, 0x0, 0x6, 0x0, 0xB, 0x0, 0xD, 0x0, 0x7,
0x85, 0x0, 0x1, 0x5, 0x1, 0x15, 0x15, 0xFF, 0x96, 0x0, 0x0, 0x0, 0x8, 0x87, 0x0, 0x0, 0x9C, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2D, 0x24, 0x28, 0x0, 0x0, 0x0, 0x5, 0x0, 0x11, 0x0, 0x6, 0x0, 0xB, 0x0, 0xD, 0x0, 0x7,
// 6 trainer names
0x87, 0x80, 0x82, 0x8A, 0x84, 0x91, 0x50, 0x00, 0x00, 0x00, 0x00,
0xFF, 0x84, 0x83, 0x50, 0x80, 0x92, 0x87, 0x50, 0x89, 0x80, 0x82,
0xFF, 0x84, 0x83, 0x50, 0x80, 0x92, 0x87, 0x50, 0x89, 0x80, 0x82,
0xFF, 0x84, 0x83, 0x50, 0x80, 0x92, 0x87, 0x50, 0x89, 0x80, 0x82,
0xFF, 0x84, 0x83, 0x50, 0x80, 0x92, 0x87, 0x50, 0x89, 0x80, 0x82,
0xFF, 0x84, 0x83, 0x50, 0x80, 0x92, 0x87, 0x50, 0x89, 0x80, 0x82,
// 6 nicknames
0x8F, 0x88, 0x83, 0x86, 0x84, 0x98, 0x50, 0x50, 0x50, 0x50, 0x50,
0x8C, 0x80, 0x86, 0x88, 0x8A, 0x80, 0x91, 0x8F, 0x50, 0x50, 0x50,
0x8C, 0x80, 0x86, 0x88, 0x8A, 0x80, 0x91, 0x8F, 0x50, 0x50, 0x50,
0x8C, 0x80, 0x86, 0x88, 0x8A, 0x80, 0x91, 0x8F, 0x50, 0x50, 0x50,
0x8C, 0x80, 0x86, 0x88, 0x8A, 0x80, 0x91, 0x8F, 0x50, 0x50, 0x50,
0x8C, 0x80, 0x86, 0x88, 0x8A, 0x80, 0x91, 0x8F, 0x50, 0x50, 0x50,
// 2 useless bytes??
0x00, 0x00, 0x00}; */

/*
const uint8_t DATA_BLOCK_GEN_II[PLAYER_LENGTH_GEN_II] = {
0x80, 0x91, 0x83, 0x94, 0x88, 0x8D, 0x8E, 0x50, 0x00, 0x00, 0x00, // name
0x1, 0x5C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // number of pokemon in party (0x00), pokemon ID (0x01 - 0x06), stop byte (0x07)
0xA9, 0xC8, //trainer ID
// 6 pokemon
//spc Held  mv1   mv2   mv3   mv4   OT ID       exp.              HP_EV       Attack_EV   Def_EV      Speed_EV    Special_EV  IV_Data     m1pp  m2pp  m3pp  m4pp  frnd  virus cght_data   lvl   sat.  N/A   curr_HP     max_HP      attack      defence     speed       spcl_att    spcl_def
0x5C, 0x00 ,0x5F, 0x7A, 0xAE, 0xD4, 0x8E, 0x47, 0x00 ,0x16, 0xDA, 0x07 ,0xB4, 0x08, 0x5F, 0x07, 0x8F, 0x09, 0xDF, 0x08, 0x6A, 0x88, 0x51, 0x14 ,0x1E, 0xA , 0x05, 0x9F, 0x00, 0xC3, 0x87, 0x14, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x2D, 0x00, 0x18, 0x00, 0x16, 0x00, 0x29, 0x00, 0x2F, 0x00, 0x15,
0x46, 0x1A, 0x21, 0x00, 0x00, 0x00, 0xA9, 0xC8, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0x1E, 0x00, 0x00, 0x00, 0xAA, 0x00, 0xC5, 0x81, 0x10, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15,
0x46, 0x1A, 0x21, 0x00, 0x00, 0x00, 0xA9, 0xC8, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0x1E, 0x00, 0x00, 0x00, 0xAA, 0x00, 0xC5, 0x81, 0x10, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 
0x46, 0x1A, 0x21, 0x00, 0x00, 0x00, 0xA9, 0xC8, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0x1E, 0x00, 0x00, 0x00, 0xAA, 0x00, 0xC5, 0x81, 0x10, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 
0x46, 0x1A, 0x21, 0x00, 0x00, 0x00, 0xA9, 0xC8, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0x1E, 0x00, 0x00, 0x00, 0xAA, 0x00, 0xC5, 0x81, 0x10, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 
0x46, 0x1A, 0x21, 0x00, 0x00, 0x00, 0xA9, 0xC8, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0x1E, 0x00, 0x00, 0x00, 0xAA, 0x00, 0xC5, 0x81, 0x10, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 
// 6 trainer names
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x50, 0x00, 0x00, 0x00,
0xFF, 0x84, 0x83, 0x50, 0x80, 0x92, 0x87, 0x50, 0x89, 0x80, 0x82,
0xFF, 0x84, 0x83, 0x50, 0x80, 0x92, 0x87, 0x50, 0x89, 0x80, 0x82,
0xFF, 0x84, 0x83, 0x50, 0x80, 0x92, 0x87, 0x50, 0x89, 0x80, 0x82,
0xFF, 0x84, 0x83, 0x50, 0x80, 0x92, 0x87, 0x50, 0x89, 0x80, 0x82,
0xFF, 0x84, 0x83, 0x50, 0x80, 0x92, 0x87, 0x50, 0x89, 0x80, 0x82,
// 6 nicknames
0x8F, 0x88, 0x83, 0x86, 0x84, 0x98, 0x50, 0x50, 0x50, 0x50, 0x50,
0x8C, 0x80, 0x86, 0x88, 0x8A, 0x80, 0x91, 0x8F, 0x50, 0x50, 0x50,
0x8C, 0x80, 0x86, 0x88, 0x8A, 0x80, 0x91, 0x8F, 0x50, 0x50, 0x50,
0x8C, 0x80, 0x86, 0x88, 0x8A, 0x80, 0x91, 0x8F, 0x50, 0x50, 0x50,
0x8C, 0x80, 0x86, 0x88, 0x8A, 0x80, 0x91, 0x8F, 0x50, 0x50, 0x50,
0x8C, 0x80, 0x86, 0x88, 0x8A, 0x80, 0x91, 0x8F, 0x50, 0x50, 0x50,
// 2 useless bytes??
0x00, 0x00, 0x00};
*/