#include <tonc.h>
#include "pokemon_data.h"
#include "background_engine.h"
#include "translated_text.h"

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

void create_textbox(int startTileX, int startTileY, int text_space_width, int text_space_height, bool eraseMainBox)
{
        // Blank for compiling for now
}

// This could honestly be an object... might want to do that in the future, depending on how complex using this gets
void create_textbox_new(int text_section, int text_key, bool eraseMainBox)
{
        int box_type = text_box_type_tables[text_section][text_key];
        int startTileX = box_type_info[box_type][BOX_TYPE_VAL_START_TILE_X];
        int startTileY = box_type_info[box_type][BOX_TYPE_VAL_START_TILE_Y];
        int text_space_width = box_type_info[box_type][BOX_TYPE_VAL_PIXELS_PER_LINE];
        int text_space_height = box_type_info[box_type][BOX_TYPE_VAL_NUM_OF_LINES] * 16;
        if (eraseMainBox)
        {
                erase_textbox_tiles();
        }
        add_menu_box(startTileX, startTileY, text_space_width + 16, text_space_height + 16);
        tte_set_pos((startTileX + 1) * 8, (startTileY + 1) * 8);
        tte_set_margins((startTileX + 1) * 8, (startTileY + 1) * 8,
                        ((startTileX + 1) * 8) + text_space_width, ((startTileY + 1) * 8) + text_space_height);
        tte_erase_rect(0, 0, H_MAX, V_MAX);
        show_textbox();
}

void reset_textbox()
{
        //tte_erase_rect(0, 0, H_MAX, V_MAX);
        reload_textbox_background();
        //tte_set_pos(, TOP);
        //tte_set_margins(LEFT, TOP, RIGHT, BOTTOM);
}

void show_textbox()
{
        BG_TEXTBOX = (BG_TEXTBOX & ~BG_PRIO_MASK) | BG_PRIO(1);
}

void hide_textbox()
{
        BG_TEXTBOX = (BG_TEXTBOX & ~BG_PRIO_MASK) | BG_PRIO(3);
}