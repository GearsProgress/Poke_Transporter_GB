#ifndef _PAYLOAD_FILE_READER_H
#define _PAYLOAD_FILE_READER_H

#include <cstdint>

class payload_file_reader {
public:
    payload_file_reader(const uint8_t *file_buffer, uint16_t buffer_size);

    bool read_payload(uint8_t *buffer, uint8_t language, uint8_t game_variant);
protected:
private:
    const uint8_t *file_buffer_;
    const uint8_t *file_buffer_end_;
};

#endif