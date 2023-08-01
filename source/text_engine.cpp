#include <tonc.h>

#include "text_engine.h"

const int H_MAX = 240;
const int V_MAX = 160;
const int LEFT = 16;
const int RIGHT = H_MAX - LEFT;
const int TOP = 122;
const int BOTTOM = V_MAX;

uint char_count = 0;

text_engine::text_engine()
{
    OBJ_ATTR *objs = &oam_mem[127];
    tte_init_obj_default(objs);
    tte_set_margins(LEFT, TOP, RIGHT, BOTTOM);
    tte_set_pos(LEFT, TOP);
    curr_string = "Hello there! Welcome to\nthe world of Pokemon!";
    next_string = "My name is OAK, but you\ncan call me professor.";
    frame_count = 0;
}

void text_engine::next_frame()
{
    tte_set_pos(LEFT, TOP);
    if(char_count < curr_string.length()){
    if (frame_count % 2 == 0 || key_held(KEY_B))
    {
        char_count++;
        tte_erase_rect(LEFT, TOP, RIGHT, BOTTOM);
        tte_write(curr_string.substr(0, char_count).c_str());
    }
    } else {
        if(key_hit(KEY_A)){
            curr_string = next_string;
            char_count = 0;
        }
    }

    frame_count++;
}
