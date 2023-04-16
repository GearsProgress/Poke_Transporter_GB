//Created by Laqieer https://github.com/laqieer/libsavgba

#include <stddef.h>

#include <tonc.h>

#include "err_def.h"
#include "gba_flash.h"

#define MEM_FLASH 0x0E000000
#define FLASH_SIZE 0x10000
#define flash_mem ((vu8*)MEM_FLASH)

#define FLASH_SECTOR_SIZE_4KB 4096 // all device types, except Atmel
#define FLASH_SECTOR_SIZE_128B 128 // only Atmel devices

#define LOOP_CNT_PER_MILLI_SECOND 1000

enum FlashCmd {
    FLASH_CMD_ERASE_CHIP = 1,
    FLASH_CMD_ERASE_SECTOR = 3,
    FLASH_CMD_ERASE = 8,
    FLASH_CMD_ENTER_ID_MODE = 9,
    FLASH_CMD_WRITE = 0xA,
    FLASH_CMD_SWITCH_BANK = 0xB,
    FLASH_CMD_LEAVE_ID_MODE = 0xF,
};

#define FLASH_CMD_BEGIN flash_mem[0x5555] = 0xAA; flash_mem[0x2AAA] = 0x55;
#define FLASH_CMD(cmd) FLASH_CMD_BEGIN; flash_mem[0x5555] = (cmd) << 4;

const unsigned char erased_byte_value = 0xFF;
const unsigned char erased_byte_value_vba = 0;

struct FlashInfo {
    u8 device;
    u8 manufacturer;
    u8 size;
} gFlashInfo;

const struct FlashInfo flash_chips[] = {
    {FLASH_DEV_MX29L512, FLASH_MFR_MACRONIX, FLASH_SIZE_64KB},
    {FLASH_DEV_MN63F805MNP, FLASH_MFR_PANASONIC, FLASH_SIZE_64KB},
    {FLASH_DEV_LE39FW512, FLASH_MFR_SST, FLASH_SIZE_64KB},
    {FLASH_DEV_AT29LV512, FLASH_MFR_ATMEL, FLASH_SIZE_64KB},
    {FLASH_DEV_MX29L010, FLASH_MFR_MACRONIX, FLASH_SIZE_128KB},
    {FLASH_DEV_LE26FV10N1TS, FLASH_MFR_SANYO, FLASH_SIZE_128KB},
};

#define FLASH_CHIP_NUM sizeof(flash_chips) / sizeof(flash_chips[0])

IWRAM_CODE
static void flash_memcpy(volatile unsigned char *dst, const volatile unsigned char *src, size_t size) {
    for (;size > 0;--size) 
        *dst++ = *src++;
}

IWRAM_CODE
static unsigned int flash_absmemcmp(const volatile unsigned char *dst, const volatile unsigned char *src, size_t size) {
    while (size-- > 0) {
        unsigned int a = *dst++;
        unsigned int b = *src++;
        if (a != b) 
            return 1;
    }

    return 0;
}

// wait until timeout 
static void wait(int timeout) {
    for (vu32 i = 0; i < LOOP_CNT_PER_MILLI_SECOND * timeout; i++);
}

// wait until [E00xxxxh]=dat (or timeout)
static int wait_until(u32 addr, const u8 *data, int timeout) {
    for (vu32 i = 0; i < LOOP_CNT_PER_MILLI_SECOND * timeout && flash_absmemcmp(&flash_mem[addr], data, 1); i++);

    if (flash_absmemcmp(&flash_mem[addr], data, 1)) {
        // Terminate Command after Timeout (only Macronix devices, ID=1CC2h)
        if (gFlashInfo.manufacturer == FLASH_MFR_MACRONIX && gFlashInfo.device == FLASH_DEV_MX29L512)
            // force end of write/erase command
            flash_mem[0x5555] = 0xF0;

        return E_TIMEOUT;
    }

    return 0;
}

// Chip Identification (all device types)
int flash_init(u8 size) {
    // Use 8 clk waitstates for initial detection (WAITCNT Bits 0,1 both set). After detection of certain device types smaller wait values may be used for write/erase, and even smaller wait values for raw reading, see Device Types table.
    REG_WAITCNT |= WS_SRAM_8;

    // enter ID mode
    FLASH_CMD(FLASH_CMD_ENTER_ID_MODE);

    // one minor thing the atmel docs say: you have to wait 20ms when entering or exiting ID mode.
    wait(20);

    // get device & manufacturer
    flash_memcpy(&gFlashInfo.device, &flash_mem[1], 1);
    flash_memcpy(&gFlashInfo.manufacturer, &flash_mem[0], 1);

    // terminate ID mode
    FLASH_CMD(FLASH_CMD_LEAVE_ID_MODE);

    // one minor thing the atmel docs say: you have to wait 20ms when entering or exiting ID mode.
    wait(20);

    // 128K sanyo flash needs to have the "exit ID mode" written TWICE to work. If you only write it once, it will not exit ID mode.
    // 64K sanyo flash has the same device/manufacturer ID as the SST part.
    if (gFlashInfo.manufacturer == FLASH_MFR_SANYO)
        flash_mem[0x5555] = FLASH_CMD_LEAVE_ID_MODE << 4;

    gFlashInfo.size = 0;

    for (int i = 0; i < FLASH_CHIP_NUM; i++) {
        if (gFlashInfo.manufacturer == flash_chips[i].manufacturer && gFlashInfo.device == flash_chips[i].device) {
            gFlashInfo.size = flash_chips[i].size;
        }
    }

    if (size)
        gFlashInfo.size = size;
    
    if (!gFlashInfo.size)
        return E_UNSUPPORTED_DEVICE;

    return 0;
}

// Erase Entire Chip (all device types)
int flash_reset() {
    int err;

    // erase command
    FLASH_CMD(FLASH_CMD_ERASE);

    // erase entire chip
    FLASH_CMD(FLASH_CMD_ERASE_CHIP);

    // wait until [E000000h]=FFh (or timeout)
    err = wait_until(0, &erased_byte_value, 20);
    // vba/vba-m fills erased memory with zeros. https://github.com/visualboyadvance-m/visualboyadvance-m/pull/855
    if (err)
        return wait_until(0, &erased_byte_value_vba, 20);

    return 0;
}

// Erase 4Kbyte Sector (all device types, except Atmel)
int flash_erase(u32 addr) {
    int err;

    // sector size: 4KB
    addr &= 0xF000;

    // erase command
    FLASH_CMD(FLASH_CMD_ERASE);

    // erase sector n
    FLASH_CMD_BEGIN
    flash_mem[addr] = FLASH_CMD_ERASE_SECTOR << 4;

    // wait until [E00n000h]=FFh (or timeout)
    err = wait_until(addr, &erased_byte_value, 20);
    // vba/vba-m fills erased memory with zeros. https://github.com/visualboyadvance-m/visualboyadvance-m/pull/855
    if (err)
        return wait_until(0, &erased_byte_value_vba, 20);

    return 0;
}

// Bank Switching (devices bigger than 64K only)
void flash_switch_bank(int bank) {
    // select bank command
    FLASH_CMD(FLASH_CMD_SWITCH_BANK);

    // write bank number 0..1
    flash_mem[0] = bank;
}

// Reading Data Bytes (all device types)
int flash_read(u32 addr, u8 *data, size_t size) {
    if (data == NULL)
        return E_INVALID_PARAM;

    if (addr > MEM_FLASH)
        addr -= MEM_FLASH;

    if (gFlashInfo.size == FLASH_SIZE_128KB)
    {
        int bank = 0;

        if (addr + size > FLASH_SIZE * 2)
            return E_OUT_OF_RANGE;

        if (addr >= FLASH_SIZE)
        {
            bank = 1;
            addr -= FLASH_SIZE;
        }

        flash_switch_bank(bank);
    }

    if (addr + size > FLASH_SIZE)
        return E_OUT_OF_RANGE;

    flash_memcpy(data, &flash_mem[addr], size);
    
    return 0;
}

// Write Single Data Byte (all device types, except Atmel)
int flash_write_byte(u32 addr, u8 data) {
    // write byte command
    FLASH_CMD(FLASH_CMD_WRITE);

    // write byte to address xxxx
    flash_mem[addr] = data;

    // wait until [E00xxxxh]=dat (or timeout)
    return wait_until(addr, &data, 20);
}

// Erase-and-Write 128 Bytes Sector (only Atmel devices)
int flash_erase_and_write_atmel(u32 addr, u8 *data) {
    // disable interrupts
    u16 REG_IME_old = REG_IME;
    REG_IME = 0;

    // erase/write sector command
    FLASH_CMD(FLASH_CMD_WRITE);

    // write 128 bytes
    for (int i = 0; i < FLASH_SECTOR_SIZE_128B - (addr & (FLASH_SECTOR_SIZE_128B - 1)); i++)
        flash_mem[addr + i] = data[i];

    // restore old IME state
    REG_IME = REG_IME_old;

    // wait until [E00xxxxh+7Fh]=dat[7Fh] (or timeout)
    return wait_until(addr | (FLASH_SECTOR_SIZE_128B - 1), &data[(FLASH_SECTOR_SIZE_128B - 1) - (addr & (FLASH_SECTOR_SIZE_128B - 1))], 20);
}

int flash_write_common(u32 addr, u8 *data, size_t size) {
    int err;
    int sectors;

    err = flash_erase(addr);
    if (err)
        return err;

    sectors = (addr % FLASH_SECTOR_SIZE_4KB + size) / FLASH_SECTOR_SIZE_4KB;
    if ((addr % FLASH_SECTOR_SIZE_4KB + size) % FLASH_SECTOR_SIZE_4KB != 0)
        sectors++;

    for (int i = 0; i < sectors; i++) {
        err = flash_erase(addr + i * FLASH_SECTOR_SIZE_4KB);
        if (err)
            return err;
    }

    for(int i = 0; i < size; i++) {
        err = flash_write_byte(addr + i, data[i]);

        if (err)
            return err;
    }

    return 0;
}

int flash_write_atmel(u32 addr, u8 *data, size_t size) {
    int err;
    int sectors;

    if (addr % FLASH_SECTOR_SIZE_128B) {
        err = flash_erase_and_write_atmel(addr, data);
        if (err)
            return err;

        int written = FLASH_SECTOR_SIZE_128B - addr % FLASH_SECTOR_SIZE_128B;
        if (written >= size)
            return 0;

        size -= written;
        addr += written;
        data += written;
    }

    sectors = size / FLASH_SECTOR_SIZE_128B;
    if (size % FLASH_SECTOR_SIZE_128B)
        sectors++;

    for (int i = 0; i < sectors; i++) {
        err = flash_erase_and_write_atmel(addr + i * FLASH_SECTOR_SIZE_128B, &data[i * FLASH_SECTOR_SIZE_128B]);
        if (err)
            return err;
    }

    return 0;
}

int flash_write(u32 addr, u8 *data, size_t size) {
    int err;

    if (data == NULL)
        return E_INVALID_PARAM;

    if (addr > MEM_FLASH)
        addr -= MEM_FLASH;

    if (gFlashInfo.size == FLASH_SIZE_128KB)
    {
        int bank = 0;

        if (addr + size > FLASH_SIZE * 2)
            return E_OUT_OF_RANGE;

        if (addr >= FLASH_SIZE)
        {
            bank = 1;
            addr -= FLASH_SIZE;
        }

        flash_switch_bank(bank);
    }

    if (addr + size > FLASH_SIZE)
        return E_OUT_OF_RANGE;

    if (gFlashInfo.manufacturer == FLASH_MFR_ATMEL)
    {
        err = flash_write_atmel(addr, data, size);
    }
    else
    {
        err = flash_write_common(addr, data, size);
    }

    if (err)
        return err;

    if (flash_absmemcmp(&flash_mem[addr], data, size))
        return E_VERIFY_FAIL;

    return 0;
}