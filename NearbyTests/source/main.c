#include "NearbyTests/main.h"
#include "NearbyProtocols/ConnectionAdvertisement.h"
#include "NearbyProtocols/MediumAdvertisement.h"
#include "NearbyProtocols/Pcp.h"
#include "NearbyProtocols/Socket.h"
#include "NearbyTests/utils.h"
#include "NearbyUtils/Buffer.h"
#include <stdio.h>

int main()
{
    const char* test_medium_data_serialized = "J\027#V7PU\0212S\030\206\360\314\242\347\220x\337\350\303\277\036\330\rE\313";

    struct nearby_medium_advertisement_ble advertisement_medium_deserialized = {};

    struct nearby_connection_advertisement_ble advertisement_connection_deserialized = {};

    {
        struct nearby_utils_buffer test_medium_data_buffer = {};

        nearby_utils_buffer_initialize(&test_medium_data_buffer, (void*)test_medium_data_serialized, 27);

        if (nearby_medium_advertisement_ble_deserialize(&advertisement_medium_deserialized, &test_medium_data_buffer) == false)
        {
            printf("Failed to deserialize!\n");
            return -1;
        }

        printf("Test Advertisement Packet Parsed:\n");
        printf(" Version: %s\n", nearby_medium_advertisement_ble_version_to_string(advertisement_medium_deserialized.version));
        printf(" Socket Version: %s\n", nearby_socket_version_to_string(advertisement_medium_deserialized.socket_version));
        printf(" Is Fast Advertisement: %s\n", advertisement_medium_deserialized.is_fast_advertisement == true ? "Yes" : "No");
        printf(" Service Hash:\n");
        print_bytes_as_hex(advertisement_medium_deserialized.service_data_hash, sizeof(advertisement_medium_deserialized.service_data_hash), 2);
        printf(" Data Size: 0x%x\n", advertisement_medium_deserialized.data_size);
        printf(" Data:\n");
        print_bytes_as_hex(advertisement_medium_deserialized.data, advertisement_medium_deserialized.data_size, 2);

        printf(" Data (Connection Parsed):\n");

        {
            struct nearby_utils_buffer test_connection_data_buffer = {};

            nearby_utils_buffer_initialize(&test_connection_data_buffer, advertisement_medium_deserialized.data, advertisement_medium_deserialized.data_size);
            nearby_connection_advertisement_ble_deserialize(&advertisement_connection_deserialized, &test_connection_data_buffer, advertisement_medium_deserialized.is_fast_advertisement);

            printf("  Version: %s\n", nearby_connection_advertisement_ble_version_to_string(advertisement_connection_deserialized.version));
            printf("  PCP: %s\n", nearby_protocols_pcp_to_string(advertisement_connection_deserialized.pcp));
            printf("  Service Id:\n");
            print_bytes_as_hex(advertisement_connection_deserialized.service_id_hash, sizeof(advertisement_connection_deserialized.service_id_hash), 3);
            printf("  Endpoint Id: %.*s\n", 4, advertisement_connection_deserialized.endpoint_id);
            printf("  Endpoint Info Size: %i\n", advertisement_connection_deserialized.endpoint_info_length);
            printf("  Endpoint Info:\n");
            print_bytes_as_hex(advertisement_connection_deserialized.endpoint_info_buffer, advertisement_connection_deserialized.endpoint_info_length, 3);
            printf("  Bluetooth Mac Address:\n");
            print_bytes_as_hex(advertisement_connection_deserialized.bluetooth_mac_address, sizeof(advertisement_connection_deserialized.bluetooth_mac_address), 3);
            printf("  UWB Address:\n");
            print_bytes_as_hex(advertisement_connection_deserialized.uwb_address_buffer, advertisement_connection_deserialized.uwb_address_length, 3);
        }

        if (advertisement_medium_deserialized.is_device_token_present == true)
        {
            printf(" Device Token:\n");
            print_bytes_as_hex(advertisement_medium_deserialized.device_token, sizeof(advertisement_medium_deserialized.device_token), 2);
        }
        else
        {
            printf(" No Device Token.\n");
        }

        printf(" Re-Serialized size required: %li\n", nearby_medium_advertisement_ble_serialize_get_required_data_length(&advertisement_medium_deserialized));

        if (nearby_medium_advertisement_ble_serialize_get_required_data_length(&advertisement_medium_deserialized) != 27)
        {
            printf("! Encountered non matching size.\n");
            return -1;
        }
    }

    {
        size_t         serialized_medium_data_length = nearby_medium_advertisement_ble_serialize_get_required_data_length(&advertisement_medium_deserialized);
        unsigned char* serialized_medium_data = malloc(serialized_medium_data_length);

        struct nearby_utils_buffer serialized_medium_data_buffer = {};

        nearby_utils_buffer_initialize(&serialized_medium_data_buffer, serialized_medium_data, serialized_medium_data_length);
        nearby_medium_advertisement_serialize(&advertisement_medium_deserialized, &serialized_medium_data_buffer);

        printf("Test Advertisement Packet Parsed and Re-Serialized:\n");
        printf(" Data Size: %li\n", serialized_medium_data_length);
        printf(" Data:\n");
        print_bytes_as_hex(serialized_medium_data, serialized_medium_data_length, 2);

        if (memcmp(serialized_medium_data, test_medium_data_serialized, serialized_medium_data_length) != 0)
        {
            printf("! Serialized output does not match.\n");
            return -1;
        }

        free(serialized_medium_data);
    }

    nearby_connection_advertisement_ble_deserialize_cleanup(&advertisement_connection_deserialized);
    nearby_medium_advertisement_ble_deserialize_cleanup(&advertisement_medium_deserialized);

    return 0;
}