#ifndef SCRIPT_OBJ_H
#define SCRIPT_OBJ_H

#include <string>

class script_obj
{
public:
    script_obj();
    script_obj(std::string nText, int nNext_index);
    script_obj(std::string nText, int nNext_index, int nCond_index, int nFalse_index);

    std::string get_text();
    int get_true_index();
    int get_false_index();
    int get_cond_id();
    int get_next_obj_id();
    int get_out_code();

private:
    std::string text;
    int next_index;
    int conditional_index;
    int next_false_index;
    bool run_conditional(int index);
    int out_code;
};

#endif