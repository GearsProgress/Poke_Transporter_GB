#ifndef SCRIPT_OBJ_H
#define SCRIPT_OBJ_H

#include <string>
#include "pokemon_party.h"

class script_obj
{
public:
    script_obj();
    script_obj(const byte* nText, uint16_t nNext);               // For dialogue
    script_obj(uint16_t nRun, uint16_t nNext);                             // For commands
    script_obj(uint16_t nRun, uint16_t nNext_if_true, uint16_t nNext_if_false); // for conditionals

    const byte* get_text();
    uint16_t get_true_index();
    uint16_t get_false_index();
    uint16_t get_cond_id();

private:
    const byte* text;
    bool has_text = false;
    uint16_t next_index;
    uint16_t conditional_index;
    uint16_t next_false_index;
};

#endif