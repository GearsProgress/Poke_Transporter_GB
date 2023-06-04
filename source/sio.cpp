#include <tonc.h>
#include "sio.h"

#define BLANK_LINES_WAIT 13

void sio_normal_inner_slave(void);
u8 sio_normal_inner_master(void);

IWRAM_CODE int timed_sio_normal_master(int data, int is_32, int vCountWait) {
    u8 curr_vcount, target_vcount;
    
    if(is_32)
        REG_SIODATA32 = data;
    else
        REG_SIODATA8 = (data & 0xFF);
        
    // - Wait at least 36 us between sends (this is a bit more, but it works)
    curr_vcount = REG_VCOUNT;
    target_vcount = curr_vcount + vCountWait;
    if(target_vcount >= SCANLINES)
        target_vcount -= SCANLINES;
    while (target_vcount != REG_VCOUNT);
    
    // - Set Start flag.
    REG_SIOCNT |= SIO_START;
    // - Wait for IRQ (or for Start bit to become zero).
    while (REG_SIOCNT & SIO_START);

    // - Process received data.
    if(is_32)
        return REG_SIODATA32;
    else
        return (REG_SIODATA8 & 0xFF);
}

IWRAM_CODE void sio_normal_inner_slave() {
    // - Set Start=0 and SO=0 (SO=LOW indicates that slave is (almost) ready).
    REG_SIOCNT &= ~(SIO_START | SIO_SO_HIGH);
    // - Set Start=1 and SO=1 (SO=HIGH indicates not ready, applied after transfer).
    //   (Expl. Old SO=LOW kept output until 1st clock bit received).
    //   (Expl. New SO=HIGH is automatically output at transfer completion).
    REG_SIOCNT |= SIO_START | SIO_SO_HIGH;
    // - Set SO to LOW to indicate that master may start now.
    REG_SIOCNT &= ~SIO_SO_HIGH;
    // - Wait for IRQ (or for Start bit to become zero). (Check timeout here!)
    while (REG_SIOCNT & SIO_START);
    
    //Stop next transfer
    REG_SIOCNT |= SIO_SO_HIGH;
}

IWRAM_CODE MAX_OPTIMIZE void sio_handle_irq_slave(int next_data) {
    REG_SIOCNT |= SIO_SO_HIGH;
	
	REG_SIODATA32 = next_data;
	REG_SIODATA8 = next_data;
	
	REG_SIOCNT &= ~(SIO_START | SIO_SO_HIGH);
    // - Set Start=1 and SO=1 (SO=HIGH indicates not ready, applied after transfer).
    //   (Expl. Old SO=LOW kept output until 1st clock bit received).
    //   (Expl. New SO=HIGH is automatically output at transfer completion).
    REG_SIOCNT |= SIO_START | SIO_SO_HIGH;
    // - Set SO to LOW to indicate that master may start now.
    REG_SIOCNT &= ~SIO_SO_HIGH;
}

IWRAM_CODE MAX_OPTIMIZE int sio_read(u8 is_32) {
    u32 data = REG_SIODATA8;
    if(is_32)
        data = REG_SIODATA32;
    return data;
}

IWRAM_CODE void sio_stop_irq_slave() {
    REG_SIOCNT &= ~SIO_SO_HIGH;
    REG_SIOCNT &= ~SIO_IRQ;
}

IWRAM_CODE void sio_normal_prepare_irq_slave(int data) {
    // - Initialize data which is to be sent to master.
    REG_SIODATA32 = data;
    REG_SIODATA8 = (data & 0xFF);
    
    REG_SIOCNT |= SIO_IRQ;

    // - Set Start=0 and SO=0 (SO=LOW indicates that slave is (almost) ready).
    REG_SIOCNT &= ~(SIO_START | SIO_SO_HIGH);
    // - Set Start=1 and SO=1 (SO=HIGH indicates not ready, applied after transfer).
    //   (Expl. Old SO=LOW kept output until 1st clock bit received).
    //   (Expl. New SO=HIGH is automatically output at transfer completion).
    REG_SIOCNT |= SIO_START | SIO_SO_HIGH;
    // - Set SO to LOW to indicate that master may start now.
    REG_SIOCNT &= ~SIO_SO_HIGH;
}

IWRAM_CODE MAX_OPTIMIZE u32 sio_send_if_ready_master(u32 data, u8 is_32, u8* success) {
    // - Wait for SI to become LOW (slave ready). (Check timeout here!)
    REG_SIODATA32 = data;
    REG_SIODATA8 = (data & 0xFF);
    if (!(REG_SIOCNT & SIO_RDY)) {
        // - Set Start flag.
        REG_SIOCNT |= SIO_START;
        // - Wait for IRQ (or for Start bit to become zero).
        while (REG_SIOCNT & SIO_START);
        *success = 1;
    }
    else
        *success = 0;
    return sio_read(is_32);
}

IWRAM_CODE MAX_OPTIMIZE u32 sio_send_master(u32 data, u8 is_32) {
    // - Wait for SI to become LOW (slave ready). (Check timeout here!)
    REG_SIODATA32 = data;
    REG_SIODATA8 = (data & 0xFF);
    // - Set Start flag.
    REG_SIOCNT |= SIO_START;
    // - Wait for IRQ (or for Start bit to become zero).
    while (REG_SIOCNT & SIO_START);
    return sio_read(is_32);
}

IWRAM_CODE u8 sio_normal_inner_master() {
    // - Wait for SI to become LOW (slave ready). (Check timeout here!)
    int curr_vcount = REG_VCOUNT;
    int target_vcount = curr_vcount + BLANK_LINES_WAIT;
    if(target_vcount >= SCANLINES)
        target_vcount -= SCANLINES;
    while (REG_SIOCNT & SIO_RDY) {
        if(REG_VCOUNT == target_vcount)
            return 0;
    }
    // - Set Start flag.
    REG_SIOCNT |= SIO_START;
    // - Wait for IRQ (or for Start bit to become zero).
    while (REG_SIOCNT & SIO_START);
    return 1;
}

IWRAM_CODE void init_sio_normal(int is_master, int is_32) {
    u16 sio_cnt_val = 0;
    
    if(is_32)
        sio_cnt_val |= SIO_32BIT;
    else
        sio_cnt_val |= SIO_8BIT;
    
    if(is_master)
        sio_cnt_val |= SIO_CLK_INT;
    else
        sio_cnt_val |= SIO_SO_HIGH;
        
    
    REG_RCNT = R_NORMAL;
    REG_SIOCNT = sio_cnt_val;
}

IWRAM_CODE int sio_normal(int data, int is_master, int is_32, u8* success) {
    // - Initialize data which is to be sent to master.
    if(is_32)
        REG_SIODATA32 = data;
    else
        REG_SIODATA8 = (data & 0xFF);
    
    if(is_master)
        *success = sio_normal_inner_master();
    else
        sio_normal_inner_slave();
    
    // - Process received data.
    if(is_32)
        return REG_SIODATA32;
    else
        return (REG_SIODATA8 & 0xFF);
}
