#ifndef BOX_MENU_H
#define BOX_MENU_H

#include <tonc.h>
#include <vector>
#include "string.h"
#include "button_handler.h"
#include "pokemon.h"
#include "string_view"
#include "pokemon_party.h"

class Box_Menu
{
public:
    Box_Menu();
    int box_main(Pokemon_Party party_data);
private:
};

#endif