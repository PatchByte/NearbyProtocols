#include "NearbyProtocols/Pcp.h"

const char* nearby_protocols_pcp_to_string(enum nearby_protocols_pcp pcp)
{
    switch (pcp)
    {
    case nearby_protocols_pcp_undefined:
        return "undefined";
    case nearby_protocols_pcp_p2p_star:
        return "p2p_star";
    case nearby_protocols_pcp_p2p_cluster:
        return "p2p_cluster";
    case nearby_protocols_pcp_p2p_point_to_point:
        return "point_to_point";
    default:
        return "unknown";
    }
}