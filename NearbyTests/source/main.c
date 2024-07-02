#include "NearbyTests/main.h"
#include "NearbyProtocols/MediumAdvertisement.h"
#include "NearbyProtocols/Socket.h"
#include "NearbyTests/utils.h"
#include "NearbyUtils/Buffer.h"
#include <stdio.h>

int main()
{
    const char* test_data_serialized = "J\027#V7PU\0212S\030\206\360\314\242\347\220x\337\350\303\277\036\330\rE\313";

    struct nearby_medium_advertisement_ble advertisement_deserialized = {};

    {
        struct nearby_utils_buffer test_data_buffer = {};

        nearby_utils_buffer_initialize(&test_data_buffer, (void*)test_data_serialized, 28);

        if (nearby_medium_advertisement_ble_deserialize(&advertisement_deserialized, &test_data_buffer) == false)
        {
            printf("Failed to deserialize!\n");
            return -1;
        }

        printf("Test Advertisement Packet Parsed:\n");
        printf(" Version: %s\n", nearby_medium_advertisement_ble_version_to_string(advertisement_deserialized.version));
        printf(" Socket Version: %s\n", nearby_socket_version_to_string(advertisement_deserialized.socket_version));
        printf(" Is Fast Advertisement: %s\n", advertisement_deserialized.is_fast_advertisement == true ? "Yes" : "No");
        printf(" Service Hash:\n");
        print_bytes_as_hex(advertisement_deserialized.service_data_hash, sizeof(advertisement_deserialized.service_data_hash), 2);
        printf(" Data Size: 0x%x\n", advertisement_deserialized.data_size);
        printf(" Data:\n");
        print_bytes_as_hex(advertisement_deserialized.data, advertisement_deserialized.data_size, 2);

        if (advertisement_deserialized.is_device_token_present == true)
        {
            printf(" Device Token:\n");
            print_bytes_as_hex(advertisement_deserialized.device_token, sizeof(advertisement_deserialized.device_token), 2);
        }
        else
        {
            printf(" No Device Token.\n");
        }

        printf(" Re-Serialized size required: %li\n", nearby_medium_advertisement_ble_serialize_get_required_data_length(&advertisement_deserialized));

        if (nearby_medium_advertisement_ble_serialize_get_required_data_length(&advertisement_deserialized) != 28)
        {
            printf("! Encountered non matching size.\n");
            return -1;
        }
    }

    {
        size_t         serialized_data_length = nearby_medium_advertisement_ble_serialize_get_required_data_length(&advertisement_deserialized);
        unsigned char* serialized_data = malloc(serialized_data_length);

        struct nearby_utils_buffer serialized_data_buffer = {};

        nearby_utils_buffer_initialize(&serialized_data_buffer, serialized_data, serialized_data_length);
        nearby_medium_advertisement_serialize(&advertisement_deserialized, &serialized_data_buffer);

        printf("Test Advertisement Packet Parsed and Re-Serialized:\n");
        printf(" Data Size: %li\n", serialized_data_length);
        printf(" Data:\n");
        print_bytes_as_hex(serialized_data, serialized_data_length, 2);

        free(serialized_data);
    }

    nearby_medium_advertisement_ble_deserialize_cleanup(&advertisement_deserialized);

    return 0;
}