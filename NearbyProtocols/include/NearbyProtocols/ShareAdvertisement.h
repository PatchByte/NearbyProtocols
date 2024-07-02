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

struct nearby_share_advertisement
{
    enum nearby_share_advertisement_version version;

    union
    {
        bool has_name;
        bool is_visible;
    };
    enum nearby_share_target_type device_type;
    unsigned char                 salt[NEARBY_SHARE_ADVERTISEMENT_SALT_SIZE];
    unsigned char                 metadata_encryption_key_hash_byte[NEARBY_SHARE_ADVERTISEMENT_METADATA_ENCRYTION_KEY_HASH_BYTE_SIZE];
    unsigned char                 name_length;
    char*                         name_data;
};

const char* nearby_share_advertisement_version_to_string(enum nearby_share_advertisement_version version);
void        nearby_share_advertisement_from_endpoint_info(struct nearby_share_advertisement* advertisement, struct nearby_utils_buffer* buffer);
void        nearby_share_advertisement_from_endpoint_info_cleanup(struct nearby_share_advertisement* advertisement);

#endif // !NEARBYPROTOCOLS_SHAREADVERTISEMENT_H