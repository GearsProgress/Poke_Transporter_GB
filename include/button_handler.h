#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <tonc.h>

class Button
{
public:
    Button();
    Button(OBJ_ATTR *L, OBJ_ATTR *R, u32 tidL, u32 tidR); // wide buttons
    Button(OBJ_ATTR *B, u32 ntidB);                       // short button
    bool isWide;
    void set_location(int x, int y);
    void set_highlight(bool highlight);
    void hide();
    void show();
    int x;
    int y;

private:
    bool highlighted;
    OBJ_ATTR *button_L;
    OBJ_ATTR *button_R;
    u32 tidL;
    u32 tidR;
};

#endif