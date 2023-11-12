#include <tonc.h>
#include <string>
#include "script_obj.h"
#include "gba_flash.h"
#include "pokemon.h"
#include "pokemon_party.h"
#include "script_array.h"

script_obj::script_obj(){
};

script_obj::script_obj(std::string_view nText, int nNext)
{
    text = nText;
    next_index = nNext;
    conditional_index = 0;
    next_false_index = 0;
}

script_obj::script_obj(int nRun, int nNext)
{
    text = "";
    next_index = nNext;
    conditional_index = nRun;
    next_false_index = nNext;
}

script_obj::script_obj(int nRun, int nNext_if_true, int nNext_if_false)
{
    text = "";
    next_index = nNext_if_true;
    conditional_index = nRun;
    next_false_index = nNext_if_false;
}


std::string script_obj::get_text()
{
    return text;
}

int script_obj::get_true_index()
{
    return next_index;
}

int script_obj::get_false_index()
{
    return next_false_index;
}

int script_obj::get_cond_id()
{
    return conditional_index;
}