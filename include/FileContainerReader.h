#ifndef _FILECONTAINERREADER_H
#define _FILECONTAINERREADER_H

#include "typeDefs.h"

#define FILE_NAME_LENGTH 16

/**
 * @brief This class provides functionality to read files from the file container format
 * created by the make-file-container tool.
 *
 * This format consists of multiple compressed chunks.
 *
 * It is done this way to keep the decompression buffer small (because we can't afford to consume too much IWRAM)
 * but still allow for large file containers and bundling files together. (which you might want to do to improve compression ratios)
 * The chunk size can be configured when creating the file container, and the
 * FileContainerReader will read and decompress chunks on demand when seeking or reading data.
 */
class FileContainerReader
{
public:
    FileContainerReader(const u8 **chunkList, u32 chunkCount, u32 chunkSize = 4096);
    ~FileContainerReader();

    /**
     * @brief This function initializes the FileContainerReader. It should be called before any other function is used.
     * The reason for this initialization step is to give you control over the moment when the first chunk is decompressed.
     * This can be useful if you want to perform some setup or checks before the decompression process begins. By calling init() explicitly, you can ensure that the FileContainerReader is ready to handle file reading operations at the appropriate time in your application.
     *
     * Note: because of this, we also only pass the decompression buffer here
     * If the decompression buffer is not large enough to hold the chunks,
     * the function will return false and the FileContainerReader will not be initialized. In this case, you should provide a larger decompression buffer and call init() again.
     *
     * If it DOES return true, please note that the FileContainerReader will keep using the decompressionBuffer_ until
     * it gets destroyed.
     */
    bool init(u8 *decompressionBuffer, u32 decompressionBufferSize);

    /**
     * @brief IF the file container stores the file names,
     * this function returns a pointer to the file name of the file at the given index.
     * Otherwise, it returns nullptr.
     */
    const char* getFileName(u32 fileIndex);

    /**
     * @brief This function returns the size of the file at the given index.
     */
    u32 getFileSize(u32 fileIndex) const;

    /**
     * @brief This function seeks to the beginning of the file at the given index.
     */
    void seekToFile(u32 fileIndex);

    /**
     * @brief Read data from the current position in the file container into the provided buffer.
     */
    void read(u8 *buffer, u32 size);
protected:
private:
    /**
     * @brief This function calculates the file offset for the specified file index
     * The file offset is determined by reading the file index (which contains the file entry sizes)
     * and summing up the sizes of all previous entries + header size + optional name table size
     * (if names are stored).
     */
    u32 getFileOffset(u32 fileIndex) const;

    /**
     * @brief This function seeks to the specified absolute offset in the file container data.
     * Absolute offset refers to an offset across the file container chunks.
     */
    void seek(u32 offset);

    /**
     * @brief This function just uncompresses the chunk at the specified index
     * into decompressionBuffer_.
     */
    void uncompressChunk(u32 chunkIndex);

    char fileNameBuffer_[FILE_NAME_LENGTH + 1];
    u8 *decompressionBuffer_;
    const u8 **chunkList_;
    u32 chunkCount_;
    u32 chunkSize_;
    u16 *fileIndex_;
    u32 curChunkIndex_;
    u32 curPos_;
    u32 fileCount_;
    bool hasNames_;
};

#endif