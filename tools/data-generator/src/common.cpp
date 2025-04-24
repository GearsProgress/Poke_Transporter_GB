#include "common.h"

#include <cstdio>

void writeTable(const char* filename, const uint8_t *buffer, size_t buffer_size)
{
    FILE* f;

    f = fopen(filename, "wb+");
    fwrite(buffer, 1, buffer_size, f);
    fclose(f);
}