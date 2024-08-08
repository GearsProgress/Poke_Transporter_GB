#ifndef POKEDEX_H
#define POKEDEX_H

#include <tonc.h>

#include "dex_handler.h"

#define DEX_MAX 7
#define DEX_SHIFT_MAX (251 - DEX_MAX)
#define SPEED_DELAY 30
#define MAX_NAME_SIZE 10

void pokedex_init();
int pokedex_loop();
void pokedex_show();
void pokedex_hide();

#endif