#include "NearbyProtocols/ShareAdvertisement.h"
#include "NearbyUtils/Buffer.h"
#include <stdlib.h>
#include <stdio.h>

#define NEARBY_SHARE_ADVERTISEMENT_VERSION_BITMASK 0b111
#define NEARBY_SHARE_ADVERTISEMENT_VISIBLITY_BITMASK 0b1
#define NEARBY_SHARE_ADVERTISEMENT_DEVICE_TYPE_BITMASK 0b111
#define NEARBY_SHARE_ADVERTISEMENT_TLV_MINIMUM_LENGTH 2

const char* nearby_share_advertisement_version_to_string(enum nearby_share_advertisement_version version)
{
    switch (version)
    {
    case nearby_share_advertisement_version_v1:
        return "v1";
    case nearby_share_advertisement_version_v2:
        return "v2";
    default:
        return "unknown";
    }
}

const char* nearby_share_blocked_vendor_id_to_string(enum nearby_share_blocked_vendor_id vendor_id)
{
    switch (vendor_id)
    {
    case nearby_share_blocked_vendor_id_none:
        return "vendor_id_none";
    case nearby_share_blocked_vendor_id_samsung:
        return "vendor_id_samsung";
    default:
        return "unknown";
    }
}

bool nearby_share_advertisement_from_endpoint_info(struct nearby_share_advertisement* advertisement, struct nearby_utils_buffer* buffer)
{
    unsigned char first_byte = nearby_utils_buffer_read_u8(buffer);

    advertisement->version = (first_byte >> 5) & NEARBY_SHARE_ADVERTISEMENT_VERSION_BITMASK;
    advertisement->is_visible = ((first_byte >> 4) & NEARBY_SHARE_ADVERTISEMENT_VISIBLITY_BITMASK) == 0;
    advertisement->device_type = ((first_byte >> 1) & NEARBY_SHARE_ADVERTISEMENT_DEVICE_TYPE_BITMASK);

    nearby_utils_buffer_read_bytes(buffer, advertisement->salt, sizeof(advertisement->salt));

    nearby_utils_buffer_read_bytes(buffer, advertisement->metadata_encryption_key_hash_byte, sizeof(advertisement->metadata_encryption_key_hash_byte));

    if (advertisement->has_name == true)
    {
        advertisement->name_length = nearby_utils_buffer_read_u8(buffer);
        advertisement->name_data = malloc(advertisement->name_length);

        nearby_utils_buffer_read_bytes(buffer, advertisement->name_data, advertisement->name_length);
    }
    else
    {
        advertisement->name_length = 0;
        advertisement->name_data = NULL;
    }

    while (buffer->buffer_left_bytes >= NEARBY_SHARE_ADVERTISEMENT_TLV_MINIMUM_LENGTH)
    {
        enum nearby_share_tlv_types current_tlv_type = nearby_utils_buffer_read_u8(buffer);
        unsigned char               current_tlv_length = nearby_utils_buffer_read_u8(buffer);

        switch (current_tlv_type)
        {
        case nearby_share_tlv_types_qr_code:
        {
            advertisement->is_qr_code_present = true;
            advertisement->qr_code_length = current_tlv_length;

            nearby_utils_buffer_skip_bytes(buffer, current_tlv_length);

            break;
        }
        case nearby_share_tlv_types_vendor_id:
        {
            if (current_tlv_length != 1)
            {
                return false;
            }

            advertisement->is_vendor_id_present = true;
            advertisement->vendor_id = nearby_utils_buffer_read_u8(buffer);

            break;
        }
        default:
        {
            nearby_utils_buffer_skip_bytes(buffer, current_tlv_length);

            break;
        }
        }
    }
}

void nearby_share_advertisement_from_endpoint_info_cleanup(struct nearby_share_advertisement* advertisement)
{
    if (advertisement->name_data)
    {
        free(advertisement->name_data);
        advertisement->name_data = NULL;
    }
}