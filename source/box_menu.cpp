#include <tonc.h>
#include "button_menu.h"
#include "button_handler.h"
#include "save_data_manager.h"
#include "global_frame_controller.h"
#include "string"
#include "sprite_data.h"
#include "box_menu.h"
#include "pokemon_data.h"

Box_Menu::Box_Menu() {};

int Box_Menu::box_main(Pokemon_Party party_data)
{
    tte_erase_screen();
    load_flex_background(BG_FENNEL, 3);
    REG_BG2VOFS = BG2VOF_LARGE_TEXTBOX;
    REG_BG2VOFS = 0;
    load_temp_box_sprites(party_data);
    Button cancel_button(button_cancel_left, button_cancel_right, 64);
    Button confirm_button(button_confirm_left, button_confirm_right, 64);
    cancel_button.set_location(32, 112);
    confirm_button.set_location(136, 112);
    cancel_button.show();
    confirm_button.show();
    curr_button = 0;
    x = 0;
    y = 0;
    bool update_pos = true;
    obj_unhide(box_select, 0);
    while (true)
    {
        if (curr_button == 0)
        {
            if (key_hit(KEY_LEFT) && (x > 0))
            {
                x--;
                update_pos = true;
            }
            else if (key_hit(KEY_RIGHT) && (x < 9))
            {
                x++;
                update_pos = true;
            }
            else if (key_hit(KEY_UP) && y > 0)
            {
                y--;
                update_pos = true;
            }
            else if (key_hit(KEY_DOWN) && (y < 2))
            {
                y++;
                update_pos = true;
            }
            else if (key_hit(KEY_DOWN) && (y == 2))
            {
                obj_hide(box_select);
                if (x < 5)
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
                x -= 5;
            }
            else if (key_hit(KEY_RIGHT) && (curr_button == CANCEL_BUTTON))
            {
                curr_button = CONFIRM_BUTTON;
                cancel_button.set_highlight(false);
                confirm_button.set_highlight(true);
                x += 5;
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
            int index = x + (y * 10);
            obj_set_pos(box_select, 40 + (x * 16), 24 + (y * 16));
            tte_erase_rect(40, 72, 220, 88);
            Simplified_Pokemon curr_pkmn = party_data.get_simple_pkmn(index);
            if (curr_pkmn.is_valid)
            {
                char nickname[11] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
                for (int i = 0; i < 10; i++)
                {
                    nickname[i] = gen_3_Intern_char_array[curr_pkmn.nickname[i]];
                    if (curr_pkmn.nickname[i] == 0xFF){
                        i = 10;
                    }
                }
                tte_set_pos(40, 72);
                tte_write(nickname);
                if (curr_pkmn.is_shiny)
                {
                    tte_set_pos(40, 80);
                    tte_write("*");
                }
                tte_set_pos(48, 80);
                tte_write(NAMES[curr_pkmn.dex_number].data());
                tte_set_pos(146, 80);
                tte_write("Lv: ");
                tte_write(std::to_string(curr_pkmn.met_level).c_str());
                update_pos = false;
            }
        }
        global_next_frame();
    }
}