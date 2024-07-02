#include "NearbyProtocols/Socket.h"

const char* nearby_socket_version_to_string(enum nearby_socket_version version)
{
    switch (version)
    {
    case nearby_socket_version_undefined:
        return "undefined";
    case nearby_socket_version_v1:
        return "v1";
    case nearby_socket_version_v2:
        return "v2";
    }
}