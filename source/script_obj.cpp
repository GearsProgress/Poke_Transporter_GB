#include <tonc.h>
#include <string>
#include "script_obj.h"
#include "pokemon.h"
#include "pokemon_party.h"
#include "script_array.h"
#include "translated_text.h"

script_obj::script_obj(){};

script_obj::script_obj(const byte* nText, uint16_t nNext)
{
    text = nText;
    next_index = nNext;
    conditional_index = 0;
    next_false_index = 0;
}

script_obj::script_obj(uint16_t nRun, uint16_t nNext)
{
    text = nullptr;
    next_index = nNext;
    conditional_index = nRun;
    next_false_index = nNext;
}

script_obj::script_obj(uint16_t nRun, uint16_t nNext_if_true, uint16_t nNext_if_false)
{
    text = nullptr;
    next_index = nNext_if_true;
    conditional_index = nRun;
    next_false_index = nNext_if_false;
}

const byte* script_obj::get_text()
{
    return text;
}

uint16_t script_obj::get_true_index()
{
    return next_index;
}

uint16_t script_obj::get_false_index()
{
    return next_false_index;
}

uint16_t script_obj::get_cond_id()
{
    return conditional_index;
}