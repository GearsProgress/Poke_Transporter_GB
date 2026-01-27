#include "debug_mode.h"
#include "pokemon_data.h"

#if PTGB_BUILD_LANGUAGE == 1

#ifndef __JAPANESE_NORMAL__
#define __JAPANESE_NORMAL__

extern const TFont japanese_normalFont;

#define japanese_normalGlyphsLen 4096
extern const unsigned int japanese_normalGlyphs[4096];

#define japanese_normalWidthsLen 256
extern const unsigned char japanese_normalWidths[256];

#endif

#endif
