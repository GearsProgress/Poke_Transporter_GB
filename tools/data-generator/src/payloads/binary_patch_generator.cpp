#include "payloads/binary_patch_generator.h"

//#include <cstdio>
binary_patch_list binary_patch_generator::diff(const uint8_t* buffer1, const uint8_t* buffer2, size_t size) const
{
    binary_patch_list patches;
    binary_patch_data current_patch;
    bool diff_started = false;
    
    // Reserve some space for the patch data to avoid frequent reallocations
    current_patch.data.reserve(10);

    for (uint16_t i = 0; i < size; ++i)
    {
        if (buffer1[i] != buffer2[i])
        {
            if(!diff_started)
            {
                // Start a new patch
                diff_started = true;
                current_patch.offset = i;
            }

            current_patch.data.push_back(buffer2[i]);
        }
        else if(diff_started)
        {
            // If we were in a diff and found a match, finalize the current patch
//          printf("Generated patch: offset: %hu, size: %zu\n", current_patch.offset, current_patch.data.size());
            patches.push_back(current_patch);
            current_patch.data.clear();
            diff_started = false;
        }
    }

//  printf("Finished generating binary patches... num=%zu\n", patches.size());
    return patches;
}

uint16_t write_binary_patch_to_buffer(const binary_patch_data &patch, uint8_t *buffer)
{
    // start by writing the size of the data as an uint16_t, little endian.
    const uint16_t size = static_cast<uint16_t>(patch.data.size());
    *buffer = size & 0xFF;
    *(buffer + 1) = (size >> 8);
    buffer += 2;

    // now write the 16 bit offset in little endian format
    *buffer = patch.offset & 0xFF;
    *(buffer + 1) = (patch.offset >> 8);
    buffer += 2;

    // finally write the data itself
    for (const uint8_t &byte : patch.data)
    {
        *buffer++ = byte;
    }

    return 4 + patch.data.size(); // 4 bytes for offset and size, plus the size of the data
}