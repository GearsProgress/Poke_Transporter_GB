#include <tonc.h>
#include "main_menu.h"
#include "button_handler.h"
#include "save_data_manager.h"

int menu_slot = 1;
int old_menu_slot = 0;
int menu_mode = BTN_MAIN_MENU;
int ani_mode = 0;
int menu_x_cord = 128;
int lang_btn_slot;
int old_lang_btn_slot;

Button wide_button_array[WIDE_BUTTON_ARRAY_SIZE];
Button lang_button_array[LANG_BUTTON_ARRAY_SIZE];

void main_menu_btn_init(Button nButton, int index)
{
    if (nButton.isWide)
    {
        wide_button_array[index] = nButton;
        wide_button_array[index].set_location(128, 7 + (38 * (index - 1)));
        wide_button_array[index].show();
    }
    else
    {
        lang_button_array[index] = nButton;
        lang_button_array[index].set_location(30 + ((40 + 30) * (index % 3)), 24 + ((24 + 24) * (index / 3)));
        lang_button_array[index].hide();
    }
}

int main_menu_loop()
{
    switch (ani_mode)
    {
    case ENTERING:
    {
        menu_x_cord = menu_x_cord + 4;
        for (int i = 1; i < (WIDE_BUTTON_ARRAY_SIZE + 1); i++)
        {
            wide_button_array[i].set_location(menu_x_cord, 7 + (38 * (i - 1)));
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
        for (int i = 1; i < (WIDE_BUTTON_ARRAY_SIZE + 1); i++)
        {
            wide_button_array[i].set_location(menu_x_cord, 7 + (38 * (i - 1)));
        }
        if (menu_x_cord <= 128)
        {
            ani_mode = BTN_MAIN_MENU;
        }
        break;
    }
    case BTN_MAIN_MENU:
    {
        if (key_hit(KEY_DOWN))
        {
            if (menu_slot != (WIDE_BUTTON_ARRAY_SIZE - 1))
            {
                menu_slot++;
            }
        }

        if (key_hit(KEY_UP))
        {
            if (menu_slot != BTN_TRANSFER)
            {
                menu_slot--;
            }
        }

        if (key_hit(KEY_A))
        {
            if ((get_tutorial_flag() == true || menu_slot == BTN_TRANSFER))
            {
                ani_mode = ENTERING;
            }
            else
            {
                // "Bad" noise here
            }
        }

        if (menu_slot != old_menu_slot)
        {
            wide_button_array[menu_slot].set_highlight(true);
            wide_button_array[old_menu_slot].set_highlight(false);
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

void show_lang_btns()
{
    for (int i = 0; i < LANG_BUTTON_ARRAY_SIZE; i++)
    {
        lang_button_array[i].show();
    }
}

void hide_lang_btns()
{
    for (int i = 0; i < LANG_BUTTON_ARRAY_SIZE; i++)
    {
        lang_button_array[i].hide();
    }
}

void highlight_lang_btn(int index, bool highlight)
{
    lang_button_array[index].set_highlight(highlight);
}

void set_arrow_point(int index)
{
    lang_button_array[LANG_ARROW].set_location(lang_button_array[index].x + 16, lang_button_array[index].y - 8);
}