#include <tonc.h>
#define CBB_0 0
#define SBB_0 28

#define CROSS_TX 15
#define CROSS_TY 10

uint frame_count = 0;

BG_POINT bg0_pt = {0, 0};
SCR_ENTRY *bg0_map = se_mem[SBB_0];

u32 tx, ty, se_curr, se_prev;

uint se_index(uint tx, uint ty, uint pitch)
{
    uint sbb = ((tx >> 5) + (ty >> 5) * (pitch >> 5));
    return sbb * 1024 + ((tx & 31) + (ty & 31) * 32);
}

void init_map()
{
    int ii, jj;

    // initialize a background
    REG_BG0CNT = BG_CBB(CBB_0) | BG_SBB(SBB_0) | BG_REG_64x64;
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;

    // (1) create the tiles:
    const TILE tile =
        {
            {0x11111111, 0x01111111, 0x01111111, 0x01111111,
             0x01111111, 0x01111111, 0x01111111, 0x00000001}};
    tile_mem[CBB_0][0] = tile;

    // (2) create a palette
    pal_bg_bank[0][1] = RGB15(31, 0, 0);

    // (3) Create a map:
    SCR_ENTRY *pse = bg0_map;
    for (jj = 0; jj < 32 * 32; jj++)
        *pse++ = SE_PALBANK(ii) | 0;
}

int back_main()
{
    init_map();
    return 0;
}

void back_frame()
{
    vid_vsync();

    key_poll();

    // (4) Moving around
    if (frame_count % 2 == 0)
    {
        bg0_pt.x += 1;
        bg0_pt.y += 1;
    }
    se_curr = se_index(tx, ty, 64);
    if (se_curr != se_prev)
    {
        bg0_map[se_prev]--;
        bg0_map[se_curr]++;
        se_prev = se_curr;
    }

    REG_BG_OFS[0] = bg0_pt; // write new position
    frame_count++;
}