#ifndef SCRIPT_OBJ_H
#define SCRIPT_OBJ_H

#include <string>
#include "pokemon_party.h"

#define CHECK_GAME 1
#define START_LINK 2

#define ERROR_TIMEOUT 10
#define ERROR_DISCONNECT 11
#define ERROR_COM_ENDED 12

class script_obj
{
public:
    script_obj();
    script_obj(std::string nText, int nNext_index);
    script_obj(std::string nText, int nNext_index, int nCond_index);
    script_obj(std::string nText, int nNext_index, int nCond_index, int nFalse_index);
    void link_party_var(Pokemon_Party *var);

    std::string get_text();
    int get_true_index();
    int get_false_index();
    int get_cond_id();
    int get_next_obj_id();

private:
    std::string text;
    int next_index;
    int conditional_index;
    int next_false_index;
    bool run_conditional(int index);
    Pokemon_Party *party_data; //ME
};

#endif