#include <cstdio>
#include <cstdint>
#include <cstring>
#include <libgen.h>

// @author risingPhil
// This file implements the zx0 compression algorithm.
// It serves as a test to see if this algorithm could suit us for the compression of several static arrays/buffers in Poke Transporter GB.

//#define LOG_OPERATIONS 1

#define MAX_OFFSET   2048  // Maximum backward offset (ZX0 limit), tuned for Poke Transporter GB to be able to use a 2 KB decompression buffer
#define MAX_LEN      255    // Maximum match length (ZX0 limit)
#define OUTPUT_BUFFER_SIZE 256 * 1024 // Maximum output buffer size (artificial limitation, I suppose)

#ifdef LOG_OPERATIONS
    #define LOG_OP(...) printf(__VA_ARGS__)
#else
    #define LOG_OP(...) 
#endif

// anonymous namespace for internal linkage
namespace
{

/**
* This class makes writing on a per-bit basis much easier
*/
class BitWriter
{
public:
	BitWriter(uint8_t* buffer);

    void write(uint8_t value, uint8_t numBits);
    void write_bit(uint8_t value);
    void write_byte(uint8_t value);

    size_t get_bits_written() const;
protected:
private:
    uint8_t* buffer_;
	uint8_t* cur_buffer_;
	uint8_t bit_index_;
};

BitWriter::BitWriter(uint8_t* buffer)
    : buffer_(buffer)
    , cur_buffer_(buffer)
    , bit_index_(0)
{
}

void BitWriter::write_bit(uint8_t value)
{
    value &= 0x1;
    *cur_buffer_ |= (value << (7 - bit_index_));

    if(bit_index_ == 7)
    {
        ++cur_buffer_;
        bit_index_ = 0;
    }
    else
    {
        ++bit_index_;
    }
}

void BitWriter::write_byte(uint8_t value)
{
    if(bit_index_)
    {
        write(value, 8);
        return;
    }
    *cur_buffer_ = value;
    ++cur_buffer_;
}

void BitWriter::write(uint8_t value, uint8_t numBits)
{
    for(int i=numBits - 1; i >= 0; --i)
    {
        write_bit(value >> i);
    }
}

size_t BitWriter::get_bits_written() const
{
    return (cur_buffer_ - buffer_) * 8 + bit_index_;
}
}

/**
 * @brief Find the best match for the current position (LZ77-style)
 * We simply try to find the longest matching bytes backwards in the buffer.
 */
static void find_backwards_match(const unsigned char *buffer, size_t buffer_size, int pos, int *best_offset, int *best_len)
{
    *best_offset = 0;
    *best_len = 0;
    const size_t max_offset = (pos > MAX_OFFSET) ? MAX_OFFSET : pos;
    const int max_len = (buffer_size - pos > MAX_LEN) ? MAX_LEN : buffer_size - pos;
    int len;

    for (size_t offset = 1; offset <= max_offset; offset++)
    {
        len = 0;
        while (len < max_len && buffer[pos - offset + len] == buffer[pos + len])
        {
            ++len;
        }
        if (len > *best_len)
        {
            *best_len = len;
            *best_offset = offset;
        }
    }
}

/**
 * @brief This function encodes the specified value with gamma encoding.
 *
 * The way it works is that we first determine of how many bits the value consists, except for the leading bits. (=num_non_leading_bits)
 * Then we write <num_non_leading_bits> zeros.
 * We also write the original value in <num_non_leading_bits + 1> bits
 * 
 * For decoding, we can determine the number of zeros and that will indicate how many bits we need to read for the actual value.
 * 
 */
static void write_elias_gamma(BitWriter& writer, int value)
{
    value++;  // Adjust because Gamma only encodes n ≥ 1
    int num_non_leading_bits = 0;
    int i;

    // Calculate floor(log2(value))
    int tmp = value >> 1;
    while(tmp)
    {
        ++num_non_leading_bits;
        tmp >>= 1;
    }
    
    // Write unary part (k zeros)
    for (i = 0; i < num_non_leading_bits; i++)
    {
        writer.write_bit(0);
    }
    // Write binary part (num_non_leading_bits+1 bits of value)
    for (int i = num_non_leading_bits; i >= 0; i--)
    {
        writer.write_bit(value >> i);
    }
}

/**
 * This struct represents a buffer to hold a number of pending "literal" bytes
 * before they actually get written to the output
 */
typedef struct LiteralBuffer
{
    uint8_t buffer[1024];
    uint16_t size;
} LiteralBuffer;

/**
 * @brief This function writes a command for the decompressor to start copying <length> bytes
 * from the last offset specified with the write_copy_from_new_offset_block() function
 */
static void write_copy_from_last_offset_block(BitWriter& writer, int length)
{
    LOG_OP("copy_last: %d\n", length);
    writer.write_bit(0);
    write_elias_gamma(writer, length);
}

/**
 * @brief Writes a command to copy the bytes in LiteralBuffer to the decompressed buffer.
 */
static void write_literal_block(BitWriter& writer, LiteralBuffer& literal_buffer)
{
    uint16_t i = 0;

    if(!literal_buffer.size)
    {
        return;
    }

    LOG_OP("copy_literal: %hu\n", literal_buffer.size);

    // flag that this is a literal block
    writer.write_bit(0);
    write_elias_gamma(writer, literal_buffer.size);

    while(i < literal_buffer.size)
    {
        writer.write_byte(literal_buffer.buffer[i]);

        ++i;
    }
    literal_buffer.size = 0;
}

/**
 * @brief Writes a command to indicate that the decompressor must copy <length> bytes from the given backwards offset.
 */
static void write_copy_from_new_offset_block(BitWriter& writer, int offset, int length)
{
    LOG_OP("copy_new: offset: %d, length: %d\n", offset, length);
    writer.write_bit(1);  // Match flag

    // Encode offset (Elias Gamma + 7-bit LSB)
    const int msb = ((offset - 1) >> 7) & 0xFF;
    const int lsb = (offset - 1) & 0x7F;

    // first bit of LSB indicates whether the MSB follows.
    writer.write_bit((msb > 0));

    // write 7 bit LSB raw bits
    writer.write(lsb, 7);

    if (msb > 0)
    {
        write_elias_gamma(writer, msb);
    }

    // Encode length (Elias Gamma)
    write_elias_gamma(writer, length - 1);
}

static void literal_buffer_push(BitWriter& writer, LiteralBuffer& literal_buffer, uint8_t byte)
{
    if(literal_buffer.size == 1024)
    {
        // EDGE case: buffer is full.
        // back-to-back literal blocks are forbidden,
        // so we must insert a dummy "use last offset" block
        write_literal_block(writer, literal_buffer);
        write_copy_from_last_offset_block(writer, 0);
    }

    literal_buffer.buffer[literal_buffer.size] = byte;
    ++literal_buffer.size;
}

/**
 * This function encodes the specified buffer with the ZX0 compression algorithm
 * and stores the result into output_buffer.
 * 
 * Please make sure the output_buffer is sufficiently large enough before calling this function.
 */
static size_t encodeZX0(uint8_t* output_buffer, const uint8_t* buffer, size_t buffer_size)
{
    BitWriter writer(output_buffer);
    LiteralBuffer literal_buffer = {
        .buffer = {0},
        .size = 0
    };
    
    int pos = 0;
    int last_offset = 0x7FFFFFFF;
    int offset;
    int length;
    int numBytes = buffer_size;

    // first write the size of the input in little endian format in the output buffer
    writer.write_byte(static_cast<uint8_t>(buffer_size));
    writer.write_byte(static_cast<uint8_t>(buffer_size >> 8));
    writer.write_byte(static_cast<uint8_t>(buffer_size >> 16));
    writer.write_byte(static_cast<uint8_t>(buffer_size >> 24));

    while(pos < numBytes)
    {
        find_backwards_match(buffer, numBytes, pos, &offset, &length);

        // important rules: You cannot have 2 consecutive literal blocks.
        // reusing the last offset can only happen after a literal block!

        if(length < 2)
        {
            // we must buffer the literals because we can only start writing them when we know the "length"
            literal_buffer_push(writer, literal_buffer, buffer[pos]);
            ++pos;
        }
        else if(offset == last_offset)
        {
            // write any pending literal bytes
            write_literal_block(writer, literal_buffer);
            write_copy_from_last_offset_block(writer, length);
            pos += length;
        }
        else
        {
            // write any pending literal bytes
            write_literal_block(writer, literal_buffer);
            write_copy_from_new_offset_block(writer, offset, length);
            last_offset = offset;
            pos += length;
        }
    }

    return writer.get_bits_written();
}

/** 
 * @brief Reads the given file completely into the specified buffer.
 * The buffer is allocated by this function, but should be delete[]'d by the caller.
 */
static bool read_file(const char* filename, uint8_t*& out_buffer, size_t& out_size)
{
    FILE* file;
    long size;
    size_t read;
    uint8_t* buffer;
    
    file = fopen(filename, "rb");
    if (!file) return false;

    // Seek to end to determine size
    if (fseek(file, 0, SEEK_END) != 0)
    {
        fclose(file);
        return false;
    }

    size = ftell(file);
    if (size < 0)
    {
        fclose(file);
        return false;
    }

    rewind(file);

    buffer = new uint8_t[size];

    read = fread(buffer, 1, size, file);
    fclose(file);

    if (read != (size_t)size) {
        delete[] buffer;
        return false;
    }

    out_buffer = buffer;
    out_size = size;

    return true;
}

static void print_usage()
{
    const char* usageString = R"delim(
Usage: compressZX0 <path/to/file> <output_path>

This program will compress the given file with the ZX0 compression algorithm and store the output in
<output_path>/<filename_without_extension>_zx0.bin
)delim";
    printf(usageString);
}

int main(int argc, char** argv)
{
    // Reserve 256KB buffer, which is already much larger than the maximum file size we'd allow for PTGB.
    // (the reason why I'm using a buffer instead of writing directly to a file is simply because I'm lazy. 
    // I wrote a test of the algorithm using buffers first. And I know that for Poke Transporter GB specifically
    // we'll never exceed the 256KB filesize. So I'm not going to rework this code, because there's currently no need)
    uint8_t output_buffer[OUTPUT_BUFFER_SIZE] = {0};
    uint8_t *input_buffer = nullptr;
    char *filename;
    char *extension_dot;
    size_t input_buffer_size;
    size_t bits_written;
    size_t num_bytes;
    double compress_ratio;
    char output_path[4096];
    FILE* f;

    if(argc < 3)
    {
        print_usage();
        return 1;
    }

    if(!read_file(argv[1], input_buffer, input_buffer_size))
    {
        perror("Could not open file: ");
        return 1;
    }

    // make sure the input_buffer_size is not larger than our output_buffer we statically allocated
    // This is a bit of an artificial limitation though.
    if(input_buffer_size > sizeof(output_buffer))
    {
        fprintf(stderr, "ERROR: The input file should not be larger than %zu KB!\n", sizeof(output_buffer));
        return 1;
    }

    // get the filename part of the given file
    // and remove the extension.
    // basename uses statically allocated memory that gets overwritten by each call.
    // but it returns a modifiable char*
    // so we might as well just edit that buffer directly because no-one will depend on this value later.
    filename = basename(argv[1]);

    printf("Compressing %s...", filename);

    bits_written = encodeZX0(output_buffer, input_buffer, input_buffer_size);
    delete[] input_buffer;
    input_buffer = nullptr;
    num_bytes = (bits_written + 7) / 8;

    printf("done\n");

    // if we have an extension in the filename, just end the string at the '.' position.
    extension_dot = strchr(filename, '.');
    if(extension_dot)
    {
        *extension_dot = '\0';
    }

    // argv[2] should be the output directory
    snprintf(output_path, sizeof(output_path), "%s/%s_zx0.bin", argv[2], filename);

    f = fopen(output_path, "wb+");
    fwrite(output_buffer, 1, num_bytes, f);
    fclose(f);

    compress_ratio = static_cast<double>(num_bytes) / input_buffer_size;
    printf("Compressed size: %zu bytes/%zu bytes, Compression ratio: %f%%\n", num_bytes, input_buffer_size, compress_ratio * 100.f);
    
    return 0;
}


