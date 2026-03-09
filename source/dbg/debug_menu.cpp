#include "dbg/debug_menu.h"
#include "dbg/debug_menu_functions.h"
#include "dbg/debug_menu_entries.h"
#include "sprite_data.h"
#include "background_engine.h"
#include "vertical_menu_cursor_handler.h"

#include <tonc.h>

static on_execute_callback delayed_execute_callback = nullptr;
static unsigned delayed_execute_user_param = 0;

void show_debug_menu()
{
    u16 charset[256];
    const s16 cursor_offset_x = 3;
    const s16 cursor_offset_y = 6;

    load_localized_charset(charset, 3, ENGLISH);
    tte_erase_rect(0, 0, H_MAX, V_MAX);
    erase_textbox_tiles();
    show_text_box();
    tte_set_ink(INK_DARK_GREY);

    obj_unhide(toggle_arrow_left, 0);

    const vertical_menu_settings menu_settings = {
        .x = 20,
        .y = 0,
        .width = 200,
        .height = 155,
        .margin_top = 8,
        .margin_bottom = 8,
        .initial_focus_index = 0,
        .item_height = 10,
        .text_table_index = INT32_MAX,
        .allow_cancel = true,
        .should_delete_item_widgets_on_destruct = false,
        .should_hide_state_changed_handler_on_not_focused = true
    };

    vertical_menu_cursor_handler cursor_handler(cursor_offset_x, cursor_offset_y);
    vertical_menu debug_menu(menu_settings);

    debug_menu.set_state_changed_handler(&cursor_handler);
    fill_debug_menu_with_entries(debug_menu, charset);

    debug_menu.show();
    debug_menu.run();
    debug_menu.hide();

    hide_text_box();
    tte_erase_rect(0, 0, H_MAX, V_MAX);

    // execute any callback that was delayed by pressing the A button on an executable row.
    // This is done to make sure the debug menu is fully hidden before executing the callback,
    // to avoid rendering issues.
    if(delayed_execute_callback)
    {
        delayed_execute_callback(delayed_execute_user_param);
        delayed_execute_callback = nullptr;
        delayed_execute_user_param = 0;
    }
}

debug_menu_row_widget::debug_menu_row_widget(const debug_menu_row_data &data)
    : data_(data)
{
}

debug_menu_row_widget::~debug_menu_row_widget()
{
}

void debug_menu_row_widget::render_item(text_data_table &text_table, unsigned x, unsigned y, bool is_focused)
{
    const int label_margin_left = 12;
    const int margin_top = 2;
    const int option_margin_left = 120;
    const int toggle_arrow_left_offset_x = -10;
    const int toggle_arrow_right_offset_x = 35;
    const int toggle_arrows_offset_y = 4;

    tte_set_pos(x + label_margin_left, y + margin_top);
    ptgb_write_debug(data_.charset, data_.labelText, true);

    if(data_.option_section.num_options > 0)
    {
        const u8 selected_option_index = data_.option_section.selected_option_index;

        tte_set_pos(x + option_margin_left, y + margin_top);
        ptgb_write_debug(data_.charset, data_.option_section.options[selected_option_index].text, true);
    }

    if(is_focused)
    {
        if(data_.option_section.num_options > 0)
        {
            const int toggle_arrow_left_x = static_cast<int>(x) + option_margin_left + toggle_arrow_left_offset_x;
            const int toggle_arrow_right_x = static_cast<int>(x) + option_margin_left + toggle_arrow_right_offset_x;
            const int toggle_arrows_y = static_cast<int>(y) + margin_top + toggle_arrows_offset_y;

            obj_set_pos(toggle_arrow_left, toggle_arrow_left_x, toggle_arrows_y);
            obj_set_pos(toggle_arrow_right, toggle_arrow_right_x, toggle_arrows_y);
            obj_unhide(toggle_arrow_left, 0);
            obj_unhide(toggle_arrow_right, 0);
        }
        else
        {
            obj_hide(toggle_arrow_left);
            obj_hide(toggle_arrow_right);
        }
    }
}

MenuInputHandleState debug_menu_row_widget::handle_input()
{
    if(data_.option_section.num_options > 0)
    {
        bool handled = false;
        if(key_hit(KEY_RIGHT))
        {
            data_.option_section.selected_option_index = (data_.option_section.selected_option_index + 1) % data_.option_section.num_options;
            handled = true;
        }
        if(key_hit(KEY_LEFT))
        {
            --data_.option_section.selected_option_index;
            if(data_.option_section.selected_option_index >= data_.option_section.num_options)
            {
                data_.option_section.selected_option_index = data_.option_section.num_options - 1;
            }
            handled = true;
        }

        if(handled && data_.option_section.on_option_activate)
        {
            data_.option_section.on_option_activate(data_.option_section.options[data_.option_section.selected_option_index].value);
        }
        
        if(handled)
        {
            return MenuInputHandleState::HANDLED_UPDATE_VIEWPORT;
        }
    }

    if(key_hit(KEY_A) && data_.on_execute)
    {
        delayed_execute_callback = data_.on_execute;
        delayed_execute_user_param = data_.user_param;
        return MenuInputHandleState::CHOICE_MADE;
    }
    
    return MenuInputHandleState::NOT_HANDLED;
}