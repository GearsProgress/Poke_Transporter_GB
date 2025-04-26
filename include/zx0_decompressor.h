#ifndef _ZX0_DECODE_H
#define _ZX0_DECODE_H

#include <cstdint>

// The ZX0 decompressor offers functionality to decompress data
// compressed with the ZX0 algorithm (see tools/compressZX0)
// This algorithm was invented by Einar Saukas
// Original implementation can be found here: https://github.com/einar-saukas/ZX0
// However, we've implemented a custom variant of this algorithm. 
// (for instance: we're storing the uncompressed size in the first 2 bytes in little endian)

// Our implementation "streams" the decompression: the decompression buffer is only 2 KB, so it can't fit the entire
// uncompressed file at once. Therefore it uses a ringbuffer to stream the decompression on-demand.

extern "C"
{
    /**
     * @brief This function slots the specified input_data buffer into the zx0 decompressor.
     * Calling this function effectively resets the ZX0 decompressors' internal state.
     */
    void zx0_decompressor_set_input(const uint8_t *input_data);

    /**
     * @brief This function returns the uncompressed size of the current input_data buffer.
     * It reads this from the first 2 bytes of input_data
     */
    uint32_t zx0_decompressor_get_decompressed_size();

    /**
     * @brief This function seeks to the specified OUTPUT buffer position.
     * NOTE: this is an expensive operation!
     * ZX0 doesn't actually support random access.
     * 
     * So if we're seeking forward, we're actually uncompressing the data until we reach the desired output buffer position.
     * And if we're seeking backward, we're actually starting to uncompress from scratch until the desired output buffer position!
     * 
     * So handle this with care!
     * @param output_byte_pos 
     */
    void zx0_decompressor_seek(uint32_t output_byte_pos);

    /**
     * @brief This function copies <num_bytes> of decompressed data into the specified <output_buffer>
     * It will trigger decompression on the go (streaming basis)
     */
    uint32_t zx0_decompressor_read(uint8_t *output_buffer, uint32_t num_bytes);
}

#endif