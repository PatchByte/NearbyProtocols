#include "NearbyProtocols/ConnectionAdvertisement.h"
#include "NearbyUtils/Buffer.h"
#include <stdio.h>
#include <stdlib.h>

#define NEARBY_CONNECTION_ADVERTISEMENT_VERSION_BITMASK 0xE0
#define NEARBY_CONNECTION_ADVERTISEMENT_PCP_BITMASK 0x1F

const char* nearby_connection_advertisement_ble_version_to_string(enum nearby_connection_advertisement_ble_version version)
{
    switch (version)
    {
    case nearby_connection_advertisement_ble_version_undefined:
        return "undefined";
    case nearby_connection_advertisement_ble_version_v1:
        return "v1";
    default:
        return "unknown";
    }
}

size_t nearby_connection_advertisement_ble_serialize_get_required_data_length(struct nearby_connection_advertisement_ble* advertisement, bool is_fast_advertisement)
{
    size_t required_data_length = 0;

    // Version and PCP
    required_data_length += 1;

    if (is_fast_advertisement == false)
    {
        required_data_length += sizeof(advertisement->service_id_hash);
    }

    required_data_length += sizeof(advertisement->endpoint_id);

    // Endpoint-Info-Length
    required_data_length += 1;
    required_data_length += advertisement->endpoint_info_length;

    if (is_fast_advertisement == false)
    {
        required_data_length += sizeof(advertisement->bluetooth_mac_address);
    }

    if (advertisement->uwb_address_length > 0)
    {
        // UWB-Address-Length
        required_data_length += 1;
        required_data_length += advertisement->uwb_address_length;

        required_data_length += advertisement->has_extra_field == true ? 1 : 0;
    }

    return required_data_length;
}

void nearby_connection_advertisement_ble_serialize(struct nearby_connection_advertisement_ble* advertisement, struct nearby_utils_buffer* buffer, bool is_fast_advertisement)
{
    unsigned char version_and_pcp_byte = 0;

    version_and_pcp_byte |= (advertisement->version << 5) & NEARBY_CONNECTION_ADVERTISEMENT_VERSION_BITMASK;
    version_and_pcp_byte |= (advertisement->pcp << 0) & NEARBY_CONNECTION_ADVERTISEMENT_PCP_BITMASK;

    nearby_utils_buffer_write_u8(buffer, version_and_pcp_byte);

    if(is_fast_advertisement == false)
    {
        nearby_utils_buffer_write_bytes(buffer, advertisement->service_id_hash, sizeof(advertisement->service_id_hash));
    }

    nearby_utils_buffer_write_bytes(buffer, advertisement->endpoint_id, sizeof(advertisement->endpoint_id));

    nearby_utils_buffer_write_u8(buffer, advertisement->endpoint_info_length);

    if(advertisement->endpoint_info_length > 0)
    {
        nearby_utils_buffer_write_bytes(buffer, advertisement->endpoint_info_buffer, advertisement->endpoint_info_length);
    }

    if (is_fast_advertisement == false)
    {
        nearby_utils_buffer_write_bytes(buffer, advertisement->bluetooth_mac_address, sizeof(advertisement->bluetooth_mac_address));
    }

    if(advertisement->uwb_address_length > 0)
    {
        nearby_utils_buffer_write_u8(buffer, advertisement->uwb_address_length);
        nearby_utils_buffer_write_bytes(buffer, advertisement->uwb_address_buffer, advertisement->uwb_address_length);

        if(advertisement->has_extra_field)
        {
            nearby_utils_buffer_write_u8(buffer, advertisement->extra_field);
        }
    }
}

void nearby_connection_advertisement_ble_deserialize(struct nearby_connection_advertisement_ble* advertisement, struct nearby_utils_buffer* buffer, bool is_fast_advertisement)
{
    unsigned char version_and_pcp_byte = nearby_utils_buffer_read_u8(buffer);

    advertisement->version = (version_and_pcp_byte & NEARBY_CONNECTION_ADVERTISEMENT_VERSION_BITMASK) >> 5;
    advertisement->pcp = (version_and_pcp_byte & NEARBY_CONNECTION_ADVERTISEMENT_PCP_BITMASK);

    if (is_fast_advertisement == false)
    {
        nearby_utils_buffer_read_bytes(buffer, advertisement->service_id_hash, sizeof(advertisement->service_id_hash));
    }

    nearby_utils_buffer_read_bytes(buffer, advertisement->endpoint_id, sizeof(advertisement->endpoint_id));

    advertisement->endpoint_info_length = nearby_utils_buffer_read_u8(buffer);

    if (advertisement->endpoint_info_length > 0)
    {
        advertisement->endpoint_info_buffer = malloc(advertisement->endpoint_info_length);
        nearby_utils_buffer_read_bytes(buffer, advertisement->endpoint_info_buffer, advertisement->endpoint_info_length);
    }
    else
    {
        advertisement->endpoint_info_buffer = NULL;
    }

    if (is_fast_advertisement == false)
    {
        nearby_utils_buffer_read_bytes(buffer, advertisement->bluetooth_mac_address, sizeof(advertisement->bluetooth_mac_address));
    }

    if (buffer->buffer_left_bytes >= 1)
    {
        advertisement->uwb_address_length = nearby_utils_buffer_read_u8(buffer);

        if (advertisement->uwb_address_length > 0)
        {
            advertisement->uwb_address_buffer = malloc(advertisement->uwb_address_length);
            nearby_utils_buffer_read_bytes(buffer, advertisement->uwb_address_buffer, advertisement->uwb_address_length);
        }
        else
        {
            advertisement->uwb_address_buffer = NULL;
        }

        if (buffer->buffer_left_bytes >= 1)
        {
            advertisement->extra_field = nearby_utils_buffer_read_u8(buffer);
            advertisement->extra_field = true;
        }
        else
        {
            advertisement->has_extra_field = false;
        }
    }
    else
    {
        advertisement->uwb_address_length = 0;
        advertisement->uwb_address_buffer = NULL;
        advertisement->has_extra_field = true;
    }
}

void nearby_connection_advertisement_ble_deserialize_cleanup(struct nearby_connection_advertisement_ble* advertisement)
{
    if (advertisement->endpoint_info_buffer)
    {
        free(advertisement->endpoint_info_buffer);
        advertisement->endpoint_info_buffer = NULL;
    }

    if (advertisement->uwb_address_buffer)
    {
        free(advertisement->uwb_address_buffer);
        advertisement->uwb_address_buffer = NULL;
    }
}
