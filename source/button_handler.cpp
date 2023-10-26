#include "button_handler.h"

Button::Button() {}

Button::Button(OBJ_ATTR *L, OBJ_ATTR *R, u32 ntidL, u32 ntidR)
{
    button_L = L;
    button_R = R;
    tidL = ntidL;
    tidR = ntidR;
    isWide = true;
    hide();
}

Button::Button(OBJ_ATTR *L, u32 ntidL)
{
    button_L = L;
    tidL = ntidL;
    isWide = false;
    hide();
}

void Button::set_location(int nx, int ny)
{
    x = nx;
    y = ny;
    obj_set_pos(button_L, x, y);
    if (isWide)
    {
        obj_set_pos(button_R, x + 48, y);
    }
}
void Button::set_highlight(bool highlight)
{
    button_L->attr2 = ATTR2_BUILD(tidL, (highlight ? 3 : 2), 0);
    if (isWide)
    {
        button_R->attr2 = ATTR2_BUILD(tidR, (highlight ? 3 : 2), 0);
    }
}
void Button::hide()
{
    if (isWide)
    {
        obj_hide_multi(button_L, 2);
    }
    else
    {
        obj_hide(button_L);
    }
}
void Button::show()
{
    if (isWide)
    {
        obj_unhide_multi(button_L, 0, 2);
    }
    else
    {
        obj_unhide(button_L, 0);
    }
}