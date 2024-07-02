#ifndef NEARBYPROTOCOLS_ADVERTISEMENT_H
#define NEARBYPROTOCOLS_ADVERTISEMENT_H

#include "NearbyProtocols/Socket.h"
#include "NearbyUtils/Buffer.h"
#include <stdbool.h>
#include <stdlib.h>

#define NEARBY_SERVICE_ID_HASH_LENGTH 3

enum nearby_medium_advertisement_version
{
    nearby_advertisement_version_undefined = 0,
    nearby_advertisement_version_v1 = 1,
    nearby_advertisement_version_v2 = 2
};

struct nearby_medium_advertisement
{
    enum nearby_medium_advertisement_version version;
    enum nearby_socket_version        socket_version;
    bool                              is_fast_advertisement;
    unsigned char                     service_data_hash[3]; // If is_fast_advertisement there is no service_data_hash.
    int                               data_size;
    void*                             data;
    bool                              is_device_token_present;
    unsigned char                     device_token[2];
};

const char* nearby_medium_advertisement_version_to_string(enum nearby_medium_advertisement_version version);

size_t nearby_medium_advertisement_serialize_get_required_data_length(struct nearby_medium_advertisement* advertisement);
// TODO: void nearby_advertisement_serialize(struct nearby_advertisement* advertisement, unsigned char* buffer);
bool nearby_medium_advertisement_deserialize(struct nearby_medium_advertisement* advertisement, struct nearby_utils_buffer* buffer);
void nearby_medium_advertisement_deserialize_cleanup(struct nearby_medium_advertisement* advertisement);

bool nearby_medium_advertisement_is_valid(struct nearby_medium_advertisement* advertisement);

#endif // !NEARBYPROTOCOLS_ADVERTISEMENT_H