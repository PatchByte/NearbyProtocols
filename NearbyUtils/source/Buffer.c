#include "NearbyUtils/Buffer.h"

void nearby_utils_buffer_initialize(struct nearby_utils_buffer* buffer_reader, void* buffer_data, unsigned long long buffer_size)
{
    buffer_reader->buffer_data = buffer_data;
    buffer_reader->buffer_index = 0;
    buffer_reader->buffer_left_bytes = buffer_size;
    buffer_reader->buffer_max_size = buffer_size;
    buffer_reader->error_message = "";
    buffer_reader->has_error_occurred = false;
}

bool nearby_utils_buffer_read_bytes(struct nearby_utils_buffer* buffer_reader, void* buffer_data, unsigned long long buffer_size)
{
    if (buffer_reader->buffer_left_bytes <= 0)
    {
        buffer_reader->has_error_occurred = true;
        buffer_reader->error_message = "Reached end of buffer.";

        return false;
    }

    if (buffer_reader->buffer_left_bytes < (long long)buffer_size)
    {
        buffer_reader->has_error_occurred = true;
        buffer_reader->error_message = "Not enough bytes left to read.";

        return false;
    }

    buffer_reader->buffer_left_bytes -= (long long)buffer_size;

    for (unsigned long long i = 0; i < buffer_size; i++)
    {
        *((unsigned char*)buffer_data + i) = *((unsigned char*)buffer_reader->buffer_data + buffer_reader->buffer_index + i);
    }

    buffer_reader->buffer_index += buffer_size;

    return true;
}

// unsigned read

unsigned char nearby_utils_buffer_read_u8(struct nearby_utils_buffer* buffer_reader)
{
    unsigned char value = 0;
    nearby_utils_buffer_read_bytes(buffer_reader, &value, sizeof(value));
    return value;
}

unsigned short nearby_utils_buffer_read_u16(struct nearby_utils_buffer* buffer_reader)
{
    unsigned short value = 0;
    nearby_utils_buffer_read_bytes(buffer_reader, &value, sizeof(value));
    return value;
}

unsigned int nearby_utils_buffer_read_u32(struct nearby_utils_buffer* buffer_reader)
{
    unsigned int value = 0;
    nearby_utils_buffer_read_bytes(buffer_reader, &value, sizeof(value));
    return value;
}

unsigned long long nearby_utils_buffer_read_u64(struct nearby_utils_buffer* buffer_reader)
{
    unsigned long long value = 0;
    nearby_utils_buffer_read_bytes(buffer_reader, &value, sizeof(value));
    return value;
}

// signed read

signed char nearby_utils_buffer_read_s8(struct nearby_utils_buffer* buffer_reader)
{
    signed char value = 0;
    nearby_utils_buffer_read_bytes(buffer_reader, &value, sizeof(value));
    return value;
}

signed short nearby_utils_buffer_read_s16(struct nearby_utils_buffer* buffer_reader)
{
    signed short value = 0;
    nearby_utils_buffer_read_bytes(buffer_reader, &value, sizeof(value));
    return value;
}

signed int nearby_utils_buffer_read_s32(struct nearby_utils_buffer* buffer_reader)
{
    signed int value = 0;
    nearby_utils_buffer_read_bytes(buffer_reader, &value, sizeof(value));
    return value;
}

signed long long nearby_utils_buffer_read_s64(struct nearby_utils_buffer* buffer_reader)
{
    signed long long value = 0;
    nearby_utils_buffer_read_bytes(buffer_reader, &value, sizeof(value));
    return value;
}
