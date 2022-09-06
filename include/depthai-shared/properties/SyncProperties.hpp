#pragma once

#include <vector>

#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for Sync
 */
struct SyncProperties : PropertiesSerializable<Properties, SyncProperties> {
    /**
     * Stub
     */
    bool syncPolicy = false;
};

DEPTHAI_SERIALIZE_EXT(SyncProperties, syncPolicy);

}  // namespace dai
