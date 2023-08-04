#ifndef TEXT_ENGINE_H
#define TEXT_ENGINE_H

#include <tonc.h>
#include <string>

#include "script_obj.h"
#include "script_array.h"

class text_engine
{
public:
    text_engine();
    void next_frame();
    int get_next_obj_id(script_obj current_line);

private:
    script_obj curr_line;
    int frame_count;
    void set_next_line(std::string next);
};

#endif