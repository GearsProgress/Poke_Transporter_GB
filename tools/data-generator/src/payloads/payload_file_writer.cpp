#include "payloads/payload_file_writer.h"
#include <cstdio>
#include <cstring>

payload_file_writer::payload_file_writer()
    : base_payload_(nullptr)
    , base_payload_metadata_()
    , binary_patches_()
{
    memset(&base_payload_metadata_, 0, sizeof(struct payload_metadata));
}

void payload_file_writer::set_base_payload(uint8_t language, uint8_t game_variant, const uint8_t *payload, uint16_t size)
{
    base_payload_ = payload;
    base_payload_metadata_.language = language;
    base_payload_metadata_.game_variant = game_variant;
    base_payload_metadata_.size = size;
}

void payload_file_writer::add_binary_patches(uint8_t language, uint8_t game_variant, const binary_patch_list &patches)
{
    const uint16_t key = (static_cast<uint16_t>(language) << 8) | static_cast<uint16_t>(game_variant);
    binary_patches_.push_back(std::make_pair(key, patches));
}

static void align_next(FILE *file)
{
    // Align to 4-byte boundary
    long pos = ftell(file);
    long aligned_pos = (pos + 3) & ~3; // Round up to the next multiple of 4
    if (aligned_pos > pos)
    {
        uint8_t padding[3] = {0, 0, 0};
        fwrite(padding, 1, aligned_pos - pos, file);
    }
}

static void write_payload_metadata(FILE *file, const payload_metadata &metadata)
{
    fwrite(&metadata.language, 1, 1, file);
    fwrite(&metadata.game_variant, 1, 1, file);
    fwrite(&metadata.size, sizeof(metadata.size), 1, file);

    // align to 4-byte boundary
    align_next(file);
}

void payload_file_writer::write_to_file(const char *path_to_file) const
{
    uint8_t binary_patch_buffer[512]; // Buffer to hold binary patches
    uint16_t binary_patch_buffer_depth;

    FILE *file = fopen(path_to_file, "wb");
    if (!file)
    {
        fprintf(stderr, "Failed to open file for writing: %s", path_to_file);
        return;
    }

    if(!base_payload_)
    {
        fprintf(stderr, "Base payload is not set. Cannot write to file: %s", path_to_file);
        fclose(file);
        return;
    }

    // Write base payload metadata
    write_payload_metadata(file, base_payload_metadata_);
    
    // Write base payload
    if (base_payload_)
    {
        fwrite(base_payload_, 1, base_payload_metadata_.size, file);
    }

    align_next(file);

    // Write binary patches
    for (const auto &pair : binary_patches_)
    {
        const uint32_t key = pair.first;

        const uint8_t language = static_cast<uint8_t>((key >> 8) & 0xFF);
        // The last byte of the key is the game variant
        const uint8_t game_variant = static_cast<uint8_t>(key & 0xFF);
        const binary_patch_list &patches = pair.second;
        const uint16_t patch_count = static_cast<uint16_t>(patches.size());

        const payload_metadata metadata = {
            language,
            game_variant,
            patch_count, // in the case of binary patches, the size field indicates the number of binary patches.
        };
        write_payload_metadata(file, metadata);

        for (const auto &patch : patches)
        {
            binary_patch_buffer_depth = write_binary_patch_to_buffer(patch, binary_patch_buffer);
            fwrite(binary_patch_buffer, 1, binary_patch_buffer_depth, file);
            // Align after each binary patch
            align_next(file);
        }
    }

    fclose(file);
}