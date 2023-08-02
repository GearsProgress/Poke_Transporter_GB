#include <tonc.h>
#include <string>
#include "script_obj.h"
#include "gba_flash.h"
#include "pokemon.h"

script_obj::script_obj()
{
    text = "null";
    next_index = 0;
    conditional_index = 0;
    next_false_index = 0;
    out_code = 0;
}

script_obj::script_obj(std::string nText, int nNext_index)
{
    text = nText;
    next_index = nNext_index;
    conditional_index = 0;
    next_false_index = 0;
    out_code = 0;
}
script_obj::script_obj(std::string nText, int nNext_index, int nCond_index, int nFalse_index)
{
    text = nText;
    next_index = nNext_index;
    conditional_index = nCond_index;
    next_false_index = nFalse_index;
    out_code = 0;
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

int script_obj::get_out_code(){
    int temp = out_code;
    out_code = 0;
    return temp;
}

int script_obj::get_next_obj_id()
{
    if (conditional_index == 0)
    {
        return next_index;
    }
    else
    {
        if (run_conditional(conditional_index))
        {
            return next_index;
        }
        return next_false_index;
    }
}

bool script_obj::run_conditional(int index)
{
    // Here is most of the logic that drives what lines show up where. It's probably not the best way to code it, but it works
    switch (index)
    {
    case 1:
    {
        u32 game_code = (*(vu32 *)(0x80000AC)) & 0xFFFFFF;
        return (game_code == 0x565841 || // Ruby
                game_code == 0x505841 || // Sapphire
                game_code == 0x525042 || // FireRed
                game_code == 0x475042 || // LeafGreen
                game_code == 0x455042    // Emerald
        );
    }
    case 2:
        out_code = 1;
        return true;
    }
    return false;
}
