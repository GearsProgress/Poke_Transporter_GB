#include "common.h"

#include <cstdio>
#include <cstring>

void writeTable(const char* output_path, const char *filename, const uint8_t *buffer, size_t buffer_size)
{
    char full_path[4096];
    FILE* f;

    if(output_path[0] != '\0')
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", output_path, filename);
    }
    else
    {
        strncpy(full_path, filename, sizeof(full_path));
    }

    f = fopen(full_path, "wb+");
    fwrite(buffer, 1, buffer_size, f);
    fclose(f);
}