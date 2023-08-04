#include <tonc.h>
#include <string>
#include "script_obj.h"
#include "gba_flash.h"
#include "pokemon.h"
#include "pokemon_party.h"

script_obj::script_obj()
{
    text = "null";
    next_index = 0;
    conditional_index = 0;
    next_false_index = 0;
}

script_obj::script_obj(std::string nText, int nNext_index)
{
    text = nText;
    next_index = nNext_index;
    conditional_index = 0;
    next_false_index = 0;
}

script_obj::script_obj(std::string nText, int nNext_index, int nCond_index)
{
    text = nText;
    next_index = nNext_index;
    conditional_index = nCond_index;
    next_false_index = nNext_index;
}

script_obj::script_obj(std::string nText, int nNext_index, int nCond_index, int nFalse_index)
{
    text = nText;
    next_index = nNext_index;
    conditional_index = nCond_index;
    next_false_index = nFalse_index;
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