#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <tonc.h>
#include <vector>

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



class Button_Menu
{
public:
    Button_Menu(int nRows, int nColumns, int nButton_width, int nButton_height);
    int button_main();
    void add_button(Button btn, int return_val);
    void hide_buttons();
    void show_buttons();
    void organize_buttons();
    unsigned int get_pos_from_xy(int nX, int nY);
    unsigned int get_x_from_pos(int nPos);
    unsigned int get_y_from_pos(int nPos);
    void set_xy_min_max(int nX_min, int nX_max, int nY_min, int nY_max);

private:
    std::vector<Button> button_vector;
    std::vector<int> return_values;
    int columns;
    int rows;
    int button_height;
    int button_width;
    unsigned int curr_position;
    int x_min;
    int x_max;
    int y_min;
    int y_max;
};
#endif