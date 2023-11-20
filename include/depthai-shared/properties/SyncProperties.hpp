#pragma once

#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * TODO
 */
struct SyncProperties : PropertiesSerializable<Properties, SyncProperties> {
    /**
     * The maximal interval the messages can be apart in milliseconds.
     */
    uint64_t syncThresholdNs = 10e6;

    /**
     * The number of syncing attempts before fail (num of replaced messages).
     */
    int32_t syncAttempts = -1;
};

DEPTHAI_SERIALIZE_EXT(SyncProperties, syncThresholdNs, syncAttempts);

}  // namespace dai
