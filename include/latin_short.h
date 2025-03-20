#include "debug_mode.h"
#include "pokemon_data.h"

#if PTGB_BUILD_LANGUAGE != JPN_ID

//{{BLOCK(latin_short)

#ifndef __LATIN_SHORT__
#define __LATIN_SHORT__

extern const TFont latin_shortFont;

#define latin_shortGlyphsLen 4096
extern const unsigned int latin_shortGlyphs[1024];
#define BUILD_FONT &latin_shortFont

#endif // __LATIN_SHORT__

//}}BLOCK(latin_short)

#endif