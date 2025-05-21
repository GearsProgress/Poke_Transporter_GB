#ifndef _TEXT_DATA_TABLE_H
#define _TEXT_DATA_TABLE_H

#include <cstdint>

/**
 * This class fully decompresses a text table in the specified decompression_buffer
 * and then gives you utility functions to retrieve the text entries
 *
 * But it requires a buffer large enough to contain the entire decompressed table.
 * It will also completely decompress the table, which may not what you want.
 *
 * If you want to use a text table in a streamed manner (use smaller decompression buffer and only decompress what's needed)
 * consider using streamed_text_data_table instead.
 */
class text_data_table
{
public:
    text_data_table(uint8_t *decompression_buffer);

    /**
     * This function will start the full decompression for the specified compressed_table
     * and stores it in the decompression_buffer_
     */
    void decompress(const uint8_t *compressed_table);

    /**
     * Returns the number of text entries in the decompression_buffer_
     */
    uint16_t get_number_of_text_entries() const;

    /**
     * This function returns a pointer to a text entry in the decompression_buffer
     */
    const uint8_t* get_text_entry(uint16_t index) const;

    /**
     * This function returns the text entry size in bytes at the given index
     */
    uint16_t get_text_entry_size(uint16_t index) const;
private:
    uint8_t *decompression_buffer_;
};

/**
 * This class is an alternative to translated_text table.
 * It provides the same functionality, yet in a streamed manner.
 *
 * This allows you to use a decompression_buffer that is smaller than the fully decoded text table and only decompress until
 * you have what you need.
 *
 * To make sure we have access to the table index at all times, you need to specify a buffer to hold the table index as well.
 *
 * REQUIREMENT: decompression_buffer needs to be larger than the zx0 window size!!
 */
class streamed_text_data_table
{
public:
    streamed_text_data_table(uint8_t *decompression_buffer, uint32_t decompression_buffer_size, uint8_t *index_buffer);

    /**
     * This function sets up the zx0 decompressor and decompresses the index into the index_buffer
     */
    void decompress(const uint8_t *compressed_table);

    /**
     * Returns the number of text entries in the decompression_buffer_
     */
    uint16_t get_number_of_text_entries() const;

    /**
     * This function returns a pointer to a text entry in the decompression_buffer
     */
    const uint8_t* get_text_entry(uint16_t index);

    /**
     * This function returns the text entry size in bytes at the given index
     */
    uint16_t get_text_entry_size(uint16_t index) const;
private:
    uint8_t* get_window_start() const;
    uint8_t* get_window_end() const;
    uint16_t get_current_zx0_window_size() const;

    const uint8_t *compressed_table_;
    uint8_t *decompression_buffer_;
    uint32_t decompression_buffer_size_;
    uint8_t *index_buffer_;
    mutable uint16_t bytes_decompressed_;
    uint16_t last_chunk_size_;
};

#endif