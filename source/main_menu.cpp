#include <tonc.h>
#include "main_menu.h"
#include "button_handler.h"
#include "save_data_manager.h"
#include "global_frame_controller.h"

Button_Menu::Button_Menu(int nRows, int nColumns, int nButton_width, int nButton_height)
{
    columns = nColumns;
    rows = nRows;
    button_height = nButton_height;
    button_width = nButton_width;
    curr_position = 0;
    x_min = 0;
    x_max = 240;
    y_min = 0;
    y_max = 160;
}

void Button_Menu::set_xy_min_max(int nX_min, int nX_max, int nY_min, int nY_max){
    x_min = nX_min;
    x_max = nX_max;
    y_min = nY_min;
    y_max = nY_max;
}

int Button_Menu::button_main()
{
    tte_set_pos(0, 0);
    organize_buttons();
    show_buttons();
    button_vector.at(curr_position).set_highlight(true);
    int curr_x;
    int curr_y;

    key_poll(); // Reset the buttons

    while (true)
    {
        curr_x = get_x_from_pos(curr_position);
        curr_y = get_y_from_pos(curr_position);

        if (key_hit(KEY_RIGHT) && (curr_x < (columns - 1)))
        {
            curr_x++;
        }
        else if (key_hit(KEY_DOWN) && (curr_y < (rows - 1)))
        {
            curr_y++;
        }
        else if (key_hit(KEY_LEFT) && (curr_x > 0))
        {
            curr_x--;
        }
        else if (key_hit(KEY_UP) && (curr_y > 0))
        {
            curr_y--;
        }
        else if (key_hit(KEY_A))
        {
            hide_buttons();
            return return_values.at(curr_position);
        }

        if (get_pos_from_xy(curr_x, curr_y) != curr_position)
        {
            button_vector.at(curr_position).set_highlight(false);
            curr_position = get_pos_from_xy(curr_x, curr_y);
            button_vector.at(curr_position).set_highlight(true);
        }
        global_next_frame();
    }
    return 0;
}

void Button_Menu::add_button(Button btn, int return_val)
{
    button_vector.push_back(btn);
    return_values.push_back(return_val);
}

void Button_Menu::show_buttons()
{
    for (unsigned int i = 0; i < button_vector.size(); i++)
    {
        button_vector.at(i).show();
    }
}

void Button_Menu::hide_buttons()
{
    for (Button &curr_btn : button_vector)
    {
        curr_btn.hide();
    }
}

void Button_Menu::organize_buttons()
{
    // Total space, minus the space taken up by the buttons, divided by the spaces between the buttons.
    int vertical_space =
        ((y_max - y_min) - ((button_vector.size() / columns) * button_height)) / ((button_vector.size() / columns) + 1);
    int horizonal_space =
        ((x_max - x_min) - ((button_vector.size() / rows) * button_width)) / ((button_vector.size() / rows) + 1);

    for (unsigned int i = 0; i < button_vector.size(); i++)
    {
        button_vector.at(i).set_location(
            ((horizonal_space + button_width) * get_x_from_pos(i)) + horizonal_space + x_min,
            ((vertical_space + button_height) * get_y_from_pos(i)) + vertical_space + y_min);
    }
}

unsigned int Button_Menu::get_pos_from_xy(int nX, int nY)
{
    return (nY * columns) + nX;
}

unsigned int Button_Menu::get_x_from_pos(int nPos)
{
    return (nPos % columns);
}

unsigned int Button_Menu::get_y_from_pos(int nPos)
{
    return (nPos / columns);
}