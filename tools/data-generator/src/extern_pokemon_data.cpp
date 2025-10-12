#include "extern_pokemon_data.h"
#include "common.h"

#include <cstdio>

const u16 gen_1_charsets[4][256] {
    // gen_1_Jpn_char_array
    {
        0x20,
        0x30A4,
        0x30F4,
        0x30A8,
        0x30AA,
        0x30AC,
        0x30AE,
        0x30B0,
        0x30B2,
        0x30B4,
        0x30B6,
        0x30B8,
        0x30BA,
        0x30BC,
        0x30BE,
        0x30C0,
        0x20,
        0x30C5,
        0x30C7,
        0x30C9,
        0x30CA,
        0x30CB,
        0x30CC,
        0x30CD,
        0x30CE,
        0x30D0,
        0x30D3,
        0x30D6,
        0x30DC,
        0x30DE,
        0x30DF,
        0x30E0,
        0x30A3,
        0x3042,
        0x3044,
        0x3094,
        0x3048,
        0x304A,
        0x304C,
        0x304E,
        0x3050,
        0x3052,
        0x3054,
        0x3056,
        0x3058,
        0x305A,
        0x305C,
        0x305E,
        0x3060,
        0x3062,
        0x3065,
        0x3067,
        0x3069,
        0x306A,
        0x306B,
        0x306C,
        0x306D,
        0x306E,
        0x3070,
        0x3073,
        0x3076,
        0x3079,
        0x307C,
        0x307E,
        0x30D1,
        0x30D4,
        0x30D7,
        0x30DD,
        0x3071,
        0x3074,
        0x3077,
        0x307A,
        0x307D,
        0x307E,
        0x20,
        0x20,
        0x20,
        0x3082,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0xFF1A,
        0x3043,
        0x3045,
        0x300C,
        0x300D,
        0x300E,
        0x300F,
        0x30FB,
        0x2026,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x30A2,
        0x30A4,
        0x30A6,
        0x30A8,
        0x30AA,
        0x30AB,
        0x30AD,
        0x30AF,
        0x30B1,
        0x30B3,
        0x30B5,
        0x30B7,
        0x30B9,
        0x30BB,
        0x30BD,
        0x30BF,
        0x30C1,
        0x30C4,
        0x30C6,
        0x30C8,
        0x30CA,
        0x30CB,
        0x30CC,
        0x30CD,
        0x30CE,
        0x30CF,
        0x30D2,
        0x30D5,
        0x30DB,
        0x30DE,
        0x30DF,
        0x30E0,
        0x30E1,
        0x30E2,
        0x30E4,
        0x30E6,
        0x30E8,
        0x30E9,
        0x30EB,
        0x30EC,
        0x30ED,
        0x30EF,
        0x30F2,
        0x30F3,
        0x30C3,
        0x30E3,
        0x30E5,
        0x30E7,
        0x30A3,
        0x3042,
        0x3044,
        0x3046,
        0x3048,
        0x304A,
        0x304B,
        0x304D,
        0x304F,
        0x3051,
        0x3053,
        0x3055,
        0x3057,
        0x3059,
        0x305B,
        0x305D,
        0x20,
        0x3061,
        0x3064,
        0x3066,
        0x3068,
        0x306A,
        0x306B,
        0x306C,
        0x306D,
        0x306E,
        0x306F,
        0x3072,
        0x3075,
        0x3078,
        0x307B,
        0x307E,
        0x307F,
        0x3080,
        0x3081,
        0x3082,
        0x3084,
        0x3086,
        0x3088,
        0x3089,
        0x30EA,
        0x308B,
        0x308C,
        0x308D,
        0x308F,
        0x3092,
        0x3093,
        0x3063,
        0x3083,
        0x50,
        0x4D,
        0x30FC,
        0x309C,
        0x309B,
        0x3F,
        0x21,
        0x3002,
        0x30A1,
        0x30A5,
        0x30A7,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x5186,
        0xD7,
        0x2E,
        0x2F,
        0x30A9,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    },
    // gen_1_Eng_char_array
    {
        0x2400,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x2018,
        0x2019,
        0x201C,
        0x201D,
        0x30FB,
        0x2026,
        0x3041,
        0x3047,
        0x3049,
        0x2554,
        0x2550,
        0x2557,
        0x2551,
        0x255A,
        0x255D,
        0x2420,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x29,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0xE9,
        0x64,
        0x6C,
        0x73,
        0x74,
        0x76,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x50,
        0x4D,
        0x2D,
        0x72,
        0x6D,
        0x3F,
        0x21,
        0x2E,
        0x30A1,
        0x30A5,
        0x30A7,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x20,
        0xD7,
        0x2E,
        0x2F,
        0x2C,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    },
    // gen_1_FreGer_char_array
    {
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x2018,
        0x2019,
        0x201C,
        0x201D,
        0x30FB,
        0x22EF,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x2420,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x29,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0xE0,
        0xE8,
        0xE9,
        0xF9,
        0xDF,
        0xE7,
        0x20,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0xEB,
        0xEF,
        0xE2,
        0xF4,
        0xFB,
        0xEA,
        0xEE,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x63,
        0x64,
        0x6A,
        0x6C,
        0x6D,
        0x6E,
        0x70,
        0x73,
        0x73,
        0x74,
        0x75,
        0x79,
        0x20,
        0x50,
        0x4D,
        0x2D,
        0x2B,
        0x20,
        0x3F,
        0x21,
        0x2E,
        0x30A1,
        0x30A5,
        0x30A7,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x20,
        0xD7,
        0x2E,
        0x2F,
        0x2C,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    },
    // gen_1_ItaSpa_char_array
    {
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x2018,
        0x2019,
        0x201C,
        0x201D,
        0x30FB,
        0x22EF,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x2420,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x29,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0xE0,
        0xE8,
        0xE9,
        0xF9,
        0xC0,
        0xC1,
        0x20,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0xC8,
        0xC9,
        0xCC,
        0xCD,
        0xD1,
        0xD2,
        0xD3,
        0xD9,
        0xDA,
        0xE1,
        0xEC,
        0xED,
        0xF1,
        0xF2,
        0xF3,
        0xFA,
        0xBA,
        0x26,
        0x64,
        0x6C,
        0x6D,
        0x72,
        0x73,
        0x74,
        0x76,
        0x20,
        0x20,
        0x50,
        0x4D,
        0x2D,
        0xBF,
        0xA1,
        0x3F,
        0x21,
        0x2E,
        0x30A1,
        0x30A5,
        0x30A7,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x20,
        0xD7,
        0x2E,
        0x2F,
        0x2C,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    }
};

const u16 gen_2_charsets[4][256]{
    // gen_2_Jpn_char_array
    {
        0x3F,
        0x30A4,
        0x30F4,
        0x30A8,
        0x30AA,
        0x30AC,
        0x30AE,
        0x30B0,
        0x30B2,
        0x30B4,
        0x30B6,
        0x30B8,
        0x30BA,
        0x30BC,
        0x30BE,
        0x30C0,
        0x30C2,
        0x30C5,
        0x30C7,
        0x30C9,
        0x2A,
        0x2A,
        0x2A,
        0x30CD,
        0x30CE,
        0x30D0,
        0x30D3,
        0x30D6,
        0x30DC,
        0x2A,
        0x2A,
        0x2A,
        0x30A3,
        0x3042,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x304C,
        0x304E,
        0x3050,
        0x3052,
        0x3054,
        0x3056,
        0x3058,
        0x305A,
        0x305C,
        0x305E,
        0x3060,
        0x3062,
        0x3065,
        0x3067,
        0x3069,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x3070,
        0x3073,
        0x3076,
        0x3079,
        0x307C,
        0x2A,
        0x30D1,
        0x30D4,
        0x30D7,
        0x30DD,
        0x3071,
        0x3074,
        0x3077,
        0x307A,
        0x307D,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x3082,
        0x2A,
        0x2A,
        0x19E,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x20,
        0x25B2,
        0x20,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x300C,
        0x300D,
        0x300E,
        0x300F,
        0x30FB,
        0x22EF,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x30A2,
        0x30A4,
        0x30A6,
        0x30A8,
        0x30AA,
        0x30AB,
        0x30AD,
        0x30AF,
        0x30B1,
        0x30B3,
        0x30B5,
        0x30B7,
        0x30B9,
        0x30BB,
        0x30BD,
        0x30BF,
        0x30C1,
        0x30C4,
        0x30C6,
        0x30C8,
        0x30CA,
        0x30CB,
        0x30CC,
        0x30CD,
        0x30CE,
        0x30CF,
        0x30D2,
        0x30D5,
        0x30DB,
        0x30DE,
        0x30DF,
        0x30E0,
        0x30E1,
        0x30E2,
        0x30E4,
        0x30E6,
        0x30E8,
        0x30E9,
        0x30EB,
        0x30EC,
        0x30ED,
        0x30EF,
        0x30F2,
        0x30F3,
        0x30C3,
        0x30E3,
        0x30E5,
        0x30E7,
        0x30A3,
        0x3042,
        0x3044,
        0x3046,
        0x3048,
        0x304A,
        0x304B,
        0x304D,
        0x304F,
        0x3051,
        0x3053,
        0x3055,
        0x3057,
        0x3059,
        0x305B,
        0x305D,
        0x305F,
        0x3061,
        0x3064,
        0x3066,
        0x3068,
        0x306A,
        0x306B,
        0x306C,
        0x306D,
        0x306E,
        0x306F,
        0x3072,
        0x3075,
        0x3078,
        0x307B,
        0x307E,
        0x307F,
        0x3080,
        0x3081,
        0x3082,
        0x3084,
        0x3086,
        0x3088,
        0x3089,
        0x30EA,
        0x308B,
        0x308C,
        0x308D,
        0x308F,
        0x3092,
        0x3093,
        0x3063,
        0x3083,
        0x3085,
        0x3087,
        0x30FC,
        0x309C,
        0x309B,
        0x3F,
        0x21,
        0x3002,
        0x30A1,
        0x30A5,
        0x30A7,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x5186,
        0xD7,
        0x2E,
        0x2F,
        0x30A9,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    },
    // gen_2_Eng_char_array
    {
        0x3F,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x20,
        0x20,
        0x20,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x20,
        0x71,
        0x72,
        0x20,
        0x20,
        0x20,
        0x20,
        0x77,
        0x78,
        0x79,
        0x7A,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0xC4,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x72,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x2588,
        0x25B2,
        0x20,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x50,
        0x4B,
        0x201C,
        0x201D,
        0x30FB,
        0x2026,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x2550,
        0x2557,
        0x2551,
        0x255A,
        0x255D,
        0x2420,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x29,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0xC4,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x64,
        0x6C,
        0x6D,
        0x72,
        0x73,
        0x74,
        0x76,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0xD83E,
        0x20,
        0x50,
        0x4D,
        0x2D,
        0x20,
        0x20,
        0x3F,
        0x21,
        0x2E,
        0x26,
        0xE9,
        0xD83E,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x20,
        0xD7,
        0x2E,
        0x2F,
        0x2C,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    },
    // gen_2_FreGer_char_array
    {
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x25B2,
        0x20,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x50,
        0x4B,
        0x201C,
        0x201D,
        0x30FB,
        0x2026,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x29,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0xE0,
        0xE8,
        0xE9,
        0xF9,
        0xDF,
        0xE7,
        0xC4,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0xEB,
        0xEF,
        0xE2,
        0xF4,
        0xFB,
        0xEA,
        0xEE,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x63,
        0x64,
        0x6A,
        0x6C,
        0x6D,
        0x6E,
        0x70,
        0x73,
        0x73,
        0x74,
        0x75,
        0x79,
        0x20,
        0x50,
        0x4D,
        0x2D,
        0x2B,
        0x20,
        0x3F,
        0x21,
        0x2E,
        0x26,
        0xE9,
        0x20,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x20,
        0xD7,
        0x2E,
        0x2F,
        0x2C,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    },
    // gen_2_ItaSpa_char_array
    {
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x25B2,
        0x20,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x50,
        0x4B,
        0x201C,
        0x201D,
        0x30FB,
        0x2026,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x29,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0xE0,
        0xE8,
        0xE9,
        0xF9,
        0xC0,
        0xC1,
        0xC4,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0xC8,
        0xC9,
        0xCC,
        0xCD,
        0xD1,
        0xD2,
        0xD3,
        0xD9,
        0xDA,
        0xE1,
        0xEC,
        0xED,
        0xF1,
        0xF2,
        0xF3,
        0xFA,
        0xBA,
        0x26,
        0x64,
        0x6C,
        0x6D,
        0x72,
        0x73,
        0x74,
        0x76,
        0x20,
        0x20,
        0x50,
        0x4D,
        0x2D,
        0xBF,
        0xA1,
        0x3F,
        0x21,
        0x2E,
        0x26,
        0xE9,
        0x20,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x20,
        0xD7,
        0x2E,
        0x2F,
        0x2C,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    }
};

const u16 gen_3_charsets[2][256]{
    // gen_3_Jpn_char_array
    {
        0x20,
        0x3042,
        0x3044,
        0x3046,
        0x3048,
        0x304A,
        0x304B,
        0x304D,
        0x304F,
        0x3051,
        0x3053,
        0x3055,
        0x3057,
        0x3059,
        0x305B,
        0x305D,
        0x305F,
        0x3061,
        0x3064,
        0x3066,
        0x3068,
        0x306A,
        0x306B,
        0x306C,
        0x306D,
        0x306E,
        0x306F,
        0x3072,
        0x3075,
        0x3078,
        0x307B,
        0x307E,
        0x307F,
        0x3080,
        0x3081,
        0x3082,
        0x3084,
        0x3086,
        0x3088,
        0x3089,
        0x308A,
        0x308B,
        0x308C,
        0x308D,
        0x308F,
        0x3092,
        0x3093,
        0x3041,
        0x3043,
        0x3045,
        0x3047,
        0x3049,
        0x3083,
        0x3085,
        0x3087,
        0x304C,
        0x304E,
        0x3050,
        0x3052,
        0x3054,
        0x3056,
        0x3058,
        0x305A,
        0x305C,
        0x305E,
        0x3060,
        0x3062,
        0x3065,
        0x3067,
        0x3069,
        0x3070,
        0x3073,
        0x3076,
        0x3079,
        0x307C,
        0x3071,
        0x3074,
        0x3077,
        0x307A,
        0x307D,
        0x3063,
        0x30A2,
        0x30A4,
        0x30A6,
        0x30A8,
        0x30AA,
        0x30AB,
        0x30AD,
        0x30AF,
        0x30B1,
        0x30B3,
        0x30B5,
        0x30B7,
        0x30B9,
        0x30BB,
        0x30BD,
        0x30BF,
        0x30C1,
        0x30C4,
        0x30C6,
        0x30C8,
        0x30CA,
        0x30CB,
        0x30CC,
        0x30CD,
        0x30CE,
        0x30CF,
        0x30D2,
        0x30D5,
        0x30D8,
        0x30DB,
        0x30DE,
        0x30DF,
        0x30E0,
        0x30E1,
        0x30E2,
        0x30E4,
        0x30E6,
        0x30E8,
        0x30E9,
        0x30EA,
        0x20,
        0x30EC,
        0x30ED,
        0x30EF,
        0x30F2,
        0x30F3,
        0x30A1,
        0x30A3,
        0x30A5,
        0x30A7,
        0x30A9,
        0x30E3,
        0x30E5,
        0x30E7,
        0x30AC,
        0x30AE,
        0x30B0,
        0x30B2,
        0x30B4,
        0x30B6,
        0x30B8,
        0x30BA,
        0x30BC,
        0x30BE,
        0x30C0,
        0x30C2,
        0x30C5,
        0x30C7,
        0x30C9,
        0x30D0,
        0x30D3,
        0x30D6,
        0x30D9,
        0x30DC,
        0x30D1,
        0x30D4,
        0x30D7,
        0x30DA,
        0x30DD,
        0x30C3,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
        0xFF01,
        0xFF1F,
        0x3002,
        0x30FC,
        0x30FB,
        0x30FB,
        0x300E,
        0x300F,
        0x300C,
        0x300D,
        0x2642,
        0x2640,
        0x5186,
        0x2E,
        0xD7,
        0x2F,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0x25B6,
        0x3A,
        0xC4,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0x2B06,
        0x2B07,
        0x2B05,
        0x15E,
        0x23C,
        0x206,
        0x1B2,
        0x147,
        0x19E,
    },
    // gen_3_Intern_char_array
    {
        0x20,
        0xC0,
        0xC1,
        0xC2,
        0xC7,
        0xC8,
        0xC9,
        0xCA,
        0xCB,
        0xCC,
        0x20,
        0xCE,
        0xCF,
        0xD2,
        0xD3,
        0xD4,
        0x152,
        0xD9,
        0xDA,
        0xDB,
        0xD1,
        0xDF,
        0xE0,
        0xE1,
        0x20,
        0xE7,
        0xE8,
        0xE9,
        0xEA,
        0xEB,
        0xEC,
        0x20,
        0xEE,
        0xEF,
        0xF2,
        0xF3,
        0xF4,
        0x153,
        0xF9,
        0xFA,
        0xFB,
        0xF1,
        0xBA,
        0xAA,
        0x1D49,
        0x26,
        0x2B,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x3D,
        0x3B,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x25AF,
        0xBF,
        0xA1,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0xCD,
        0x25,
        0x28,
        0x29,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0xE2,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0xED,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x2B07,
        0x2B05,
        0x27A1,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x1D49,
        0x3C,
        0x3E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x2B3,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
        0x21,
        0x3F,
        0x2E,
        0x2D,
        0x30FB,
        0x2026,
        0x201C,
        0x201D,
        0x2018,
        0x2019,
        0x2642,
        0x2640,
        0x20,
        0x2C,
        0xD7,
        0x2F,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0x25B6,
        0x3A,
        0xC4,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0x20,
        0x20,
        0x20,
        0x15E,
        0x23C,
        0x206,
        0x1B2,
        0x147,
        0x19E,
    }
};

const u8 EXP_GROUPS[POKEMON_ARRAY_SIZE] = {
    0, // Offset the list to remove "off by one" errors
    3, // Bulbasaur
    3, // Ivysaur
    3, // Venusaur
    3, // Charmander
    3, // Charmeleon
    3, // Charizard
    3, // Squirtle
    3, // Wartortle
    3, // Blastoise
    0, // Caterpie
    0, // Metapod
    0, // Butterfree
    0, // Weedle
    0, // Kakuna
    0, // Beedrill
    3, // Pidgey
    3, // Pidgeotto
    3, // Pidgeot
    0, // Rattata
    0, // Raticate
    0, // Spearow
    0, // Fearow
    0, // Ekans
    0, // Arbok
    0, // Pikachu
    0, // Raichu
    0, // Sandshrew
    0, // Sandslash
    3, // Nidoran♀
    3, // Nidorina
    3, // Nidoqueen
    3, // Nidoran♂
    3, // Nidorino
    3, // Nidoking
    4, // Clefairy
    4, // Clefable
    0, // Vulpix
    0, // Ninetales
    4, // Jigglypuff
    4, // Wigglytuff
    0, // Zubat
    0, // Golbat
    3, // Oddish
    3, // Gloom
    3, // Vileplume
    0, // Paras
    0, // Parasect
    0, // Venonat
    0, // Venomoth
    0, // Diglett
    0, // Dugtrio
    0, // Meowth
    0, // Persian
    0, // Psyduck
    0, // Golduck
    0, // Mankey
    0, // Primeape
    5, // Growlithe
    5, // Arcanine
    3, // Poliwag
    3, // Poliwhirl
    3, // Poliwrath
    3, // Abra
    3, // Kadabra
    3, // Alakazam
    3, // Machop
    3, // Machoke
    3, // Machamp
    3, // Bellsprout
    3, // Weepinbell
    3, // Victreebel
    5, // Tentacool
    5, // Tentacruel
    3, // Geodude
    3, // Graveler
    3, // Golem
    0, // Ponyta
    0, // Rapidash
    0, // Slowpoke
    0, // Slowbro
    0, // Magnemite
    0, // Magneton
    0, // Farfetch'd
    0, // Doduo
    0, // Dodrio
    0, // Seel
    0, // Dewgong
    0, // Grimer
    0, // Muk
    5, // Shellder
    5, // Cloyster
    3, // Gastly
    3, // Haunter
    3, // Gengar
    0, // Onix
    0, // Drowzee
    0, // Hypno
    0, // Krabby
    0, // Kingler
    0, // Voltorb
    0, // Electrode
    5, // Exeggcute
    5, // Exeggutor
    0, // Cubone
    0, // Marowak
    0, // Hitmonlee
    0, // Hitmonchan
    0, // Lickitung
    0, // Koffing
    0, // Weezing
    5, // Rhyhorn
    5, // Rhydon
    4, // Chansey
    0, // Tangela
    0, // Kangaskhan
    0, // Horsea
    0, // Seadra
    0, // Goldeen
    0, // Seaking
    5, // Staryu
    5, // Starmie
    0, // Mr. Mime
    0, // Scyther
    0, // Jynx
    0, // Electabuzz
    0, // Magmar
    5, // Pinsir
    5, // Tauros
    5, // Magikarp
    5, // Gyarados
    5, // Lapras
    0, // Ditto
    0, // Eevee
    0, // Vaporeon
    0, // Jolteon
    0, // Flareon
    0, // Porygon
    0, // Omanyte
    0, // Omastar
    0, // Kabuto
    0, // Kabutops
    5, // Aerodactyl
    5, // Snorlax
    5, // Articuno
    5, // Zapdos
    5, // Moltres
    5, // Dratini
    5, // Dragonair
    5, // Dragonite
    5, // Mewtwo
    3, // Mew
    3, // Chikorita
    3, // Bayleef
    3, // Meganium
    3, // Cyndaquil
    3, // Quilava
    3, // Typhlosion
    3, // Totodile
    3, // Croconaw
    3, // Feraligatr
    0, // Sentret
    0, // Furret
    0, // Hoothoot
    0, // Noctowl
    4, // Ledyba
    4, // Ledian
    4, // Spinarak
    4, // Ariados
    0, // Crobat
    5, // Chinchou
    5, // Lanturn
    0, // Pichu
    4, // Cleffa
    4, // Igglybuff
    4, // Togepi
    4, // Togetic
    0, // Natu
    0, // Xatu
    3, // Mareep
    3, // Flaaffy
    3, // Ampharos
    3, // Bellossom
    4, // Marill
    4, // Azumarill
    0, // Sudowoodo
    3, // Politoed
    3, // Hoppip
    3, // Skiploom
    3, // Jumpluff
    4, // Aipom
    3, // Sunkern
    3, // Sunflora
    0, // Yanma
    0, // Wooper
    0, // Quagsire
    0, // Espeon
    0, // Umbreon
    3, // Murkrow
    0, // Slowking
    4, // Misdreavus
    0, // Unown
    0, // Wobbuffet
    0, // Girafarig
    0, // Pineco
    0, // Forretress
    0, // Dunsparce
    3, // Gligar
    0, // Steelix
    4, // Snubbull
    4, // Granbull
    0, // Qwilfish
    0, // Scizor
    3, // Shuckle
    5, // Heracross
    3, // Sneasel
    0, // Teddiursa
    0, // Ursaring
    0, // Slugma
    0, // Magcargo
    5, // Swinub
    5, // Piloswine
    4, // Corsola
    0, // Remoraid
    0, // Octillery
    4, // Delibird
    5, // Mantine
    5, // Skarmory
    5, // Houndour
    5, // Houndoom
    0, // Kingdra
    0, // Phanpy
    0, // Donphan
    0, // Porygon2
    5, // Stantler
    4, // Smeargle
    0, // Tyrogue
    0, // Hitmontop
    0, // Smoochum
    0, // Elekid
    0, // Magby
    5, // Miltank
    4, // Blissey
    5, // Raikou
    5, // Entei
    5, // Suicune
    5, // Larvitar
    5, // Pupitar
    5, // Tyranitar
    5, // Lugia
    5, // Ho-Oh
    3, // Celebi
    3, // Treecko
};
const u8 GENDER_RATIO[POKEMON_ARRAY_SIZE] = {
    0, // Offset the list to remove "off by one" errors
    1, // Bulbasaur         [1♀:7♂]
    1, // Ivysaur           [1♀:7♂]
    1, // Venusaur          [1♀:7♂]
    1, // Charmander        [1♀:7♂]
    1, // Charmeleon        [1♀:7♂]
    1, // Charizard         [1♀:7♂]
    1, // Squirtle          [1♀:7♂]
    1, // Wartortle         [1♀:7♂]
    1, // Blastoise         [1♀:7♂]
    3, // Caterpie          [1♀:1♂]
    3, // Metapod           [1♀:1♂]
    3, // Butterfree        [1♀:1♂]
    3, // Weedle            [1♀:1♂]
    3, // Kakuna            [1♀:1♂]
    3, // Beedrill          [1♀:1♂]
    3, // Pidgey            [1♀:1♂]
    3, // Pidgeotto         [1♀:1♂]
    3, // Pidgeot           [1♀:1♂]
    3, // Rattata           [1♀:1♂]
    3, // Raticate          [1♀:1♂]
    3, // Spearow           [1♀:1♂]
    3, // Fearow            [1♀:1♂]
    3, // Ekans             [1♀:1♂]
    3, // Arbok             [1♀:1♂]
    3, // Pikachu           [1♀:1♂]
    3, // Raichu            [1♀:1♂]
    3, // Sandshrew         [1♀:1♂]
    3, // Sandslash         [1♀:1♂]
    6, // Nidoran♀          [Female Only]
    6, // Nidorina          [Female Only]
    6, // Nidoqueen         [Female Only]
    0, // Nidoran♂          [Male Only]
    0, // Nidorino          [Male Only]
    0, // Nidoking          [Male Only]
    4, // Clefairy          [3♀:1♂]
    4, // Clefable          [3♀:1♂]
    4, // Vulpix            [3♀:1♂]
    4, // Ninetales         [3♀:1♂]
    4, // Jigglypuff        [3♀:1♂]
    4, // Wigglytuff        [3♀:1♂]
    3, // Zubat             [1♀:1♂]
    3, // Golbat            [1♀:1♂]
    3, // Oddish            [1♀:1♂]
    3, // Gloom             [1♀:1♂]
    3, // Vileplume         [1♀:1♂]
    3, // Paras             [1♀:1♂]
    3, // Parasect          [1♀:1♂]
    3, // Venonat           [1♀:1♂]
    3, // Venomoth          [1♀:1♂]
    3, // Diglett           [1♀:1♂]
    3, // Dugtrio           [1♀:1♂]
    3, // Meowth            [1♀:1♂]
    3, // Persian           [1♀:1♂]
    3, // Psyduck           [1♀:1♂]
    3, // Golduck           [1♀:1♂]
    3, // Mankey            [1♀:1♂]
    3, // Primeape          [1♀:1♂]
    2, // Growlithe         [1♀:3♂]
    2, // Arcanine          [1♀:3♂]
    3, // Poliwag           [1♀:1♂]
    3, // Poliwhirl         [1♀:1♂]
    3, // Poliwrath         [1♀:1♂]
    2, // Abra              [1♀:3♂]
    2, // Kadabra           [1♀:3♂]
    2, // Alakazam          [1♀:3♂]
    2, // Machop            [1♀:3♂]
    2, // Machoke           [1♀:3♂]
    2, // Machamp           [1♀:3♂]
    3, // Bellsprout        [1♀:1♂]
    3, // Weepinbell        [1♀:1♂]
    3, // Victreebel        [1♀:1♂]
    3, // Tentacool         [1♀:1♂]
    3, // Tentacruel        [1♀:1♂]
    3, // Geodude           [1♀:1♂]
    3, // Graveler          [1♀:1♂]
    3, // Golem             [1♀:1♂]
    3, // Ponyta            [1♀:1♂]
    3, // Rapidash          [1♀:1♂]
    3, // Slowpoke          [1♀:1♂]
    3, // Slowbro           [1♀:1♂]
    7, // Magnemite         [Gender Unknown]
    7, // Magneton          [Gender Unknown]
    3, // Farfetch'd        [1♀:1♂]
    3, // Doduo             [1♀:1♂]
    3, // Dodrio            [1♀:1♂]
    3, // Seel              [1♀:1♂]
    3, // Dewgong           [1♀:1♂]
    3, // Grimer            [1♀:1♂]
    3, // Muk               [1♀:1♂]
    3, // Shellder          [1♀:1♂]
    3, // Cloyster          [1♀:1♂]
    3, // Gastly            [1♀:1♂]
    3, // Haunter           [1♀:1♂]
    3, // Gengar            [1♀:1♂]
    3, // Onix              [1♀:1♂]
    3, // Drowzee           [1♀:1♂]
    3, // Hypno             [1♀:1♂]
    3, // Krabby            [1♀:1♂]
    3, // Kingler           [1♀:1♂]
    7, // Voltorb           [Gender Unknown]
    7, // Electrode         [Gender Unknown]
    3, // Exeggcute         [1♀:1♂]
    3, // Exeggutor         [1♀:1♂]
    3, // Cubone            [1♀:1♂]
    3, // Marowak           [1♀:1♂]
    0, // Hitmonlee         [Male Only]
    0, // Hitmonchan        [Male Only]
    3, // Lickitung         [1♀:1♂]
    3, // Koffing           [1♀:1♂]
    3, // Weezing           [1♀:1♂]
    3, // Rhyhorn           [1♀:1♂]
    3, // Rhydon            [1♀:1♂]
    6, // Chansey           [Female Only]
    3, // Tangela           [1♀:1♂]
    6, // Kangaskhan        [Female Only]
    3, // Horsea            [1♀:1♂]
    3, // Seadra            [1♀:1♂]
    3, // Goldeen           [1♀:1♂]
    3, // Seaking           [1♀:1♂]
    7, // Staryu            [Gender Unknown]
    7, // Starmie           [Gender Unknown]
    3, // Mr. Mime          [1♀:1♂]
    3, // Scyther           [1♀:1♂]
    6, // Jynx              [Female Only]
    2, // Electabuzz        [1♀:3♂]
    2, // Magmar            [1♀:3♂]
    3, // Pinsir            [1♀:1♂]
    0, // Tauros            [Male Only]
    3, // Magikarp          [1♀:1♂]
    3, // Gyarados          [1♀:1♂]
    3, // Lapras            [1♀:1♂]
    7, // Ditto             [Gender Unknown]
    1, // Eevee             [1♀:7♂]
    1, // Vaporeon          [1♀:7♂]
    1, // Jolteon           [1♀:7♂]
    1, // Flareon           [1♀:7♂]
    7, // Porygon           [Gender Unknown]
    1, // Omanyte           [1♀:7♂]
    1, // Omastar           [1♀:7♂]
    1, // Kabuto            [1♀:7♂]
    1, // Kabutops          [1♀:7♂]
    1, // Aerodactyl        [1♀:7♂]
    1, // Snorlax           [1♀:7♂]
    7, // Articuno          [Gender Unknown]
    7, // Zapdos            [Gender Unknown]
    7, // Moltres           [Gender Unknown]
    3, // Dratini           [1♀:1♂]
    3, // Dragonair         [1♀:1♂]
    3, // Dragonite         [1♀:1♂]
    7, // Mewtwo            [Gender Unknown]
    7, // Mew               [Gender Unknown]
    1, // Chikorita         [1♀:7♂]
    1, // Bayleef           [1♀:7♂]
    1, // Meganium          [1♀:7♂]
    1, // Cyndaquil         [1♀:7♂]
    1, // Quilava           [1♀:7♂]
    1, // Typhlosion        [1♀:7♂]
    1, // Totodile          [1♀:7♂]
    1, // Croconaw          [1♀:7♂]
    1, // Feraligatr        [1♀:7♂]
    3, // Sentret           [1♀:1♂]
    3, // Furret            [1♀:1♂]
    3, // Hoothoot          [1♀:1♂]
    3, // Noctowl           [1♀:1♂]
    3, // Ledyba            [1♀:1♂]
    3, // Ledian            [1♀:1♂]
    3, // Spinarak          [1♀:1♂]
    3, // Ariados           [1♀:1♂]
    3, // Crobat            [1♀:1♂]
    3, // Chinchou          [1♀:1♂]
    3, // Lanturn           [1♀:1♂]
    3, // Pichu             [1♀:1♂]
    4, // Cleffa            [3♀:1♂]
    4, // Igglybuff         [3♀:1♂]
    1, // Togepi            [1♀:7♂]
    1, // Togetic           [1♀:7♂]
    3, // Natu              [1♀:1♂]
    3, // Xatu              [1♀:1♂]
    3, // Mareep            [1♀:1♂]
    3, // Flaaffy           [1♀:1♂]
    3, // Ampharos          [1♀:1♂]
    3, // Bellossom         [1♀:1♂]
    3, // Marill            [1♀:1♂]
    3, // Azumarill         [1♀:1♂]
    3, // Sudowoodo         [1♀:1♂]
    3, // Politoed          [1♀:1♂]
    3, // Hoppip            [1♀:1♂]
    3, // Skiploom          [1♀:1♂]
    3, // Jumpluff          [1♀:1♂]
    3, // Aipom             [1♀:1♂]
    3, // Sunkern           [1♀:1♂]
    3, // Sunflora          [1♀:1♂]
    3, // Yanma             [1♀:1♂]
    3, // Wooper            [1♀:1♂]
    3, // Quagsire          [1♀:1♂]
    1, // Espeon            [1♀:7♂]
    1, // Umbreon           [1♀:7♂]
    3, // Murkrow           [1♀:1♂]
    3, // Slowking          [1♀:1♂]
    3, // Misdreavus        [1♀:1♂]
    7, // Unown             [Gender Unknown]
    3, // Wobbuffet         [1♀:1♂]
    3, // Girafarig         [1♀:1♂]
    3, // Pineco            [1♀:1♂]
    3, // Forretress        [1♀:1♂]
    3, // Dunsparce         [1♀:1♂]
    3, // Gligar            [1♀:1♂]
    3, // Steelix           [1♀:1♂]
    4, // Snubbull          [3♀:1♂]
    4, // Granbull          [3♀:1♂]
    3, // Qwilfish          [1♀:1♂]
    3, // Scizor            [1♀:1♂]
    3, // Shuckle           [1♀:1♂]
    3, // Heracross         [1♀:1♂]
    3, // Sneasel           [1♀:1♂]
    3, // Teddiursa         [1♀:1♂]
    3, // Ursaring          [1♀:1♂]
    3, // Slugma            [1♀:1♂]
    3, // Magcargo          [1♀:1♂]
    3, // Swinub            [1♀:1♂]
    3, // Piloswine         [1♀:1♂]
    4, // Corsola           [3♀:1♂]
    3, // Remoraid          [1♀:1♂]
    3, // Octillery         [1♀:1♂]
    3, // Delibird          [1♀:1♂]
    3, // Mantine           [1♀:1♂]
    3, // Skarmory          [1♀:1♂]
    3, // Houndour          [1♀:1♂]
    3, // Houndoom          [1♀:1♂]
    3, // Kingdra           [1♀:1♂]
    3, // Phanpy            [1♀:1♂]
    3, // Donphan           [1♀:1♂]
    7, // Porygon2          [Gender Unknown]
    3, // Stantler          [1♀:1♂]
    3, // Smeargle          [1♀:1♂]
    0, // Tyrogue           [Male Only]
    0, // Hitmontop         [Male Only]
    6, // Smoochum          [Female Only]
    2, // Elekid            [1♀:3♂]
    2, // Magby             [1♀:3♂]
    6, // Miltank           [Female Only]
    6, // Blissey           [Female Only]
    7, // Raikou            [Gender Unknown]
    7, // Entei             [Gender Unknown]
    7, // Suicune           [Gender Unknown]
    3, // Larvitar          [1♀:1♂]
    3, // Pupitar           [1♀:1♂]
    3, // Tyranitar         [1♀:1♂]
    7, // Lugia             [Gender Unknown]
    7, // Ho-Oh             [Gender Unknown]
    7, // Celebi            [Gender Unknown]
    1, // Treecko           [1♀:7♂]

};
const bool NUM_ABILITIES[POKEMON_ARRAY_SIZE] = {
    0, // Offset the list to remove "off by one" errors
    0, // Bulbasaur         Overgrow
    0, // Ivysaur           Overgrow
    0, // Venusaur          Overgrow
    0, // Charmander        Blaze
    0, // Charmeleon        Blaze
    0, // Charizard         Blaze
    0, // Squirtle          Torrent
    0, // Wartortle         Torrent
    0, // Blastoise         Torrent
    0, // Caterpie          Shield Dust
    0, // Metapod           Shed Skin
    0, // Butterfree        Compound Eyes
    0, // Weedle            Shield Dust
    0, // Kakuna            Shed Skin
    0, // Beedrill          Swarm
    0, // Pidgey            Keen Eye
    0, // Pidgeotto         Keen Eye
    0, // Pidgeot           Keen Eye
    1, // Rattata           Run Away/Guts
    1, // Raticate          Run Away/Guts
    0, // Spearow           Keen Eye
    0, // Fearow            Keen Eye
    1, // Ekans             Intimidate/Shed Skin
    1, // Arbok             Intimidate/Shed Skin
    0, // Pikachu           Static
    0, // Raichu            Static
    0, // Sandshrew         Sand Veil
    0, // Sandslash         Sand Veil
    0, // Nidoran♀          Poison Point
    0, // Nidorina          Poison Point
    0, // Nidoqueen         Poison Point
    0, // Nidoran♂          Poison Point
    0, // Nidorino          Poison Point
    0, // Nidoking          Poison Point
    0, // Clefairy          Cute Charm
    0, // Clefable          Cute Charm
    0, // Vulpix            Flash Fire
    0, // Ninetales         Flash Fire
    0, // Jigglypuff        Cute Charm
    0, // Wigglytuff        Cute Charm
    0, // Zubat             Inner Focus
    0, // Golbat            Inner Focus
    0, // Oddish            Chlorophyll
    0, // Gloom             Chlorophyll
    0, // Vileplume         Chlorophyll
    0, // Paras             Effect Spore
    0, // Parasect          Effect Spore
    0, // Venonat           Compound Eyes
    0, // Venomoth          Shield Dust
    1, // Diglett           Sand Veil/Arena Trap
    1, // Dugtrio           Sand Veil/Arena Trap
    0, // Meowth            Pickup
    0, // Persian           Limber
    1, // Psyduck           Damp/Cloud Nine
    1, // Golduck           Damp/Cloud Nine
    0, // Mankey            Vital Spirit
    0, // Primeape          Vital Spirit
    1, // Growlithe         Intimidate/Flash Fire
    1, // Arcanine          Intimidate/Flash Fire
    1, // Poliwag           Water Absorb/Damp
    1, // Poliwhirl         Water Absorb/Damp
    1, // Poliwrath         Water Absorb/Damp
    1, // Abra              Synchronize/Inner Focus
    1, // Kadabra           Synchronize/Inner Focus
    1, // Alakazam          Synchronize/Inner Focus
    0, // Machop            Guts
    0, // Machoke           Guts
    0, // Machamp           Guts
    0, // Bellsprout        Chlorophyll
    0, // Weepinbell        Chlorophyll
    0, // Victreebel        Chlorophyll
    1, // Tentacool         Clear Body/Liquid Ooze
    1, // Tentacruel        Clear Body/Liquid Ooze
    1, // Geodude           Rock Head/Sturdy
    1, // Graveler          Rock Head/Sturdy
    1, // Golem             Rock Head/Sturdy
    1, // Ponyta            Run Away/Flash Fire
    1, // Rapidash          Run Away/Flash Fire
    1, // Slowpoke          Oblivious/Own Tempo
    1, // Slowbro           Oblivious/Own Tempo
    1, // Magnemite         Magnet Pull/Sturdy
    1, // Magneton          Magnet Pull/Sturdy
    1, // Farfetch'd        Keen Eye/Inner Focus
    1, // Doduo             Run Away/Early Bird
    1, // Dodrio            Run Away/Early Bird
    0, // Seel              Thick Fat
    0, // Dewgong           Thick Fat
    1, // Grimer            Stench/Sticky Hold
    1, // Muk               Stench/Sticky Hold
    0, // Shellder          Shell Armor
    0, // Cloyster          Shell Armor
    0, // Gastly            Levitate
    0, // Haunter           Levitate
    0, // Gengar            Cursed Body
    1, // Onix              Rock Head/Sturdy
    0, // Drowzee           Insomnia
    0, // Hypno             Insomnia
    1, // Krabby            Hyper Cutter/Shell Armor
    1, // Kingler           Hyper Cutter/Shell Armor
    1, // Voltorb           Soundproof/Static
    1, // Electrode         Soundproof/Static
    0, // Exeggcute         Chlorophyll
    0, // Exeggutor         Chlorophyll
    1, // Cubone            Rock Head/Lightning Rod
    1, // Marowak           Rock Head/Lightning Rod
    0, // Hitmonlee         Limber
    0, // Hitmonchan        Keen Eye
    1, // Lickitung         Own Tempo/Oblivious
    0, // Koffing           Levitate
    0, // Weezing           Levitate
    1, // Rhyhorn           Lightning Rod/Rock Head
    1, // Rhydon            Lightning Rod/Rock Head
    1, // Chansey           Natural Cure/Serene Grace
    0, // Tangela           Chlorophyll
    0, // Kangaskhan        Early Bird
    0, // Horsea            Swift Swim
    0, // Seadra            Poison Point
    1, // Goldeen           Swift Swim/Water Veil
    1, // Seaking           Swift Swim/Water Veil
    1, // Staryu            Illuminate/Natural Cure
    1, // Starmie           Illuminate/Natural Cure
    0, // Mr. Mime          Soundproof
    0, // Scyther           Swarm
    0, // Jynx              Oblivious
    0, // Electabuzz        Static
    0, // Magmar            Flame Body
    0, // Pinsir            Hyper Cutter
    0, // Tauros            Intimidate
    0, // Magikarp          Swift Swim
    0, // Gyarados          Intimidate
    1, // Lapras            Water Absorb/Shell Armor
    0, // Ditto             Limber
    0, // Eevee             Run Away
    0, // Vaporeon          Water Absorb
    0, // Jolteon           Volt Absorb
    0, // Flareon           Flash Fire
    0, // Porygon           Trace
    1, // Omanyte           Swift Swim/Shell Armor
    1, // Omastar           Swift Swim/Shell Armor
    1, // Kabuto            Swift Swim/Battle Armor
    1, // Kabutops          Swift Swim/Battle Armor
    1, // Aerodactyl        Rock Head/Pressure
    1, // Snorlax           Immunity/Thick Fat
    0, // Articuno          Pressure
    0, // Zapdos            Pressure
    0, // Moltres           Pressure
    0, // Dratini           Shed Skin
    0, // Dragonair         Shed Skin
    0, // Dragonite         Inner Focus
    0, // Mewtwo            Pressure
    0, // Mew               Synchronize
    0, // Chikorita         Overgrow
    0, // Bayleef           Overgrow
    0, // Meganium          Overgrow
    0, // Cyndaquil         Blaze
    0, // Quilava           Blaze
    0, // Typhlosion        Blaze
    0, // Totodile          Torrent
    0, // Croconaw          Torrent
    0, // Feraligatr        Torrent
    1, // Sentret           Run Away/Keen Eye
    1, // Furret            Run Away/Keen Eye
    1, // Hoothoot          Insomnia/Keen Eye
    1, // Noctowl           Insomnia/Keen Eye
    1, // Ledyba            Swarm/Early Bird
    1, // Ledian            Swarm/Early Bird
    1, // Spinarak          Swarm/Insomnia
    1, // Ariados           Swarm/Insomnia
    0, // Crobat            Inner Focus
    1, // Chinchou          Volt Absorb/Illuminate
    1, // Lanturn           Volt Absorb/Illuminate
    0, // Pichu             Static
    0, // Cleffa            Cute Charm
    0, // Igglybuff         Cute Charm
    1, // Togepi            Hustle/Serene Grace
    1, // Togetic           Hustle/Serene Grace
    1, // Natu              Synchronize/Early Bird
    1, // Xatu              Synchronize/Early Bird
    0, // Mareep            Static
    0, // Flaaffy           Static
    0, // Ampharos          Static
    0, // Bellossom         Chlorophyll
    1, // Marill            Thick Fat/Huge Power
    1, // Azumarill         Thick Fat/Huge Power
    1, // Sudowoodo         Sturdy/Rock Head
    1, // Politoed          Water Absorb/Damp
    0, // Hoppip            Chlorophyll
    0, // Skiploom          Chlorophyll
    0, // Jumpluff          Chlorophyll
    1, // Aipom             Run Away/Pickup
    0, // Sunkern           Chlorophyll
    0, // Sunflora          Chlorophyll
    1, // Yanma             Speed Boost/Compound Eyes
    1, // Wooper            Damp/Water Absorb
    1, // Quagsire          Damp/Water Absorb
    0, // Espeon            Synchronize
    0, // Umbreon           Synchronize
    0, // Murkrow           Insomnia
    1, // Slowking          Oblivious/Own Tempo
    0, // Misdreavus        Levitate
    0, // Unown             Levitate
    0, // Wobbuffet         Shadow Tag
    1, // Girafarig         Inner Focus/Early Bird
    0, // Pineco            Sturdy
    0, // Forretress        Sturdy
    1, // Dunsparce         Serene Grace/Run Away
    1, // Gligar            Hyper Cutter/Sand Veil
    1, // Steelix           Rock Head/Sturdy
    1, // Snubbull          Intimidate/Run Away
    0, // Granbull          Intimidate
    1, // Qwilfish          Poison Point/Swift Swim
    0, // Scizor            Swarm
    0, // Shuckle           Sturdy
    1, // Heracross         Swarm/Guts
    1, // Sneasel           Inner Focus/Keen Eye
    0, // Teddiursa         Pickup
    0, // Ursaring          Guts
    1, // Slugma            Magma Armor/Flame Body
    1, // Magcargo          Magma Armor/Flame Body
    0, // Swinub            Oblivious
    0, // Piloswine         Oblivious
    1, // Corsola           Hustle/Natural Cure
    0, // Remoraid          Hustle
    0, // Octillery         Suction Cups
    1, // Delibird          Vital Spirit/Hustle
    1, // Mantine           Swift Swim/Water Absorb
    1, // Skarmory          Keen Eye/Sturdy
    1, // Houndour          Early Bird/Flash Fire
    1, // Houndoom          Early Bird/Flash Fire
    0, // Kingdra           Swift Swim
    0, // Phanpy            Pickup
    0, // Donphan           Sturdy
    0, // Porygon2          Trace
    0, // Stantler          Intimidate
    0, // Smeargle          Own Tempo
    0, // Tyrogue           Guts
    0, // Hitmontop         Intimidate
    0, // Smoochum          Oblivious
    0, // Elekid            Static
    0, // Magby             Flame Body
    0, // Miltank           Thick Fat
    1, // Blissey           Natural Cure/Serene Grace
    0, // Raikou            Pressure
    0, // Entei             Pressure
    0, // Suicune           Pressure
    0, // Larvitar          Guts
    0, // Pupitar           Shed Skin
    0, // Tyranitar         Sand Stream
    0, // Lugia             Pressure
    0, // Ho-Oh             Pressure
    0, // Celebi            Natural Cure
    0, // Treecko           Overgrow
};

const byte FIRST_MOVES[POKEMON_ARRAY_SIZE] = {
    // Data obtained through PokeAPI
    0,    // Offset the list to remove "off by one" errors
    0x21, // Bulbasaur       (tackle)
    0x21, // Ivysaur         (tackle)
    0x16, // Venusaur        (vine-whip)
    0x0a, // Charmander      (scratch)
    0x0a, // Charmeleon      (scratch)
    0x0a, // Charizard       (scratch)
    0x21, // Squirtle        (tackle)
    0x21, // Wartortle       (tackle)
    0x21, // Blastoise       (tackle)
    0x21, // Caterpie        (tackle)
    0x6a, // Metapod         (harden)
    0x5d, // Butterfree      (confusion)
    0x28, // Weedle          (poison-sting)
    0x6a, // Kakuna          (harden)
    0x1f, // Beedrill        (fury-attack)
    0x21, // Pidgey          (tackle)
    0x10, // Pidgeotto       (gust)
    0x10, // Pidgeot         (gust)
    0x21, // Rattata         (tackle)
    0x21, // Raticate        (tackle)
    0x2d, // Spearow         (growl)
    0x1f, // Fearow          (fury-attack)
    0x23, // Ekans           (wrap)
    0x23, // Arbok           (wrap)
    0x2d, // Pikachu         (growl)
    0x27, // Raichu          (tail-whip)
    0x0a, // Sandshrew       (scratch)
    0x0a, // Sandslash       (scratch)
    0x0a, // Nidoran-f       (scratch)
    0x0a, // Nidorina        (scratch)
    0x0a, // Nidoqueen       (scratch)
    0x2b, // Nidoran-m       (leer)
    0x2b, // Nidorino        (leer)
    0x18, // Nidoking        (double-kick)
    0x01, // Clefairy        (pound)
    0x03, // Clefable        (double-slap)
    0x34, // Vulpix          (ember)
    0x34, // Ninetales       (ember)
    0x2f, // Jigglypuff      (sing)
    0x03, // Wigglytuff      (double-slap)
    0x8d, // Zubat           (leech-life)
    0x30, // Golbat          (supersonic)
    0x47, // Oddish          (absorb)
    0x47, // Gloom           (absorb)
    0x47, // Vileplume       (absorb)
    0x0a, // Paras           (scratch)
    0x0a, // Parasect        (scratch)
    0x21, // Venonat         (tackle)
    0x21, // Venomoth        (tackle)
    0x0a, // Diglett         (scratch)
    0x0a, // Dugtrio         (scratch)
    0x0a, // Meowth          (scratch)
    0x0a, // Persian         (scratch)
    0x0a, // Psyduck         (scratch)
    0x0a, // Golduck         (scratch)
    0x0a, // Mankey          (scratch)
    0x0a, // Primeape        (scratch)
    0x2c, // Growlithe       (bite)
    0x2c, // Arcanine        (bite)
    0x91, // Poliwag         (bubble)
    0x37, // Poliwhirl       (water-gun)
    0x03, // Poliwrath       (double-slap)
    0x64, // Abra            (teleport)
    0x5d, // Kadabra         (confusion)
    0x5d, // Alakazam        (confusion)
    0x2b, // Machop          (leer)
    0x2b, // Machoke         (leer)
    0x2b, // Machamp         (leer)
    0x16, // Bellsprout      (vine-whip)
    0x16, // Weepinbell      (vine-whip)
    0x16, // Victreebel      (vine-whip)
    0x28, // Tentacool       (poison-sting)
    0x28, // Tentacruel      (poison-sting)
    0x21, // Geodude         (tackle)
    0x21, // Graveler        (tackle)
    0x21, // Golem           (tackle)
    0x21, // Ponyta          (tackle)
    0x21, // Rapidash        (tackle)
    0x21, // Slowpoke        (tackle)
    0x21, // Slowbro         (tackle)
    0x21, // Magnemite       (tackle)
    0x21, // Magneton        (tackle)
    0x40, // Farfetchd       (peck)
    0x2d, // Doduo           (growl)
    0x1f, // Dodrio          (fury-attack)
    0x1d, // Seel            (headbutt)
    0x1d, // Dewgong         (headbutt)
    0x01, // Grimer          (pound)
    0x01, // Muk             (pound)
    0x21, // Shellder        (tackle)
    0x30, // Cloyster        (supersonic)
    0x5f, // Gastly          (hypnosis)
    0x5f, // Haunter         (hypnosis)
    0x5f, // Gengar          (hypnosis)
    0x21, // Onix            (tackle)
    0x01, // Drowzee         (pound)
    0x01, // Hypno           (pound)
    0x91, // Krabby          (bubble)
    0x0b, // Kingler         (vice-grip)
    0x21, // Voltorb         (tackle)
    0x21, // Electrode       (tackle)
    0x5f, // Exeggcute       (hypnosis)
    0x5d, // Exeggutor       (confusion)
    0x2d, // Cubone          (growl)
    0x1d, // Marowak         (headbutt)
    0x18, // Hitmonlee       (double-kick)
    0x04, // Hitmonchan      (comet-punch)
    0x7a, // Lickitung       (lick)
    0x21, // Koffing         (tackle)
    0x21, // Weezing         (tackle)
    0x1e, // Rhyhorn         (horn-attack)
    0x17, // Rhydon          (stomp)
    0x01, // Chansey         (pound)
    0x84, // Tangela         (constrict)
    0x04, // Kangaskhan      (comet-punch)
    0x91, // Horsea          (bubble)
    0x2b, // Seadra          (leer)
    0x27, // Goldeen         (tail-whip)
    0x27, // Seaking         (tail-whip)
    0x21, // Staryu          (tackle)
    0x37, // Starmie         (water-gun)
    0x70, // Mr-mime         (barrier)
    0x2b, // Scyther         (leer)
    0x01, // Jynx            (pound)
    0x09, // Electabuzz      (thunder-punch)
    0x07, // Magmar          (fire-punch)
    0x0b, // Pinsir          (vice-grip)
    0x21, // Tauros          (tackle)
    0x96, // Magikarp        (splash)
    0x25, // Gyarados        (thrash)
    0x2d, // Lapras          (growl)
    0x90, // Ditto           (transform)
    0x21, // Eevee           (tackle)
    0x21, // Vaporeon        (tackle)
    0x21, // Jolteon         (tackle)
    0x21, // Flareon         (tackle)
    0x21, // Porygon         (tackle)
    0x6e, // Omanyte         (withdraw)
    0x2c, // Omastar         (bite)
    0x0a, // Kabuto          (scratch)
    0x0a, // Kabutops        (scratch)
    0x11, // Aerodactyl      (wing-attack)
    0x21, // Snorlax         (tackle)
    0x10, // Articuno        (gust)
    0x40, // Zapdos          (peck)
    0x11, // Moltres         (wing-attack)
    0x23, // Dratini         (wrap)
    0x23, // Dragonair       (wrap)
    0x23, // Dragonite       (wrap)
    0x32, // Mewtwo          (disable)
    0x01, // Mew             (pound)
    0x21, // Chikorita       (tackle)
    0x21, // Bayleef         (tackle)
    0x21, // Meganium        (tackle)
    0x21, // Cyndaquil       (tackle)
    0x21, // Quilava         (tackle)
    0x21, // Typhlosion      (tackle)
    0x0a, // Totodile        (scratch)
    0x0a, // Croconaw        (scratch)
    0x0a, // Feraligatr      (scratch)
    0x0a, // Sentret         (scratch)
    0x0a, // Furret          (scratch)
    0x21, // Hoothoot        (tackle)
    0x21, // Noctowl         (tackle)
    0x21, // Ledyba          (tackle)
    0x21, // Ledian          (tackle)
    0x28, // Spinarak        (poison-sting)
    0x28, // Ariados         (poison-sting)
    0x30, // Crobat          (supersonic)
    0x56, // Chinchou        (thunder-wave)
    0x30, // Lanturn         (supersonic)
    0x54, // Pichu           (thunder-shock)
    0x01, // Cleffa          (pound)
    0x2f, // Igglybuff       (sing)
    0x2d, // Togepi          (growl)
    0x2d, // Togetic         (growl)
    0x2b, // Natu            (leer)
    0x2b, // Xatu            (leer)
    0x21, // Mareep          (tackle)
    0x21, // Flaaffy         (tackle)
    0x21, // Ampharos        (tackle)
    0x47, // Bellossom       (absorb)
    0x21, // Marill          (tackle)
    0x21, // Azumarill       (tackle)
    0x58, // Sudowoodo       (rock-throw)
    0x03, // Politoed        (double-slap)
    0x96, // Hoppip          (splash)
    0x21, // Skiploom        (tackle)
    0x21, // Jumpluff        (tackle)
    0x0a, // Aipom           (scratch)
    0x47, // Sunkern         (absorb)
    0x01, // Sunflora        (pound)
    0x21, // Yanma           (tackle)
    0x27, // Wooper          (tail-whip)
    0x27, // Quagsire        (tail-whip)
    0x21, // Espeon          (tackle)
    0x21, // Umbreon         (tackle)
    0x40, // Murkrow         (peck)
    0x21, // Slowking        (tackle)
    0x2d, // Misdreavus      (growl)
    0xed, // Unown           (hidden-power)
    0x44, // Wobbuffet       (counter)
    0x21, // Girafarig       (tackle)
    0x21, // Pineco          (tackle)
    0x21, // Forretress      (tackle)
    0x63, // Dunsparce       (rage)
    0x28, // Gligar          (poison-sting)
    0x21, // Steelix         (tackle)
    0x21, // Snubbull        (tackle)
    0x21, // Granbull        (tackle)
    0x21, // Qwilfish        (tackle)
    0x2b, // Scizor          (leer)
    0x6e, // Shuckle         (withdraw)
    0x21, // Heracross       (tackle)
    0x0a, // Sneasel         (scratch)
    0x0a, // Teddiursa       (scratch)
    0x0a, // Ursaring        (scratch)
    0x7b, // Slugma          (smog)
    0x34, // Magcargo        (ember)
    0x21, // Swinub          (tackle)
    0x1e, // Piloswine       (horn-attack)
    0x21, // Corsola         (tackle)
    0x37, // Remoraid        (water-gun)
    0x37, // Octillery       (water-gun)
    0xd9, // Delibird        (present)
    0x21, // Mantine         (tackle)
    0x2b, // Skarmory        (leer)
    0x2b, // Houndour        (leer)
    0x2b, // Houndoom        (leer)
    0x2b, // Kingdra         (leer)
    0x21, // Phanpy          (tackle)
    0x1e, // Donphan         (horn-attack)
    0x21, // Porygon2        (tackle)
    0x21, // Stantler        (tackle)
    0xa6, // Smeargle        (sketch)
    0x21, // Tyrogue         (tackle)
    0x1b, // Hitmontop       (rolling-kick)
    0x01, // Smoochum        (pound)
    0x2b, // Elekid          (leer)
    0x34, // Magby           (ember)
    0x21, // Miltank         (tackle)
    0x01, // Blissey         (pound)
    0x2b, // Raikou          (leer)
    0x2b, // Entei           (leer)
    0x2b, // Suicune         (leer)
    0x2b, // Larvitar        (leer)
    0x2b, // Pupitar         (leer)
    0x2b, // Tyranitar       (leer)
    0x12, // Lugia           (whirlwind)
    0x12, // Ho-oh           (whirlwind)
    0x49, // Celebi          (leech-seed)
    0x01, // Treecko         (pound)
};

const u16 JPN_NAMES[POKEMON_ARRAY_SIZE][6]{
    {},                                              // Offset the list to remove "off by one" errors
    {0x30D5, 0x30B7, 0x30AE, 0x30C0, 0x30CD, 0x19E}, // Bulbasaur
    {0x30D5, 0x30B7, 0x30AE, 0x30BD, 0x30A6, 0x19E}, // Ivysaur
    {0x30D5, 0x30B7, 0x30AE, 0x30D0, 0x30CA, 0x19E}, // Venusaur
    {0x30D2, 0x30C8, 0x30AB, 0x30B2, 0x19E},         // Charmander
    {0x30EA, 0x30B6, 0x30FC, 0x30C9, 0x19E},         // Charmeleon
    {0x30EA, 0x30B6, 0x30FC, 0x30C9, 0x30F3, 0x19E}, // Charizard
    {0x30BC, 0x30CB, 0x30AC, 0x30E1, 0x19E},         // Squirtle
    {0x30AB, 0x30E1, 0x30FC, 0x30EB, 0x19E},         // Wartortle
    {0x30AB, 0x30E1, 0x30C3, 0x30AF, 0x30B9, 0x19E}, // Blastoise
    {0x30AD, 0x30E3, 0x30BF, 0x30D4, 0x30FC, 0x19E}, // Caterpie
    {0x30C8, 0x30E9, 0x30F3, 0x30BB, 0x30EB, 0x19E}, // Metapod
    {0x30D0, 0x30BF, 0x30D5, 0x30EA, 0x30FC, 0x19E}, // Butterfree
    {0x30D3, 0x30FC, 0x30C9, 0x30EB, 0x19E},         // Weedle
    {0x30B3, 0x30AF, 0x30FC, 0x30F3, 0x19E},         // Kakuna
    {0x30B9, 0x30D4, 0x30A2, 0x30FC, 0x19E},         // Beedrill
    {0x30DD, 0x30C3, 0x30DD, 0x19E},                 // Pidgey
    {0x30D4, 0x30B8, 0x30E7, 0x30F3, 0x19E},         // Pidgeotto
    {0x30D4, 0x30B8, 0x30E7, 0x30C3, 0x30C8, 0x19E}, // Pidgeot
    {0x30B3, 0x30E9, 0x30C3, 0x30BF, 0x19E},         // Rattata
    {0x30E9, 0x30C3, 0x30BF, 0x19E},                 // Raticate
    {0x30AA, 0x30CB, 0x30B9, 0x30BA, 0x30E1, 0x19E}, // Spearow
    {0x30AA, 0x30CB, 0x30C9, 0x30EA, 0x30EB, 0x19E}, // Fearow
    {0x30A2, 0x30FC, 0x30DC, 0x19E},                 // Ekans
    {0x30A2, 0x30FC, 0x30DC, 0x30C3, 0x30AF, 0x19E}, // Arbok
    {0x30D4, 0x30AB, 0x30C1, 0x30E5, 0x30A6, 0x19E}, // Pikachu
    {0x30E9, 0x30A4, 0x30C1, 0x30E5, 0x30A6, 0x19E}, // Raichu
    {0x30B5, 0x30F3, 0x30C9, 0x19E},                 // Sandshrew
    {0x30B5, 0x30F3, 0x30C9, 0x30D1, 0x30F3, 0x19E}, // Sandslash
    {0x30CB, 0x30C9, 0x30E9, 0x30F3, 0x2640, 0x19E}, // Nidoran♀
    {0x30CB, 0x30C9, 0x30EA, 0x30FC, 0x30CA, 0x19E}, // Nidorina
    {0x30CB, 0x30C9, 0x30AF, 0x30A4, 0x30F3, 0x19E}, // Nidoqueen
    {0x30CB, 0x30C9, 0x30E9, 0x30F3, 0x2642, 0x19E}, // Nidoran♂
    {0x30CB, 0x30C9, 0x30EA, 0x30FC, 0x30CE, 0x19E}, // Nidorino
    {0x30CB, 0x30C9, 0x30AD, 0x30F3, 0x30B0, 0x19E}, // Nidoking
    {0x30D4, 0x30C3, 0x30D4, 0x19E},                 // Clefairy
    {0x30D4, 0x30AF, 0x30B7, 0x30FC, 0x19E},         // Clefable
    {0x30ED, 0x30B3, 0x30F3, 0x19E},                 // Vulpix
    {0x30AD, 0x30E5, 0x30A6, 0x30B3, 0x30F3, 0x19E}, // Ninetales
    {0x30D7, 0x30EA, 0x30F3, 0x19E},                 // Jigglypuff
    {0x30D7, 0x30AF, 0x30EA, 0x30F3, 0x19E},         // Wigglytuff
    {0x30BA, 0x30D0, 0x30C3, 0x30C8, 0x19E},         // Zubat
    {0x30B4, 0x30EB, 0x30D0, 0x30C3, 0x30C8, 0x19E}, // Golbat
    {0x30CA, 0x30BE, 0x30CE, 0x30AF, 0x30B5, 0x19E}, // Oddish
    {0x30AF, 0x30B5, 0x30A4, 0x30CF, 0x30CA, 0x19E}, // Gloom
    {0x30E9, 0x30D5, 0x30EC, 0x30B7, 0x30A2, 0x19E}, // Vileplume
    {0x30D1, 0x30E9, 0x30B9, 0x19E},                 // Paras
    {0x30D1, 0x30E9, 0x30BB, 0x30AF, 0x30C8, 0x19E}, // Parasect
    {0x30B3, 0x30F3, 0x30D1, 0x30F3, 0x19E},         // Venonat
    {0x30E2, 0x30EB, 0x30D5, 0x30A9, 0x30F3, 0x19E}, // Venomoth
    {0x30C7, 0x30A3, 0x30B0, 0x30C0, 0x19E},         // Diglett
    {0x30C0, 0x30B0, 0x30C8, 0x30EA, 0x30AA, 0x19E}, // Dugtrio
    {0x30CB, 0x30E3, 0x30FC, 0x30B9, 0x19E},         // Meowth
    {0x30DA, 0x30EB, 0x30B7, 0x30A2, 0x30F3, 0x19E}, // Persian
    {0x30B3, 0x30C0, 0x30C3, 0x30AF, 0x19E},         // Psyduck
    {0x30B4, 0x30EB, 0x30C0, 0x30C3, 0x30AF, 0x19E}, // Golduck
    {0x30DE, 0x30F3, 0x30AD, 0x30FC, 0x19E},         // Mankey
    {0x30AA, 0x30B3, 0x30EA, 0x30B6, 0x30EB, 0x19E}, // Primeape
    {0x30AC, 0x30FC, 0x30C7, 0x30A3, 0x19E},         // Growlithe
    {0x30A6, 0x30A4, 0x30F3, 0x30C7, 0x30A3, 0x19E}, // Arcanine
    {0x30CB, 0x30E7, 0x30ED, 0x30E2, 0x19E},         // Poliwag
    {0x30CB, 0x30E7, 0x30ED, 0x30BE, 0x19E},         // Poliwhirl
    {0x30CB, 0x30E7, 0x30ED, 0x30DC, 0x30F3, 0x19E}, // Poliwrath
    {0x30B1, 0x30FC, 0x30B7, 0x30A3, 0x19E},         // Abra
    {0x30E6, 0x30F3, 0x30B2, 0x30E9, 0x30FC, 0x19E}, // Kadabra
    {0x30D5, 0x30FC, 0x30C7, 0x30A3, 0x30F3, 0x19E}, // Alakazam
    {0x30EF, 0x30F3, 0x30EA, 0x30AD, 0x30FC, 0x19E}, // Machop
    {0x30B4, 0x30FC, 0x30EA, 0x30AD, 0x30FC, 0x19E}, // Machoke
    {0x30AB, 0x30A4, 0x30EA, 0x30AD, 0x30FC, 0x19E}, // Machamp
    {0x30DE, 0x30C0, 0x30C4, 0x30DC, 0x30DF, 0x19E}, // Bellsprout
    {0x30A6, 0x30C4, 0x30C9, 0x30F3, 0x19E},         // Weepinbell
    {0x30A6, 0x30C4, 0x30DC, 0x30C3, 0x30C8, 0x19E}, // Victreebel
    {0x30E1, 0x30CE, 0x30AF, 0x30E9, 0x30B2, 0x19E}, // Tentacool
    {0x30C9, 0x30AF, 0x30AF, 0x30E9, 0x30B2, 0x19E}, // Tentacruel
    {0x30A4, 0x30B7, 0x30C4, 0x30D6, 0x30C6, 0x19E}, // Geodude
    {0x30B4, 0x30ED, 0x30FC, 0x30F3, 0x19E},         // Graveler
    {0x30B4, 0x30ED, 0x30FC, 0x30CB, 0x30E3, 0x19E}, // Golem
    {0x30DD, 0x30CB, 0x30FC, 0x30BF, 0x19E},         // Ponyta
    {0x30AE, 0x30E3, 0x30ED, 0x30C3, 0x30D7, 0x19E}, // Rapidash
    {0x30E4, 0x30C9, 0x30F3, 0x19E},                 // Slowpoke
    {0x30E4, 0x30C9, 0x30E9, 0x30F3, 0x19E},         // Slowbro
    {0x30B3, 0x30A4, 0x30EB, 0x19E},                 // Magnemite
    {0x30EC, 0x30A2, 0x30B3, 0x30A4, 0x30EB, 0x19E}, // Magneton
    {0x30AB, 0x30E2, 0x30CD, 0x30AE, 0x19E},         // Farfetch'd
    {0x30C9, 0x30FC, 0x30C9, 0x30FC, 0x19E},         // Doduo
    {0x30C9, 0x30FC, 0x30C9, 0x30EA, 0x30AA, 0x19E}, // Dodrio
    {0x30D1, 0x30A6, 0x30EF, 0x30A6, 0x19E},         // Seel
    {0x30B8, 0x30E5, 0x30B4, 0x30F3, 0x19E},         // Dewgong
    {0x30D9, 0x30C8, 0x30D9, 0x30BF, 0x30FC, 0x19E}, // Grimer
    {0x30D9, 0x30C8, 0x30D9, 0x30C8, 0x30F3, 0x19E}, // Muk
    {0x30B7, 0x30A7, 0x30EB, 0x30C0, 0x30FC, 0x19E}, // Shellder
    {0x30D1, 0x30EB, 0x30B7, 0x30A7, 0x30F3, 0x19E}, // Cloyster
    {0x30B4, 0x30FC, 0x30B9, 0x19E},                 // Gastly
    {0x30B4, 0x30FC, 0x30B9, 0x30C8, 0x19E},         // Haunter
    {0x30B2, 0x30F3, 0x30AC, 0x30FC, 0x19E},         // Gengar
    {0x30A4, 0x30EF, 0x30FC, 0x30AF, 0x19E},         // Onix
    {0x30B9, 0x30EA, 0x30FC, 0x30D7, 0x19E},         // Drowzee
    {0x30B9, 0x30EA, 0x30FC, 0x30D1, 0x30FC, 0x19E}, // Hypno
    {0x30AF, 0x30E9, 0x30D6, 0x19E},                 // Krabby
    {0x30AD, 0x30F3, 0x30B0, 0x30E9, 0x30FC, 0x19E}, // Kingler
    {0x30D3, 0x30EA, 0x30EA, 0x30C0, 0x30DE, 0x19E}, // Voltorb
    {0x30DE, 0x30EB, 0x30DE, 0x30A4, 0x30F3, 0x19E}, // Electrode
    {0x30BF, 0x30DE, 0x30BF, 0x30DE, 0x19E},         // Exeggcute
    {0x30CA, 0x30C3, 0x30B7, 0x30FC, 0x19E},         // Exeggutor
    {0x30AB, 0x30E9, 0x30AB, 0x30E9, 0x19E},         // Cubone
    {0x30AC, 0x30E9, 0x30AC, 0x30E9, 0x19E},         // Marowak
    {0x30B5, 0x30EF, 0x30E0, 0x30E9, 0x30FC, 0x19E}, // Hitmonlee
    {0x30A8, 0x30D3, 0x30EF, 0x30E9, 0x30FC, 0x19E}, // Hitmonchan
    {0x30D9, 0x30ED, 0x30EA, 0x30F3, 0x30AC, 0x19E}, // Lickitung
    {0x30C9, 0x30AC, 0x30FC, 0x30B9, 0x19E},         // Koffing
    {0x30DE, 0x30BF, 0x30C9, 0x30AC, 0x30B9, 0x19E}, // Weezing
    {0x30B5, 0x30A4, 0x30DB, 0x30FC, 0x30F3, 0x19E}, // Rhyhorn
    {0x30B5, 0x30A4, 0x30C9, 0x30F3, 0x19E},         // Rhydon
    {0x30E9, 0x30C3, 0x30AD, 0x30FC, 0x19E},         // Chansey
    {0x30E2, 0x30F3, 0x30B8, 0x30E3, 0x30E9, 0x19E}, // Tangela
    {0x30AC, 0x30EB, 0x30FC, 0x30E9, 0x19E},         // Kangaskhan
    {0x30BF, 0x30C3, 0x30C4, 0x30FC, 0x19E},         // Horsea
    {0x30B7, 0x30FC, 0x30C9, 0x30E9, 0x19E},         // Seadra
    {0x30C8, 0x30B5, 0x30AD, 0x30F3, 0x30C8, 0x19E}, // Goldeen
    {0x30A2, 0x30BA, 0x30DE, 0x30AA, 0x30A6, 0x19E}, // Seaking
    {0x30D2, 0x30C8, 0x30C7, 0x30DE, 0x30F3, 0x19E}, // Staryu
    {0x30B9, 0x30BF, 0x30FC, 0x30DF, 0x30FC, 0x19E}, // Starmie
    {0x30D0, 0x30EA, 0x30E4, 0x30FC, 0x30C9, 0x19E}, // Mr. Mime
    {0x30B9, 0x30C8, 0x30E9, 0x30A4, 0x30AF, 0x19E}, // Scyther
    {0x30EB, 0x30FC, 0x30B8, 0x30E5, 0x30E9, 0x19E}, // Jynx
    {0x30A8, 0x30EC, 0x30D6, 0x30FC, 0x19E},         // Electabuzz
    {0x30D6, 0x30FC, 0x30D0, 0x30FC, 0x19E},         // Magmar
    {0x30AB, 0x30A4, 0x30ED, 0x30B9, 0x19E},         // Pinsir
    {0x30B1, 0x30F3, 0x30BF, 0x30ED, 0x30B9, 0x19E}, // Tauros
    {0x30B3, 0x30A4, 0x30AD, 0x30F3, 0x30B0, 0x19E}, // Magikarp
    {0x30AE, 0x30E3, 0x30E9, 0x30C9, 0x30B9, 0x19E}, // Gyarados
    {0x30E9, 0x30D7, 0x30E9, 0x30B9, 0x19E},         // Lapras
    {0x30E1, 0x30BF, 0x30E2, 0x30F3, 0x19E},         // Ditto
    {0x30A4, 0x30FC, 0x30D6, 0x30A4, 0x19E},         // Eevee
    {0x30B7, 0x30E3, 0x30EF, 0x30FC, 0x30BA, 0x19E}, // Vaporeon
    {0x30B5, 0x30F3, 0x30C0, 0x30FC, 0x30B9, 0x19E}, // Jolteon
    {0x30D6, 0x30FC, 0x30B9, 0x30BF, 0x30FC, 0x19E}, // Flareon
    {0x30DD, 0x30EA, 0x30B4, 0x30F3, 0x19E},         // Porygon
    {0x30AA, 0x30E0, 0x30CA, 0x30A4, 0x30C8, 0x19E}, // Omanyte
    {0x30AA, 0x30E0, 0x30B9, 0x30BF, 0x30FC, 0x19E}, // Omastar
    {0x30AB, 0x30D6, 0x30C8, 0x19E},                 // Kabuto
    {0x30AB, 0x30D6, 0x30C8, 0x30D7, 0x30B9, 0x19E}, // Kabutops
    {0x30D7, 0x30C6, 0x30E9, 0x19E},                 // Aerodactyl
    {0x30AB, 0x30D3, 0x30B4, 0x30F3, 0x19E},         // Snorlax
    {0x30D5, 0x30EA, 0x30FC, 0x30B6, 0x30FC, 0x19E}, // Articuno
    {0x30B5, 0x30F3, 0x30C0, 0x30FC, 0x19E},         // Zapdos
    {0x30D5, 0x30A1, 0x30A4, 0x30E4, 0x30FC, 0x19E}, // Moltres
    {0x30DF, 0x30CB, 0x30EA, 0x30E5, 0x30A6, 0x19E}, // Dratini
    {0x30CF, 0x30AF, 0x30EA, 0x30E5, 0x30FC, 0x19E}, // Dragonair
    {0x30AB, 0x30A4, 0x30EA, 0x30E5, 0x30FC, 0x19E}, // Dragonite
    {0x30DF, 0x30E5, 0x30A6, 0x30C4, 0x30FC, 0x19E}, // Mewtwo
    {0x30DF, 0x30E5, 0x30A6, 0x19E},                 // Mew
    {0x30C1, 0x30B3, 0x30EA, 0x30FC, 0x30BF, 0x19E}, // Chikorita
    {0x30D9, 0x30A4, 0x30EA, 0x30FC, 0x30D5, 0x19E}, // Bayleef
    {0x30E1, 0x30AC, 0x30CB, 0x30A6, 0x30E0, 0x19E}, // Meganium
    {0x30D2, 0x30CE, 0x30A2, 0x30E9, 0x30B7, 0x19E}, // Cyndaquil
    {0x30DE, 0x30B0, 0x30DE, 0x30E9, 0x30B7, 0x19E}, // Quilava
    {0x30D0, 0x30AF, 0x30D5, 0x30FC, 0x30F3, 0x19E}, // Typhlosion
    {0x30EF, 0x30CB, 0x30CE, 0x30B3, 0x19E},         // Totodile
    {0x30A2, 0x30EA, 0x30B2, 0x30A4, 0x30C4, 0x19E}, // Croconaw
    {0x30AA, 0x30FC, 0x30C0, 0x30A4, 0x30EB, 0x19E}, // Feraligatr
    {0x30AA, 0x30BF, 0x30C1, 0x19E},                 // Sentret
    {0x30AA, 0x30AA, 0x30BF, 0x30C1, 0x19E},         // Furret
    {0x30DB, 0x30FC, 0x30DB, 0x30FC, 0x19E},         // Hoothoot
    {0x30E8, 0x30EB, 0x30CE, 0x30BA, 0x30AF, 0x19E}, // Noctowl
    {0x30EC, 0x30C7, 0x30A3, 0x30D0, 0x19E},         // Ledyba
    {0x30EC, 0x30C7, 0x30A3, 0x30A2, 0x30F3, 0x19E}, // Ledian
    {0x30A4, 0x30C8, 0x30DE, 0x30EB, 0x19E},         // Spinarak
    {0x30A2, 0x30EA, 0x30A2, 0x30C9, 0x30B9, 0x19E}, // Ariados
    {0x30AF, 0x30ED, 0x30D0, 0x30C3, 0x30C8, 0x19E}, // Crobat
    {0x30C1, 0x30E7, 0x30F3, 0x30C1, 0x30FC, 0x19E}, // Chinchou
    {0x30E9, 0x30F3, 0x30BF, 0x30FC, 0x30F3, 0x19E}, // Lanturn
    {0x30D4, 0x30C1, 0x30E5, 0x30FC, 0x19E},         // Pichu
    {0x30D4, 0x30A3, 0x19E},                         // Cleffa
    {0x30D7, 0x30D7, 0x30EA, 0x30F3, 0x19E},         // Igglybuff
    {0x30C8, 0x30B2, 0x30D4, 0x30FC, 0x19E},         // Togepi
    {0x30C8, 0x30B2, 0x30C1, 0x30C3, 0x30AF, 0x19E}, // Togetic
    {0x30CD, 0x30A4, 0x30C6, 0x30A3, 0x19E},         // Natu
    {0x30CD, 0x30A4, 0x30C6, 0x30A3, 0x30AA, 0x19E}, // Xatu
    {0x30E1, 0x30EA, 0x30FC, 0x30D7, 0x19E},         // Mareep
    {0x30E2, 0x30B3, 0x30B3, 0x19E},                 // Flaaffy
    {0x30C7, 0x30F3, 0x30EA, 0x30E5, 0x30A6, 0x19E}, // Ampharos
    {0x30AD, 0x30EC, 0x30A4, 0x30CF, 0x30CA, 0x19E}, // Bellossom
    {0x30DE, 0x30EA, 0x30EB, 0x19E},                 // Marill
    {0x30DE, 0x30EA, 0x30EB, 0x30EA, 0x19E},         // Azumarill
    {0x30A6, 0x30BD, 0x30C3, 0x30AD, 0x30FC, 0x19E}, // Sudowoodo
    {0x30CB, 0x30E7, 0x30ED, 0x30C8, 0x30CE, 0x19E}, // Politoed
    {0x30CF, 0x30CD, 0x30C3, 0x30B3, 0x19E},         // Hoppip
    {0x30DD, 0x30DD, 0x30C3, 0x30B3, 0x19E},         // Skiploom
    {0x30EF, 0x30BF, 0x30C3, 0x30B3, 0x19E},         // Jumpluff
    {0x30A8, 0x30A4, 0x30D1, 0x30E0, 0x19E},         // Aipom
    {0x30D2, 0x30DE, 0x30CA, 0x30C3, 0x30C4, 0x19E}, // Sunkern
    {0x30AD, 0x30DE, 0x30EF, 0x30EA, 0x19E},         // Sunflora
    {0x30E4, 0x30F3, 0x30E4, 0x30F3, 0x30DE, 0x19E}, // Yanma
    {0x30A6, 0x30D1, 0x30FC, 0x19E},                 // Wooper
    {0x30CC, 0x30AA, 0x30FC, 0x19E},                 // Quagsire
    {0x30A8, 0x30FC, 0x30D5, 0x30A3, 0x19E},         // Espeon
    {0x30D6, 0x30E9, 0x30C3, 0x30AD, 0x30FC, 0x19E}, // Umbreon
    {0x30E4, 0x30DF, 0x30AB, 0x30E9, 0x30B9, 0x19E}, // Murkrow
    {0x30E4, 0x30C9, 0x30AD, 0x30F3, 0x30B0, 0x19E}, // Slowking
    {0x30E0, 0x30A6, 0x30DE, 0x19E},                 // Misdreavus
    {0x30A2, 0x30F3, 0x30CE, 0x30FC, 0x30F3, 0x19E}, // Unown
    {0x30BD, 0x30FC, 0x30CA, 0x30F3, 0x30B9, 0x19E}, // Wobbuffet
    {0x30AD, 0x30EA, 0x30F3, 0x30EA, 0x30AD, 0x19E}, // Girafarig
    {0x30AF, 0x30CC, 0x30AE, 0x30C0, 0x30DE, 0x19E}, // Pineco
    {0x30D5, 0x30A9, 0x30EC, 0x30C8, 0x30B9, 0x19E}, // Forretress
    {0x30CE, 0x30B3, 0x30C3, 0x30C1, 0x19E},         // Dunsparce
    {0x30B0, 0x30E9, 0x30A4, 0x30AC, 0x30FC, 0x19E}, // Gligar
    {0x30CF, 0x30AC, 0x30CD, 0x30FC, 0x30EB, 0x19E}, // Steelix
    {0x30D6, 0x30EB, 0x30FC, 0x19E},                 // Snubbull
    {0x30B0, 0x30E9, 0x30F3, 0x30D6, 0x30EB, 0x19E}, // Granbull
    {0x30CF, 0x30EA, 0x30FC, 0x30BB, 0x30F3, 0x19E}, // Qwilfish
    {0x30CF, 0x30C3, 0x30B5, 0x30E0, 0x19E},         // Scizor
    {0x30C4, 0x30DC, 0x30C4, 0x30DC, 0x19E},         // Shuckle
    {0x30D8, 0x30E9, 0x30AF, 0x30ED, 0x30B9, 0x19E}, // Heracross
    {0x30CB, 0x30E5, 0x30FC, 0x30E9, 0x19E},         // Sneasel
    {0x30D2, 0x30E1, 0x30B0, 0x30DE, 0x19E},         // Teddiursa
    {0x30EA, 0x30F3, 0x30B0, 0x30DE, 0x19E},         // Ursaring
    {0x30DE, 0x30B0, 0x30DE, 0x30C3, 0x30B0, 0x19E}, // Slugma
    {0x30DE, 0x30B0, 0x30AB, 0x30EB, 0x30B4, 0x19E}, // Magcargo
    {0x30A6, 0x30EA, 0x30E0, 0x30FC, 0x19E},         // Swinub
    {0x30A4, 0x30CE, 0x30E0, 0x30FC, 0x19E},         // Piloswine
    {0x30B5, 0x30CB, 0x30FC, 0x30B4, 0x19E},         // Corsola
    {0x30C6, 0x30C3, 0x30DD, 0x30A6, 0x30AA, 0x19E}, // Remoraid
    {0x30AA, 0x30AF, 0x30BF, 0x30F3, 0x19E},         // Octillery
    {0x30C7, 0x30EA, 0x30D0, 0x30FC, 0x30C9, 0x19E}, // Delibird
    {0x30DE, 0x30F3, 0x30BF, 0x30A4, 0x30F3, 0x19E}, // Mantine
    {0x30A8, 0x30A2, 0x30FC, 0x30E0, 0x30C9, 0x19E}, // Skarmory
    {0x30C7, 0x30EB, 0x30D3, 0x30EB, 0x19E},         // Houndour
    {0x30D8, 0x30EB, 0x30AC, 0x30FC, 0x19E},         // Houndoom
    {0x30AD, 0x30F3, 0x30B0, 0x30C9, 0x30E9, 0x19E}, // Kingdra
    {0x30B4, 0x30DE, 0x30BE, 0x30A6, 0x19E},         // Phanpy
    {0x30C9, 0x30F3, 0x30D5, 0x30A1, 0x30F3, 0x19E}, // Donphan
    {0x30DD, 0x30EA, 0x30B4, 0x30F3, 0xFF12, 0x19E}, // Porygon2
    {0x30AA, 0x30C9, 0x30B7, 0x30B7, 0x19E},         // Stantler
    {0x30C9, 0x30FC, 0x30D6, 0x30EB, 0x19E},         // Smeargle
    {0x30D0, 0x30EB, 0x30AD, 0x30FC, 0x19E},         // Tyrogue
    {0x30AB, 0x30DD, 0x30A8, 0x30E9, 0x30FC, 0x19E}, // Hitmontop
    {0x30E0, 0x30C1, 0x30E5, 0x30FC, 0x30EB, 0x19E}, // Smoochum
    {0x30A8, 0x30EC, 0x30AD, 0x30C3, 0x30C9, 0x19E}, // Elekid
    {0x30D6, 0x30D3, 0x30A3, 0x19E},                 // Magby
    {0x30DF, 0x30EB, 0x30BF, 0x30F3, 0x30AF, 0x19E}, // Miltank
    {0x30CF, 0x30D4, 0x30CA, 0x30B9, 0x19E},         // Blissey
    {0x30E9, 0x30A4, 0x30B3, 0x30A6, 0x19E},         // Raikou
    {0x30A8, 0x30F3, 0x30C6, 0x30A4, 0x19E},         // Entei
    {0x30B9, 0x30A4, 0x30AF, 0x30F3, 0x19E},         // Suicune
    {0x30E8, 0x30FC, 0x30AE, 0x30E9, 0x30B9, 0x19E}, // Larvitar
    {0x30B5, 0x30CA, 0x30AE, 0x30E9, 0x30B9, 0x19E}, // Pupitar
    {0x30D0, 0x30F3, 0x30AE, 0x30E9, 0x30B9, 0x19E}, // Tyranitar
    {0x30EB, 0x30AE, 0x30A2, 0x19E},                 // Lugia
    {0x30DB, 0x30A6, 0x30AA, 0x30A6, 0x19E},         // Ho-Oh
    {0x30BB, 0x30EC, 0x30D3, 0x30A3, 0x19E},         // Celebi
    {0x30AD, 0x30E2, 0x30EA},                        // Treecko
};

const u8 POWER_POINTS[252]{
    0,  // Offset the list to remove "off by one" errors
    35, // Pound
    25, // Karate-chop
    10, // Double-slap
    15, // Comet-punch
    20, // Mega-punch
    20, // Pay-day
    15, // Fire-punch
    15, // Ice-punch
    15, // Thunder-punch
    35, // Scratch
    30, // Vice-grip
    5,  // Guillotine
    10, // Razor-wind
    20, // Swords-dance
    30, // Cut
    35, // Gust
    35, // Wing-attack
    20, // Whirlwind
    15, // Fly
    20, // Bind
    20, // Slam
    25, // Vine-whip
    20, // Stomp
    30, // Double-kick
    5,  // Mega-kick
    10, // Jump-kick
    15, // Rolling-kick
    15, // Sand-attack
    15, // Headbutt
    25, // Horn-attack
    20, // Fury-attack
    5,  // Horn-drill
    35, // Tackle
    15, // Body-slam
    20, // Wrap
    20, // Take-down
    10, // Thrash
    15, // Double-edge
    30, // Tail-whip
    35, // Poison-sting
    20, // Twineedle
    20, // Pin-missile
    30, // Leer
    25, // Bite
    40, // Growl
    20, // Roar
    15, // Sing
    20, // Supersonic
    20, // Sonic-boom
    20, // Disable
    30, // Acid
    25, // Ember
    15, // Flamethrower
    30, // Mist
    25, // Water-gun
    5,  // Hydro-pump
    15, // Surf
    10, // Ice-beam
    5,  // Blizzard
    20, // Psybeam
    20, // Bubble-beam
    20, // Aurora-beam
    5,  // Hyper-beam
    35, // Peck
    20, // Drill-peck
    20, // Submission
    20, // Low-kick
    20, // Counter
    20, // Seismic-toss
    15, // Strength
    25, // Absorb
    15, // Mega-drain
    10, // Leech-seed
    20, // Growth
    25, // Razor-leaf
    10, // Solar-beam
    35, // Poison-powder
    30, // Stun-spore
    15, // Sleep-powder
    10, // Petal-dance
    40, // String-shot
    10, // Dragon-rage
    15, // Fire-spin
    30, // Thunder-shock
    15, // Thunderbolt
    20, // Thunder-wave
    10, // Thunder
    15, // Rock-throw
    10, // Earthquake
    5,  // Fissure
    10, // Dig
    10, // Toxic
    25, // Confusion
    10, // Psychic
    20, // Hypnosis
    40, // Meditate
    30, // Agility
    30, // Quick-attack
    20, // Rage
    20, // Teleport
    15, // Night-shade
    10, // Mimic
    40, // Screech
    15, // Double-team
    10, // Recover
    30, // Harden
    10, // Minimize
    20, // Smokescreen
    10, // Confuse-ray
    40, // Withdraw
    40, // Defense-curl
    20, // Barrier
    30, // Light-screen
    30, // Haze
    20, // Reflect
    30, // Focus-energy
    10, // Bide
    10, // Metronome
    20, // Mirror-move
    5,  // Self-destruct
    10, // Egg-bomb
    30, // Lick
    20, // Smog
    20, // Sludge
    20, // Bone-club
    5,  // Fire-blast
    15, // Waterfall
    15, // Clamp
    20, // Swift
    10, // Skull-bash
    15, // Spike-cannon
    35, // Constrict
    20, // Amnesia
    15, // Kinesis
    10, // Soft-boiled
    10, // High-jump-kick
    30, // Glare
    15, // Dream-eater
    40, // Poison-gas
    20, // Barrage
    10, // Leech-life
    10, // Lovely-kiss
    5,  // Sky-attack
    10, // Transform
    30, // Bubble
    10, // Dizzy-punch
    15, // Spore
    20, // Flash
    15, // Psywave
    40, // Splash
    20, // Acid-armor
    10, // Crabhammer
    5,  // Explosion
    15, // Fury-swipes
    10, // Bonemerang
    10, // Rest
    10, // Rock-slide
    15, // Hyper-fang
    30, // Sharpen
    30, // Conversion
    10, // Tri-attack
    10, // Super-fang
    20, // Slash
    10, // Substitute
    1,  // Struggle
    1,  // Sketch
    10, // Triple-kick
    25, // Thief
    10, // Spider-web
    5,  // Mind-reader
    15, // Nightmare
    25, // Flame-wheel
    15, // Snore
    10, // Curse
    15, // Flail
    30, // Conversion-2
    5,  // Aeroblast
    40, // Cotton-spore
    15, // Reversal
    10, // Spite
    25, // Powder-snow
    10, // Protect
    30, // Mach-punch
    10, // Scary-face
    20, // Feint-attack
    10, // Sweet-kiss
    10, // Belly-drum
    10, // Sludge-bomb
    10, // Mud-slap
    10, // Octazooka
    20, // Spikes
    5,  // Zap-cannon
    40, // Foresight
    5,  // Destiny-bond
    5,  // Perish-song
    15, // Icy-wind
    5,  // Detect
    10, // Bone-rush
    5,  // Lock-on
    10, // Outrage
    10, // Sandstorm
    10, // Giga-drain
    10, // Endure
    20, // Charm
    20, // Rollout
    40, // False-swipe
    15, // Swagger
    10, // Milk-drink
    20, // Spark
    20, // Fury-cutter
    25, // Steel-wing
    5,  // Mean-look
    15, // Attract
    10, // Sleep-talk
    5,  // Heal-bell
    20, // Return
    15, // Present
    20, // Frustration
    25, // Safeguard
    20, // Pain-split
    5,  // Sacred-fire
    30, // Magnitude
    5,  // Dynamic-punch
    10, // Megahorn
    20, // Dragon-breath
    40, // Baton-pass
    5,  // Encore
    20, // Pursuit
    40, // Rapid-spin
    20, // Sweet-scent
    15, // Iron-tail
    35, // Metal-claw
    10, // Vital-throw
    5,  // Morning-sun
    5,  // Synthesis
    5,  // Moonlight
    15, // Hidden-power
    5,  // Cross-chop
    20, // Twister
    5,  // Rain-dance
    5,  // Sunny-day
    15, // Crunch
    20, // Mirror-coat
    10, // Psych-up
    5,  // Extreme-speed
    5,  // Ancient-power
    15, // Shadow-ball
    10, // Future-sight
    15, // Rock-smash
    15, // Whirlpool
    10, // Beat-up
};

#define ICON_RED 0
#define ICON_BLU 1
#define ICON_GRN 2
#define ICON_BRN 3
#define ICON_PNK 4

const u8 MENU_SPRITE_PALS[POKEMON_ARRAY_SIZE + 26][2] = {
    {ICON_BLU, ICON_RED}, // MISSINGNO
    {ICON_GRN, ICON_GRN}, // BULBASAUR
    {ICON_GRN, ICON_GRN}, // IVYSAUR
    {ICON_GRN, ICON_GRN}, // VENUSAUR
    {ICON_RED, ICON_BRN}, // CHARMANDER
    {ICON_RED, ICON_PNK}, // CHARMELEON
    {ICON_RED, ICON_BLU}, // CHARIZARD
    {ICON_BLU, ICON_GRN}, // SQUIRTLE
    {ICON_BLU, ICON_GRN}, // WARTORTLE
    {ICON_BLU, ICON_GRN}, // BLASTOISE
    {ICON_GRN, ICON_BRN}, // CATERPIE
    {ICON_GRN, ICON_BRN}, // METAPOD
    {ICON_PNK, ICON_GRN}, // BUTTERFREE
    {ICON_RED, ICON_PNK}, // WEEDLE
    {ICON_BRN, ICON_GRN}, // KAKUNA
    {ICON_RED, ICON_GRN}, // BEEDRILL
    {ICON_BRN, ICON_GRN}, // PIDGEY
    {ICON_BRN, ICON_GRN}, // PIDGEOTTO
    {ICON_RED, ICON_GRN}, // PIDGEOT
    {ICON_PNK, ICON_GRN}, // RATTATA
    {ICON_BRN, ICON_RED}, // RATICATE
    {ICON_BRN, ICON_GRN}, // SPEAROW
    {ICON_BRN, ICON_GRN}, // FEAROW
    {ICON_PNK, ICON_GRN}, // EKANS
    {ICON_PNK, ICON_BRN}, // ARBOK
    {ICON_RED, ICON_PNK}, // PIKACHU
    {ICON_RED, ICON_BRN}, // RAICHU
    {ICON_BRN, ICON_GRN}, // SANDSHREW
    {ICON_BRN, ICON_RED}, // SANDSLASH
    {ICON_BLU, ICON_PNK}, // NIDORAN_F
    {ICON_BLU, ICON_PNK}, // NIDORINA
    {ICON_BLU, ICON_GRN}, // NIDOQUEEN
    {ICON_PNK, ICON_BLU}, // NIDORAN_M
    {ICON_PNK, ICON_BLU}, // NIDORINO
    {ICON_PNK, ICON_BLU}, // NIDOKING
    {ICON_PNK, ICON_GRN}, // CLEFAIRY
    {ICON_PNK, ICON_GRN}, // CLEFABLE
    {ICON_RED, ICON_BRN}, // VULPIX
    {ICON_BRN, ICON_BLU}, // NINETALES
    {ICON_PNK, ICON_GRN}, // JIGGLYPUFF
    {ICON_PNK, ICON_GRN}, // WIGGLYTUFF
    {ICON_BLU, ICON_GRN}, // ZUBAT
    {ICON_BLU, ICON_GRN}, // GOLBAT
    {ICON_GRN, ICON_BRN}, // ODDISH
    {ICON_RED, ICON_BRN}, // GLOOM
    {ICON_RED, ICON_BRN}, // VILEPLUME
    {ICON_RED, ICON_GRN}, // PARAS
    {ICON_RED, ICON_GRN}, // PARASECT
    {ICON_PNK, ICON_BLU}, // VENONAT
    {ICON_PNK, ICON_BLU}, // VENOMOTH
    {ICON_BRN, ICON_BLU}, // DIGLETT
    {ICON_BRN, ICON_BLU}, // DUGTRIO
    {ICON_BRN, ICON_PNK}, // MEOWTH
    {ICON_BRN, ICON_PNK}, // PERSIAN
    {ICON_BRN, ICON_BLU}, // PSYDUCK
    {ICON_BLU, ICON_BLU}, // GOLDUCK
    {ICON_BRN, ICON_GRN}, // MANKEY
    {ICON_BRN, ICON_GRN}, // PRIMEAPE
    {ICON_RED, ICON_GRN}, // GROWLITHE
    {ICON_RED, ICON_GRN}, // ARCANINE
    {ICON_BLU, ICON_BLU}, // POLIWAG
    {ICON_BLU, ICON_BLU}, // POLIWHIRL
    {ICON_BLU, ICON_GRN}, // POLIWRATH
    {ICON_BRN, ICON_PNK}, // ABRA
    {ICON_BRN, ICON_PNK}, // KADABRA
    {ICON_BRN, ICON_PNK}, // ALAKAZAM
    {ICON_BLU, ICON_BRN}, // MACHOP
    {ICON_BLU, ICON_GRN}, // MACHOKE
    {ICON_BLU, ICON_GRN}, // MACHAMP
    {ICON_GRN, ICON_BRN}, // BELLSPROUT
    {ICON_GRN, ICON_BRN}, // WEEPINBELL
    {ICON_GRN, ICON_BRN}, // VICTREEBEL
    {ICON_BLU, ICON_GRN}, // TENTACOOL
    {ICON_BLU, ICON_GRN}, // TENTACRUEL
    {ICON_BRN, ICON_RED}, // GEODUDE
    {ICON_BRN, ICON_RED}, // GRAVELER
    {ICON_BRN, ICON_RED}, // GOLEM
    {ICON_RED, ICON_PNK}, // PONYTA
    {ICON_RED, ICON_PNK}, // RAPIDASH
    {ICON_PNK, ICON_BLU}, // SLOWPOKE
    {ICON_PNK, ICON_BLU}, // SLOWBRO
    {ICON_BLU, ICON_BRN}, // MAGNEMITE
    {ICON_BLU, ICON_BRN}, // MAGNETON
    {ICON_BRN, ICON_GRN}, // FARFETCH_D
    {ICON_BRN, ICON_GRN}, // DODUO
    {ICON_BRN, ICON_GRN}, // DODRIO
    {ICON_RED, ICON_PNK}, // SEEL
    {ICON_RED, ICON_PNK}, // DEWGONG
    {ICON_PNK, ICON_GRN}, // GRIMER
    {ICON_PNK, ICON_GRN}, // MUK
    {ICON_PNK, ICON_BRN}, // SHELLDER
    {ICON_PNK, ICON_BLU}, // CLOYSTER
    {ICON_PNK, ICON_BLU}, // GASTLY
    {ICON_PNK, ICON_BLU}, // HAUNTER
    {ICON_RED, ICON_BLU}, // GENGAR
    {ICON_BRN, ICON_GRN}, // ONIX
    {ICON_BRN, ICON_PNK}, // DROWZEE
    {ICON_BRN, ICON_PNK}, // HYPNO
    {ICON_RED, ICON_GRN}, // KRABBY
    {ICON_RED, ICON_GRN}, // KINGLER
    {ICON_RED, ICON_BLU}, // VOLTORB
    {ICON_RED, ICON_BLU}, // ELECTRODE
    {ICON_PNK, ICON_GRN}, // EXEGGCUTE
    {ICON_GRN, ICON_BRN}, // EXEGGUTOR
    {ICON_BRN, ICON_GRN}, // CUBONE
    {ICON_BRN, ICON_GRN}, // MAROWAK
    {ICON_BRN, ICON_GRN}, // HITMONLEE
    {ICON_BRN, ICON_GRN}, // HITMONCHAN
    {ICON_PNK, ICON_GRN}, // LICKITUNG
    {ICON_PNK, ICON_BLU}, // KOFFING
    {ICON_PNK, ICON_BLU}, // WEEZING
    {ICON_BLU, ICON_BRN}, // RHYHORN
    {ICON_BLU, ICON_BLU}, // RHYDON
    {ICON_PNK, ICON_GRN}, // CHANSEY
    {ICON_BLU, ICON_GRN}, // TANGELA
    {ICON_BRN, ICON_GRN}, // KANGASKHAN
    {ICON_BLU, ICON_PNK}, // HORSEA
    {ICON_BLU, ICON_PNK}, // SEADRA
    {ICON_RED, ICON_BRN}, // GOLDEEN
    {ICON_RED, ICON_BRN}, // SEAKING
    {ICON_BRN, ICON_BLU}, // STARYU
    {ICON_PNK, ICON_BLU}, // STARMIE
    {ICON_PNK, ICON_GRN}, // MR__MIME
    {ICON_GRN, ICON_GRN}, // SCYTHER
    {ICON_RED, ICON_PNK}, // JYNX
    {ICON_BRN, ICON_GRN}, // ELECTABUZZ
    {ICON_RED, ICON_PNK}, // MAGMAR
    {ICON_BRN, ICON_BLU}, // PINSIR
    {ICON_BRN, ICON_GRN}, // TAUROS
    {ICON_RED, ICON_GRN}, // MAGIKARP
    {ICON_BLU, ICON_RED}, // GYARADOS
    {ICON_BLU, ICON_PNK}, // LAPRAS
    {ICON_PNK, ICON_BLU}, // DITTO
    {ICON_BRN, ICON_BLU}, // EEVEE
    {ICON_BLU, ICON_PNK}, // VAPOREON
    {ICON_BRN, ICON_GRN}, // JOLTEON
    {ICON_RED, ICON_BRN}, // FLAREON
    {ICON_PNK, ICON_BLU}, // PORYGON
    {ICON_BLU, ICON_BRN}, // OMANYTE
    {ICON_BLU, ICON_BRN}, // OMASTAR
    {ICON_BRN, ICON_GRN}, // KABUTO
    {ICON_BRN, ICON_GRN}, // KABUTOPS
    {ICON_PNK, ICON_BLU}, // AERODACTYL
    {ICON_RED, ICON_BLU}, // SNORLAX
    {ICON_BLU, ICON_BLU}, // ARTICUNO
    {ICON_BRN, ICON_RED}, // ZAPDOS
    {ICON_RED, ICON_PNK}, // MOLTRES
    {ICON_BLU, ICON_PNK}, // DRATINI
    {ICON_BLU, ICON_PNK}, // DRAGONAIR
    {ICON_RED, ICON_GRN}, // DRAGONITE
    {ICON_PNK, ICON_GRN}, // MEWTWO
    {ICON_PNK, ICON_BLU}, // MEW
    {ICON_GRN, ICON_BRN}, // CHIKORITA
    {ICON_GRN, ICON_BRN}, // BAYLEEF
    {ICON_GRN, ICON_BRN}, // MEGANIUM
    {ICON_RED, ICON_PNK}, // CYNDAQUIL
    {ICON_RED, ICON_PNK}, // QUILAVA
    {ICON_RED, ICON_PNK}, // TYPHLOSION
    {ICON_BLU, ICON_GRN}, // TOTODILE
    {ICON_BLU, ICON_GRN}, // CROCONAW
    {ICON_BLU, ICON_GRN}, // FERALIGATR
    {ICON_BRN, ICON_PNK}, // SENTRET
    {ICON_BRN, ICON_PNK}, // FURRET
    {ICON_BRN, ICON_GRN}, // HOOTHOOT
    {ICON_BRN, ICON_GRN}, // NOCTOWL
    {ICON_RED, ICON_BRN}, // LEDYBA
    {ICON_RED, ICON_BRN}, // LEDIAN
    {ICON_GRN, ICON_PNK}, // SPINARAK
    {ICON_RED, ICON_PNK}, // ARIADOS
    {ICON_PNK, ICON_PNK}, // CROBAT
    {ICON_BLU, ICON_BLU}, // CHINCHOU
    {ICON_BLU, ICON_PNK}, // LANTURN
    {ICON_RED, ICON_BRN}, // PICHU
    {ICON_PNK, ICON_GRN}, // CLEFFA
    {ICON_PNK, ICON_GRN}, // IGGLYBUFF
    {ICON_RED, ICON_BLU}, // TOGEPI
    {ICON_RED, ICON_BLU}, // TOGETIC
    {ICON_GRN, ICON_GRN}, // NATU
    {ICON_GRN, ICON_GRN}, // XATU
    {ICON_BLU, ICON_BLU}, // MAREEP
    {ICON_PNK, ICON_PNK}, // FLAAFFY
    {ICON_BRN, ICON_BLU}, // AMPHAROS
    {ICON_GRN, ICON_BLU}, // BELLOSSOM
    {ICON_BLU, ICON_GRN}, // MARILL
    {ICON_BLU, ICON_BRN}, // AZUMARILL
    {ICON_GRN, ICON_PNK}, // SUDOWOODO
    {ICON_GRN, ICON_BLU}, // POLITOED
    {ICON_PNK, ICON_GRN}, // HOPPIP
    {ICON_GRN, ICON_PNK}, // SKIPLOOM
    {ICON_BLU, ICON_PNK}, // JUMPLUFF
    {ICON_PNK, ICON_PNK}, // AIPOM
    {ICON_GRN, ICON_BRN}, // SUNKERN
    {ICON_GRN, ICON_BRN}, // SUNFLORA
    {ICON_RED, ICON_BLU}, // YANMA
    {ICON_BLU, ICON_PNK}, // WOOPER
    {ICON_BLU, ICON_PNK}, // QUAGSIRE
    {ICON_PNK, ICON_GRN}, // ESPEON
    {ICON_BRN, ICON_BLU}, // UMBREON
    {ICON_BLU, ICON_PNK}, // MURKROW
    {ICON_PNK, ICON_BLU}, // SLOWKING
    {ICON_BLU, ICON_BRN}, // MISDREAVUS
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BLU, ICON_PNK}, // WOBBUFFET
    {ICON_PNK, ICON_BLU}, // GIRAFARIG
    {ICON_GRN, ICON_RED}, // PINECO
    {ICON_RED, ICON_GRN}, // FORRETRESS
    {ICON_BLU, ICON_PNK}, // DUNSPARCE
    {ICON_PNK, ICON_BLU}, // GLIGAR
    {ICON_BLU, ICON_BRN}, // STEELIX
    {ICON_PNK, ICON_BLU}, // SNUBBULL
    {ICON_PNK, ICON_BLU}, // GRANBULL
    {ICON_BLU, ICON_PNK}, // QWILFISH
    {ICON_RED, ICON_GRN}, // SCIZOR
    {ICON_RED, ICON_BLU}, // SHUCKLE
    {ICON_BLU, ICON_PNK}, // HERACROSS
    {ICON_BLU, ICON_PNK}, // SNEASEL
    {ICON_BRN, ICON_GRN}, // TEDDIURSA
    {ICON_BRN, ICON_GRN}, // URSARING
    {ICON_RED, ICON_BLU}, // SLUGMA
    {ICON_RED, ICON_BLU}, // MAGCARGO
    {ICON_BRN, ICON_BLU}, // SWINUB
    {ICON_BRN, ICON_GRN}, // PILOSWINE
    {ICON_PNK, ICON_BLU}, // CORSOLA
    {ICON_BLU, ICON_BLU}, // REMORAID
    {ICON_RED, ICON_GRN}, // OCTILLERY
    {ICON_RED, ICON_PNK}, // DELIBIRD
    {ICON_BLU, ICON_BLU}, // MANTINE
    {ICON_RED, ICON_GRN}, // SKARMORY
    {ICON_RED, ICON_BLU}, // HOUNDOUR
    {ICON_RED, ICON_BLU}, // HOUNDOOM
    {ICON_BLU, ICON_PNK}, // KINGDRA
    {ICON_BLU, ICON_BLU}, // PHANPY
    {ICON_BLU, ICON_RED}, // DONPHAN
    {ICON_PNK, ICON_BLU}, // PORYGON2
    {ICON_BRN, ICON_GRN}, // STANTLER
    {ICON_GRN, ICON_PNK}, // SMEARGLE
    {ICON_PNK, ICON_BLU}, // TYROGUE
    {ICON_BRN, ICON_BLU}, // HITMONTOP
    {ICON_PNK, ICON_PNK}, // SMOOCHUM
    {ICON_BRN, ICON_BRN}, // ELEKID
    {ICON_RED, ICON_BRN}, // MAGBY
    {ICON_PNK, ICON_BLU}, // MILTANK
    {ICON_PNK, ICON_PNK}, // BLISSEY
    {ICON_BRN, ICON_BRN}, // RAIKOU
    {ICON_RED, ICON_RED}, // ENTEI
    {ICON_BLU, ICON_BLU}, // SUICUNE
    {ICON_GRN, ICON_GRN}, // LARVITAR
    {ICON_BLU, ICON_PNK}, // PUPITAR
    {ICON_GRN, ICON_PNK}, // TYRANITAR
    {ICON_BLU, ICON_PNK}, // LUGIA
    {ICON_RED, ICON_BRN}, // HO_OH
    {ICON_GRN, ICON_PNK}, // CELEBI
    {ICON_GRN, ICON_BLU}, // TREECKO
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
    {ICON_BRN, ICON_BLU}, // UNOWN
};

extern const byte EVENT_PKMN[8][80]{
    // Events taken from the PKHeX Event Database.
    // Sanitize 4 bytes at 0x00, 2 bytes at 0x1C, the highest bit at 0x46 and 4 bytes at 0x48

    // Japanese Hadō (Aura) Mew
    {0x00, 0x00, 0x00, 0x00, 0x1C, 0xC6, 0x00, 0x00, 0x70, 0x85, 0x53, 0xFF, 0x08, 0x70, 0x01, 0x34, 0x01, 0x31, 0x01, 0x02, 0x6A, 0x95, 0x53, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0x30, 0x02, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x01, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x0A, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80},
    // English Aura Mew
    {0x00, 0x00, 0x00, 0x00, 0x6E, 0x4E, 0x00, 0x00, 0xC7, 0xBF, 0xD1, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0xBB, 0xE9, 0xE6, 0xD5, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0x30, 0x02, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x01, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x0A, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80},
    // French Aura Mew
    {0x00, 0x00, 0x00, 0x00, 0x6E, 0x4E, 0x00, 0x00, 0xC7, 0xBF, 0xD1, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0xBB, 0xE9, 0xE6, 0xD5, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0x30, 0x02, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x01, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x0A, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80},
    // Italian Aura Mew
    {0x00, 0x00, 0x00, 0x00, 0x6E, 0x4E, 0x00, 0x00, 0xC7, 0xBF, 0xD1, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0xBB, 0xE9, 0xE6, 0xD5, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0x30, 0x02, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x01, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x0A, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80},
    // German Aura Mew
    {0x00, 0x00, 0x00, 0x00, 0x6E, 0x4E, 0x00, 0x00, 0xC7, 0xBF, 0xD1, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x02, 0xBB, 0xE9, 0xE6, 0xD5, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0x30, 0x02, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x01, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x0A, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80},
    // Spanish Aura Mew
    {0x00, 0x00, 0x00, 0x00, 0x6E, 0x4E, 0x00, 0x00, 0xC7, 0xBF, 0xD1, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x02, 0xBB, 0xE9, 0xE6, 0xD5, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0x30, 0x02, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x01, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x0A, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80},
    // Mitsurin Celebi
    {0x00, 0x00, 0x00, 0x00, 0x30, 0xED, 0x00, 0x00, 0x5E, 0x7A, 0x97, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x70, 0x62, 0x78, 0x7E, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFB, 0x00, 0x00, 0x00, 0x30, 0x02, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x49, 0x00, 0x69, 0x00, 0xD7, 0x00, 0xDB, 0x00, 0x0A, 0x14, 0x05, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x0A, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // 10th Anniversary Celebi
    {0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0xBD, 0xBF, 0xC6, 0xBF, 0xBC, 0xC3, 0xFF, 0x34, 0x01, 0x31, 0x02, 0x02, 0xA2, 0xA1, 0x00, 0xBB, 0xC8, 0xC3, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFB, 0x00, 0x00, 0x00, 0x80, 0x43, 0x05, 0x00, 0x00, 0x64, 0x00, 0x00, 0xF6, 0x00, 0xF8, 0x00, 0xE2, 0x00, 0xC3, 0x00, 0x05, 0x0F, 0x28, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x46, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

const u8 TYPES[POKEMON_ARRAY_SIZE][2]{
    {0x0, 0x0},   // Missingno is ???/???
    {0xc, 0x3},   // Bulbasaur is grass/poison
    {0xc, 0x3},   // Ivysaur is grass/poison
    {0xc, 0x3},   // Venusaur is grass/poison
    {0xa, 0xa},   // Charmander is fire/fire
    {0xa, 0xa},   // Charmeleon is fire/fire
    {0xa, 0x2},   // Charizard is fire/flying
    {0xb, 0xb},   // Squirtle is water/water
    {0xb, 0xb},   // Wartortle is water/water
    {0xb, 0xb},   // Blastoise is water/water
    {0x6, 0x6},   // Caterpie is bug/bug
    {0x6, 0x6},   // Metapod is bug/bug
    {0x6, 0x2},   // Butterfree is bug/flying
    {0x6, 0x3},   // Weedle is bug/poison
    {0x6, 0x3},   // Kakuna is bug/poison
    {0x6, 0x3},   // Beedrill is bug/poison
    {0x0, 0x2},   // Pidgey is normal/flying
    {0x0, 0x2},   // Pidgeotto is normal/flying
    {0x0, 0x2},   // Pidgeot is normal/flying
    {0x0, 0x0},   // Rattata is normal/normal
    {0x0, 0x0},   // Raticate is normal/normal
    {0x0, 0x2},   // Spearow is normal/flying
    {0x0, 0x2},   // Fearow is normal/flying
    {0x3, 0x3},   // Ekans is poison/poison
    {0x3, 0x3},   // Arbok is poison/poison
    {0xd, 0xd},   // Pikachu is electric/electric
    {0xd, 0xd},   // Raichu is electric/electric
    {0x4, 0x4},   // Sandshrew is ground/ground
    {0x4, 0x4},   // Sandslash is ground/ground
    {0x3, 0x3},   // Nidoran-f is poison/poison
    {0x3, 0x3},   // Nidorina is poison/poison
    {0x3, 0x4},   // Nidoqueen is poison/ground
    {0x3, 0x3},   // Nidoran-m is poison/poison
    {0x3, 0x3},   // Nidorino is poison/poison
    {0x3, 0x4},   // Nidoking is poison/ground
    {0x0, 0x0},   // Clefairy is normal/normal
    {0x0, 0x0},   // Clefable is normal/normal
    {0xa, 0xa},   // Vulpix is fire/fire
    {0xa, 0xa},   // Ninetales is fire/fire
    {0x0, 0x0},   // Jigglypuff is normal/normal
    {0x0, 0x0},   // Wigglytuff is normal/normal
    {0x3, 0x2},   // Zubat is poison/flying
    {0x3, 0x2},   // Golbat is poison/flying
    {0xc, 0x3},   // Oddish is grass/poison
    {0xc, 0x3},   // Gloom is grass/poison
    {0xc, 0x3},   // Vileplume is grass/poison
    {0x6, 0xc},   // Paras is bug/grass
    {0x6, 0xc},   // Parasect is bug/grass
    {0x6, 0x3},   // Venonat is bug/poison
    {0x6, 0x3},   // Venomoth is bug/poison
    {0x4, 0x4},   // Diglett is ground/ground
    {0x4, 0x4},   // Dugtrio is ground/ground
    {0x0, 0x0},   // Meowth is normal/normal
    {0x0, 0x0},   // Persian is normal/normal
    {0xb, 0xb},   // Psyduck is water/water
    {0xb, 0xb},   // Golduck is water/water
    {0x1, 0x1},   // Mankey is fighting/fighting
    {0x1, 0x1},   // Primeape is fighting/fighting
    {0xa, 0xa},   // Growlithe is fire/fire
    {0xa, 0xa},   // Arcanine is fire/fire
    {0xb, 0xb},   // Poliwag is water/water
    {0xb, 0xb},   // Poliwhirl is water/water
    {0xb, 0x1},   // Poliwrath is water/fighting
    {0xe, 0xe},   // Abra is psychic/psychic
    {0xe, 0xe},   // Kadabra is psychic/psychic
    {0xe, 0xe},   // Alakazam is psychic/psychic
    {0x1, 0x1},   // Machop is fighting/fighting
    {0x1, 0x1},   // Machoke is fighting/fighting
    {0x1, 0x1},   // Machamp is fighting/fighting
    {0xc, 0x3},   // Bellsprout is grass/poison
    {0xc, 0x3},   // Weepinbell is grass/poison
    {0xc, 0x3},   // Victreebel is grass/poison
    {0xb, 0x3},   // Tentacool is water/poison
    {0xb, 0x3},   // Tentacruel is water/poison
    {0x5, 0x4},   // Geodude is rock/ground
    {0x5, 0x4},   // Graveler is rock/ground
    {0x5, 0x4},   // Golem is rock/ground
    {0xa, 0xa},   // Ponyta is fire/fire
    {0xa, 0xa},   // Rapidash is fire/fire
    {0xb, 0xe},   // Slowpoke is water/psychic
    {0xb, 0xe},   // Slowbro is water/psychic
    {0xd, 0x8},   // Magnemite is electric/steel
    {0xd, 0x8},   // Magneton is electric/steel
    {0x0, 0x2},   // Farfetchd is normal/flying
    {0x0, 0x2},   // Doduo is normal/flying
    {0x0, 0x2},   // Dodrio is normal/flying
    {0xb, 0xb},   // Seel is water/water
    {0xb, 0xf},   // Dewgong is water/ice
    {0x3, 0x3},   // Grimer is poison/poison
    {0x3, 0x3},   // Muk is poison/poison
    {0xb, 0xb},   // Shellder is water/water
    {0xb, 0xf},   // Cloyster is water/ice
    {0x7, 0x3},   // Gastly is ghost/poison
    {0x7, 0x3},   // Haunter is ghost/poison
    {0x7, 0x3},   // Gengar is ghost/poison
    {0x5, 0x4},   // Onix is rock/ground
    {0xe, 0xe},   // Drowzee is psychic/psychic
    {0xe, 0xe},   // Hypno is psychic/psychic
    {0xb, 0xb},   // Krabby is water/water
    {0xb, 0xb},   // Kingler is water/water
    {0xd, 0xd},   // Voltorb is electric/electric
    {0xd, 0xd},   // Electrode is electric/electric
    {0xc, 0xe},   // Exeggcute is grass/psychic
    {0xc, 0xe},   // Exeggutor is grass/psychic
    {0x4, 0x4},   // Cubone is ground/ground
    {0x4, 0x4},   // Marowak is ground/ground
    {0x1, 0x1},   // Hitmonlee is fighting/fighting
    {0x1, 0x1},   // Hitmonchan is fighting/fighting
    {0x0, 0x0},   // Lickitung is normal/normal
    {0x3, 0x3},   // Koffing is poison/poison
    {0x3, 0x3},   // Weezing is poison/poison
    {0x4, 0x5},   // Rhyhorn is ground/rock
    {0x4, 0x5},   // Rhydon is ground/rock
    {0x0, 0x0},   // Chansey is normal/normal
    {0xc, 0xc},   // Tangela is grass/grass
    {0x0, 0x0},   // Kangaskhan is normal/normal
    {0xb, 0xb},   // Horsea is water/water
    {0xb, 0xb},   // Seadra is water/water
    {0xb, 0xb},   // Goldeen is water/water
    {0xb, 0xb},   // Seaking is water/water
    {0xb, 0xb},   // Staryu is water/water
    {0xb, 0xe},   // Starmie is water/psychic
    {0xe, 0xe},   // Mr-mime is psychic/psychic
    {0x6, 0x2},   // Scyther is bug/flying
    {0xf, 0xe},   // Jynx is ice/psychic
    {0xd, 0xd},   // Electabuzz is electric/electric
    {0xa, 0xa},   // Magmar is fire/fire
    {0x6, 0x6},   // Pinsir is bug/bug
    {0x0, 0x0},   // Tauros is normal/normal
    {0xb, 0xb},   // Magikarp is water/water
    {0xb, 0x2},   // Gyarados is water/flying
    {0xb, 0xf},   // Lapras is water/ice
    {0x0, 0x0},   // Ditto is normal/normal
    {0x0, 0x0},   // Eevee is normal/normal
    {0xb, 0xb},   // Vaporeon is water/water
    {0xd, 0xd},   // Jolteon is electric/electric
    {0xa, 0xa},   // Flareon is fire/fire
    {0x0, 0x0},   // Porygon is normal/normal
    {0x5, 0xb},   // Omanyte is rock/water
    {0x5, 0xb},   // Omastar is rock/water
    {0x5, 0xb},   // Kabuto is rock/water
    {0x5, 0xb},   // Kabutops is rock/water
    {0x5, 0x2},   // Aerodactyl is rock/flying
    {0x0, 0x0},   // Snorlax is normal/normal
    {0xf, 0x2},   // Articuno is ice/flying
    {0xd, 0x2},   // Zapdos is electric/flying
    {0xa, 0x2},   // Moltres is fire/flying
    {0x10, 0x10}, // Dratini is dragon/dragon
    {0x10, 0x10}, // Dragonair is dragon/dragon
    {0x10, 0x2},  // Dragonite is dragon/flying
    {0xe, 0xe},   // Mewtwo is psychic/psychic
    {0xe, 0xe},   // Mew is psychic/psychic
    {0xc, 0xc},   // Chikorita is grass/grass
    {0xc, 0xc},   // Bayleef is grass/grass
    {0xc, 0xc},   // Meganium is grass/grass
    {0xa, 0xa},   // Cyndaquil is fire/fire
    {0xa, 0xa},   // Quilava is fire/fire
    {0xa, 0xa},   // Typhlosion is fire/fire
    {0xb, 0xb},   // Totodile is water/water
    {0xb, 0xb},   // Croconaw is water/water
    {0xb, 0xb},   // Feraligatr is water/water
    {0x0, 0x0},   // Sentret is normal/normal
    {0x0, 0x0},   // Furret is normal/normal
    {0x0, 0x2},   // Hoothoot is normal/flying
    {0x0, 0x2},   // Noctowl is normal/flying
    {0x6, 0x2},   // Ledyba is bug/flying
    {0x6, 0x2},   // Ledian is bug/flying
    {0x6, 0x3},   // Spinarak is bug/poison
    {0x6, 0x3},   // Ariados is bug/poison
    {0x3, 0x2},   // Crobat is poison/flying
    {0xb, 0xd},   // Chinchou is water/electric
    {0xb, 0xd},   // Lanturn is water/electric
    {0xd, 0xd},   // Pichu is electric/electric
    {0x0, 0x0},   // Cleffa is normal/normal
    {0x0, 0x0},   // Igglybuff is normal/normal
    {0x0, 0x0},   // Togepi is normal/normal
    {0x0, 0x2},   // Togetic is normal/flying
    {0xe, 0x2},   // Natu is psychic/flying
    {0xe, 0x2},   // Xatu is psychic/flying
    {0xd, 0xd},   // Mareep is electric/electric
    {0xd, 0xd},   // Flaaffy is electric/electric
    {0xd, 0xd},   // Ampharos is electric/electric
    {0xc, 0xc},   // Bellossom is grass/grass
    {0xb, 0xb},   // Marill is water/water
    {0xb, 0xb},   // Azumarill is water/water
    {0x5, 0x5},   // Sudowoodo is rock/rock
    {0xb, 0xb},   // Politoed is water/water
    {0xc, 0x2},   // Hoppip is grass/flying
    {0xc, 0x2},   // Skiploom is grass/flying
    {0xc, 0x2},   // Jumpluff is grass/flying
    {0x0, 0x0},   // Aipom is normal/normal
    {0xc, 0xc},   // Sunkern is grass/grass
    {0xc, 0xc},   // Sunflora is grass/grass
    {0x6, 0x2},   // Yanma is bug/flying
    {0xb, 0x4},   // Wooper is water/ground
    {0xb, 0x4},   // Quagsire is water/ground
    {0xe, 0xe},   // Espeon is psychic/psychic
    {0x10, 0x10}, // Umbreon is dark/dark
    {0x10, 0x2},  // Murkrow is dark/flying
    {0xb, 0xe},   // Slowking is water/psychic
    {0x7, 0x7},   // Misdreavus is ghost/ghost
    {0xe, 0xe},   // Unown is psychic/psychic
    {0xe, 0xe},   // Wobbuffet is psychic/psychic
    {0x0, 0xe},   // Girafarig is normal/psychic
    {0x6, 0x6},   // Pineco is bug/bug
    {0x6, 0x8},   // Forretress is bug/steel
    {0x0, 0x0},   // Dunsparce is normal/normal
    {0x4, 0x2},   // Gligar is ground/flying
    {0x8, 0x4},   // Steelix is steel/ground
    {0x0, 0x0},   // Snubbull is normal/normal
    {0x0, 0x0},   // Granbull is normal/normal
    {0xb, 0x3},   // Qwilfish is water/poison
    {0x6, 0x8},   // Scizor is bug/steel
    {0x6, 0x5},   // Shuckle is bug/rock
    {0x6, 0x1},   // Heracross is bug/fighting
    {0x10, 0xf},  // Sneasel is dark/ice
    {0x0, 0x0},   // Teddiursa is normal/normal
    {0x0, 0x0},   // Ursaring is normal/normal
    {0xa, 0xa},   // Slugma is fire/fire
    {0xa, 0x5},   // Magcargo is fire/rock
    {0xf, 0x4},   // Swinub is ice/ground
    {0xf, 0x4},   // Piloswine is ice/ground
    {0xb, 0x5},   // Corsola is water/rock
    {0xb, 0xb},   // Remoraid is water/water
    {0xb, 0xb},   // Octillery is water/water
    {0xf, 0x2},   // Delibird is ice/flying
    {0xb, 0x2},   // Mantine is water/flying
    {0x8, 0x2},   // Skarmory is steel/flying
    {0x10, 0xa},  // Houndour is dark/fire
    {0x10, 0xa},  // Houndoom is dark/fire
    {0xb, 0x10},  // Kingdra is water/dragon
    {0x4, 0x4},   // Phanpy is ground/ground
    {0x4, 0x4},   // Donphan is ground/ground
    {0x0, 0x0},   // Porygon2 is normal/normal
    {0x0, 0x0},   // Stantler is normal/normal
    {0x0, 0x0},   // Smeargle is normal/normal
    {0x1, 0x1},   // Tyrogue is fighting/fighting
    {0x1, 0x1},   // Hitmontop is fighting/fighting
    {0xf, 0xe},   // Smoochum is ice/psychic
    {0xd, 0xd},   // Elekid is electric/electric
    {0xa, 0xa},   // Magby is fire/fire
    {0x0, 0x0},   // Miltank is normal/normal
    {0x0, 0x0},   // Blissey is normal/normal
    {0xd, 0xd},   // Raikou is electric/electric
    {0xa, 0xa},   // Entei is fire/fire
    {0xb, 0xb},   // Suicune is water/water
    {0x5, 0x4},   // Larvitar is rock/ground
    {0x5, 0x4},   // Pupitar is rock/ground
    {0x5, 0x10},  // Tyranitar is rock/dark
    {0xe, 0x2},   // Lugia is psychic/flying
    {0xa, 0x2},   // Ho-oh is fire/flying
    {0xe, 0xc},   // Celebi is psychic/grass
    {0xc, 0xc},   // Treecko is grass/grass
};

void generate_pokemon_data(const char *output_path)
{
    writeTable("tools/data-generator/src/extern_pokemon_data.cpp", output_path, "gen_1_charsets.bin", (const char*)gen_1_charsets, sizeof(gen_1_charsets));
    writeTable("tools/data-generator/src/extern_pokemon_data.cpp", output_path, "gen_2_charsets.bin", (const char*)gen_2_charsets, sizeof(gen_2_charsets));
    writeTable("tools/data-generator/src/extern_pokemon_data.cpp", output_path, "gen_3_charsets.bin", (const char*)gen_3_charsets, sizeof(gen_3_charsets));
    writeTable("tools/data-generator/src/extern_pokemon_data.cpp", output_path, "EXP_GROUPS.bin", (const char*)EXP_GROUPS, sizeof(EXP_GROUPS));
    writeTable("tools/data-generator/src/extern_pokemon_data.cpp", output_path, "GENDER_RATIO.bin", (const char*)GENDER_RATIO, sizeof(GENDER_RATIO));
    writeTable("tools/data-generator/src/extern_pokemon_data.cpp", output_path, "NUM_ABILITIES.bin", (const char*)(NUM_ABILITIES), sizeof(NUM_ABILITIES));
    writeTable("tools/data-generator/src/extern_pokemon_data.cpp", output_path, "FIRST_MOVES.bin", (const char*)FIRST_MOVES, sizeof(FIRST_MOVES));
    writeTable("tools/data-generator/src/extern_pokemon_data.cpp", output_path, "JPN_NAMES.bin", (const char*)JPN_NAMES, sizeof(JPN_NAMES));
    writeTable("tools/data-generator/src/extern_pokemon_data.cpp", output_path, "POWER_POINTS.bin", (const char*)POWER_POINTS, sizeof(POWER_POINTS));
    writeTable("tools/data-generator/src/extern_pokemon_data.cpp", output_path, "MENU_SPRITE_PALS.bin", (const char*)MENU_SPRITE_PALS, sizeof(MENU_SPRITE_PALS));
    writeTable("tools/data-generator/src/extern_pokemon_data.cpp", output_path, "EVENT_PKMN.bin", (const char*)EVENT_PKMN, sizeof(EVENT_PKMN));
    writeTable("tools/data-generator/src/extern_pokemon_data.cpp", output_path, "TYPES.bin", (const char*)TYPES, sizeof(TYPES));
}