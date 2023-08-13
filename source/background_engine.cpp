#include <tonc.h>
#include <cstring>

#include "sprite_data.h"

#define CBB 0
#define SBB 24
int x, y;

void background_frame()
{
        x += key_tri_horz();
        y += key_tri_vert();

        REG_BG0HOFS= x;
        REG_BG0VOFS= y;
}