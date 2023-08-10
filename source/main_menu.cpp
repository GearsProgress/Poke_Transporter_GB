#include <tonc.h>
#include "main_menu.h"
#include "button_handler.h"



int menu_slot = 1;
int old_menu_slot = 0;

Button button_array[4];

void main_menu_init(Button nTransfer, Button nPokedex, Button nCredits)
{
    button_array[TRANSFER] = nTransfer;
    button_array[POKEDEX] = nPokedex;
    button_array[CREDITS] = nCredits;
    button_array[TRANSFER].set_location(10, 10);
    button_array[POKEDEX].set_location(10, 60);
    button_array[CREDITS].set_location(10, 100);
    button_array[TRANSFER].show();
    button_array[POKEDEX].show();
    button_array[CREDITS].show();
}

int main_menu_loop()
{
    if(key_hit(KEY_DOWN)){
        if (menu_slot != CREDITS){
            menu_slot++;
        }
    }

    if (key_hit(KEY_UP)){
        if (menu_slot != TRANSFER){
            menu_slot--;
        }
    }

    if (key_hit(KEY_A)){
        return (menu_slot);
    }

    if (menu_slot != old_menu_slot)
    {
        button_array[menu_slot].set_highlight(true);
        button_array[old_menu_slot].set_highlight(false);
        old_menu_slot = menu_slot;
    }
    return 0;
}
