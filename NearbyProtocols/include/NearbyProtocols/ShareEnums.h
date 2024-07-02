#ifndef NEARBYPROTOCOLS_SHAREENUMS_H
#define NEARBYPROTOCOLS_SHAREENUMS_H

enum nearby_share_target_type
{
    nearby_share_target_type_unknown = 0,
    nearby_share_target_type_phone = 1,
    nearby_share_target_type_tablet = 2,
    nearby_share_target_type_laptop = 3,
    nearby_share_target_type_car = 4,
    nearby_share_target_type_foldable = 5
};

const char* nearby_share_target_type_to_string(enum nearby_share_target_type type);

#endif // !NEARBYPROTOCOLS_SHAREENUMS_H