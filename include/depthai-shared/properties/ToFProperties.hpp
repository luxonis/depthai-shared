#pragma once

#include "depthai-shared/datatype/RawToFConfig.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for ToF
 */
struct ToFProperties : PropertiesSerializable<Properties, ToFProperties> {
    /**
     * Initial ToF config
     */
    RawToFConfig initialConfig;

    /**
     * Num frames in output pool
     */
    int numFramesPool = 4;

    /**
     * Number of shaves reserved for ToF decoding.
     */
    std::int32_t numShaves = 1;

    /// Warp HW IDs to use for undistortion, if empty, use auto/default
    std::vector<int> warpHwIds;
};

DEPTHAI_SERIALIZE_EXT(ToFProperties, initialConfig, numFramesPool, numShaves, warpHwIds);

}  // namespace dai
