#include <tonc.h>
#include <string>
#include "script_obj.h"
#include "pokemon.h"
#include "pokemon_party.h"
#include "script_array.h"

script_obj::script_obj(){};

script_obj::script_obj(const byte* nText, int nNext)
{
    text = nText;
    has_text = true;
    next_index = nNext;
    conditional_index = 0;
    next_false_index = 0;
}

script_obj::script_obj(int nRun, int nNext)
{
    next_index = nNext;
    conditional_index = nRun;
    next_false_index = nNext;
}

script_obj::script_obj(int nRun, int nNext_if_true, int nNext_if_false)
{
    next_index = nNext_if_true;
    conditional_index = nRun;
    next_false_index = nNext_if_false;
}

const byte* script_obj::get_text()
{
    if (has_text)
    {
        return text;
    }
    else
    {
        return NULL;
    }
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