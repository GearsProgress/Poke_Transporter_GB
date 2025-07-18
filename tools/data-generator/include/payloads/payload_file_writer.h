#ifndef _PAYLOAD_FILE_WRITER_H
#define _PAYLOAD_FILE_WRITER_H

#include "payloads/binary_patch_generator.h"
#include <vector>

typedef std::vector<std::pair<uint16_t, binary_patch_list>> binary_patch_map;

typedef struct payload_metadata
{
    uint8_t language;
    uint8_t game_variant;
    // for the first payload in the file, the size field represents the number of bytes, because it's the base payload
    // for all subsequent payloads, however, the size field represents the number of binary patches!
    uint16_t size;
} payload_metadata;

/// @brief This class writes a file containing a base payload alongside various
/// payloads represented as binary patches that are supposed to be applied on top of the base payload.
class payload_file_writer
{
public:
    payload_file_writer();
    void set_base_payload(uint8_t language, uint8_t game_variant, const uint8_t *payload, uint16_t size);
    void add_binary_patches(uint8_t language, uint8_t game_variant, const binary_patch_list &patches);

    void write_to_file(const char *path_to_file) const;
protected:
private:
    const uint8_t *base_payload_;
    payload_metadata base_payload_metadata_;
    binary_patch_map binary_patches_;
};

#endif