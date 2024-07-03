#ifndef _NEARBYPROTOCOLS_SOCKET_H
#define _NEARBYPROTOCOLS_SOCKET_H

#ifdef __cplusplus
extern "C"
{
#endif

    enum nearby_socket_version
    {
        nearby_socket_version_undefined = 0,
        nearby_socket_version_v1 = 1,
        nearby_socket_version_v2 = 2
    };

    const char* nearby_socket_version_to_string(enum nearby_socket_version version);

#ifdef __cplusplus
}
#endif

#endif // !_NEARBYPROTOCOLS_SOCKET_H