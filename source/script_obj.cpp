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

void script_obj::link_party_var(Pokemon_Party *var){
    party_data = var;
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
    case CHECK_GAME:
    {
        u32 game_code = (*(vu32 *)(0x80000AC)) & 0xFFFFFF;
        return (game_code == 0x565841 || // Ruby
                game_code == 0x505841 || // Sapphire
                game_code == 0x525042 || // FireRed
                game_code == 0x475042 || // LeafGreen
                game_code == 0x455042    // Emerald
        );
    }
    case START_LINK:
        party_data->start_link();
        return true;

    //case :
    default:
        tte_set_pos(0, 0);
        tte_write("ERROR! No conditional found.");
        return false;
    }
}
