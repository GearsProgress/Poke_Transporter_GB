#include "select_menu.h"
#include "sprite_data.h"

#define TEXT_HEIGHT 10
#define TEXT_WIDTH 8
#define TILE_HEIGHT 8
#define TILE_WIDTH 8

Select_Menu::Select_Menu(bool enable_cancel, int nMenu_type)
{
    cancel_enabled = enable_cancel;
    menu_type = nMenu_type;
}

void Select_Menu::add_option(std::string option, int return_value)
{
    menu_options.push_back(option);
    return_values.push_back(return_value);
}

int Select_Menu::select_menu_main()
{
    show_menu();
    curr_selection = 0;

    key_poll(); // Reset the buttons

    bool update = true;
    bool first = true;
    while (true)
    {
        update = true;
        if (key_hit(KEY_DOWN))
        {
            curr_selection = ((curr_selection + 1) % menu_options.size());
        }
        else if (key_hit(KEY_UP))
        {
            curr_selection = ((curr_selection + (menu_options.size() - 1)) % menu_options.size());
        }
        else if (key_hit(KEY_A))
        {
            hide_menu();
            return return_values[curr_selection];
        }
        else if (cancel_enabled && key_hit(KEY_B))
        {
            hide_menu();
            return -1;
        }
        else if (!first)
        {
            update = false;
        }
        update_y_offset();
        obj_set_pos(point_arrow, 19 * TILE_HEIGHT, (2 + curr_selection) * TEXT_HEIGHT);
        global_next_frame();

        if (update)
        {
            if (return_values[curr_selection] == -1)
            {
                switch (menu_type)
                {
                case CART_MENU:
                    obj_hide(cart_shell);
                    obj_hide(cart_label);
                    break;
                case LANG_MENU:
                    obj_hide(flag);
                    break;
                }
            }
            else
            {
                switch (menu_type)
                {
                case CART_MENU:
                    load_select_sprites(return_values[curr_selection], lang);
                    obj_unhide(cart_shell, 0);
                    obj_unhide(cart_label, 0);
                    break;
                case LANG_MENU:
                    load_select_sprites(0, return_values[curr_selection]);
                    obj_unhide(flag, 0);
                    break;
                }
            }
        }
    }
    return 0;
}

void Select_Menu::show_menu()
{
    add_menu_box(menu_options.size());
    for (unsigned int i = 0; i < menu_options.size(); i++)
    {
        tte_set_pos(20 * TEXT_WIDTH, (2 + i) * TEXT_HEIGHT);
        ptgb_write(menu_options[i].c_str());
    }
    obj_unhide(point_arrow, 0);
    obj_set_pos(point_arrow, 19 * TEXT_WIDTH, 2 * TEXT_HEIGHT);
}

void Select_Menu::hide_menu()
{
    obj_hide(point_arrow);
    tte_erase_rect(160, 16, 224, 160);
    reload_textbox_background();
    clear_options();
    obj_hide(point_arrow);
    switch (menu_type)
    {
    case CART_MENU:
        obj_hide(cart_shell);
        obj_hide(cart_label);
        break;
    case LANG_MENU:
        obj_hide(flag);
        break;
    }
}

void Select_Menu::clear_options()
{
    menu_options.clear();
    return_values.clear();
}

void Select_Menu::set_lang(int nLang)
{
    lang = nLang;
}