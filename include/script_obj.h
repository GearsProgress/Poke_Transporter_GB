#ifndef SCRIPT_OBJ_H
#define SCRIPT_OBJ_H

#include <string>
#include "pokemon_party.h"

class script_obj
{
public:
    script_obj();
    script_obj(std::string_view nText, int nNext);
    script_obj(std::string_view nText, int nRun, int nNext);
    script_obj(int nRun, int nNext);
    script_obj(std::string_view nText, int nRun, int nNext_if_true, int nNext_if_false);
    script_obj(int nRun, int nNext_if_true, int nNext_if_false);

    std::string get_text();
    int get_true_index();
    int get_false_index();
    int get_cond_id();

private:
    std::string text;
    int next_index;
    int conditional_index;
    int next_false_index;
};

#endif