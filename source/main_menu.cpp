#include <tonc.h>
#include "main_menu.h"
#include "button_handler.h"

int menu_slot = 1;
int old_menu_slot = 0;
int menu_mode = MAIN_MENU;
int ani_mode = 0;
int menu_x_cord = 128;

Button button_array[4];

void main_menu_init(Button nTransfer, Button nPokedex, Button nCredits)
{
    button_array[TRANSFER] = nTransfer;
    button_array[POKEDEX] = nPokedex;
    button_array[CREDITS] = nCredits;
    button_array[TRANSFER].set_location(128, 16);
    button_array[POKEDEX].set_location(128, 64);
    button_array[CREDITS].set_location(128, 112);
    button_array[TRANSFER].show();
    button_array[POKEDEX].show();
    button_array[CREDITS].show();
}

int main_menu_loop()
{
    switch (ani_mode)
    {
    case ENTERING:
    {
        menu_x_cord = menu_x_cord + 4;
        for (int i = 1; i < 4; i++)
        {
            button_array[i].set_location(menu_x_cord, 16 + (48 * (i - 1)));
        }
        if (menu_x_cord > 240)
        {
            ani_mode = DISABLE;
        }
        break;
    }
    case EXITING:
    {
        menu_x_cord = menu_x_cord - 4;
        for (int i = 1; i < 4; i++)
        {
            button_array[i].set_location(menu_x_cord, 16 + (48 * (i - 1)));
        }
        if (menu_x_cord <= 128)
        {
            ani_mode = MAIN_MENU;
        }
        break;
    }
    case MAIN_MENU:
    {
        if (key_hit(KEY_DOWN))
        {
            if (menu_slot != CREDITS)
            {
                menu_slot++;
            }
        }

        if (key_hit(KEY_UP))
        {
            if (menu_slot != TRANSFER)
            {
                menu_slot--;
            }
        }

        if (key_hit(KEY_A))
        {
            ani_mode = ENTERING;
        }

        if (menu_slot != old_menu_slot)
        {
            button_array[menu_slot].set_highlight(true);
            button_array[old_menu_slot].set_highlight(false);
            old_menu_slot = menu_slot;
        }
        return 0;
    }
    };
    if (ani_mode == DISABLE)
    {
        return menu_slot;
    }
    return 0;
}

void main_menu_enter()
{
    ani_mode = ENTERING;
}

void main_menu_exit()
{
    ani_mode = EXITING;
}