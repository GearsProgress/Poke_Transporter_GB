#include "dbg/debug_menu.h"
#include "dbg/debug_menu_functions.h"
#include "pokemon_data.h"
#include "text_engine.h"
#include "sprite_data.h"
#include "background_engine.h"
#include "vertical_menu_cursor_handler.h"

#include <tonc.h>

static const option_data toggle_options[2] = {
    {
        .text = "Off",
        .value = 0
    },
    {
        .text = "On",
        .value = 1
    }
};

static const option_data custom_options[] = {
    {
        .text = "One",
        .value = 1
    },
    {
        .text = "Two",
        .value = 2
    },
    {
        .text = "Three",
        .value = 3
    }
};

/**
 * @brief This helper function makes it easy to define a multiple choice debug row.
 */
static debug_menu_row_widget define_debug_choice_row(const u16 *charset, const char *labelText, on_execute_callback option_activate_callback, const option_data *options_metadata, u8 num_options, bool should_delete_options, u8 default_option_index)
{
    const debug_menu_row_data row_data = {
        .charset = charset,
        .labelText = labelText,
        .option_section = {
            .num_options = num_options,
            .options = options_metadata,
            .on_option_activate = option_activate_callback,
            .selected_option_index = default_option_index,
            .should_delete_on_destruct = should_delete_options
        },
        .on_execute = nullptr,
        .user_param = 0
    };
    return debug_menu_row_widget(row_data);
}

/**
 * @brief This helper function makes it easy to define a toggle row.
 */
static debug_menu_row_widget define_toggle_row(const u16 *charset, const char* labelText, on_execute_callback on_toggle_callback, bool default_value)
{
    return define_debug_choice_row(charset, labelText, on_toggle_callback, toggle_options, 2, false, default_value ? 1 : 0);
}

/**
 * @brief This helper function makes it easy to define a row that executes a function when you select it and press A.
 */
static debug_menu_row_widget define_executable_row(const u16 *charset, const char* labelText, on_execute_callback on_execute, unsigned user_param)
{
    const debug_menu_row_data row_data = {
        .charset = charset,
        .labelText = labelText,
        .option_section = {
            .num_options = 0,
            .options = nullptr,
            .on_option_activate = nullptr,
            .selected_option_index = 0,
            .should_delete_on_destruct = false
        },
        .on_execute = on_execute,
        .user_param = user_param
    };
    return debug_menu_row_widget(row_data);
}

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

    debug_menu_row_widget row_widget_default_off = define_toggle_row(charset, "Def_Off", dbg_menu_print_number, false);
    debug_menu_row_widget row_widget_default_on = define_toggle_row(charset, "Def_On", dbg_menu_print_number, true);
    debug_menu_row_widget row_widget_custom_options = define_debug_choice_row(charset, "Custom", dbg_menu_print_number, custom_options, 3, false, 1);
    debug_menu_row_widget row_widget_executable = define_executable_row(charset, "Exec", dbg_menu_print_number, 128);

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

    i_item_widget* item_widgets[] = {
        &row_widget_default_off,
        &row_widget_default_on,
        &row_widget_custom_options,
        &row_widget_executable
    };
    debug_menu.set_state_changed_handler(&cursor_handler);
    debug_menu.add_item_widgets(item_widgets, sizeof(item_widgets) / sizeof(item_widgets[0]));

    debug_menu.show();
    debug_menu.run();
    debug_menu.hide();

    hide_text_box();
    tte_erase_rect(0, 0, H_MAX, V_MAX);
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
            data_.option_section.on_option_activate(this, data_.option_section.options[data_.option_section.selected_option_index].value);
        }
        
        if(handled)
        {
            return MenuInputHandleState::HANDLED_UPDATE_VIEWPORT;
        }
    }

    if(key_hit(KEY_A) && data_.on_execute)
    {
        data_.on_execute(this, data_.user_param);
        return MenuInputHandleState::HANDLED;
    }
    
    return MenuInputHandleState::NOT_HANDLED;
}