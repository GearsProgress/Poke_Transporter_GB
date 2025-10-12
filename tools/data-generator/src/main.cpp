//#include "pokemon_data.h"
#include "common.h"
#include "gba_rom_values/gba_rom_values.h"
#include "gb_rom_values/gb_rom_values.h"
#include "payloads/payload_file_writer.h"
#include "payloads/payload_file_reader.h"
#include "payloads/binary_patch_generator.h"
#include "payloads/payload_builder.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <filesystem>

// This application holds the various long static data arrays that Poke Transporter GB uses
// and it writes them to .bin files that can be compressed with gbalzss later.
// it's useful to do it this way because it keeps this data easy to view, edit and document

// This function generates a binary file containing the specified list of ROM_DATA structs
void generate_gba_rom_value_tables(const char *input_path, const char *output_path, const char *filename, const struct ROM_DATA *rom_data_values, u16 num_elements)
{
    writeTable(input_path, output_path, filename, reinterpret_cast<const char *>(rom_data_values), num_elements * sizeof(struct ROM_DATA));
}

void generate_gb_rom_value_tables(const char *input_path, const char *output_path, const char *filename, const struct GB_ROM *rom_data_values, u16 num_elements)
{
    writeTable(input_path, output_path, filename, reinterpret_cast<const char *>(rom_data_values), num_elements * sizeof(struct GB_ROM));
}

/**
 * Generates the payloads for the specific pokémon generation.
 * Note: yellow_version indicates that we'd want to generate the payloads for pokémon yellow.
 * The reason we single out pokémon yellow, is because the binary patch diff is significant compared to Blue, Red and Green.
 * It's easier to compress the data if we generate it into a separate file.
 */
void generate_payloads_for(uint8_t generation, bool yellow_version, const char *full_path)
{
    uint8_t base_payload_buffer[PAYLOAD_SIZE];
    uint8_t other_payload_buffer[PAYLOAD_SIZE];
    payload_file_writer payload_writer;
    binary_patch_generator patch_generator;
    u16 rom_set_index;
    u16 base_payload_index;
    u16 index;

    const struct GB_ROM *rom_value_sets[] = {
        gb_rom_values_eng,
        gb_rom_values_fre};

    const u16 rom_value_sizes[] = {
        gb_rom_values_eng_size,
        gb_rom_values_fre_size};

    const u8 num_elements = sizeof(rom_value_sizes) / sizeof(u16);

    // search for the first english GB_ROM struct for the given generation
    for (base_payload_index = 0; base_payload_index < gb_rom_values_eng_size; ++base_payload_index)
    {
        if (gb_rom_values_eng[base_payload_index].generation == generation)
        {
            if ((!yellow_version && gb_rom_values_eng[base_payload_index].version != YELLOW_ID) || (yellow_version && gb_rom_values_eng[base_payload_index].version == YELLOW_ID))
            {
                break;
            }
        }
    }

    memset(base_payload_buffer, 0, sizeof(base_payload_buffer));

    // initialize the found GB_ROM struct as the base payload
    init_payload(base_payload_buffer, gb_rom_values_eng[base_payload_index], TRANSFER, false);
    payload_writer.set_base_payload(gb_rom_values_eng[base_payload_index].language, gb_rom_values_eng[base_payload_index].version, base_payload_buffer, gb_rom_values_eng[base_payload_index].payload_size);

    for (rom_set_index = 0; rom_set_index < num_elements; ++rom_set_index)
    {
        for (index = 0; index < rom_value_sizes[rom_set_index]; ++index)
        {
            const struct GB_ROM *curr_rom = &rom_value_sets[rom_set_index][index];
            if (curr_rom->generation != generation ||
                (rom_set_index == 0 && index == base_payload_index) ||
                (yellow_version && curr_rom->version != YELLOW_ID) ||
                (!yellow_version && curr_rom->version == YELLOW_ID))
            {
                // skip if:
                // - the generation does not match
                // - if it's the base payload
                // - if we specified yellow_version == true and the current rom is not a pokémon yellow rom.
                // - if we specified yellow_version == false and the current rom IS a pokémon yellow rom.
                continue;
            }

            // add the binary patches for this ROM
            memset(other_payload_buffer, 0, PAYLOAD_SIZE);
            init_payload(other_payload_buffer, *curr_rom, TRANSFER, false);
            binary_patch_list patches = patch_generator.diff(base_payload_buffer, other_payload_buffer, PAYLOAD_SIZE);
            payload_writer.add_binary_patches(curr_rom->language, curr_rom->version, patches);
        }
    }

    payload_writer.write_to_file(full_path);
}

void test_payloads(const char *full_path)
{
    uint8_t buffer[2048]; // 2048 bytes is enough for the payloads
    uint8_t reference_payload_buffer[PAYLOAD_SIZE];
    uint8_t reconstructed_payload_buffer[PAYLOAD_SIZE];
    FILE *file;
    size_t size;
    u16 rom_set_index;
    u16 index;

    file = fopen(full_path, "rb"); /*open file*/
    fseek(file, 0, SEEK_END);
    size = ftell(file); /*calc the size needed*/
    fseek(file, 0, SEEK_SET);

    payload_file_reader payload_reader(buffer, size);

    const struct GB_ROM *rom_value_sets[] = {
        gb_rom_values_eng,
        gb_rom_values_fre};

    const u16 rom_value_sizes[] = {
        gb_rom_values_eng_size,
        gb_rom_values_fre_size};

    const u8 num_elements = sizeof(rom_value_sizes) / sizeof(u16);

    fread(&buffer, 1, size, file);

    for (rom_set_index = 0; rom_set_index < num_elements; ++rom_set_index)
    {
        for (index = 0; index < rom_value_sizes[rom_set_index]; ++index)
        {
            const struct GB_ROM *curr_rom = &rom_value_sets[rom_set_index][index];

            // first generate the reference payload
            memset(reference_payload_buffer, 0, PAYLOAD_SIZE);
            init_payload(reference_payload_buffer, *curr_rom, TRANSFER, false);

            // now read the payload from the file
            memset(reconstructed_payload_buffer, 0, PAYLOAD_SIZE);

            // okay, so, the given file may or may not contain the desired payload.
            // we should just skip if the read call returns false
            if (!payload_reader.read_payload(reconstructed_payload_buffer, curr_rom->language, curr_rom->version))
            {
                continue; // skip if the payload was not found
            }

            // printf("Testing payload from file %s for language %u, variant %u: ", full_path, curr_rom->language, curr_rom->version);
            if (!memcmp(reference_payload_buffer, reconstructed_payload_buffer, PAYLOAD_SIZE))
            {
                printf("P");
            }
            else
            {
                printf("\n\n!!!Payload from file %s for language %u, variant %u failed the payload test!!!\n", full_path, curr_rom->language, curr_rom->version);
                // print the differences
                for (size_t i = 0; i < PAYLOAD_SIZE; ++i)
                {
                    if (reference_payload_buffer[i] != reconstructed_payload_buffer[i])
                    {
                        printf("Byte %zu: expected 0x%02X, got 0x%02X\n", i, reference_payload_buffer[i], reconstructed_payload_buffer[i]);
                    }
                }
                abort(); // stop execution on failure
            }
        }
    }
}

void generate_and_test_payloads_for(uint8_t generation, bool yellow_version, const char *output_path, const char *filename)
{

    char full_output_path[4096];

    if (output_path[0] != '\0')
    {
        snprintf(full_output_path, sizeof(full_output_path), "%s/%s", output_path, filename);
    }
    else
    {
        strncpy(full_output_path, filename, sizeof(full_output_path));
    }

    if (std::filesystem::exists(full_output_path))
    {

        std::filesystem::file_time_type inf_time = std::filesystem::last_write_time("tools/data-generator/src/payloads/payload_builder.cpp");
        std::filesystem::file_time_type outf_time = std::filesystem::last_write_time(full_output_path);

        if (outf_time > inf_time)
        {
            // printf("File %s is newer than %s, skipping\n", full_output_path, input_path);
            printf("S");
            return;
        }
    }
    generate_payloads_for(generation, yellow_version, full_output_path);
    test_payloads(full_output_path);
    printf("B");
}

int main(int argc, char **argv)
{
    printf("Converting data into bin files!\n[");
    const char *output_path = (argc > 1) ? argv[1] : "";
    generate_pokemon_data(output_path);

    // generate the ROM_DATA tables for each language
    generate_gba_rom_value_tables("tools/data-generator/src/gba_rom_values/gba_rom_values_eng.cpp", output_path, "gba_rom_values_eng.bin", rom_data_values_eng, rom_data_values_eng_size);
    generate_gba_rom_value_tables("tools/data-generator/src/gba_rom_values/gba_rom_values_fre.cpp", output_path, "gba_rom_values_fre.bin", rom_data_values_fre, rom_data_values_fre_size);
    generate_gba_rom_value_tables("tools/data-generator/src/gba_rom_values/gba_rom_values_ger.cpp", output_path, "gba_rom_values_ger.bin", rom_data_values_ger, rom_data_values_ger_size);
    generate_gba_rom_value_tables("tools/data-generator/src/gba_rom_values/gba_rom_values_ita.cpp", output_path, "gba_rom_values_ita.bin", rom_data_values_ita, rom_data_values_ita_size);
    generate_gba_rom_value_tables("tools/data-generator/src/gba_rom_values/gba_rom_values_jpn.cpp", output_path, "gba_rom_values_jpn.bin", rom_data_values_jpn, rom_data_values_jpn_size);
    generate_gba_rom_value_tables("tools/data-generator/src/gba_rom_values/gba_rom_values_spa.cpp", output_path, "gba_rom_values_spa.bin", rom_data_values_spa, rom_data_values_spa_size);

    generate_gb_rom_value_tables("tools/data-generator/src/gb_rom_values/gb_rom_values_eng.cpp", output_path, "gb_rom_values_eng.bin", gb_rom_values_eng, gb_rom_values_eng_size);
    generate_gb_rom_value_tables("tools/data-generator/src/gb_rom_values/gb_rom_values_fre.cpp", output_path, "gb_rom_values_fre.bin", gb_rom_values_fre, gb_rom_values_fre_size);

    generate_and_test_payloads_for(1, false, output_path, "gb_gen1_payloads_RB.bin");
    generate_and_test_payloads_for(1, true, output_path, "gb_gen1_payloads_Y.bin");
    generate_and_test_payloads_for(2, false, output_path, "gb_gen2_payloads.bin");

    printf("]\nConvertion finished!\n\n");
    return 0;
}