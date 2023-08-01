#ifndef TEXT_ENGINE_H
#define TEXT_ENGINE_H

#include <tonc.h>
#include <string>

class text_engine
{
public:
    text_engine();
    void next_frame();

private:
    std::string curr_string;
    std::string next_string;
    int frame_count;
};

#endif