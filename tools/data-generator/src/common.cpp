#include "common.h"
#include "extern_pokemon_data.h"

#include <cstdio>
#include <cstring>
#include <filesystem>

// Data pulled from https://docs.google.com/spreadsheets/d/14LLs5lLqWasFcssBmJdGXjjYxARAJBa_QUOUhXZt4v8/edit

void writeTable(const char *input_path, const char *output_path, const char *filename, const char *buffer, size_t buffer_size)
{
    char full_output_path[4096];

    FILE *f;

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

        std::filesystem::file_time_type inf_time = std::filesystem::last_write_time(input_path);
        std::filesystem::file_time_type outf_time = std::filesystem::last_write_time(full_output_path);

        if (outf_time > inf_time)
        {
            //printf("File %s is newer than %s, skipping\n", full_output_path, input_path);
            printf("S");
            return;
        }
    }

    f = fopen(full_output_path, "wb+");
    fwrite(buffer, 1, buffer_size, f);
    fclose(f);
    printf("B");
}