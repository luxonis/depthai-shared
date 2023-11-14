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
    uint64_t syncIntervalMs = 10;

    /**
     * The number of syncing attempts before fail (num of replaced messages).
     */
    uint32_t syncAttempts = -1;

    /**
     * Frame pool size for the output
     */
    int numFramesPool = 8;
};

DEPTHAI_SERIALIZE_EXT(SyncProperties, syncIntervalMs, syncAttempts, numFramesPool);

}  // namespace dai
