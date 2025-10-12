#ifndef _COMMON_H
#define _COMMON_H

#include <cstdint>
#include <cstddef>

void writeTable(const char *input_path, const char *output_path, const char *filename, const char *buffer, size_t buffer_size);
void generate_pokemon_data(const char *output_path);

#endif