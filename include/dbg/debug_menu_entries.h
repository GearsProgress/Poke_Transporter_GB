#ifndef _DEBUG_MENU_ENTRIES_H
#define _DEBUG_MENU_ENTRIES_H

#include "typeDefs.h"

class vertical_menu;

/**
 * @brief This function constructs the actual debug menu entries and fills the provided menu with them.
 */
void fill_debug_menu_with_entries(vertical_menu &menu, u16 *charset);

#endif