#ifndef _ZX0_DECODE_H
#define _ZX0_DECODE_H

#include <cstdint>

#define ZX0_DEFAULT_WINDOW_SIZE 2048

// The ZX0 decompressor offers functionality to decompress data
// compressed with the ZX0 algorithm (see tools/compressZX0)
// This algorithm was invented by Einar Saukas
// Original implementation can be found here: https://github.com/einar-saukas/ZX0
// However, we've implemented a custom variant of this algorithm. 
// (for instance: we're storing the uncompressed size in the first 2 bytes in little endian)
extern "C"
{
    /**
     * @brief This function slots the specified input_data buffer into the zx0 decompressor.
     * Calling this function effectively resets the ZX0 decompressors' internal state.
     */
    void zx0_decompressor_start(uint8_t *output_buffer, const uint8_t *input_data);

    /**
     * @brief This function returns the uncompressed size of the current input_data buffer.
     * It reads this from the first 2 bytes of input_data
     */
    uint32_t zx0_decompressor_get_decompressed_size();

    /**
     * @brief This function copies <num_bytes> of decompressed data into the specified <output_buffer>
     * It will append to the existing output_buffer you set earlier with zx0_decompressor_start()
     */
    void zx0_decompressor_read(uint32_t num_bytes);

    /**
     * @brief this function does a partial decompress into output_buffer.
     * HOWEVER: zx0 decompression requires you to use previously decompressed bytes to decompress the current ones.
     * In order to accomplish this, output_buffer MUST NOT point to the start of the buffer!!
     * Instead it should refer to a point within the buffer with previously decoded bytes available before it,
     * with up to the <ZX0 window size> bytes available before that point.
     * (So if you decoded >= window size, <window size> bytes should be available before output_buffer.
     * If not, before output_buffer should have <all decompressed bytes up until that point>)
     *
     * This function is intended as a way to read data in a "streamed" way into a smaller buffer that is smaller than the actual decompressed file size.
     * NOTE: when used in a loop, you should manually move the decompressed data from the previous iteration to the front of the buffer (output_buffer + window_size - num_bytes)
     */
    void zx0_decompressor_read_partial(uint8_t *output_buffer, uint16_t num_bytes);
}

#endif