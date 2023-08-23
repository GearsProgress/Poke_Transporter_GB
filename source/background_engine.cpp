#include <tonc.h>
#include <cstring>

#include "sprite_data.h"

#define CBB 0
#define SBB 24
int x, y;

void background_frame()
{
        x++;
        y++;

        REG_BG0HOFS = x;
        REG_BG0VOFS = y;
}