#include "dex_handler.h"

Dex::Dex(){}

Dex::Dex(OBJ_ATTR *L, OBJ_ATTR *M, OBJ_ATTR *R, u32 ntidL, u32 ntidM, u32 ntidR)
{
    dex_L = L;
    dex_M = M;
    dex_R = R;
    tidL = ntidL;
    tidM = ntidM;
    tidR = ntidR;
    hide();
}
void Dex::set_location(int nx, int ny)
{
    x = nx;
    y = ny;
    obj_set_pos(dex_L, x, y);
    obj_set_pos(dex_M, x + 64, y);
    obj_set_pos(dex_R, x + 128, y);
}
void Dex::set_highlight(bool highlight)
{
    dex_L->attr2 = ATTR2_BUILD(tidL, (highlight ? 3 : 2), 2);
    dex_M->attr2 = ATTR2_BUILD(tidM, (highlight ? 3 : 2), 2);
    dex_R->attr2 = ATTR2_BUILD(tidR, (highlight ? 3 : 2), 2);
}
void Dex::hide()
{
    obj_hide_multi(dex_L, 3);
}
void Dex::show()
{
    obj_unhide_multi(dex_L, 0, 3);
}