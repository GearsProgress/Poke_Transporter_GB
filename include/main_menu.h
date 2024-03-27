#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <tonc.h>

#include "button_handler.h"

#define BTN_MAIN_MENU 0
#define BTN_TRANSFER 1
#define BTN_POKEDEX 2
#define BTN_LANGUAGE 3
#define BTN_CREDITS 4
#define WIDE_BUTTON_ARRAY_SIZE 5

#define BTN_ENG 0
#define BTN_FRE 1
#define BTN_ITA 2
#define BTN_GER 3
#define BTN_SPA 4
#define BTN_KOR 5
#define LANG_ARROW 6
#define LANG_BUTTON_ARRAY_SIZE 7

#define NO_ANI 0
#define ENTERING -1
#define EXITING -2
#define DISABLE -3

void main_menu_btn_init(Button nButton, int index);
int main_menu_loop();
void main_menu_enter();
void main_menu_exit();
void show_lang_btns();
void hide_lang_btns();
void show_main_btns();
void hide_main_btns();
void highlight_lang_btn(int index, bool highlight);
void set_arrow_point(int index);

#endif