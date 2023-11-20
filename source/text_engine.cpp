#include <tonc.h>
#include <string>
#include <cstring>

#include "text_engine.h"
#include "global_frame_counter.h"
#include "pkmn_font.h"
#include "script_array.h"

#define TEXT_CBB 3
#define TEXT_SBB 28

script_obj curr_line;
uint char_index;
uint line_char_index;
std::string curr_text;
bool disabled;

void init_text_engine()
{
    // Load the TTE
    tte_init_se(3, BG_CBB(TEXT_CBB) | BG_SBB(TEXT_SBB) | BG_PRIO(0), 0, CLR_WHITE, 14, &pkmn_fontFont, NULL);
    tte_set_margins(LEFT, TOP, RIGHT, BOTTOM);
    tte_set_pos(LEFT, TOP);

    pal_bg_bank[13][15] = CLR_WHITE;
    pal_bg_bank[14][15] = 0b0000001001111111;
    pal_bg_bank[15][15] = 0b0001100011100110;
    

    // Set default variables
    curr_line = script[SCRIPT_START];
    char_index = 0;
    line_char_index = 0;
    disabled = false;
    curr_text = curr_line.get_text();
}

void text_next_frame()
{
    if (!disabled)
    {
        tte_set_pos(LEFT, TOP);
        if (char_index < curr_text.length() && curr_text.substr(char_index, 1) != "|")
        {
            if (get_frame_count() % 2 == 0 || key_held(KEY_B))
            {
                char_index++;
                tte_erase_rect(LEFT, TOP, RIGHT, BOTTOM);
                tte_write(curr_text.substr(0, char_index).c_str());
            }
        }
        else
        {
            if (key_hit(KEY_A) || curr_text.length() == 0)
            {
                if (curr_text.substr(char_index, 1) == "|")
                {
                    line_char_index += char_index;
                    line_char_index++;
                    curr_text = curr_line.get_text().substr(line_char_index);
                    char_index = 0;
                }
                else
                {
                    line_char_index = 0;
                    curr_line = script[text_next_obj_id(curr_line)];
                    curr_text = curr_line.get_text();
                    char_index = 0;
                }
            }
        }
    }
}

int text_next_obj_id(script_obj current_line)
{
    if (current_line.get_cond_id() == 0)
    {
        return current_line.get_true_index();
    }
    else
    {
        if (run_conditional(current_line.get_cond_id()))
        {
            return current_line.get_true_index();
        }
        return current_line.get_false_index();
    }
}

void text_enable()
{
    disabled = false;
    show_text_box();
}

void text_disable()
{
    disabled = true;
    tte_erase_screen();
    hide_text_box();
}

void show_text_box()
{
    REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(1);
}

void hide_text_box()
{
    REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
}
