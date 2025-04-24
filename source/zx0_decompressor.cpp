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
    RingBuffer(uint8_t *buffer, const uint16_t bufferSize);

    /**
     * Returns the buffer size.
     */
    uint16_t getBufferSize() const;

    uint16_t read(uint8_t *outputBuffer, uint16_t bytesToRead);
    uint8_t readByte();
    void writeByte(uint8_t value);

    /**
     * This function seeks backwards from the current end of the buffer
     */
    void seekBackwardsFromBufferEnd(uint16_t offset);

    void reset();
protected:
private:
    uint8_t *buffer_;
    uint16_t ringStartPos_;
    uint16_t ringReadPos_;
    uint16_t ringEndPos_;
    uint16_t bufferSize_;
};

/**
* This class makes reading on a per-bit basis much easier.
*/
class BitReader
{
public:
    BitReader(const uint8_t* buffer);

    uint8_t readBit();
    uint8_t read(uint8_t numBits);
    uint8_t readByte();
protected:
private:
    const uint8_t* buffer_;
    const uint8_t* curBuffer_;
    uint8_t currentByte_;
    uint8_t bitsLeft_;
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
    uint16_t length;
    uint16_t offset;
    uint16_t bytePos;
} ZX0Command;

/**
 * @brief This class implements the actual ZX0 decompression.
 */
class ZX0Decompressor
{
public:
    ZX0Decompressor(uint8_t* decompressionBuffer, uint16_t decompressionBufferSize);

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
    uint16_t getDecompressedSize() const;

    /**
     * @brief This function reads <numBytes> of data into <outputBuffer>
     */
    uint16_t read(uint8_t *outputBuffer, uint16_t numBytes);

    /**
     * @brief This function uncompresses from the current point until the 
     * specified outputBytePos lies inside the decompressionBuffer
     */
    void seek(uint16_t outputBytePos);
protected:
private:
    void readNextCommand();
    uint16_t copy_block(uint8_t *outputBuffer, uint16_t numBytes);

    RingBuffer buffer_;
    BitReader reader_;
    ZX0Command cur_command_;
    const uint8_t *inputData_;
    uint16_t bytesDecompressed_;
    uint16_t lastOffset_;
};

RingBuffer::RingBuffer(uint8_t *buffer, const uint16_t bufferSize)
 : buffer_(buffer)
 , ringStartPos_(0)
 , ringReadPos_(0)
 , ringEndPos_(0)
 , bufferSize_(bufferSize)
{
}

__attribute__((unused))
uint16_t RingBuffer::getBufferSize() const
{
    return bufferSize_;
}

__attribute__((unused))
uint16_t RingBuffer::read(uint8_t *outputBuffer, uint16_t bytesToRead)
{
    if(ringReadPos_ == ringEndPos_) return 0;  // Early exit if empty

    const uint16_t wrapMask = bufferSize_ - 1;
    uint16_t available;
    uint16_t bytesRead;
    uint16_t chunkSize;

    available = (ringReadPos_ < ringEndPos_) ? (ringEndPos_ - ringReadPos_) : (bufferSize_ - ringReadPos_);
    
    chunkSize = (bytesToRead < available) ? bytesToRead : available;
    memcpy(outputBuffer, buffer_ + ringReadPos_, chunkSize);
    bytesRead = chunkSize;
    ringReadPos_ = (ringReadPos_ + chunkSize) & wrapMask; // wraparound done by bitmask
    bytesToRead -= chunkSize;

    if(bytesToRead > 0 && ringReadPos_ != ringEndPos_)
    {
        // we need more bytes from the start of the buffer
        available = ringEndPos_;
        chunkSize = (bytesToRead <= ringEndPos_) ? bytesToRead : available;
        memcpy(outputBuffer + bytesRead, buffer_, chunkSize);
        bytesRead += chunkSize;
        ringReadPos_ = chunkSize & wrapMask;  // Since we wrapped around to start
    }
    return bytesRead;
}

uint8_t RingBuffer::readByte()
{
    uint8_t value;
    if(ringReadPos_ == ringEndPos_) return 0;  // Early exit if empty

    value = buffer_[ringReadPos_];
    ringReadPos_ = (ringReadPos_ + 1) & (bufferSize_ - 1);
    return value;
}

void RingBuffer::writeByte(uint8_t value)
{
    buffer_[ringEndPos_] = value;
    ringEndPos_ = (ringEndPos_ + 1) & (bufferSize_ - 1);  // wraparound done by bitmask

    if(ringEndPos_ == ringStartPos_)
    {
        // buffer is full, overwrite oldest byte
        ringStartPos_ = (ringStartPos_ + 1) & (bufferSize_ - 1);  // wraparound done by bitmask
    }
}

void RingBuffer::seekBackwardsFromBufferEnd(uint16_t offset)
{    
    ringReadPos_ = (ringEndPos_ - offset) & (bufferSize_ - 1);
}

void RingBuffer::reset()
{
    ringStartPos_ = 0;
    ringReadPos_ = 0;
    ringEndPos_ = 0;
}

static inline uint16_t read_elias_gamma(BitReader& reader)
{
    uint16_t num_non_leading_bits = 0;
    uint16_t value;
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

static inline void read_new_offset(BitReader& reader, uint16_t& offset)
{
    const uint8_t has_msb = reader.readBit();

    const uint16_t lsb = reader.read(7);
    const uint16_t msb = (has_msb) ? read_elias_gamma(reader) : 0;

    offset = ((msb << 7) | lsb) + 1;
}

BitReader::BitReader(const uint8_t* buffer)
    : buffer_(buffer)
    , curBuffer_(buffer)
    , currentByte_(0)
    , bitsLeft_(0)
{
}

uint8_t BitReader::readBit()
{
    // Pre-decrement and check underflow
    if (--bitsLeft_ == 0xFF)
    {
        currentByte_ = (*curBuffer_);
        ++curBuffer_;
        bitsLeft_ = 7;
    }
    return (currentByte_ >> bitsLeft_) & 1;
}

uint8_t BitReader::read(uint8_t numBits)
{
    uint8_t result = 0;
    while (numBits--)
    {
        result = (result << 1) | readBit();
    }
    return result;
}

uint8_t BitReader::readByte()
{
    if(bitsLeft_ == 0)
    {
        const uint8_t value = (*curBuffer_);
        ++curBuffer_;
        return value;
    }
    // Handle byte reads across bit boundaries
    return read(8);
}

ZX0Decompressor::ZX0Decompressor(uint8_t* decompressionBuffer, uint16_t decompressionBufferSize)
    : buffer_(decompressionBuffer, decompressionBufferSize)
    , reader_(nullptr)
    , cur_command_({ZX0OperationType::NONE, 0, 0, 0})
    , inputData_(nullptr)
    , bytesDecompressed_(0)
    , lastOffset_(UINT16_MAX)
{
}

void ZX0Decompressor::setInput(const uint8_t *inputData)
{
    buffer_.reset();
    reader_ = BitReader(inputData + 2);
    cur_command_ = {ZX0OperationType::NONE, 0, 0, 0};
    inputData_ = inputData;
    bytesDecompressed_ = 0;
    lastOffset_ = UINT16_MAX;
}

uint16_t ZX0Decompressor::getDecompressedSize() const
{
    if(!inputData_)
    {
        return 0;
    }
    return *((uint16_t*)inputData_);
}

uint16_t ZX0Decompressor::read(uint8_t *outputBuffer, uint16_t numBytes)
{
    const uint16_t decompressed_size = getDecompressedSize();
    const uint16_t bytesDecompressedBefore = bytesDecompressed_;
    uint16_t bytesRead;

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

void ZX0Decompressor::seek(uint16_t outputBytePos)
{
    uint8_t read_buffer[32];
    uint16_t bytesToRead;
    uint16_t chunkSize;

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
    const uint8_t cmdBit = reader_.readBit();

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

uint16_t ZX0Decompressor::copy_block(uint8_t *outputBuffer, uint16_t numBytes)
{
    const uint16_t available = cur_command_.length - cur_command_.bytePos;
    const uint16_t bytesToRead = (numBytes > available) ? available : numBytes;
    uint16_t bytesRemaining = bytesToRead;

    if(cur_command_.cmdType == ZX0OperationType::LITERAL_BLOCK)
    {
        // Literal copy
        do
        {
            (*outputBuffer) = reader_.readByte();
            buffer_.writeByte((*outputBuffer));
            ++outputBuffer;
        }
        while(--bytesRemaining);
    }
    else
    {
        if(!cur_command_.bytePos)
        {
            buffer_.seekBackwardsFromBufferEnd(cur_command_.offset);
        }

        do
        {
            *outputBuffer = buffer_.readByte();
            buffer_.writeByte(*outputBuffer);
            ++outputBuffer;
        }
        while(--bytesRemaining);
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
__attribute__((section(".iwram")))
static uint8_t decompression_buffer[2048];
__attribute__((section(".iwram")))
static ZX0Decompressor decompressor(decompression_buffer, sizeof(decompression_buffer));

extern "C"
{
void zx0_decompressor_set_input(const uint8_t *input_data)
{
    decompressor.setInput(input_data);
}

uint16_t zx0_decompressor_get_decompressed_size()
{
    return decompressor.getDecompressedSize();
}

void zx0_decompressor_seek(uint16_t output_byte_pos)
{
    decompressor.seek(output_byte_pos);
}

uint16_t zx0_decompressor_read(uint8_t *output_buffer, uint16_t num_bytes)
{
    return decompressor.read(output_buffer, num_bytes);
}
}