#include <tonc.h>

#include "global_frame_controller.h"
#include "random.h"
#include "background_engine.h"
#include "text_engine.h"
#include "sprite_data.h"

int global_frame_count = 0;

void global_next_frame()
{
    key_poll();
    rand_next_frame();
    // tte_set_pos(0, 0);
    // tte_write(std::to_string(get_rand_u32()).c_str());
    background_frame();
    text_next_frame();
    oam_copy(oam_mem, obj_buffer, NUM_SPRITES);
    VBlankIntrWait();
    // mmFrame(); //Music
    global_frame_count++;
};

int get_frame_count()
{
    return global_frame_count;
}