#include "Gen3CartridgeSaveReader.h"
#include "libraries/Pokemon-Gen3-to-Gen-X/include/save.h"
#include "flash_mem.h"
#include <cstring>

#define HALL_OF_FAME 0x01C000

Gen3CartridgeSaveReader::Gen3CartridgeSaveReader(u8 *sector_buffer)
    : sector_start_(0)
    , sector_buffer_(sector_buffer)
    , cur_(sector_buffer)
    , dirty_(false)
{
}

Gen3CartridgeSaveReader::~Gen3CartridgeSaveReader()
{
}

void Gen3CartridgeSaveReader::read(u8 *buffer, u32 size)
{
    memcpy(buffer, cur_, size);
    cur_ += size;
}

void Gen3CartridgeSaveReader::readUint8(u8& outByte)
{
    outByte = *cur_;
    ++cur_;
}

void Gen3CartridgeSaveReader::readUint16(u16& outWord, Endianness fieldEndianness)
{
    // Right now we only support little endian (no need for big endian thus far)
    outWord = *((u16*)cur_);
    cur_ += sizeof(u16);
}

void Gen3CartridgeSaveReader::readUint32(u32& outDWord, Endianness fieldEndianness)
{
    // Right now we only support little endian (no need for big endian thus far)
    outDWord = *((u32*)cur_);
    cur_ += sizeof(u32);
}

void Gen3CartridgeSaveReader::write(const u8 *buffer, u32 size)
{
    memcpy(cur_, buffer, size);
    cur_ += size;
    dirty_ = true;

}

void Gen3CartridgeSaveReader::writeUint8(u8 value)
{
    *cur_ = value;
    ++cur_;
    dirty_ = true;
}

void Gen3CartridgeSaveReader::writeUint16(u16 value, Endianness fieldEndianness)
{
    // Right now we only support little endian (no need for big endian thus far)
    *((u16*)cur_) = value;
    cur_ += sizeof(u16);
    dirty_ = true;
}

void Gen3CartridgeSaveReader::writeUint32(u32 value, Endianness fieldEndianness)
{
    // Right now we only support little endian (no need for big endian thus far)
    *((u32*)cur_) = value;
    cur_ += sizeof(u32);
    dirty_ = true;
}

void Gen3CartridgeSaveReader::seek(u32 offset)
{
    const uintptr_t sector_start = offset / SECTOR_SIZE;
    if(sector_start != sector_start_)
    {
        // write any pending changes.
        flush();
        sector_start_ = sector_start;
        copy_save_to_ram(sector_start, sector_buffer_, SECTOR_SIZE);
    }

    cur_ = sector_buffer_ + (offset - sector_start);
}

void Gen3CartridgeSaveReader::advance(u32 numBytes)
{
    u8 *sector_end = sector_buffer_ + SECTOR_SIZE;
    cur_ += numBytes;
    if (cur_ > sector_end)
    {
        cur_ = sector_end;
    }
}

void Gen3CartridgeSaveReader::rewind(u32 numBytes)
{
    if(static_cast<uintptr_t>(cur_ - sector_buffer_) >= numBytes)
    {
        cur_ -= numBytes;
    }
    else
    {
        cur_ = sector_buffer_;
    }
}

void Gen3CartridgeSaveReader::flush()
{
    if(!dirty_)
    {
        return;
    }

    update_memory_buffer_checksum(sector_buffer_, (sector_start_ == HALL_OF_FAME));
    copy_ram_to_save(sector_buffer_, sector_start_, SECTOR_SIZE);
    dirty_ = false;
}