#include <tonc.h>

#include "sprite_data.h"
#include "text_engine.h"

#define CBB 0
#define SBB 24
int x, y;

void background_frame(int global_frame_count)
{
        if (!get_missingno_enabled())
        {
                x++;
                y++;

                REG_BG0HOFS = x;
                REG_BG0VOFS = y;
        }
}

void create_textbox(int startTileX, int startTileY, int width, int height, bool eraseMainBox)
{
        if (eraseMainBox)
        {
                erase_textbox_tiles();
        }
        add_menu_box(startTileX, startTileY, width, height);
        tte_set_pos((startTileX + 1) * 8, (startTileY + 1) * 8);
        tte_set_margins((startTileX + 1) * 8, (startTileY + 1) * 8,
                        (startTileX + 1 + width) * 8, (startTileY + 1 + height) * 8);
        tte_erase_rect(0, 0, H_MAX, V_MAX);
}

void reset_textbox()
{
        tte_erase_rect(0, 0, H_MAX, V_MAX);
        reload_textbox_background();
        tte_set_pos(1 * 8, 14 * 8);
        tte_set_margins(LEFT, TOP, RIGHT, BOTTOM);
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