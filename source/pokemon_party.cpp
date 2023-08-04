#include "gameboy_colour.h"
#include "pokemon_party.h"

Pokemon_Party::Pokemon_Party(){};
int Pokemon_Party::start_link()
{
    setup();
    loop(&party_data[0]);
}
