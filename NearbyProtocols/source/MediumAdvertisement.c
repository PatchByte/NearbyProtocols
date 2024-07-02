#include "NearbyProtocols/MediumAdvertisement.h"
#include "NearbyUtils/Buffer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEARBY_MEDIUM_ADVERTISEMENT_VERSION_BITMASK 0xE0
#define NEARBY_MEDIUM_ADVERTISEMENT_SOCKET_VERSION_BITMASK 0x1C
#define NEARBY_MEDIUM_ADVERTISEMENT_FAST_ADVERTISEMENT_FLAG_BITMASK 0x02

const char* nearby_medium_advertisement_ble_version_to_string(enum nearby_medium_advertisement_ble_version version)
{
    switch (version)
    {
    case nearby_advertisement_version_undefined:
        return "undefined";
    case nearby_advertisement_version_v1:
        return "v1";
    case nearby_advertisement_version_v2:
        return "v2";
    }
}

size_t nearby_medium_advertisement_ble_serialize_get_required_data_length(struct nearby_medium_advertisement_ble* advertisement)
{
    size_t required_data_length = 0;

    required_data_length += 1; // version_byte
    
    if (advertisement->is_fast_advertisement == false)
    {
        required_data_length += sizeof(advertisement->service_data_hash); // explains itself
    }

    required_data_length += advertisement->is_fast_advertisement == true ? 1 : 4;
    required_data_length += advertisement->data_size;
    
    if(advertisement->is_device_token_present == true)
    {
        required_data_length += sizeof(advertisement->device_token);
    }

    return required_data_length;
}

bool nearby_medium_advertisement_ble_deserialize(struct nearby_medium_advertisement_ble* advertisement, struct nearby_utils_buffer* buffer)
{
    unsigned char version_byte = nearby_utils_buffer_read_u8(buffer);

    advertisement->version = (version_byte & NEARBY_MEDIUM_ADVERTISEMENT_VERSION_BITMASK) >> 5;
    advertisement->socket_version = (version_byte & NEARBY_MEDIUM_ADVERTISEMENT_SOCKET_VERSION_BITMASK) >> 2;
    advertisement->is_fast_advertisement = (version_byte & NEARBY_MEDIUM_ADVERTISEMENT_FAST_ADVERTISEMENT_FLAG_BITMASK) >> 1;

    if (advertisement->is_fast_advertisement == false)
    {
        nearby_utils_buffer_read_bytes(buffer, advertisement->service_data_hash, sizeof(advertisement->service_data_hash));
    }

    if (advertisement->is_fast_advertisement == true)
    {
        advertisement->data_size = nearby_utils_buffer_read_u8(buffer);
    }
    else
    {
        advertisement->data_size = nearby_utils_buffer_read_u32(buffer);
    }

    if (advertisement->data_size > 0)
    {
        advertisement->data = malloc(advertisement->data_size);
        nearby_utils_buffer_read_bytes(buffer, advertisement->data, advertisement->data_size);
    }

    if ((buffer->buffer_left_bytes - (long long)sizeof(advertisement->device_token)) >= 0)
    {
        advertisement->is_device_token_present = true;
        nearby_utils_buffer_read_bytes(buffer, advertisement->device_token, sizeof(advertisement->device_token));
    }
    else
    {
        advertisement->is_device_token_present = false;
        return true;
    }

    return true;
}

void nearby_medium_advertisement_ble_deserialize_cleanup(struct nearby_medium_advertisement_ble* advertisement)
{
    if (advertisement->data)
    {
        free(advertisement->data);
        advertisement->data = NULL;
    }
}