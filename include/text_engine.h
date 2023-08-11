#ifndef TEXT_ENGINE_H
#define TEXT_ENGINE_H

#include <tonc.h>
#include <string>

#include "script_obj.h"
#include "script_array.h"

    void init_text_engine();
    void text_next_frame();
    int text_next_obj_id(script_obj current_line);
    void text_enable();
    void text_disable();

#endif