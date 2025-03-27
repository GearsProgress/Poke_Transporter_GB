#include <tonc.h>
#include "button_menu.h"
#include "button_handler.h"
#include "save_data_manager.h"
#include "global_frame_controller.h"
#include "string"
#include "sprite_data.h"
#include "box_menu.h"
#include "pokemon_data.h"
#include "text_engine.h"
#include "translated_text.h"

Box_Menu::Box_Menu() {};

int Box_Menu::box_main(Pokemon_Party party_data)
{
    tte_erase_screen();
    load_flex_background(BG_BOX, 2);
    REG_BG1VOFS = 0;
    REG_BG1HOFS = 0;
    REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
    load_temp_box_sprites(&party_data);
    Button cancel_button(button_cancel_left, button_cancel_right, 64);
    Button confirm_button(button_confirm_left, button_confirm_right, 64);
    cancel_button.set_location(88, 144);
    confirm_button.set_location(160, 144);
    cancel_button.show();
    confirm_button.show();
    curr_button = 0;
    x = 0;
    y = 0;
    bool update_pos = true;
    obj_unhide(box_select, 0);
    int index = 0;
    while (true)
    {
        if (get_frame_count() % 20 == 0)
        {
            for (int i = 0; i < 30; i++)
            {
                update_menu_sprite(&party_data, i, get_frame_count() % 40);
            }
        }
        if (curr_button == 0)
        {
            if (key_hit(KEY_LEFT) && (x > 0))
            {
                x--;
                update_pos = true;
            }
            else if (key_hit(KEY_RIGHT) && (x < 5))
            {
                x++;
                update_pos = true;
            }
            else if (key_hit(KEY_UP) && y > 0)
            {
                y--;
                update_pos = true;
            }
            else if (key_hit(KEY_DOWN) && (y < 4))
            {
                y++;
                update_pos = true;
            }
            else if (key_hit(KEY_DOWN) && (y == 4))
            {
                obj_hide(box_select);
                if (x < 3)
                {
                    cancel_button.set_highlight(true);
                    curr_button = CANCEL_BUTTON;
                }
                else
                {
                    confirm_button.set_highlight(true);
                    curr_button = CONFIRM_BUTTON;
                }
            }
        }
        else
        {
            if (key_hit(KEY_LEFT) && (curr_button == CONFIRM_BUTTON))
            {
                curr_button = CANCEL_BUTTON;
                cancel_button.set_highlight(true);
                confirm_button.set_highlight(false);
                x -= 3;
            }
            else if (key_hit(KEY_RIGHT) && (curr_button == CANCEL_BUTTON))
            {
                curr_button = CONFIRM_BUTTON;
                cancel_button.set_highlight(false);
                confirm_button.set_highlight(true);
                x += 3;
            }
            else if (key_hit(KEY_UP))
            {
                curr_button = 0;
                cancel_button.set_highlight(false);
                confirm_button.set_highlight(false);
                obj_unhide(box_select, 0);
                update_pos = true;
            }
            else if (key_hit(KEY_A))
            {
                cancel_button.hide();
                confirm_button.hide();
                for (int i = 0; i < 30; i++)
                {
                    obj_hide(party_sprites[i]);
                }
                tte_erase_screen();
                load_flex_background(BG_FENNEL, 2);
                REG_BG2VOFS = BG2VOF_SMALL_TEXTBOX;
                global_next_frame();
                return curr_button;
            }
        }
        if (update_pos)
        {
            index = x + (y * BOXMENU_HNUM);
            obj_set_pos(box_select, BOXMENU_LEFT + (x * (BOXMENU_SPRITE_WIDTH + BOXMENU_HSPACE)), BOXMENU_TOP + (y * (BOXMENU_SPRITE_HEIGHT + BOXMENU_VSPACE)));
            tte_erase_rect(6, 16, 80, 152);
            Simplified_Pokemon curr_pkmn = party_data.get_simple_pkmn(index);
            obj_hide(grabbed_front_sprite);
            if (curr_pkmn.is_valid)
            {
                byte val[11];
                tte_set_pos(6, 88);
                ptgb_write(curr_pkmn.nickname, true);

                if (curr_pkmn.is_shiny)
                {
                    tte_set_pos(64, 16);
                    val[0] = 0xF7;
                    val[1] = 0xFF;
                    ptgb_write(val, true);
                }
                tte_set_pos(14, 98);
                if (curr_pkmn.is_missingno)
                {
                    ptgb_write(PKMN_NAMES[0], true);
                }
                else
                {
                    ptgb_write(PKMN_NAMES[curr_pkmn.dex_number], true);
                }
                tte_set_pos(6, 108);
                val[0] = 0xC6; // L
                val[1] = 0xEA; // v
                val[2] = 0xF0; // :
                val[3] = 0x00; // " "
                val[4] = 0xFF; // endline
                ptgb_write(val, true);
                convert_int_to_ptgb_str(curr_pkmn.met_level, val); // Val should never go out of bounds
                ptgb_write(val, true);

                update_front_box_sprite(&curr_pkmn);
                obj_unhide(grabbed_front_sprite, 0);
                update_pos = false;
            }
        }
        global_next_frame();
    }
}