#pragma once

#include "depthai-shared/common/ProcessorType.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for Sync.
 */
struct SyncProperties : PropertiesSerializable<Properties, SyncProperties> {
    /**
     * The maximal interval the messages can be apart in nanoseconds.
     */
    uint64_t syncThresholdNs = 10e6;

    /**
     * The number of syncing attempts before fail (num of replaced messages).
     */
    int32_t syncAttempts = -1;

    /**
     * Which processor should execute the node.
     */
    ProcessorType processor = ProcessorType::LEON_CSS;
};

DEPTHAI_SERIALIZE_EXT(SyncProperties, syncThresholdNs, syncAttempts, processor);

}  // namespace dai
