#ifndef BOX_MENU_H
#define BOX_MENU_H

#include <tonc.h>
#include <vector>
#include "string.h"
#include "button_handler.h"
#include "pokemon.h"
#include "string_view"
#include "pokemon_party.h"
#include "button_handler.h"

#define CANCEL_BUTTON 1
#define CONFIRM_BUTTON 2

// Box is 144 x 104, top left is 88 32, sprite is 16x16, sprites are not centered
#define BOXMENU_TOP 32
#define BOXMENU_LEFT 88
#define BOXMENU_VSPACE -4
#define BOXMENU_HSPACE -8
#define BOXMENU_HNUM 6
#define BOXMENU_SPRITE_WIDTH 32
#define BOXMENU_SPRITE_HEIGHT 24
#define BOXMENU_SPRITE_VOFFSET -8
#define BOXMENU_SPRITE_HOFFSET 0

class Box_Menu
{
public:
    Box_Menu();
    int box_main(Pokemon_Party party_data);
private:
    int curr_button;
    int x;
    int y;

};

#endif