#ifndef SCRIPT_ARRAY_H
#define SCRIPT_ARRAY_H

#include "script_obj.h"
#include "pokemon_party.h"

extern script_obj script[];

void add_script_party_var(Pokemon_Party var);
bool run_conditional(int index);

#endif