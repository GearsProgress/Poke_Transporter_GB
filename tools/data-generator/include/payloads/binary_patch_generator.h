#ifndef BINARY_PATCH_GENERATOR_H
#define BINARY_PATCH_GENERATOR_H

#include <vector>
#include <cstdint>
#include <cstddef>

/// @brief This struct represents a single binary patch to transform a chunk of buffer1's data into buffer2's variant.
typedef struct binary_patch_data
{
    /// the offset in the original buffer where the patch should be applied
    uint16_t offset;
    /// @brief the data to be patched in
    std::vector<uint8_t> data;
} binary_patch_data;

typedef std::vector<binary_patch_data> binary_patch_list;

/// @brief This class is used to generate binary patches by diffing 2 buffers.
/// The buffers need to have the same size though.
class binary_patch_generator
{
public:
    binary_patch_list diff(const uint8_t* buffer1, const uint8_t* buffer2, size_t size) const;
protected:
private:
};

/// @brief This function writes a binary patch to the specified buffer.
/// It's the caller's responsibility to ensure that the buffer is large enough to accommodate the patch.
uint16_t write_binary_patch_to_buffer(const binary_patch_data &patch, uint8_t *buffer);

#endif