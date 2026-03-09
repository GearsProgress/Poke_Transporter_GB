#ifndef _DEBUG_MENU_H
#define _DEBUG_MENU_H

#include "vertical_menu.h"

typedef void (*on_execute_callback)(void *context, unsigned user_param);

/**
 * @brief This struct represents the metadata associated to a single option of a single row in the debug menu.
 */
typedef struct option_data
{
    const char *text;
    unsigned value;
} option_data;

/**
 * @brief This struct represents a single row in the debug menu. Each row has a label and a set of options.
 * 
 */
typedef struct debug_menu_row_data
{
    const u16 *charset;
    const char *labelText;
    struct {
        u8 num_options;
        const option_data *options;
        on_execute_callback on_option_activate;
        u8 selected_option_index;
        bool should_delete_on_destruct;
    } option_section;
    /**
     * @brief A callback that you can set to execute when the user selects this row and presses the A button.
     */
    on_execute_callback on_execute;
    unsigned user_param;
} debug_menu_row_data;

/**
 * @brief This class is responsible for rendering and handling input for a single row in the vertical_menu based
 * debug menu.
 */
class debug_menu_row_widget : public i_item_widget
{
public:
    debug_menu_row_widget(const debug_menu_row_data &data);
    virtual ~debug_menu_row_widget();
    void render_item(text_data_table &text_table, unsigned x, unsigned y, bool is_focused) override;
    MenuInputHandleState handle_input() override;
protected:
private:
    debug_menu_row_data data_;
};

void show_debug_menu();

#endif