#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <tonc.h>

#include "button_handler.h"

#define MAIN_MENU 0
#define TRANSFER 1
#define POKEDEX 2
#define CREDITS 3

#define NO_ANI 0
#define ENTERING -1
#define EXITING -2
#define DISABLE -3

void main_menu_init(Button transfer, Button pokedex, Button credits);
int main_menu_loop();
void main_menu_enter();
void main_menu_exit();

#endif