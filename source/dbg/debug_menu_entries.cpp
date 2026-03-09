#include "dbg/debug_menu.h"
#include "dbg/debug_menu_entries.h"
#include "dbg/debug_menu_functions.h"
#include "vertical_menu.h"

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

void fill_debug_menu_with_entries(vertical_menu &menu, u16 *charset)
{
    debug_menu_row_widget row_widget_default_off = define_toggle_row(charset, "Def_Off", dbg_menu_print_number, false);
    debug_menu_row_widget row_widget_default_on = define_toggle_row(charset, "Def_On", dbg_menu_print_number, true);
    debug_menu_row_widget row_widget_custom_options = define_debug_choice_row(charset, "Custom", dbg_menu_print_number, custom_options, 3, false, 1);
    debug_menu_row_widget row_widget_executable = define_executable_row(charset, "Exec", dbg_menu_print_number, 128);

    i_item_widget* item_widgets[] = {
        &row_widget_default_off,
        &row_widget_default_on,
        &row_widget_custom_options,
        &row_widget_executable
    };

    menu.add_item_widgets(item_widgets, sizeof(item_widgets) / sizeof(item_widgets[0]));
}