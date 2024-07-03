#ifndef NEARBYPROTOCOLS_SHAREENUMS_H
#define NEARBYPROTOCOLS_SHAREENUMS_H

#ifdef __cplusplus
extern "C"
{
#endif

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

#ifdef __cplusplus
}
#endif

#endif // !NEARBYPROTOCOLS_SHAREENUMS_H