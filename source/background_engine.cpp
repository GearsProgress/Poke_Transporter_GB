#include <tonc.h>
#include <cstring>

#include "sprite_data.h"
#include "text_engine.h"

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

void set_textbox_large()
{
        tte_set_pos(40, 24);
        tte_set_margins(40, 24, 206, 104);
        tte_erase_rect(0, 0, H_MAX, V_MAX);
        REG_BG2VOFS = 0;
}
void set_textbox_small()
{
        tte_set_margins(LEFT, TOP, RIGHT, BOTTOM);
        tte_erase_rect(0, 0, H_MAX, V_MAX);
        REG_BG2VOFS = 96;
}

void show_textbox()
{
        REG_BG0CNT = (REG_BG0CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
        REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(2);
}

void hide_textbox()
{
        REG_BG0CNT = (REG_BG0CNT & ~BG_PRIO_MASK) | BG_PRIO(2);
        REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
}