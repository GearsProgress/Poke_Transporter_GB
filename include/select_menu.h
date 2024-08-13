#ifndef SELECT_MENU_H
#define SELECT_MENU_H

#include <tonc.h>
#include <vector>
#include <string>

#define LANG_MENU 1
#define CART_MENU 2

class Select_Menu
{
public:
    Select_Menu(bool enable_cancel, int nMenu_type);
    int select_menu_main();
    void hide_menu();
    void show_menu();
    void clear_options();
    void add_option(std::string option, int return_value);
    void set_lang(int nLang);

private:
    std::vector<std::string> menu_options;
    std::vector<int> return_values;
    unsigned int curr_selection;
    bool cancel_enabled;
    int menu_type;
    int lang;
};

#endif