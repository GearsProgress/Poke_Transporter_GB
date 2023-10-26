#ifndef TEXT_ENGINE_H
#define TEXT_ENGINE_H

#include <tonc.h>
#include <string>

#include "script_obj.h"
#include "script_array.h"

#define H_MAX 240
#define V_MAX 160
#define LEFT 8
#define RIGHT (H_MAX - LEFT)
#define TOP 120
#define BOTTOM V_MAX

    void init_text_engine();
    void text_next_frame();
    int text_next_obj_id(script_obj current_line);
    void text_enable();
    void text_disable();
    void show_text_box();
    void hide_text_box();

#endif