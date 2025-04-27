#include "zx0_decompressor.h"
#include <cstring>

// The following code is a custom implementation of the ZX0 decompression algorithm invented by Einar Saukas
// Original implementation can be found here: https://github.com/einar-saukas/ZX0
// It uses classes, but keeps them completely hidden in the .cpp file with an anonymous namespace for internal linkage.
// The header provides a C facade to access the relevant methods, but the rest of Poke Transporter GB
// doesn't need to be aware of all the datatypes/classes defined here.
namespace
{
/**
* This class makes reading on a per-bit basis much easier.
*/
class BitReader
{
public:
    BitReader(const uint8_t* buffer);

    uint32_t readBit();
    uint32_t read(uint32_t numBits);
protected:
private:
    const uint8_t* buffer_;
    const uint8_t* curBuffer_;
    uint32_t currentDWord_;
    uint32_t bitsLeft_;
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
    ZX0OperationType cmdType;
    uint32_t length;
    uint32_t offset;
    uint32_t bytePos;
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
    uint32_t getDecompressedSize() const;

    /**
     * @brief This function reads <numBytes> of data into <outputBuffer>
     */
    uint32_t read(uint32_t numBytes);
protected:
private:
    void readNextCommand();
    uint32_t copy_block(uint32_t numBytes);

    BitReader reader_;
    ZX0Command cur_command_;
    const uint8_t *inputData_;
    uint8_t *back_pos_;
    uint8_t *cur_out;
    uint32_t bytesDecompressed_;
    uint32_t lastOffset_;
};

static inline uint32_t read_elias_gamma(BitReader& reader)
{
    uint32_t num_non_leading_bits = 0;
    uint32_t value;
    while (!reader.readBit())
    {
        ++num_non_leading_bits;  // Count leading zeros
    }
    // reconstruct the most significant bit of value
    value = 1 << num_non_leading_bits;              // Start with MSB
    
    // now apply the binary part (the actual value)
    while(num_non_leading_bits--)
    {
        value |= (reader.readBit() << num_non_leading_bits);
    }
    
    // Adjust back to zero-based
    return value - 1;
}

static inline void read_new_offset(BitReader& reader, uint32_t& offset)
{
    const uint32_t has_msb = reader.readBit();

    const uint32_t lsb = reader.read(7);
    const uint32_t msb = (has_msb) ? read_elias_gamma(reader) : 0;

    offset = ((msb << 7) | lsb) + 1;
}

BitReader::BitReader(const uint8_t* buffer)
    : buffer_(buffer)
    , curBuffer_(buffer)
    , currentDWord_(0)
    , bitsLeft_(0)
{
}

inline uint32_t BitReader::readBit()
{
    return read(1);
}

inline uint32_t BitReader::read(uint32_t numBits)
{
    uint32_t result = 0;
    
    // Fast path: Read all bits from cached data
    if (numBits <= bitsLeft_)
    {
        result = (currentDWord_ >> (bitsLeft_ - numBits)) & ((1 << numBits) - 1);
        bitsLeft_ -= numBits;
        return result;
    }
    
    // Slow path: Refill cache and combine bits
    result = currentDWord_ & ((1 << bitsLeft_) - 1);
    numBits -= bitsLeft_;
    
    // Refill cache (32-bit aligned read)
    // but the GBA (or x86 processor on pc) would read the value as little endian.
    // and we need it as big endian. Therefore we do a byte swap
    currentDWord_ = __builtin_bswap32(*(uint32_t*)curBuffer_);

    curBuffer_ += sizeof(uint32_t);
    bitsLeft_ = 32;
    
    // Combine remaining bits
    result = (result << numBits) | (currentDWord_ >> (32 - numBits));
    bitsLeft_ -= numBits;

    return result;
}

ZX0Decompressor::ZX0Decompressor()
    : reader_(nullptr)
    , cur_command_({ZX0OperationType::NONE, 0, 0, 0})
    , inputData_(nullptr)
    , back_pos_(nullptr)
    , cur_out(nullptr)
    , bytesDecompressed_(0)
    , lastOffset_(UINT32_MAX)
{
}

void ZX0Decompressor::start(uint8_t *output_buffer, const uint8_t *input_data)
{
    reader_ = BitReader(input_data + 4);
    cur_command_ = {ZX0OperationType::NONE, 0, 0, 0};
    inputData_ = input_data;
    back_pos_ = nullptr;
    cur_out = output_buffer;
    bytesDecompressed_ = 0;
    lastOffset_ = UINT32_MAX;
}

uint32_t ZX0Decompressor::getDecompressedSize() const
{
    if(!inputData_)
    {
        return 0;
    }
    return *((uint32_t*)inputData_);
}

uint32_t ZX0Decompressor::read(uint32_t numBytes)
{
    const uint32_t decompressed_size = getDecompressedSize();
    const uint32_t bytesDecompressedBefore = bytesDecompressed_;
    uint32_t bytesRead;

    while(numBytes && bytesDecompressed_ < decompressed_size)
    {
        // Check if we have finished processing the previous pending command
        // if we have, we need to read a new operation
        if(cur_command_.cmdType == ZX0OperationType::NONE || cur_command_.bytePos >= cur_command_.length)
        {
            readNextCommand();
        }

        bytesRead = copy_block(numBytes);
        numBytes -= bytesRead;
        bytesDecompressed_ += bytesRead;
    }

    return bytesDecompressed_ - bytesDecompressedBefore;
}

inline void ZX0Decompressor::readNextCommand()
{
    const uint32_t cmdBit = reader_.readBit();

    // the "COPY_NEW_OFFSET" command adds + 1 to the length, but the other commands don't.
    // given that read_elias_gamma() function is marked "inline", the way I set the length
    // is to avoid having multiple calls to it here. (for code size)
    if(cmdBit)
    {
        read_new_offset(reader_, lastOffset_);
        cur_command_.cmdType = ZX0OperationType::COPY_NEW_OFFSET;
        cur_command_.length = 1; 
        cur_command_.offset = lastOffset_;
        cur_command_.bytePos = 0;
    }
    else if(cur_command_.cmdType == ZX0OperationType::LITERAL_BLOCK)
    {
        cur_command_.cmdType = ZX0OperationType::COPY_LAST_OFFSET;
        // copy from new offset and last offset differs in the sense that with the new offset the encoded length is reduced by one
        // and for last offset it isn't. This is likely because you still need to be able to insert a dummy "copy-from-last-offset" operation.
        cur_command_.length = 0;
        cur_command_.offset = lastOffset_;
    }
    else
    {
        cur_command_.cmdType = ZX0OperationType::LITERAL_BLOCK;
        cur_command_.length = 0;
    }
    cur_command_.length += read_elias_gamma(reader_);
    cur_command_.bytePos = 0;
}

uint32_t ZX0Decompressor::copy_block(uint32_t numBytes)
{
    const uint32_t available = cur_command_.length - cur_command_.bytePos;
    const uint32_t bytesToRead = (numBytes > available) ? available : numBytes;
    uint32_t bytesRemaining = bytesToRead;

    if(cur_command_.cmdType == ZX0OperationType::LITERAL_BLOCK)
    {
        // Literal copy

        // Align cur_out first
        while (bytesRemaining && ((uintptr_t)cur_out & 3))
        {
            (*cur_out++) = reader_.read(8);
            bytesRemaining--;
        }

        // Use bulk 32-bit writes when aligned
        while (bytesRemaining >= 4)
        {
            *(uint32_t*)cur_out = __builtin_bswap32(reader_.read(32));
            cur_out += 4;
            bytesRemaining -= 4;
        }
        // Handle remaining bytes
        while (bytesRemaining--)
        {
            (*cur_out++) = reader_.read(8);
        }
    }
    else
    {
        if(!cur_command_.bytePos)
        {
            back_pos_ = cur_out - cur_command_.offset;
        }

        // try to get cur_out and back_pos aligned to 32 bit accesses first
        while (bytesRemaining && (((uintptr_t)cur_out & 3) || ((uintptr_t)back_pos_ & 3)))
        {
            (*cur_out++) = (*back_pos_++);
            bytesRemaining--;
        }

        // now try bulk 32 bit writes
        while(bytesRemaining >= 4)
        {
            *(uint32_t*)cur_out = *((uint32_t*)back_pos_);
            cur_out += 4;
            back_pos_ += 4;
            bytesRemaining -= 4;
        }

        while(bytesRemaining--)
        {
            (*cur_out++) = (*back_pos_++);
        }
    }
    
    cur_command_.bytePos += bytesToRead;

    return bytesToRead;
}

}

__attribute__((section(".iwram")))
static ZX0Decompressor decompressor;

extern "C"
{
void zx0_decompressor_start(uint8_t *output_buffer, const uint8_t *input_data)
{
    decompressor.start(output_buffer, input_data);
}

uint32_t zx0_decompressor_get_decompressed_size()
{
    return decompressor.getDecompressedSize();
}

uint32_t zx0_decompressor_read(uint32_t num_bytes)
{
    return decompressor.read(num_bytes);
}
}