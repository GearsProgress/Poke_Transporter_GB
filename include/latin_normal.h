#include "debug_mode.h"
#include "pokemon_data.h"

#if PTGB_BUILD_LANGUAGE != 1

#ifndef __LATIN_NORMAL__
#define __LATIN_NORMAL__

extern const TFont latin_normalFont;

#define latin_normalGlyphsLen 8192
extern const unsigned int latin_normalGlyphs[8192];

#define latin_normalWidthsLen 256
extern const unsigned char latin_normalWidths[256];

#endif

#endif
