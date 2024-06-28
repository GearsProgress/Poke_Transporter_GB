#include <tonc.h>
#include <string>
#include <cmath>

#include "pokedex.h"
#include "dex_handler.h"
#include "sprite_data.h"
#include "pokemon_data.h"
#include "global_frame_controller.h"
#include "save_data_manager.h"
#include "button_handler.h"

Dex dex_array[DEX_MAX];
int dex_shift = 0;
int dex_x_cord = 8;
int speed = 0;
int delay = 0;
int count = 0;
int leading_zeros = 0;
Button kanto_count;
Button johto_count;
int kanto_dex_num;
int johto_dex_num;
int kanto_offset;
int johto_offset;
bool mew_caught;
bool celebi_caught;
bool missingno_caught = false;

void pokedex_init()
{
    for (int i = 0; i < DEX_MAX; i++)
    {
        dex_array[i] = Dex(dex_sprites[DEX_SPRITE_LEFT][i], dex_sprites[DEX_SPRITE_MID][i], dex_sprites[DEX_SPRITE_RIGHT][i]);
        dex_array[i].set_location(dex_x_cord, (i * (8 * 3)) + 8);
    }
    kanto_count = Button(button_blank_left, button_blank_right, 64);
    johto_count = Button(button_blank_left_2, button_blank_right_2, 64);
    kanto_dex_num = get_dex_completion(1, true);
    johto_dex_num = get_dex_completion(2, true);
    if (kanto_dex_num >= 100)
    {
        kanto_offset = 0;
    }
    else if (kanto_dex_num >= 10)
    {
        kanto_offset = 1;
    }
    else
    {
        kanto_offset = 2;
    }
    if (johto_dex_num >= 100)
    {
        johto_offset = 0;
    }
    else if (johto_dex_num >= 10)
    {
        johto_offset = 1;
    }
    else
    {
        johto_offset = 2;
    }
    mew_caught = is_caught(151);
    celebi_caught = is_caught(251);
}

int pokedex_loop()
{
    load_temp_sprites(SPRITE_BATCH_DEX);
    pokedex_init();
    pokedex_show();
    // TODO: For some reason there is screen tearing here. Probably not noticable on console,
    // but it should be removed at some point

    while (true)
    {
        if (key_hit(KEY_B))
        {
            pokedex_hide();
            return 0;
        }
        else if (key_hit(KEY_DOWN) || key_hit(KEY_UP))
        {
            dex_shift += key_tri_vert();
        }
        else if (key_held(KEY_DOWN) || key_held(KEY_UP))
        {
            if (delay > SPEED_DELAY)
            {
                if ((get_frame_count() % speed == 0))
                {
                    if (count > 3 && speed >= 5)
                    {
                        speed = speed / 2;
                        count = 0;
                    }
                    else
                    {
                        count++;
                    }
                    dex_shift += key_tri_vert();
                }
            }
            else
            {
                delay++;
            }
        }
        else
        {
            speed = 20;
            delay = 0;
            count = 0;
        }

        if (dex_shift > DEX_SHIFT_MAX - !celebi_caught)
        {
            dex_shift = DEX_SHIFT_MAX - !celebi_caught;
        }
        else if (dex_shift < 0 - missingno_caught)
        {
            dex_shift = 0 - missingno_caught;
        }

        tte_erase_rect(0, 0, 240, 160);
        int mythic_skip = 0;
        for (int i = 0; i < DEX_MAX; i++)
        {
            if (dex_shift + i + 1 == 151 && !mew_caught){
                mythic_skip++;
            }
            tte_set_pos(dex_x_cord + (1 * 8), (i * 8 * 3) + 16);
            tte_write(is_caught(dex_shift + i + 1 + mythic_skip) ? "^" : " ");
            tte_set_pos(dex_x_cord + (3 * 8), (i * 8 * 3) + 16);
            tte_write(is_caught(dex_shift + i + 1 + mythic_skip) ? std::string(NAMES[dex_shift + i + 1]).data() : "----------");
            tte_set_pos(dex_x_cord + (14 * 8), (i * 8 * 3) + 16);
            tte_write("000");
            if (dex_shift + i + 1 + mythic_skip < 10)
            {
                leading_zeros = 2;
            }
            else if (dex_shift + i + 1 + mythic_skip < 100)
            {
                leading_zeros = 1;
            }
            else
            {
                leading_zeros = 0;
            }
            tte_set_pos(dex_x_cord + ((14 + leading_zeros) * 8), (i * 8 * 3) + 16);
            tte_write(std::to_string(dex_shift + i + 1 + mythic_skip).c_str());
        }
        tte_set_pos(176, 48);
        tte_write("KANTO");
        tte_set_pos(168 + (8 * kanto_offset), 56);
        tte_write(std::to_string(kanto_dex_num).c_str());
        tte_write("/");
        tte_write(mew_caught ? "151" : "150");

        tte_set_pos(176, 96);
        tte_write("JOHTO");
        tte_set_pos(168 + (8 * johto_offset), 104);
        tte_write(std::to_string(johto_dex_num).c_str());
        tte_write("/");
        tte_write(celebi_caught ? "100" : "99");

        global_next_frame();
    }
}

void pokedex_show()
{
    for (int i = 0; i < DEX_MAX; i++)
    {
        dex_array[i].show();
    }
    kanto_count.set_location(160, 40);
    johto_count.set_location(160, 88);
    kanto_count.show();
    johto_count.show();
}

void pokedex_hide()
{
    for (int i = 0; i < DEX_MAX; i++)
    {
        tte_erase_rect(0, 0, 240, 160);
        dex_array[i].hide();
    }
    kanto_count.hide();
    johto_count.hide();
}