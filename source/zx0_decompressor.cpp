#include "zx0_decompressor.h"
#include <cstring>
#include <tonc.h>

// The following code is a custom implementation of the ZX0 decompression algorithm invented by Einar Saukas
// Original implementation can be found here: https://github.com/einar-saukas/ZX0
// The header provides a C facade to access the relevant methods, but the rest of Poke Transporter GB
// doesn't need to be aware of all the datatypes/classes defined here.
/**
* This class makes reading on a per-bit basis much easier.
*/
class BitReader
{
public:
    BitReader(const uint8_t* buffer);

    IWRAM_CODE uint32_t read(uint32_t numBits);
protected:
private:
    const uint8_t* cur_buffer_;
    uint32_t cur_dword_;
    uint32_t bits_left_;
};

enum class ZX0OperationType
{
    NONE,
    LITERAL_BLOCK,
    COPY_LAST_OFFSET,
    COPY_NEW_OFFSET
};

typedef struct ZX0Command
{
    ZX0OperationType cmd_type;
    uint32_t length;
    uint32_t offset;
    uint32_t byte_pos;
} ZX0Command;

/**
 * @brief This class implements the actual ZX0 decompression.
 */
class ZX0Decompressor
{
public:
    ZX0Decompressor();

    /**
     * @brief This function prepares the ZX0Decompressor instance
     * for decompressing the specified inputData
     * into the specified output_buffer
     * @param compressedData 
     */
    void start(uint8_t *output_buffer, const uint8_t *input_data);

    /**
     * @brief Retrieves the size of the data when it is fully decompressed
     * This is read from the first 2 bytes of the inputData
     */
    IWRAM_CODE uint32_t get_decompressed_size() const;

    /**
     * @brief This function reads <numBytes> of data into <outputBuffer>
     */
    IWRAM_CODE void read(uint32_t num_bytes);
protected:
private:
    IWRAM_CODE void read_next_command();
    IWRAM_CODE uint32_t copy_block(uint32_t num_bytes);

    BitReader reader_;
    ZX0Command cur_command_;
    const uint8_t *input_data_;
    uint8_t *back_pos_;
    uint8_t *cur_out;
    uint32_t last_offset_;
};

IWRAM_CODE static inline uint32_t read_elias_gamma(BitReader& reader)
{
    uint32_t num_non_leading_bits = 0;
    uint32_t value;
    while (!reader.read(1))
    {
        ++num_non_leading_bits;  // Count leading zeros
    }
    // reconstruct the most significant bit of value
    value = (1 << num_non_leading_bits) | reader.read(num_non_leading_bits);              // Start with MSB
    
    // Adjust back to zero-based
    return value - 1;
}

IWRAM_CODE static inline void read_new_offset(BitReader& reader, uint32_t& offset)
{
    const uint32_t has_msb = reader.read(1);

    const uint32_t lsb = reader.read(7);
    const uint32_t msb = (has_msb) ? read_elias_gamma(reader) : 0;

    offset = ((msb << 7) | lsb) + 1;
}

BitReader::BitReader(const uint8_t* buffer)
    : cur_buffer_(buffer)
    , cur_dword_(0)
    , bits_left_(0)
{
}

IWRAM_CODE inline uint32_t BitReader::read(uint32_t num_bits)
{
    uint32_t result;
    
    // Fast path: Read all bits from cached data
    if (num_bits <= bits_left_)
    {
        result = (cur_dword_ >> (bits_left_ - num_bits)) & ((1 << num_bits) - 1);
        bits_left_ -= num_bits;
        return result;
    }
    
    // Slow path: Refill cache and combine bits
    result = cur_dword_ & ((1 << bits_left_) - 1);
    num_bits -= bits_left_;
    
    // Refill cache (32-bit aligned read)
    // but the GBA (or x86 processor on pc) would read the value as little endian.
    // and we need it as big endian. Therefore we do a byte swap
    cur_dword_ = __builtin_bswap32(*(uint32_t*)cur_buffer_);

    cur_buffer_ += sizeof(uint32_t);
    bits_left_ = 32;
    
    // Combine remaining bits
    result = (result << num_bits) | (cur_dword_ >> (32 - num_bits));
    bits_left_ -= num_bits;

    return result;
}

ZX0Decompressor::ZX0Decompressor()
    : reader_(nullptr)
    , cur_command_({ZX0OperationType::NONE, 0, 0, 0})
    , input_data_(nullptr)
    , back_pos_(nullptr)
    , cur_out(nullptr)
    , last_offset_(UINT32_MAX)
{
}

void ZX0Decompressor::start(uint8_t *output_buffer, const uint8_t *input_data)
{
    reader_ = BitReader(input_data + 4);
    cur_command_ = {ZX0OperationType::NONE, 0, 0, 0};
    input_data_ = input_data;
    back_pos_ = nullptr;
    cur_out = output_buffer;
    last_offset_ = UINT32_MAX;
}

IWRAM_CODE uint32_t ZX0Decompressor::get_decompressed_size() const
{
    if(!input_data_)
    {
        return 0;
    }
    return *((uint32_t*)input_data_);
}

IWRAM_CODE void ZX0Decompressor::read(uint32_t num_bytes)
{
    while(num_bytes)
    {
        // Check if we have finished processing the previous pending command
        // if we have, we need to read a new operation
        if(cur_command_.byte_pos >= cur_command_.length)
        {
            read_next_command();
        }

        const uint32_t bytes_read = copy_block(num_bytes);
        num_bytes -= bytes_read;
    }
}

IWRAM_CODE inline void ZX0Decompressor::read_next_command()
{
    const uint32_t cmd_bit = reader_.read(1);

    // the "COPY_NEW_OFFSET" command adds + 1 to the length, but the other commands don't.
    // given that read_elias_gamma() function is marked "inline", the way I set the length
    // is to avoid having multiple calls to it here. (for code size)
    if(cmd_bit)
    {
        read_new_offset(reader_, last_offset_);
        cur_command_.cmd_type = ZX0OperationType::COPY_NEW_OFFSET;
        cur_command_.length = 1; 
        cur_command_.offset = last_offset_;
    }
    else if(cur_command_.cmd_type == ZX0OperationType::LITERAL_BLOCK)
    {
        cur_command_.cmd_type = ZX0OperationType::COPY_LAST_OFFSET;
        // copy from new offset and last offset differs in the sense that with the new offset the encoded length is reduced by one
        // and for last offset it isn't. This is likely because you still need to be able to insert a dummy "copy-from-last-offset" operation.
        cur_command_.length = 0;
        cur_command_.offset = last_offset_;
    }
    else
    {
        cur_command_.cmd_type = ZX0OperationType::LITERAL_BLOCK;
        cur_command_.length = 0;
    }
    cur_command_.length += read_elias_gamma(reader_);
    cur_command_.byte_pos = 0;
}

IWRAM_CODE uint32_t ZX0Decompressor::copy_block(uint32_t num_bytes)
{
    const uint32_t available = cur_command_.length - cur_command_.byte_pos;
    const uint32_t bytes_to_read = (num_bytes > available) ? available : num_bytes;
    uint32_t bytes_remaining = bytes_to_read;

    if(cur_command_.cmd_type == ZX0OperationType::LITERAL_BLOCK)
    {
        // Literal copy

        // Align cur_out first
        while (bytes_remaining && ((uintptr_t)cur_out & 3))
        {
            (*cur_out++) = reader_.read(8);
            bytes_remaining--;
        }

        // Use bulk 32-bit writes when aligned
        while (bytes_remaining >= 4)
        {
            // we need to swap again, because the data was originally stored in big endian format
            // BitReader converted it to little endian format to make reading easier.
            // and now we need to convert it back to big endian format.
            *(uint32_t*)cur_out = __builtin_bswap32(reader_.read(32));
            cur_out += 4;
            bytes_remaining -= 4;
        }
        // Handle remaining bytes
        while (bytes_remaining--)
        {
            (*cur_out++) = reader_.read(8);
        }
    }
    else
    {
        if(!cur_command_.byte_pos)
        {
            back_pos_ = cur_out - cur_command_.offset;
        }

        // try to get cur_out and back_pos aligned to 32 bit accesses first
        while (bytes_remaining && (((uintptr_t)cur_out & 3) || ((uintptr_t)back_pos_ & 3)))
        {
            (*cur_out++) = (*back_pos_++);
            bytes_remaining--;
        }

        // now try bulk 32 bit writes
        while(bytes_remaining >= 4)
        {
            // these don't need to be byteswapped, because the data is being read with the same endianness as it is being written.
            // this is different when reading from BitReader.
            *(uint32_t*)cur_out = *((uint32_t*)back_pos_);
            cur_out += 4;
            back_pos_ += 4;
            bytes_remaining -= 4;
        }

        while(bytes_remaining--)
        {
            (*cur_out++) = (*back_pos_++);
        }
    }
    
    cur_command_.byte_pos += bytes_to_read;

    return bytes_to_read;
}

// gets stored in .bss, and therefore will end up in IWRAM by default
static ZX0Decompressor decompressor;

extern "C"
{
void zx0_decompressor_start(uint8_t *output_buffer, const uint8_t *input_data)
{
    decompressor.start(output_buffer, input_data);
}

uint32_t zx0_decompressor_get_decompressed_size()
{
    return decompressor.get_decompressed_size();
}

void zx0_decompressor_read(uint32_t num_bytes)
{
    decompressor.read(num_bytes);
}
}