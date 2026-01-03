#include "payloads/payload_file_reader.h"
#include "payloads/payload_file_writer.h"
#include "gb_rom_values/base_gb_rom_struct.h"
#include <cstring>

// Reads a payload from the specified buffer pointer based on generation, language, and game variant
static const uint8_t* read_payload_metadata(const uint8_t *buffer, payload_metadata &out_metadata)
{
    out_metadata.language = buffer[0];
    out_metadata.game_variant = buffer[1];
    out_metadata.size = *(uint16_t *)(buffer + 2);
    
    return buffer + sizeof(struct payload_metadata); // Move past the metadata header
}

// Reads the payload data from the file buffer and returns a pointer to where we stopped reading
static const uint8_t* read_payload_data(const uint8_t *input_buffer, uint8_t *output_buffer, size_t size)
{
    memcpy(output_buffer, input_buffer, size);
    return input_buffer + size;
}

/**
 * @brief Calculate the next 4 byte aligned offset.
 * 
 * The Gameboy Advance needs alignment to read data correctly.
 * For (u)int16_t data types, for example, the data needs to be aligned to 2 bytes
 * For (u)int32_t data types, the data needs to be aligned to 4 bytes.
 */
static uint16_t get_aligned_offset(uint16_t current_offset)
{
    // Align to 4-byte boundary
    return (current_offset + 3) & ~3; // Round up to the next multiple of 4
}

static const uint8_t* skip_to_aligned_offset(const uint8_t* buffer_start, const uint8_t* input_buffer)
{
    // Skip to the next 4-byte aligned offset
    const uint16_t offset = static_cast<uint16_t>(input_buffer - buffer_start);
    return buffer_start + get_aligned_offset(offset);
}

static const uint8_t* read_binary_patch(const uint8_t *input_buffer, uint8_t *output_buffer, uint16_t &out_offset, uint16_t &out_patch_size, bool skip)
{
    out_patch_size = static_cast<uint16_t>(input_buffer[0]) | (static_cast<uint16_t>(input_buffer[1]) << 8);

    if(skip)
    {
        return input_buffer + 4 + out_patch_size;
    }

    input_buffer += 2; // Move past the size

    out_offset = static_cast<uint16_t>(input_buffer[0]) | (static_cast<uint16_t>(input_buffer[1]) << 8);
    input_buffer += 2; // Move past the offset

    memcpy(output_buffer, input_buffer, out_patch_size);
    return input_buffer + out_patch_size; // Return the pointer to where we stopped reading
}

payload_file_reader::payload_file_reader(const uint8_t *file_buffer, uint16_t buffer_size)
    : file_buffer_(file_buffer)
    , file_buffer_end_(file_buffer + buffer_size)
{
}

bool payload_file_reader::read_payload(uint8_t *buffer, uint8_t language, uint8_t game_variant)
{
    uint8_t binary_patch_buffer[512]; // Buffer to hold binary patches
    payload_metadata base_payload_metadata;
    payload_metadata current_variant_metadata;
    const uint8_t *cur = file_buffer_;
    uint16_t i;
    uint16_t binary_patch_offset;
    uint16_t binary_patch_size;
    bool found = false;

    // first read the base payload metadata and the base payload
    cur = read_payload_metadata(cur, base_payload_metadata);
    cur = skip_to_aligned_offset(file_buffer_, cur);

    cur = read_payload_data(cur, buffer, base_payload_metadata.size);
    cur = skip_to_aligned_offset(file_buffer_, cur);

    // check if the base payload is actually the payload we requested.
    found = (base_payload_metadata.language == language &&
        base_payload_metadata.game_variant == game_variant);
    
    if(found)
    {
        return true;
    }

    // now start reading the other payloads (which consist of binary patches)
    while(cur < file_buffer_end_)
    {
        cur = read_payload_metadata(cur, current_variant_metadata);
        cur = skip_to_aligned_offset(file_buffer_, cur);

        found = (current_variant_metadata.language == language &&
                current_variant_metadata.game_variant == game_variant);

        // we need to read every binary patch, because we either need to apply them or skip them
        for(i = 0; i < current_variant_metadata.size; ++i)
        {
            cur = read_binary_patch(cur, binary_patch_buffer, binary_patch_offset, binary_patch_size, !found);
            cur = skip_to_aligned_offset(file_buffer_, cur);

            if(found)
            {
                // apply the binary patch to the payload data
                if(binary_patch_offset + binary_patch_size <= PAYLOAD_SIZE)
                {
                    memcpy(buffer + binary_patch_offset, binary_patch_buffer, binary_patch_size);
                }
                else
                {
                    return false; // Patch exceeds payload size
                }
            }
            // else -> the patch is skipped, we've just read it to move the cur pointer forward
        }

        if(found)
        {
            return true;
        }
    }

    return false; // No matching payload found
}

