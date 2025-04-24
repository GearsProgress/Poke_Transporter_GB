#ifndef SELECT_MENU_H
#define SELECT_MENU_H

#include <tonc.h>
#include "libstd_replacements.h"
#include "text_engine.h"

#define LANG_MENU 1
#define CART_MENU 2

class Select_Menu
{
public:
    Select_Menu(bool enable_cancel, u8 nMenu_type, int nStartX, int nStartY);
    int select_menu_main();
    void hide_menu();
    void show_menu();
    void clear_options();
    void add_option(const byte *option, u8 return_value);
    void set_lang(u8 nLang);

private:
    ptgb::vector<const byte*> menu_options;
    ptgb::vector<u8> return_values;
    u16 curr_selection;
    bool cancel_enabled;
    u8 menu_type;
    u8 lang;
    int startTileX;
    int startTileY;
};

#endif