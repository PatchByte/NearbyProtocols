#ifndef NEARBYPROTOCOLS_MEDIUMADVERTISEMENT_H
#define NEARBYPROTOCOLS_MEDIUMADVERTISEMENT_H

#include "NearbyProtocols/Socket.h"
#include "NearbyUtils/Buffer.h"
#include <stdbool.h>
#include <stdlib.h>

#define NEARBY_SERVICE_ID_HASH_LENGTH 3

enum nearby_medium_advertisement_ble_version
{
    nearby_advertisement_version_undefined = 0,
    nearby_advertisement_version_v1 = 1,
    nearby_advertisement_version_v2 = 2
};

struct nearby_medium_advertisement_ble
{
    enum nearby_medium_advertisement_ble_version version;
    enum nearby_socket_version                   socket_version;
    bool                                         is_fast_advertisement;
    unsigned char                                service_data_hash[3]; // If is_fast_advertisement there is no service_data_hash.
    int                                          data_size;
    void*                                        data;
    bool                                         is_device_token_present;
    unsigned char                                device_token[2];
    bool                                         is_extra_field_present;
    unsigned char                                extra_field;
};

const char* nearby_medium_advertisement_ble_version_to_string(enum nearby_medium_advertisement_ble_version version);

size_t nearby_medium_advertisement_ble_serialize_get_required_data_length(struct nearby_medium_advertisement_ble* advertisement);
void nearby_medium_advertisement_serialize(struct nearby_medium_advertisement_ble* advertisement, struct nearby_utils_buffer* buffer);
bool nearby_medium_advertisement_ble_deserialize(struct nearby_medium_advertisement_ble* advertisement, struct nearby_utils_buffer* buffer);
void nearby_medium_advertisement_ble_deserialize_cleanup(struct nearby_medium_advertisement_ble* advertisement);

#endif // !NEARBYPROTOCOLS_ADVERTISEMENT_H