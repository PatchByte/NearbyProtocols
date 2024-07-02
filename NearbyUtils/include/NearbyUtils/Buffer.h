#ifndef NEARBYUTILS_BUFFER_H
#define NEARBYUTILS_BUFFER_H

#include <stdbool.h>

struct nearby_utils_buffer
{
    void* buffer_data;
    unsigned long long buffer_max_size;
    long long buffer_left_bytes;
    unsigned long long buffer_index;
    bool has_error_occurred;
    const char* error_message;
};

void nearby_utils_buffer_initialize(struct nearby_utils_buffer* buffer_reader, void* buffer_data, unsigned long long buffer_size);

bool nearby_utils_buffer_read_bytes(struct nearby_utils_buffer* buffer_reader, void* buffer_data, unsigned long long buffer_size);

unsigned char nearby_utils_buffer_read_u8(struct nearby_utils_buffer* buffer_reader);
unsigned short nearby_utils_buffer_read_u16(struct nearby_utils_buffer* buffer_reader);
unsigned int nearby_utils_buffer_read_u32(struct nearby_utils_buffer* buffer_reader);
unsigned long long nearby_utils_buffer_read_u64(struct nearby_utils_buffer* buffer_reader);

signed char nearby_utils_buffer_read_s8(struct nearby_utils_buffer* buffer_reader);
signed short nearby_utils_buffer_read_s16(struct nearby_utils_buffer* buffer_reader);
signed int nearby_utils_buffer_read_s32(struct nearby_utils_buffer* buffer_reader);
signed long long nearby_utils_buffer_read_s64(struct nearby_utils_buffer* buffer_reader);

#endif // !NEARBYUTILS_BUFFER_H