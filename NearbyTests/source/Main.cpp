#include "NearbyTests/Main.hpp"
#include "NearbyTests/Utils.hpp"
#include "NearbyProtocols/ConnectionAdvertisement.h"
#include "NearbyProtocols/MediumAdvertisement.h"
#include "NearbyProtocols/Pcp.h"
#include "NearbyProtocols/ShareAdvertisement.h"
#include "NearbyProtocols/ShareEnums.h"
#include "NearbyProtocols/Socket.h"
#include "NearbyUtils/Buffer.h"
#include <stdio.h>

int main()
{
    const char* test_medium_data_serialized = "J\027#96BK\021\0264\234pGh\324\315\342^\2513t\177\234\350\325\023\315";

    struct nearby_medium_advertisement_ble     advertisement_medium_deserialized = {};
    struct nearby_connection_advertisement_ble advertisement_connection_deserialized = {};

    struct nearby_share_advertisement advertisement_share_deserialized = {};

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
            printf("  Endpoint Info (Share Connection Info Parsed):\n");

            if (advertisement_connection_deserialized.endpoint_info_length > 0)
            {
                struct nearby_utils_buffer test_share_data_buffer = {};
                nearby_utils_buffer_initialize(&test_share_data_buffer, advertisement_connection_deserialized.endpoint_info_buffer, advertisement_connection_deserialized.endpoint_info_length);

                nearby_share_advertisement_from_endpoint_info(&advertisement_share_deserialized, &test_share_data_buffer);

                printf("   Version: %s\n", nearby_share_advertisement_version_to_string(advertisement_share_deserialized.version));
                printf("   Has Name: %i\n", advertisement_share_deserialized.has_name);
                printf("   Device Type: %s\n", nearby_share_target_type_to_string(advertisement_share_deserialized.device_type));
                printf("   Salt:\n");
                print_bytes_as_hex(advertisement_share_deserialized.salt, sizeof(advertisement_share_deserialized.salt), 4);
                printf("   Metadata Encryption Key Hash Byte:\n");
                print_bytes_as_hex(advertisement_share_deserialized.metadata_encryption_key_hash_byte, sizeof(advertisement_share_deserialized.metadata_encryption_key_hash_byte), 4);
            
                if(advertisement_share_deserialized.has_name == false)
                {
                    printf("   No name.\n");
                }
                else
                {
                    printf("   Name: %s\n", advertisement_share_deserialized.name_data);
                }
            }

            printf("  Bluetooth Mac Address:\n");
            print_bytes_as_hex(advertisement_connection_deserialized.bluetooth_mac_address, sizeof(advertisement_connection_deserialized.bluetooth_mac_address), 3);
            printf("  UWB Address:\n");
            print_bytes_as_hex(advertisement_connection_deserialized.uwb_address_buffer, advertisement_connection_deserialized.uwb_address_length, 3);
            printf("  Extra Field: %i\n", advertisement_connection_deserialized.extra_field);
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
        unsigned char* serialized_medium_data = (unsigned char*) malloc(serialized_medium_data_length);

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

    nearby_share_advertisement_from_endpoint_info_cleanup(&advertisement_share_deserialized);
    nearby_connection_advertisement_ble_deserialize_cleanup(&advertisement_connection_deserialized);
    nearby_medium_advertisement_ble_deserialize_cleanup(&advertisement_medium_deserialized);

    return 0;
}