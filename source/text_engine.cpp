#include <tonc.h>
#include <string>

#include "text_engine.h"
#include "script_array.h"

const int H_MAX = 240;
const int V_MAX = 160;
const int LEFT = 16;
const int RIGHT = H_MAX - LEFT;
const int TOP = 122;
const int BOTTOM = V_MAX;

uint char_count = 0;
Pokemon_Party party_data;

text_engine::text_engine()
{
    OBJ_ATTR *objs = &oam_mem[127];
    tte_init_obj_default(objs);

    tte_set_margins(LEFT, TOP, RIGHT, BOTTOM);
    tte_set_pos(LEFT, TOP);

    curr_line = script[0];
    frame_count = 0;
}

void text_engine::next_frame()
{
    tte_set_pos(LEFT, TOP);
    if (char_count < curr_line.get_text().length())
    {
        if (frame_count % 2 == 0 || key_held(KEY_B))
        {
            char_count++;
            tte_erase_rect(LEFT, TOP, RIGHT, BOTTOM);
            tte_write(curr_line.get_text().substr(0, char_count).c_str());
        }
    }
    else
    {
        if (key_hit(KEY_A) || frame_count <= 1)
        {
            curr_line = script[curr_line.get_next_obj_id()];
            char_count = 0;
        }
    }

    frame_count++;
}
