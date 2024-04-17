#include <tonc.h>

#include "global_frame_controller.h"
#include "random.h"
#include "background_engine.h"
#include "text_engine.h"
#include "sprite_data.h"
#include "string.h"

int global_frame_count = 0;
bool rand_enabled = true;

void global_next_frame()
{
    key_poll();
    rand_next_frame();
    // tte_set_pos(0, 0);
    // tte_write(std::to_string(get_rand_u32()).c_str());
    background_frame();
    oam_copy(oam_mem, obj_buffer, num_sprites);
    VBlankIntrWait();
    // mmFrame(); //Music
    if (global_frame_count % 60 == 0)
    {
        memcpy(pal_obj_mem + (MENU_SPRITE_PAL * 16), frame_one_pal, 32);
    }
    else if (global_frame_count % 60 == 30)
    {
        memcpy(pal_obj_mem + (MENU_SPRITE_PAL * 16), frame_two_pal, 32);
    }
    global_frame_count++;
};

int get_frame_count()
{
    return global_frame_count;
}

void enable_auto_random(){
    rand_enabled = true;
}

void disable_auto_random(){
    rand_enabled = false;
}