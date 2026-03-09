#include "dbg/debug_menu_functions.h"
#include "libraries/nanoprintf/nanoprintf.h"
#include "text_engine.h"
#include "pokemon_data.h"

void dbg_menu_print_number(void *context, unsigned user_param)
{
    (void)context;
    char buf[64];
    npf_snprintf(buf, sizeof(buf), "%u", user_param);
    uint16_t charset[256];
    load_localized_charset(charset, 3, ENGLISH);

    tte_erase_rect(0, 0, 100, 12);
    tte_set_pos(0, 0);
    ptgb_write_debug(charset, buf, true);
}