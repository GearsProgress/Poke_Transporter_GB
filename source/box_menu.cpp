#include <tonc.h>
#include "main_menu.h"
#include "button_handler.h"
#include "save_data_manager.h"
#include "global_frame_controller.h"
#include "string"
#include "sprite_data.h"
#include "box_menu.h"
#include "pokemon_data.h"

Box_Menu::Box_Menu(){};

int Box_Menu::box_main(Pokemon_Party party_data)
{
    REG_BG0CNT = (REG_BG0CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
    REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(2);
    REG_BG2VOFS = 0;
    load_temp_box_sprites(party_data);
    int x = 0;
    int y = 0;
    bool update_pos = true;
    obj_unhide(box_select, 0);
    while (true)
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
        if (update_pos)
        {
            int index = x + (y * 10);
            obj_set_pos(box_select, 40 + (x * 16), 24 + (y * 16));
            tte_erase_rect(40, 72, 220, 88);
            if (party_data.get_simple_pkmn(index).is_valid)
            {
                char nickname[10] = {'t', 'e', 's', 't', 'i', 'n', 'g'};
                for (int i = 0; i < 10; i++)
                {
                    nickname[i] = gen_3_Intern_char_array[party_data.get_simple_pkmn(index).nickname[i]];
                }
                tte_set_pos(40, 72);
                tte_write(nickname);
                tte_set_pos(56, 80);
                tte_write(NAMES[party_data.get_simple_pkmn(index).dex_number].data());
                tte_set_pos(146, 80);
                tte_write("Lv: ");
                tte_write(std::to_string(party_data.get_simple_pkmn(index).met_level).c_str());
            }
        }
        global_next_frame();
    }
}