#pragma once

#include <vector>

#include "depthai-shared/common/Interpolation.hpp"
#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/RawImageAlignConfig.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for ImageAlign
 */
struct ImageAlignProperties : PropertiesSerializable<Properties, ImageAlignProperties> {
    RawImageAlignConfig initialConfig;

    /// Num frames in output pool
    int numFramesPool = 4;

    /**
     * Optional output width
     */
    int alignWidth = 0;
    /**
     * Optional output height
     */
    int alignHeight = 0;

    /// Warp HW IDs to use, if empty, use auto/default
    std::vector<int> warpHwIds;
    using Interpolation = dai::Interpolation;
    /// Interpolation type to use
    Interpolation interpolation = Interpolation::AUTO;
};

DEPTHAI_SERIALIZE_EXT(ImageAlignProperties, initialConfig, numFramesPool, alignWidth, alignHeight, warpHwIds, interpolation);

}  // namespace dai
