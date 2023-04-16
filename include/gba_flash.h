//Created by Laqieer https://github.com/laqieer/libsavgba

#ifndef GBA_Flash_H
#define GBA_Flash_H

/**
 * @brief Flash chip size.
 */
enum FlashSize {
    FLASH_SIZE_AUTO = 0, ///< Auto-detect
    FLASH_SIZE_64KB, ///< 64KB(512Kb)
    FLASH_SIZE_128KB, ///< 128KB(1Mb)
};

/**
 * @brief Flash chip manufacturer.
 */
enum FlashManufacturer {
    FLASH_MFR_ATMEL = 0x1F,
    FLASH_MFR_PANASONIC = 0x32,
    FLASH_MFR_SANYO = 0x62,
    FLASH_MFR_SST = 0xBF,
    FLASH_MFR_MACRONIX = 0xC2,
};

/**
 * @brief Flash chip device code.
 */
enum FlashDevice {
    FLASH_DEV_MX29L010 = 0x09,
    FLASH_DEV_LE26FV10N1TS = 0x13,
    FLASH_DEV_MN63F805MNP = 0x1B,
    FLASH_DEV_MX29L512 = 0x1C,
    FLASH_DEV_AT29LV512 = 0x3D,
    FLASH_DEV_LE39FW512 = 0xD4,
};

/**
 * @brief Init Flash chip.
 *
 * Detect the type (and presence) of FLASH chips. **It should be called once at first.**
 *
 * @param size Flash chip size (\c FLASH_SIZE_AUTO / \c FLASH_SIZE_64KB / \c FLASH_SIZE_128KB). Use \c FLASH_SIZE_AUTO if you don't know.
 *
 * @return \c 0 for success, \c non-zero for error.
 */
int flash_init(u8 size);

/**
 * @brief Reset Flash chip.
 *
 * Erases all memory in chip, erased memory is FFh-filled.
 *
 * @return \c 0 for success, \c non-zero for error.
 */
int flash_reset();

/**
 * @brief Read data from Flash (size: 64KB/128KB).
 *
 * @param addr address in Flash (unit: byte).
 * @param data buffer to hold data.
 * @param size data size (unit: byte).
 *
 * @return \c 0 for success, \c non-zero for error. 
 */
int flash_read(u32 addr, u8 *data, size_t size);

/**
 * @brief Write data to Flash (size: 64KB/128KB).
 *
 * **Target sector will be erased.**
 *
 * @param addr address in Flash (unit: byte).
 * @param data buffer to hold data.
 * @param size data size (unit: byte).
 *
 * @return \c 0 for success, \c non-zero for error.
 */
int flash_write(u32 addr, u8 *data, size_t size);

#endif /* GBA_Flash_H */