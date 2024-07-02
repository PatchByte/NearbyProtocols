#ifndef NEARBYPROTOCOLS_CONNECTIONADVERTISEMENT_H
#define NEARBYPROTOCOLS_CONNECTIONADVERTISEMENT_H

#include "NearbyProtocols/Pcp.h"
#include "NearbyUtils/Buffer.h"

#define NEARBY_CONNECTION_ADVERTISEMENT_BLE_SERVICE_ID_HASH_LENGTH 3
#define NEARBY_CONNECTION_ADVERTISEMENT_BLE_ENDPOINT_ID_LENGTH 4
#define NEARBY_CONNECTION_ADVERTISEMENT_BLE_BLUETOOTH_MAC_LENGTH 6

enum nearby_connection_advertisement_ble_version
{
    nearby_connection_advertisement_ble_version_undefined = 0,
    nearby_connection_advertisement_ble_version_v1 = 1
};

struct nearby_connection_advertisement_ble
{
    enum nearby_connection_advertisement_ble_version version;
    enum nearby_protocols_pcp                        pcp;
    unsigned char                                    service_id_hash[NEARBY_CONNECTION_ADVERTISEMENT_BLE_SERVICE_ID_HASH_LENGTH];
    char                                             endpoint_id[NEARBY_CONNECTION_ADVERTISEMENT_BLE_ENDPOINT_ID_LENGTH];
    unsigned char                                    endpoint_info_length;
    unsigned char*                                   endpoint_info_buffer;
    unsigned char                                    bluetooth_mac_address[NEARBY_CONNECTION_ADVERTISEMENT_BLE_BLUETOOTH_MAC_LENGTH];
    unsigned char                                    uwb_address_length;
    unsigned char*                                   uwb_address_buffer;
    unsigned char                                    extra_field; // Essentially just an web rtc connection state.
};

const char* nearby_connection_advertisement_ble_version_to_string(enum nearby_connection_advertisement_ble_version version);

void nearby_connection_advertisement_ble_deserialize(struct nearby_connection_advertisement_ble* advertisement, struct nearby_utils_buffer* buffer, bool is_fast_advertisement);
void nearby_connection_advertisement_ble_deserialize_cleanup(struct nearby_connection_advertisement_ble* advertisement);

#endif // !NEARBYPROTOCOLS_CONNECTIONADVERTISEMENT_H