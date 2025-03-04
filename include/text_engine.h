#ifndef TEXT_ENGINE_H
#define TEXT_ENGINE_H

#include <tonc.h>
#include <string>

#include "script_obj.h"
#include "script_array.h"

#define H_MAX 240
#define V_MAX 160
#define LEFT 8
#define RIGHT (H_MAX - LEFT)
#define TOP 112
#define BOTTOM V_MAX

void init_text_engine();
int text_loop(int script);
int text_next_obj_id(script_obj current_line);
void show_text_box();
void hide_text_box();
void set_text_exit();
int ptgb_write(const char *text);
int ptgb_write(const byte *text, bool instant);
int ptgb_write(const byte *text, bool instant, int length);
void wait_for_user_to_continue(bool clear_text);

#endif