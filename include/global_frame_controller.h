#ifndef GLOBAL_FRAME_CONTROLLER_H
#define GLOBAL_FRAME_CONTROLLER_H

#define STATE_CONNECTION 1
#define STATE_TRANSFER 2
#define STATE_NO_ANIM 3

void global_next_frame();
int get_frame_count();
void set_menu_sprite_pal(int frame);
void run_link_cable_animation(int frame);
void link_animation_state(int state);
void determine_fennel_blink();
void set_missingno(bool val);
bool get_missingno_enabled();
void set_treecko(bool val);
bool get_treecko_enabled();
u32 fnv1a_hash(unsigned char* data, size_t length);
int get_string_length(const byte *str);
void convert_int_to_ptgb_str(int val, byte str[]);
void convert_int_to_ptgb_str(int val, byte str[], int min_length);

#endif
