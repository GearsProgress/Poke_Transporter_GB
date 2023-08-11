#include <tonc.h>
#include <string>

#include "text_engine.h"
#include <cstring>

#define TEXT_CBB 3
#define TEXT_SBB 28

const int H_MAX = 240;
const int V_MAX = 160;
const int LEFT = 8;
const int RIGHT = H_MAX - LEFT;
const int TOP = 120;
const int BOTTOM = V_MAX;

script_obj curr_line;
int frame_count;
uint char_count;
bool disabled;

void init_text_engine()
{
    // Load the TTE
    tte_init_se(3, BG_CBB(TEXT_CBB) | BG_SBB(TEXT_SBB) | BG_PRIO(0), 0xF000, CLR_ORANGE, 0, &fwf_default, NULL);
    tte_set_margins(LEFT, TOP, RIGHT, BOTTOM);
    tte_set_pos(LEFT, TOP);

    // Set default variables
    curr_line = script[0];
    frame_count = 0;
    char_count = 0;
    disabled = false;
}

void text_next_frame()
{
    if (!disabled)
    {
        tte_set_pos(LEFT, TOP);
        if (char_count < curr_line.get_text().length())
        {
            if (frame_count % 2 == 0 || key_held(KEY_B))
            {
                char_count++;
                tte_erase_rect(LEFT, TOP, RIGHT, BOTTOM);
                tte_set_ink(CLR_RED);
                tte_write(curr_line.get_text().substr(0, char_count).c_str());
            }
        }
        else
        {
            if (key_hit(KEY_A) || char_count == 0)
            {
                curr_line = script[text_next_obj_id(curr_line)];
                char_count = 0;
            }
        }

        frame_count++;
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
    REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(1);
}

void text_disable()
{
    disabled = true;
    tte_erase_screen();
    REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
}
