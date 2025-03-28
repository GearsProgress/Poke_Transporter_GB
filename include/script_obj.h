#ifndef SCRIPT_OBJ_H
#define SCRIPT_OBJ_H

#include <string>
#include "pokemon_party.h"

class script_obj
{
public:
    script_obj();
    script_obj(const byte* nText, int nNext);               // For dialogue
    script_obj(int nRun, int nNext);                             // For commands
    script_obj(int nRun, int nNext_if_true, int nNext_if_false); // for conditionals

    const byte* get_text();
    int get_true_index();
    int get_false_index();
    int get_cond_id();

private:
    const byte* text;
    bool has_text = false;
    int next_index;
    int conditional_index;
    int next_false_index;
};

#endif