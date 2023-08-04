#include "gameboy_colour.h"
#include "pokemon_party.h"

Pokemon_Party::Pokemon_Party(){};
void Pokemon_Party::start_link()
{
    setup();
    last_error = loop(&party_data_array[0]);
}
int Pokemon_Party::get_last_error(){
    return last_error;
}
