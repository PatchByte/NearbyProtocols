#include "NearbyTests/main.h"
#include "NearbyProtocols/MediumAdvertisement.h"
#include "NearbyProtocols/Socket.h"
#include "NearbyTests/utils.h"
#include "NearbyUtils/Buffer.h"
#include <stdio.h>

int main()
{
    const char* test_data_serialized = "J\027#V7PU\0212S\030\206\360\314\242\347\220x\337\350\303\277\036\330\rE\313";

    struct nearby_medium_advertisement_ble advertisement_serialized = {};

    {
        struct nearby_utils_buffer test_data_buffer = {};

        nearby_utils_buffer_initialize(&test_data_buffer, (void*)test_data_serialized, 28);

        if (nearby_medium_advertisement_ble_deserialize(&advertisement_serialized, &test_data_buffer) == false)
        {
            printf("Failed to deserialize!\n");
            return -1;
        }

        printf("Test Advertisement Packet Parsed:\n");
        printf(" Version: %s\n", nearby_medium_advertisement_ble_version_to_string(advertisement_serialized.version));
        printf(" Socket Version: %s\n", nearby_socket_version_to_string(advertisement_serialized.socket_version));
        printf(" Is Fast Advertisement: %s\n", advertisement_serialized.is_fast_advertisement == true ? "Yes" : "No");
        printf(" Service Hash:\n");
        print_bytes_as_hex(advertisement_serialized.service_data_hash, sizeof(advertisement_serialized.service_data_hash), 2);
        printf(" Data Size: 0x%x\n", advertisement_serialized.data_size);
        printf(" Data:\n");
        print_bytes_as_hex(advertisement_serialized.data, advertisement_serialized.data_size, 2);

        if (advertisement_serialized.is_device_token_present == true)
        {
            printf(" Device Token:\n");
            print_bytes_as_hex(advertisement_serialized.device_token, sizeof(advertisement_serialized.device_token), 2);
        }
        else
        {
            printf(" No Device Token.\n");
        }

        printf(" Re-Serialized size required: %li\n", nearby_medium_advertisement_ble_serialize_get_required_data_length(&advertisement_serialized));
    }

    nearby_medium_advertisement_ble_deserialize_cleanup(&advertisement_serialized);

    return 0;
}