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

// This could honestly be an object... might want to do that in the future, depending on how complex using this gets
void create_textbox(int startTileX, int startTileY, int text_space_width, int text_space_height, bool eraseMainBox)
{
        if (eraseMainBox)
        {
                erase_textbox_tiles();
        }
        add_menu_box(startTileX, startTileY, text_space_width + 16, text_space_height + 16);
        tte_set_pos((startTileX + 1) * 8, (startTileY + 1) * 8);
        tte_set_margins((startTileX + 1) * 8, (startTileY + 1) * 8,
                        (startTileX + text_space_width) * 8, (startTileY + text_space_height) * 8);
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