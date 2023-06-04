#include <tonc.h>

#ifndef SIO__
#define SIO__

#define SIO_32 1
#define SIO_8 0

#define SIO_MASTER 1
#define SIO_SLAVE 0

#define SIO_DEFAULT_VALUE 0xFE

#define SCANLINES 0xE4
#define SIO_START		(1<<7)
#define SIO_SO_HIGH		(1<<3)	// Our SO state
#define SIO_RDY			(1<<2)	// Opponent SO state
#define SIO_8BIT		0x0000	// Normal 8-bit communication mode
#define SIO_32BIT		0x1000	// Normal 32-bit communication mode
#define SIO_CLK_INT		(1<<0)	// Select internal clock
#define R_NORMAL		0x0000

#define MAX_OPTIMIZE __attribute__((optimize(3)))


void init_sio_normal(int, int);
int sio_normal(int, int, int, u8*);
void sio_normal_prepare_irq_slave(int);
int timed_sio_normal_master(int, int, int);
void sio_handle_irq_slave(int);
void sio_stop_irq_slave(void);
int sio_read(u8);
u32 sio_send_if_ready_master(u32, u8, u8*);
u32 sio_send_master(u32 data, u8 is_32);

#endif
