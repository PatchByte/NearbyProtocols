#include "NearbyProtocols/ShareEnums.h"

const char* nearby_share_target_type_to_string(enum nearby_share_target_type type)
{
    switch (type)
    {
    case nearby_share_target_type_unknown:
        return "target_type_unknown";
    case nearby_share_target_type_phone:
        return "target_type_phone";
    case nearby_share_target_type_tablet:
        return "target_type_tablet";
    case nearby_share_target_type_laptop:
        return "target_type_laptop";
    case nearby_share_target_type_car:
        return "target_type_car";
    case nearby_share_target_type_foldable:
        return "target_type_foldable";
    default:
        return "unknown";
    }
}