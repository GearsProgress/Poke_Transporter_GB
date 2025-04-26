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
 * This class implements a ringbuffer. This is useful for ZX0 decompression
 * because it allows you to look back easily.
 * 
 * WARNING: the specified bufferSize MUST be a power of 2!
 * This is needed because I optimized a modulo division (for wraparound)
 * with a bitmask AND. (and it simply won't work correctly if the bufferSize is not a power of 2!)
 */
class RingBuffer
{
public:
    RingBuffer(uint8_t *buffer, const uint32_t bufferSize);

    /**
     * Returns the buffer size.
     */
    uint32_t getBufferSize() const;

    uint32_t read(uint8_t *outputBuffer, uint32_t bytesToRead);
    uint32_t readByte();
    uint32_t readWord();
    void writeByte(uint32_t value);
    void writeWord(uint32_t value);

    /**
     * This function seeks backwards from the current end of the buffer
     */
    void seekBackwardsFromBufferEnd(uint32_t offset);

    uint32_t getReadPos() const;
    uint32_t getWritePos() const;

    void reset();
protected:
private:
    uint8_t *buffer_;
    uint32_t ringStartPos_;
    uint32_t ringReadPos_;
    uint32_t ringEndPos_;
    uint32_t bufferSize_;
    uint32_t sizeMask_;
};

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
    ZX0Decompressor(uint8_t* decompressionBuffer, uint32_t decompressionBufferSize);

    /**
     * @brief This function prepares the ZX0Decompressor instance
     * for decompressing the specified inputData
     * @param compressedData 
     */
    void setInput(const uint8_t *inputData);

    /**
     * @brief Retrieves the size of the data when it is fully decompressed
     * This is read from the first 2 bytes of the inputData
     */
    uint32_t getDecompressedSize() const;

    /**
     * @brief This function reads <numBytes> of data into <outputBuffer>
     */
    uint32_t read(uint8_t *outputBuffer, uint32_t numBytes);

    /**
     * @brief This function uncompresses from the current point until the 
     * specified outputBytePos lies inside the decompressionBuffer
     */
    void seek(uint32_t outputBytePos);
protected:
private:
    void readNextCommand();
    uint32_t copy_block(uint8_t *outputBuffer, uint32_t numBytes);

    RingBuffer buffer_;
    BitReader reader_;
    ZX0Command cur_command_;
    const uint8_t *inputData_;
    uint32_t bytesDecompressed_;
    uint32_t lastOffset_;
};

RingBuffer::RingBuffer(uint8_t *buffer, const uint32_t bufferSize)
 : buffer_(buffer)
 , ringStartPos_(0)
 , ringReadPos_(0)
 , ringEndPos_(0)
 , bufferSize_(bufferSize)
 , sizeMask_(bufferSize - 1)
{
}

__attribute__((unused))
uint32_t RingBuffer::getBufferSize() const
{
    return bufferSize_;
}

__attribute__((unused))
uint32_t RingBuffer::read(uint8_t *outputBuffer, uint32_t bytesToRead)
{
    uint32_t bytesRead = 0;
        
    // Align destination to 32-bit if possible
    while ((ringEndPos_ != ringReadPos_) && (bytesToRead > 0) && ((ringReadPos_ & 3) != 0))
    {
        *outputBuffer++ = buffer_[ringReadPos_];
        ringReadPos_ = (ringReadPos_ + 1) & sizeMask_;
        --bytesToRead;
        ++bytesRead;
    }

    // Bulk 32-bit copies
    while (bytesToRead >= 4 && ((ringEndPos_ - ringReadPos_) & sizeMask_) >= 4)
    {
        *(uint32_t*)outputBuffer = *(uint32_t*)(buffer_ + ringReadPos_);
        outputBuffer += 4;
        ringReadPos_ = (ringReadPos_ + 4) & sizeMask_;
        bytesToRead -= 4;
        bytesRead += 4;
    }

    // Remaining bytes
    while (bytesToRead-- && (ringEndPos_ != ringReadPos_)) {
        *outputBuffer++ = buffer_[ringReadPos_];
        ringReadPos_ = (ringReadPos_ + 1) & sizeMask_;
        ++bytesRead;
    }

    return bytesRead;
}

uint32_t RingBuffer::readByte()
{
    uint32_t value;
    if(ringReadPos_ == ringEndPos_) return 0;  // Early exit if empty

    value = *(buffer_ + ringReadPos_);
    ringReadPos_ = (ringReadPos_ + 1) & (bufferSize_ - 1);
    return value;
}

uint32_t RingBuffer::readWord()
{
    uint32_t value;
    if(ringReadPos_ == ringEndPos_) return 0;  // Early exit if empty

    if(ringReadPos_ + 4 <= bufferSize_)
    {
        value = *(uint32_t*)(buffer_ + ringReadPos_);
        ringReadPos_ = (ringReadPos_ + 4) & (bufferSize_ - 1);
    }
    else
    {
        value = readByte();
        value = (value << 8) | readByte();
        value = (value << 8) | readByte();
        value = (value << 8) | readByte();
    }

    return value;
}

void RingBuffer::writeByte(uint32_t value)
{
    buffer_[ringEndPos_] = static_cast<uint8_t>(value);
    ringEndPos_ = (ringEndPos_ + 1) & (bufferSize_ - 1);  // wraparound done by bitmask

    if(ringEndPos_ == ringStartPos_)
    {
        // buffer is full, overwrite oldest byte
        ringStartPos_ = (ringStartPos_ + 1) & (bufferSize_ - 1);  // wraparound done by bitmask
    }
}

void RingBuffer::writeWord(uint32_t value)
{
    // Check 32-bit alignment
    if ((ringEndPos_ & 3) == 0)
    {
        *(uint32_t*)(buffer_ + ringEndPos_) = value;
        ringEndPos_ = (ringEndPos_ + 4) & sizeMask_;
    } else {
        // Fallback to byte-wise for unaligned (little endian)
        buffer_[ringEndPos_] = value & 0xFF;
        ringEndPos_ = (ringEndPos_ + 1) & sizeMask_;
        buffer_[ringEndPos_] = (value >> 8) & 0xFF;
        ringEndPos_ = (ringEndPos_ + 1) & sizeMask_;
        buffer_[ringEndPos_] = (value >> 16) & 0xFF;
        ringEndPos_ = (ringEndPos_ + 1) & sizeMask_;
        buffer_[ringEndPos_] = (value >> 24) & 0xFF;
        ringEndPos_ = (ringEndPos_ + 1) & sizeMask_;
    }
}

void RingBuffer::seekBackwardsFromBufferEnd(uint32_t offset)
{    
    ringReadPos_ = (ringEndPos_ - offset) & (bufferSize_ - 1);
}

uint32_t RingBuffer::getReadPos() const
{
    return ringReadPos_;
}

uint32_t RingBuffer::getWritePos() const
{
    return ringEndPos_;
}

void RingBuffer::reset()
{
    ringStartPos_ = 0;
    ringReadPos_ = 0;
    ringEndPos_ = 0;
}

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

uint32_t BitReader::readBit()
{
    return read(1);
}

uint32_t BitReader::read(uint32_t numBits)
{
    uint32_t result = 0;
    
    // Fast path: Read all bits from cached data
    if (numBits <= bitsLeft_) {
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

ZX0Decompressor::ZX0Decompressor(uint8_t* decompressionBuffer, uint32_t decompressionBufferSize)
    : buffer_(decompressionBuffer, decompressionBufferSize)
    , reader_(nullptr)
    , cur_command_({ZX0OperationType::NONE, 0, 0, 0})
    , inputData_(nullptr)
    , bytesDecompressed_(0)
    , lastOffset_(UINT32_MAX)
{
}

void ZX0Decompressor::setInput(const uint8_t *inputData)
{
    buffer_.reset();
    reader_ = BitReader(inputData + 4);
    cur_command_ = {ZX0OperationType::NONE, 0, 0, 0};
    inputData_ = inputData;
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

uint32_t ZX0Decompressor::read(uint8_t *outputBuffer, uint32_t numBytes)
{
    const uint32_t decompressed_size = getDecompressedSize();
    const uint32_t bytesDecompressedBefore = bytesDecompressed_;
    uint32_t bytesRead;

    while(numBytes)
    {
        if(bytesDecompressed_ == decompressed_size)
        {
            break;
        }

        // Check if we have finished processing the previous pending command
        // if we have, we need to read a new operation
        if(cur_command_.cmdType == ZX0OperationType::NONE || cur_command_.bytePos >= cur_command_.length)
        {
            readNextCommand();
        }

        bytesRead = copy_block(outputBuffer + bytesDecompressed_, numBytes);
        numBytes -= bytesRead;
        bytesDecompressed_ += bytesRead;
    }

    return bytesDecompressed_ - bytesDecompressedBefore;
}

void ZX0Decompressor::seek(uint32_t outputBytePos)
{
    uint8_t read_buffer[32];
    uint32_t bytesToRead;
    uint32_t chunkSize;

    // NOTE: outputBytePos denotes the index of the byte in the output (decompressed data) buffer!!

    // ZX0 doesn't actually have random access
    // so we'll have to simulate it.
    // first check if the specified position is in the backwards direction.
    if(outputBytePos < bytesDecompressed_)
    {
        // the specified position is in earlier decoded data.
        // this will be expensive, because we will have to start decompression from the beginning
        // until the specified position.
        // reset the decoder
        setInput(inputData_);
        bytesToRead = outputBytePos;
    }
    else
    {
        // The specified position is in future -to-be-decoded- decompressed data.
        // so we just need to keep decoding until we're there.
        bytesToRead = outputBytePos - bytesDecompressed_;
    }

    // Start decompressing until we're at the desired point
    do
    {
        chunkSize = (bytesToRead > sizeof(read_buffer)) ? sizeof(read_buffer) : bytesToRead;
        bytesToRead -= read(read_buffer, chunkSize);
    }
    while(bytesToRead);
}

void ZX0Decompressor::readNextCommand()
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

uint32_t ZX0Decompressor::copy_block(uint8_t *outputBuffer, uint32_t numBytes)
{
    const uint32_t available = cur_command_.length - cur_command_.bytePos;
    const uint32_t bytesToRead = (numBytes > available) ? available : numBytes;
    uint32_t bytesRemaining = bytesToRead;

    if(cur_command_.cmdType == ZX0OperationType::LITERAL_BLOCK)
    {
        // Literal copy
        // Use bulk 32-bit writes when aligned
        while (bytesRemaining >= 4 && (buffer_.getWritePos() & 3) == 0)
        {
            const uint32_t word = __builtin_bswap32(reader_.read(32));
            buffer_.writeWord(word);
            *(uint32_t*)outputBuffer = word;
            outputBuffer += 4;
            bytesRemaining -= 4;
        }
        // Handle remaining bytes
        while (bytesRemaining--)
        {
            uint32_t byte = reader_.read(8);
            buffer_.writeByte(byte);
            *outputBuffer++ = byte;
        }
    }
    else
    {
        if(!cur_command_.bytePos)
        {
            buffer_.seekBackwardsFromBufferEnd(cur_command_.offset);
        }

        while (bytesRemaining >= 4 && (buffer_.getReadPos() & 3) == 0)
        {
            const uint32_t word = __builtin_bswap32(buffer_.readWord());
            buffer_.writeWord(word);
            *(uint32_t*)outputBuffer = word;
            outputBuffer += 4;
            bytesRemaining -= 4;
        }

        while(bytesRemaining--)
        {
            *outputBuffer = static_cast<uint8_t>(buffer_.readByte());
            buffer_.writeByte(*outputBuffer);
            ++outputBuffer;
        }
    }
    
    cur_command_.bytePos += bytesToRead;

    return bytesToRead;
}

}

// define a global 2 KB decompression buffer in IWRAM.
// IWRAM is much faster than EXRAM, so it's ideally suited for decompression.
// 2 KB is a modest/reasonable size to reserve.
// But this also means we can only have one instance of ZX0Decompressor.
// This is one of the reasons why it is implemented in the way that it is.
//__attribute__((section(".iwram")))
static uint8_t decompression_buffer[2048];
//__attribute__((section(".iwram")))
static ZX0Decompressor decompressor(decompression_buffer, sizeof(decompression_buffer));

extern "C"
{
void zx0_decompressor_set_input(const uint8_t *input_data)
{
    decompressor.setInput(input_data);
}

uint32_t zx0_decompressor_get_decompressed_size()
{
    return decompressor.getDecompressedSize();
}

void zx0_decompressor_seek(uint32_t output_byte_pos)
{
    decompressor.seek(output_byte_pos);
}

uint32_t zx0_decompressor_read(uint8_t *output_buffer, uint32_t num_bytes)
{
    return decompressor.read(output_buffer, num_bytes);
}
}