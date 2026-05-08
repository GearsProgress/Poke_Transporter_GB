#include "FileContainerChunkWriter.h"

#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>

#include <sys/stat.h>

#define FILE_RECORD_NAME_LENGTH 16
#define LINE_BUFFER_SIZE 2048
#define PATH_BUFFER_SIZE 4096
#define DEFAULT_CHUNK_SIZE 4096


typedef struct
{
    uint16_t offset;
    uint16_t size;
    char altName[FILE_RECORD_NAME_LENGTH];
    char path[PATH_BUFFER_SIZE];
} FileRecord;

typedef struct
{
    uint8_t hasNames;
    uint16_t chunkSize;
    std::vector<FileRecord> entries;
} ContainerMetadata;

static void printUsage()
{
    printf("Usage: make-file-container [-n] <path/to/file.containerdef> <output folder>\n\n");
    printf("Definition syntax:\n  <filename>[:<optional alternative name>]\n\n");
    printf("Flags:\n  -n    Store filenames in the container\n");
}

/**
 * @brief This function parses a single line from the definition file, extracting the file path and optional alternative name.
 */
static bool parseDefinitionLine(char *line, char **path, char **altName)
{
    char *colon = strchr(line, ':');

    if(colon != NULL)
{
        *colon = '\0';
        *altName = colon + 1;
        if((*altName)[0] == '\0')
        {
            *altName = NULL;
        }
    }
    else
    {
        *altName = NULL;
    }

    *path = line;
    return (*path)[0] != '\0';
}

/**
 * @brief This function determines the file size
 */
static bool determineFileSize(const char *path, uint16_t &outSize)
{
    struct stat st;

    if(stat(path, &st) != 0)
    {
        fprintf(stderr, "Failed to stat input file: %s\n", path);
        return false;
    }

    if(!S_ISREG(st.st_mode))
    {
        fprintf(stderr, "Input path is not a regular file: %s\n", path);
        return false;
    }

    if(st.st_size < 0 || st.st_size > 0xFFFF)
    {
        fprintf(stderr, "Input file too large for uint16 size field: %s\n", path);
        return false;
    }

    outSize = static_cast<uint16_t>(st.st_size);
    return true;
}

/**
 * @brief This function parses the container definition file.
 */
static bool parseDefinition(const char *defPath, ContainerMetadata &meta)
{
    FILE *f = fopen(defPath, "rb");
    char line[LINE_BUFFER_SIZE];
    char *filePath;
    char *altName;
    size_t line_no = 0;

    if(f == NULL)
    {
        fprintf(stderr, "Failed to open container definition: %s\n", defPath);
        return false;
    }

    while (fgets(line, sizeof(line), f) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0';
        FileRecord entry;

        ++line_no;
        if(line[0] == '\0' || line[0] == '#')
        {
            continue;
        }

        if(!parseDefinitionLine(line, &filePath, &altName))
        {
            fprintf(stderr, "Invalid entry at line %zu\n", line_no);
            fclose(f);
            return false;
        }

        if(meta.entries.size() >= 0xFF)
        {
            fprintf(stderr, "Too many files (max 255).\n");
            fclose(f);
            return false;
        }

        memset(&entry, 0, sizeof(entry));

        if(!determineFileSize(filePath, entry.size))
        {
            fclose(f);
            return false;
        }

        strncpy(entry.path, filePath, PATH_BUFFER_SIZE - 1);
        entry.path[PATH_BUFFER_SIZE - 1] = '\0';

        if(altName != NULL)
        {
            strncpy(entry.altName, altName, FILE_RECORD_NAME_LENGTH - 1);
            entry.altName[FILE_RECORD_NAME_LENGTH - 1] = '\0';
        }

        meta.entries.push_back(entry);
    }

    fclose(f);

    if(meta.entries.empty())
    {
        fprintf(stderr, "No files defined in: %s\n", defPath);
        return false;
    }

    return true;
}

/**
 * @brief This function reads a file into memory, allocating a buffer and returning its size. The caller is responsible for freeing the buffer.
 */
static void readFileIntoMemory(const char *path, uint8_t **outBuffer, uint16_t &outSize)
{
    FILE *f = fopen(path, "rb");
    size_t read_size;

    if(f == NULL)
    {
        fprintf(stderr, "Failed to open input file: %s\n", path);
        return;
    }

    if(!determineFileSize(path, outSize))
    {
        fclose(f);
        return;
    }

    *outBuffer = static_cast<uint8_t *>(std::malloc(outSize));

    read_size = fread(*outBuffer, 1, outSize, f);
    fclose(f);

    if(read_size != outSize)
    {
        fprintf(stderr, "Failed to read entire file into memory: %s\n", path);
        free(*outBuffer);
        *outBuffer = NULL;
        return;
    }
}

static void writeHeader(FileContainerChunkWriter &writer, const ContainerMetadata &meta)
{

    const uint8_t num_files = static_cast<uint8_t>(meta.entries.size());

    writer.writeUint8(num_files);
    writer.writeUint8(meta.hasNames);
    writer.writeUint16(meta.chunkSize);
}

static void writeIndex(FileContainerChunkWriter &writer, ContainerMetadata &meta)
{
    // first we need to determine where the actual file data starts.
    // That is, after the header, index entries and optional names.
    constexpr uint16_t headerSize = 4;
    uint16_t current_offset = headerSize + sizeof(uint16_t) * meta.entries.size();

    if(meta.hasNames)
    {
        current_offset += FILE_RECORD_NAME_LENGTH * meta.entries.size();
    }

    for(auto &entry : meta.entries)
    {
        entry.offset = current_offset;
        current_offset += entry.size;

        writer.writeUint16(entry.offset);
    }
}

static void writeNames(FileContainerChunkWriter &writer, const ContainerMetadata &meta)
{
    char nameBuffer[FILE_RECORD_NAME_LENGTH];
    char pathBasename[PATH_BUFFER_SIZE];

    for(auto &entry : meta.entries)
    {
        strncpy(pathBasename, entry.path, PATH_BUFFER_SIZE - 1);
        pathBasename[PATH_BUFFER_SIZE - 1] = '\0';
        // Not using FILE_RECORD_NAME_LENGTH - 1 is intentional here. I want to be able to use the last character.
        // When reading the data, we just have to allocate an extra byte and set it to 0 to ensure null termination, so we can safely use the entire buffer for the name.
        strncpy(nameBuffer, entry.altName[0] != '\0' ? entry.altName : basename(pathBasename), FILE_RECORD_NAME_LENGTH);
        writer.write(reinterpret_cast<uint8_t*>(nameBuffer), FILE_RECORD_NAME_LENGTH);
    }
}

static void writeFiles(FileContainerChunkWriter &writer, ContainerMetadata &meta)
{
    uint8_t *fileBuffer = NULL;
    uint16_t fileSize;

    for(auto &entry : meta.entries)
    {
        readFileIntoMemory(entry.path, &fileBuffer, fileSize);
        if(!fileBuffer)
        {
            fprintf(stderr, "Failed to read file into memory: %s\n", entry.path);
            return;
        }

        writer.write(fileBuffer, fileSize);
        free(fileBuffer);
    }
}

static void determineContainerBaseName(const char *containerDefPath, char *outNameBuffer)
{
    char pathBuffer[PATH_BUFFER_SIZE];
    strncpy(pathBuffer, containerDefPath, PATH_BUFFER_SIZE);
    pathBuffer[PATH_BUFFER_SIZE - 1] = '\0';

    char *basenameStr = basename(pathBuffer);
    char *dot = strrchr(basenameStr, '.');
    // We don't want the extension in the chunk file names, so we terminate the string at the last dot if it exists.
    // If there is no dot, we just use the entire basename.
    if(dot)
    {
        *dot = '\0';
    }
    strncpy(outNameBuffer, basenameStr, PATH_BUFFER_SIZE);
}

static bool writeContainer(ContainerMetadata &meta, const char *outPath, const char *containerDefPath)
{
    char nameBuffer[PATH_BUFFER_SIZE];
    determineContainerBaseName(containerDefPath, nameBuffer);

    FileContainerChunkWriter writer(outPath, nameBuffer, meta.chunkSize);

    writeHeader(writer, meta);
    writeIndex(writer, meta);

    if(meta.hasNames)
    {
        writeNames(writer, meta);
    }

    writeFiles(writer, meta);

    return true;
}

static bool parseArgs(int argc, char **argv, bool *storeNames, const char **defPath, const char **outPath)
{
    if(argc == 3)
    {
        *storeNames = false;
        *defPath = argv[1];
        *outPath = argv[2];
        return true;
    }

    if(argc == 4 && std::strcmp(argv[1], "-n") == 0)
    {
        *storeNames = true;
        *defPath = argv[2];
        *outPath = argv[3];
        return true;
    }

    return false;
}

int main(int argc, char *argv[])
{
    ContainerMetadata meta;
    bool storeNames = false;
    const char *defPath = NULL;
    const char *outPath = NULL;
    int rc = 1;

    if(!parseArgs(argc, argv, &storeNames, &defPath, &outPath))
    {
        printUsage();
        return rc;
    }

    meta.hasNames = storeNames ? 1 : 0;
    meta.chunkSize = DEFAULT_CHUNK_SIZE;

    if(!parseDefinition(defPath, meta))
    {
        return rc;
    }

    if(!writeContainer(meta, outPath, defPath))
    {
        fprintf(stderr, "Failed to write output container: %s\n", outPath);
    }
    else
    {
        printf("Built container: files=%zu, hasNames=%u\n", meta.entries.size(), storeNames ? 1u : 0u);
        rc = 0;
    }

    return rc;
}
