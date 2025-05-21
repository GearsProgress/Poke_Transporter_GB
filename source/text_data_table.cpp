#include "text_data_table.h"
#include "zx0_decompressor.h"
#include <cstring>

static uint16_t get_entry_offset_by_index(const uint8_t *text_table, uint8_t index)
{
    return *((uint16_t*)(text_table + 2 + index * 2));
}

static uint16_t get_entries_start_offset_of(uint8_t num_text_entries)
{
    // This returns the byte offset to skip the table index and reach the start of the actual entries.
    return 2 + (num_text_entries * 2);
}

text_data_table::text_data_table(uint8_t *decompression_buffer)
    : decompression_buffer_(decompression_buffer)
{
}

void text_data_table::decompress(const uint8_t *compressed_table)
{
    zx0_decompressor_start(decompression_buffer_, compressed_table);
    zx0_decompressor_read(zx0_decompressor_get_decompressed_size());
}

uint16_t text_data_table::get_number_of_text_entries() const
{
    return *((uint16_t*)decompression_buffer_);
}

const uint8_t* text_data_table::get_text_entry(uint8_t index) const
{
    const uint16_t entry_offset = get_entry_offset_by_index(decompression_buffer_, index);
    return decompression_buffer_ + get_entries_start_offset_of(get_number_of_text_entries()) + entry_offset;
}

streamed_text_data_table::streamed_text_data_table(uint8_t *decompression_buffer, uint32_t decompression_buffer_size, uint8_t *index_buffer)
    : compressed_table_(nullptr)
    , decompression_buffer_(decompression_buffer)
    , decompression_buffer_size_(decompression_buffer_size)
    , index_buffer_(index_buffer)
    , bytes_decompressed_(0)
    , last_chunk_size_(0)
{
}

void streamed_text_data_table::decompress(const uint8_t *compressed_table)
{
    zx0_decompressor_start(index_buffer_, compressed_table);
    zx0_decompressor_read(2);
    zx0_decompressor_read(get_number_of_text_entries() * 2);
    compressed_table_ = compressed_table;
    bytes_decompressed_ = 2 + get_number_of_text_entries() * 2;

    // for further decompressing, we need this data to be available in the decompression buffer too.
    // ZX0 looks back to already decompressed data after all.
    memcpy(decompression_buffer_ + ZX0_DEFAULT_WINDOW_SIZE, index_buffer_, bytes_decompressed_);
    last_chunk_size_ = bytes_decompressed_;
}

uint16_t streamed_text_data_table::get_number_of_text_entries() const
{
    return *((uint16_t*)index_buffer_);
}

const uint8_t* streamed_text_data_table::get_text_entry(uint8_t index)
{
    const uint16_t num_text_entries = get_number_of_text_entries();
    const uint16_t entries_start_offset = get_entries_start_offset_of(num_text_entries);
    const uint16_t entry_offset = get_entry_offset_by_index(index_buffer_, index);
    const uint16_t entry_byte_offset = entries_start_offset + entry_offset;
    const uint16_t space_remaining_outside_lookback_window = decompression_buffer_size_ - ZX0_DEFAULT_WINDOW_SIZE;
    const uint16_t current_window_size = get_current_zx0_window_size();
    const uint16_t window_start_offset = bytes_decompressed_ - current_window_size;
    uint16_t bytes_to_decompress;
    uint16_t chunk_size;
    uint16_t entry_size_in_bytes;
    uint16_t entry_end_byte_offset;

    // figure out how many bytes we need to read to have the entire text entry
    // unfortunately ZX0 doesn't have random access, so we need to linearly decompress
    // until we have reached the bytes we actually want.
    if(index != num_text_entries - 1)
    {
        const uint16_t next_entry_offset = get_entry_offset_by_index(index_buffer_, index + 1);
        entry_size_in_bytes = next_entry_offset - entry_offset;
    }
    else
    {
        // we don't have a next entry. So we need to consider the end of the file
        const uint16_t decompressed_size = static_cast<uint16_t>(zx0_decompressor_get_decompressed_size());
        entry_size_in_bytes = decompressed_size - entry_byte_offset;
    }
    entry_end_byte_offset = entry_byte_offset + entry_size_in_bytes;

    if(entry_end_byte_offset < bytes_decompressed_)
    {
        // already decoded, let's check if we have it completely in our current decompressed window
        if(entry_byte_offset >= window_start_offset)
        {
            // one thing to realize is that when we have less than our ZX0 window size, the decoded data doesn't start
            // at the start of the buffer. But instead it ends at decompression_buffer + ZX0_DEFAULT_WINDOW_SIZE
            return get_window_start() + (entry_byte_offset - window_start_offset);
        }
        else
        {
            // unfortunately it's in front of our current decompression window.
            // Since ZX0 doesn't actually have random access, it means we have to start
            // decompression from scratch
            decompress(compressed_table_);
            // now that we decompressed JUST the index table again,
            // we should be able to reach desired_byte_offset.
        }
    }

    bytes_to_decompress = entry_end_byte_offset - bytes_decompressed_;
    // keep decompressing until we have decompressed what we need.
    while(bytes_to_decompress > 0)
    {
        // move the last decompressed chunk backwards
        memmove(decompression_buffer_, decompression_buffer_ + last_chunk_size_, ZX0_DEFAULT_WINDOW_SIZE);
        chunk_size = (bytes_to_decompress > space_remaining_outside_lookback_window) ? space_remaining_outside_lookback_window : bytes_to_decompress;

        zx0_decompressor_read_partial(decompression_buffer_ + ZX0_DEFAULT_WINDOW_SIZE, chunk_size);
        last_chunk_size_ = chunk_size;
        bytes_to_decompress -= chunk_size;
        bytes_decompressed_ += chunk_size;
    }

    // we know the last byte we decompressed should be the last byte of the entry
    // so we need to count backwards to get to the beginning
    return decompression_buffer_ + ZX0_DEFAULT_WINDOW_SIZE + last_chunk_size_ - entry_size_in_bytes;
}

uint8_t* streamed_text_data_table::get_window_start() const
{
    uint16_t without_last_chunk_size = (bytes_decompressed_ - last_chunk_size_);
    if(without_last_chunk_size > ZX0_DEFAULT_WINDOW_SIZE)
    {
        without_last_chunk_size = ZX0_DEFAULT_WINDOW_SIZE;
    }
    return decompression_buffer_ + ZX0_DEFAULT_WINDOW_SIZE - without_last_chunk_size;
}

uint8_t* streamed_text_data_table::get_window_end() const
{
    return decompression_buffer_ + ZX0_DEFAULT_WINDOW_SIZE + last_chunk_size_;
}

uint16_t streamed_text_data_table::get_current_zx0_window_size() const
{
    return static_cast<uint16_t>(get_window_end() - get_window_start());
}