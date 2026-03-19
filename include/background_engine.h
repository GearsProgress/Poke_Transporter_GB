#ifndef BG_ENGINE_H
#define BG_ENGINE_H

#include "sprite_data.h"
#include "text_engine.h"
#include "global_frame_controller.h"

// This order does matter, as if two backgrounds are on the same layer,
// the lowest number will be the one that is displayed
#define BG_BACKDROP REG_BG0CNT
#define BG_FLEX REG_BG1CNT
#define BG_TEXTBOX REG_BG2CNT
#define BG_TEXT REG_BG3CNT

void background_frame(int global_frame_count);
void create_textbox_new(int text_section, int text_key, bool eraseMainBox);
void show_textbox();
void hide_textbox();
#endif