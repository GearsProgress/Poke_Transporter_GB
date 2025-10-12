#include "debug_mode.h"
#include "pokemon_data.h"

#if PTGB_BUILD_LANGUAGE == JPN_ID

//{{BLOCK(japanese_small)

#ifndef __JAPANESE_SMALL__
#define __JAPANESE_SMALL__

extern const TFont japanese_smallFont;

#define japanese_smallGlyphsLen 4096
extern const unsigned int japanese_smallGlyphs[1024];
#define BUILD_FONT &japanese_smallFont

#endif // __JAPANESE_SMALL__

//}}BLOCK(japanese_small)

#endif