#include <tonc.h>

#include "global_frame_controller.h"
#include "random.h"
#include "background_engine.h"
#include "text_engine.h"
#include "sprite_data.h"
#include "string.h"

int global_frame_count = 0;
bool rand_enabled = true;
int cable_frame = 0;
int curr_link_animation_state = 0;
int fennel_blink_timer = 0;
int fennel_blink_state = 0;
bool missingno_enabled = false;

void global_next_frame()
{
    key_poll();
    rand_next_frame();
    // tte_set_pos(0, 0);
    // tte_write(std::to_string(get_rand_u32()).c_str());
    background_frame(global_frame_count);
    determine_fennel_blink();
    if (missingno_enabled)
    {
        set_background_pal(0xFF, false, false);
    }
    oam_copy(oam_mem, obj_buffer, num_sprites);
    VBlankIntrWait();
    // mmFrame(); //Music
    if (global_frame_count % 60 == 0)
    {
        set_menu_sprite_pal(0);
        if (!curr_rom.verify_rom())
        {
            REG_BG0CNT = (REG_BG0CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
            REG_BG1CNT = (REG_BG1CNT & ~BG_PRIO_MASK) | BG_PRIO(2);
            REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(1);
            REG_BG2VOFS = 0;
            tte_set_pos(40, 24);
            tte_set_margins(40, 24, 206, 104);
            set_textbox_large();
            tte_write("\n\n#{cx:0xF000}The Pok@mon game was\nremoved. Please turn\noff the system and\nrestart the program.");
            // obj_hide_multi(testroid, 128);
            oam_copy(oam_mem, obj_buffer, num_sprites);
            while (true)
            {
            };
        }
    }
    else if (global_frame_count % 60 == 30)
    {
        set_menu_sprite_pal(1);
    }

    if (global_frame_count % (40 / curr_link_animation_state) == 0)
    {
        cable_frame = (cable_frame + 1) % 12;
        if (curr_link_animation_state > 0)
        {
            run_link_cable_animation(cable_frame);
        }
    }
    global_frame_count++;
};

int get_frame_count()
{
    return global_frame_count;
}

void enable_auto_random()
{
    rand_enabled = true;
}

void disable_auto_random()
{
    rand_enabled = false;
}

const unsigned short MENU_PALS[5][4] = {
    {RGB15(31, 31, 31), RGB15(31, 19, 10), RGB15(31, 7, 01), RGB15(00, 00, 00)},  // Red
    {RGB15(31, 31, 31), RGB15(31, 19, 10), RGB15(10, 9, 31), RGB15(00, 00, 00)},  // Blue
    {RGB15(31, 31, 31), RGB15(31, 19, 10), RGB15(07, 23, 03), RGB15(00, 00, 00)}, // Green
    {RGB15(31, 31, 31), RGB15(31, 19, 10), RGB15(15, 10, 03), RGB15(00, 00, 00)}, // Brown
    {RGB15(31, 31, 31), RGB15(31, 19, 10), RGB15(29, 5, 13), RGB15(00, 00, 00)},  // Pink
};

void set_menu_sprite_pal(int frame)
{
    for (int i = 0; i < 5; i++)
    {
        unsigned short curr_pal[16] = {
            //              frame: 1 | 2
            MENU_PALS[i][(!frame ? 0 : 0)],
            MENU_PALS[i][(!frame ? 0 : 1)],
            MENU_PALS[i][(!frame ? 0 : 2)],
            MENU_PALS[i][(!frame ? 0 : 3)],
            MENU_PALS[i][(!frame ? 1 : 0)],
            MENU_PALS[i][(!frame ? 1 : 1)],
            MENU_PALS[i][(!frame ? 1 : 2)],
            MENU_PALS[i][(!frame ? 1 : 3)],
            MENU_PALS[i][(!frame ? 2 : 0)],
            MENU_PALS[i][(!frame ? 2 : 1)],
            MENU_PALS[i][(!frame ? 2 : 2)],
            MENU_PALS[i][(!frame ? 2 : 3)],
            MENU_PALS[i][(!frame ? 3 : 0)],
            MENU_PALS[i][(!frame ? 3 : 1)],
            MENU_PALS[i][(!frame ? 3 : 2)],
            MENU_PALS[i][(!frame ? 3 : 3)],
        };
        memcpy(pal_obj_mem + ((MENU_PAL_START + i) * 16), curr_pal, 32);
    }
}

int path[12][2] = {{19, 18}, {19, 19}, {18, 19}, {17, 19}, {16, 19}, {15, 19}, {14, 19}, {13, 19}, {12, 19}, {11, 19}, {10, 19}, {24, 24}};

void run_link_cable_animation(int frame)
{
    switch (curr_link_animation_state)
    {
    case STATE_CONNECTION:
        frame %= 4;
        obj_hide_multi(link_frame1, 4);
        obj_unhide_multi(link_frame1, 0, frame);
        break;
    case STATE_TRANSFER:
        obj_set_pos(link_blob1, path[frame][0] * 8, path[frame][1] * 8);
        obj_set_pos(link_blob2, path[frame][0] * 8, path[frame][1] * 8);
        obj_set_pos(link_blob3, path[frame][0] * 8, path[frame][1] * 8);

        obj_hide_multi(link_blob1, 3);
        switch (frame % 3)
        {
        case 0:
            obj_unhide(link_blob1, 0);
            break;
        case 1:
            obj_unhide(link_blob2, 0);
            break;
        case 2:
            obj_unhide(link_blob3, 0);
            break;
        }
        break;
    }
}

void link_animation_state(int state)
{
    cable_frame = 0;
    switch (state)
    {
    case STATE_CONNECTION:
        obj_unhide(gba_cart, 0);
        obj_set_pos(gba_cart, 17 * 8, 14 * 8);

        obj_unhide(cart_shell, 0);
        obj_set_pos(cart_shell, (8 * 8), (11 * 8) + 11);
        obj_unhide(cart_label, 0);
        obj_set_pos(cart_label, (8 * 8) + 8, (11 * 8) + 11 + 13);

        obj_set_pos(link_frame1, 17 * 8, 17 * 8);
        obj_set_pos(link_frame2, 13 * 8, 19 * 8);
        obj_set_pos(link_frame3, 9 * 8, 18 * 8);
        break;
    case STATE_TRANSFER:
        obj_unhide_multi(link_blob1, 0, 3);
    case STATE_NO_ANIM:
        obj_unhide(gba_cart, 0);
        obj_set_pos(gba_cart, 17 * 8, 14 * 8);

        obj_unhide(cart_shell, 0);
        obj_set_pos(cart_shell, (8 * 8), (11 * 8) + 11);
        obj_unhide(cart_label, 0);
        obj_set_pos(cart_label, (8 * 8) + 8, (11 * 8) + 11 + 13);

        obj_unhide(link_frame1, 0);
        obj_set_pos(link_frame1, 17 * 8, 17 * 8);
        obj_unhide(link_frame2, 0);
        obj_set_pos(link_frame2, 13 * 8, 19 * 8);
        obj_unhide(link_frame3, 0);
        obj_set_pos(link_frame3, 9 * 8, 18 * 8);
        break;

    default:
        obj_hide_multi(link_frame1, 3);
        obj_hide_multi(link_blob1, 3);
        obj_hide(gba_cart);
        obj_hide(cart_shell);
        obj_hide(cart_label);
        break;
    }
    curr_link_animation_state = state;
}

void determine_fennel_blink()
{
    if (get_curr_flex_background() == BG_FENNEL)
    {
        if (fennel_blink_timer == 0)
        {
            fennel_blink(fennel_blink_state);
            fennel_blink_state = (fennel_blink_state + 1) % 4;
            if (fennel_blink_state == 3) // Wait a random amount of time
            {
                fennel_blink_timer = get_rand_range(4 * 60, 8 * 60);
            }
            else // Continue with the animation
            {

                fennel_blink_timer = 4;
            }
        }
        else
        {
            fennel_blink_timer--;
        }
    }
    else
    {
        fennel_blink_timer = get_rand_range(4 * 60, 8 * 60);
    }
}

void set_missingno(bool val)
{
    missingno_enabled = val;
    if (val == false)
    {
        set_background_pal(curr_rom.gamecode, false, false);
        fennel_blink_timer = 0;
    }
}

bool get_missingno_enabled()
{
    return missingno_enabled;
}
// FNV-1a 32-bit hash function for byte arrays
u32 fnv1a_hash(unsigned char *data, size_t length)
{
    const uint32_t fnv_prime = 0x01000193;
    const uint32_t fnv_offset_basis = 0x811C9DC5;
    uint32_t hash = fnv_offset_basis;

    for (size_t i = 0; i < length; ++i)
    {
        hash ^= data[i];
        hash *= fnv_prime;
    }
    return hash;
}