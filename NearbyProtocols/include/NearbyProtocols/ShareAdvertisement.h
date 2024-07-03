#ifndef NEARBYPROTOCOLS_SHAREADVERTISEMENT_H
#define NEARBYPROTOCOLS_SHAREADVERTISEMENT_H

#include "NearbyProtocols/ShareEnums.h"
#include "NearbyUtils/Buffer.h"

#define NEARBY_SHARE_ADVERTISEMENT_SALT_SIZE 2
#define NEARBY_SHARE_ADVERTISEMENT_METADATA_ENCRYTION_KEY_HASH_BYTE_SIZE 14

enum nearby_share_advertisement_version
{
    nearby_share_advertisement_version_v1 = 0,
    nearby_share_advertisement_version_v2 = 1
};

enum nearby_share_tlv_types
{
    nearby_share_tlv_types_unknown = 0,
    nearby_share_tlv_types_qr_code = 1,
    nearby_share_tlv_types_vendor_id = 2
};

enum nearby_share_blocked_vendor_id
{
    nearby_share_blocked_vendor_id_none = 0,
    nearby_share_blocked_vendor_id_samsung = 1
};

struct nearby_share_advertisement
{
    enum nearby_share_advertisement_version version;

    union
    {
        bool has_name;
        bool is_visible;
    };

    enum nearby_share_target_type       device_type;
    unsigned char                       salt[NEARBY_SHARE_ADVERTISEMENT_SALT_SIZE];
    unsigned char                       metadata_encryption_key_hash_byte[NEARBY_SHARE_ADVERTISEMENT_METADATA_ENCRYTION_KEY_HASH_BYTE_SIZE];
    unsigned char                       name_length;
    char*                               name_data;
    bool                                is_vendor_id_present;
    enum nearby_share_blocked_vendor_id vendor_id;
    bool                                is_qr_code_present;
    unsigned char                       qr_code_length;
};

const char* nearby_share_advertisement_version_to_string(enum nearby_share_advertisement_version version);
const char* nearby_share_blocked_vendor_id_to_string(enum nearby_share_blocked_vendor_id vendor_id);

bool nearby_share_advertisement_from_endpoint_info(struct nearby_share_advertisement* advertisement, struct nearby_utils_buffer* buffer);
void nearby_share_advertisement_from_endpoint_info_cleanup(struct nearby_share_advertisement* advertisement);

#endif // !NEARBYPROTOCOLS_SHAREADVERTISEMENT_H