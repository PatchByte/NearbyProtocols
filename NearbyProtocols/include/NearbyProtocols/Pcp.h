#ifndef NEARBYPROTOCOLS_PCP_H
#define NEARBYPROTOCOLS_PCP_H

#ifdef __cplusplus
extern "C"
{
#endif

    enum nearby_protocols_pcp
    {
        nearby_protocols_pcp_undefined = 0,
        nearby_protocols_pcp_p2p_star = 1,
        nearby_protocols_pcp_p2p_cluster = 2,
        nearby_protocols_pcp_p2p_point_to_point = 3
    };

    const char* nearby_protocols_pcp_to_string(enum nearby_protocols_pcp pcp);

#ifdef __cplusplus
}
#endif

#endif // !NEARBYPROTOCOLS_PCP_H