#ifndef BACKGROUND_ENGINE_H
#define BACKGROUND_ENGINE_H

void background_frame(int global_frame_count);
void create_textbox(int startTileX, int startTileY, int text_space_width, int text_space_height, bool eraseMainBox);
void reset_textbox();
void show_textbox();
void hide_textbox();
#endif