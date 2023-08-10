#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <tonc.h>

#include "button_handler.h"

#define TRANSFER 1
#define POKEDEX 2
#define CREDITS 3

void main_menu_init(Button transfer, Button pokedex, Button credits);
int main_menu_loop();

#endif