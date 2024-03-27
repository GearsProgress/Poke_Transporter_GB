#include <tonc.h>
#include <string>
#include <cmath>

#include "pokedex.h"
#include "dex_handler.h"
#include "sprite_data.h"
#include "pokemon_data.h"
#include "global_frame_controller.h"
#include "save_data_manager.h"

Dex dex_array[DEX_MAX];
int dex_shift = 0;
int dex_x_cord = 48;
int speed = 0;
int delay = 0;
int count = 0;
int leading_zeros = 0;

void pokedex_init()
{
    for (int i = 0; i < DEX_MAX; i++)
    {
        dex_array[i] = Dex(dex_l[i], dex_m[i], dex_r[i], 320, 352, 384);
        dex_array[i].set_location(dex_x_cord, (i * (8 * 3)) + 8);
    }
}

int pokedex_loop()
{
    if (key_hit(KEY_DOWN) || key_hit(KEY_UP))
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

    if (dex_shift > DEX_SHIFT_MAX)
    {
        dex_shift = DEX_SHIFT_MAX;
    }
    else if (dex_shift < 0)
    {
        dex_shift = 0;
    }

    tte_erase_rect(0, 0, 240, 160);
    for (int i = 0; i < DEX_MAX; i++)
    {
        tte_set_pos(dex_x_cord + (1 * 8), (i * 8 * 3) + 16);
        tte_write(is_caught(dex_shift + i + 1) ? "^" : " ");
        tte_set_pos(dex_x_cord + (3 * 8), (i * 8 * 3) + 16);
        tte_write(is_caught(dex_shift + i + 1) ? std::string(NAMES[dex_shift + i + 1]).data() : "----------");
        tte_set_pos(dex_x_cord + (14 * 8), (i * 8 * 3) + 16);
        tte_write("000");
        if(dex_shift + i + 1 < 10){
            leading_zeros = 2;
        } else if (dex_shift + i + 1 < 100){
            leading_zeros = 1;
        } else {
            leading_zeros = 0;
        }
        tte_set_pos(dex_x_cord + ((14 + leading_zeros) * 8), (i * 8 * 3) + 16);
        tte_write(std::to_string(dex_shift + i + 1).c_str());
    }
    return 0;
}

void pokedex_show()
{
    for (int i = 0; i < DEX_MAX; i++)
    {
        dex_array[i].show();
    }
}

void pokedex_hide()
{
    for (int i = 0; i < DEX_MAX; i++)
    {
        tte_erase_rect(0, 0, 240, 160);
        dex_array[i].hide();
    }
}