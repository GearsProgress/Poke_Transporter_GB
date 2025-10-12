#ifndef _TEXT_DATA_TABLE_H
#define _TEXT_DATA_TABLE_H

#include <cstdint>

/**
 * This class fully decompresses a text table in the specified decompression_buffer
 * and then gives you utility functions to retrieve the text entries
 *
 * But it requires a buffer large enough to contain the entire decompressed table.
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
    uint32_t decompressed_size_;
};

#endif