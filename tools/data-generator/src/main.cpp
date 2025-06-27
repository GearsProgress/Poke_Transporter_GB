#include "pokemon_data.h"
#include "common.h"
#include "gba_rom_values/gba_rom_values.h"
#include "gb_rom_values/gb_rom_values.h"
#include <cstdio>
// This application holds the various long static data arrays that Poke Transporter GB uses
// and it writes them to .bin files that can be compressed with compressZX0 later.
// it's useful to do it this way because it keeps this data easy to view, edit and document

// This function generates a binary file containing the specified list of ROM_DATA structs
void generate_gba_rom_value_tables(const char *output_path, const char *filename, const struct ROM_DATA *rom_data_values, u16 num_elements)
{
    writeTable(output_path, filename, reinterpret_cast<const char*>(rom_data_values), num_elements * sizeof(struct ROM_DATA));
}

void generate_gb_rom_value_tables(const char *output_path, const char *filename, const struct GB_ROM *rom_data_values, u16 num_elements)
{
    writeTable(output_path, filename, reinterpret_cast<const char*>(rom_data_values), num_elements * sizeof(struct GB_ROM));
}

int main(int argc, char **argv)
{
    const char *output_path = (argc > 1) ? argv[1] : "";
    generate_pokemon_data(output_path);

    // generate the ROM_DATA tables for each language
    generate_gba_rom_value_tables(output_path, "gba_rom_values_eng.bin", rom_data_values_eng, rom_data_values_eng_size);
    generate_gba_rom_value_tables(output_path, "gba_rom_values_fre.bin", rom_data_values_fre, rom_data_values_fre_size);
    generate_gba_rom_value_tables(output_path, "gba_rom_values_ger.bin", rom_data_values_ger, rom_data_values_ger_size);
    generate_gba_rom_value_tables(output_path, "gba_rom_values_ita.bin", rom_data_values_ita, rom_data_values_ita_size);
    generate_gba_rom_value_tables(output_path, "gba_rom_values_jpn.bin", rom_data_values_jpn, rom_data_values_jpn_size);
    generate_gba_rom_value_tables(output_path, "gba_rom_values_spa.bin", rom_data_values_spa, rom_data_values_spa_size);

    generate_gb_rom_value_tables(output_path, "gb_rom_values_eng.bin", gb_rom_values_eng, gb_rom_values_eng_size);
    generate_gb_rom_value_tables(output_path, "gb_rom_values_fre.bin", gb_rom_values_fre, gb_rom_values_fre_size);
    
    printf("sizeof ROM_DATA: %zu\n", sizeof(struct ROM_DATA));
    printf("sizeof GB_ROM: %zu\n", sizeof(struct GB_ROM));

    return 0;
}