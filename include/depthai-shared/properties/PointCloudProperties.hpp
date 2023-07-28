#pragma once

#include <vector>

#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/RawPointCloudConfig.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for PointCloud
 */
struct PointCloudProperties : PropertiesSerializable<Properties, PointCloudProperties> {
    RawPointCloudConfig initialConfig;

    int numFramesPool = 4;

    int numShaves = 1;
};

DEPTHAI_SERIALIZE_EXT(PointCloudProperties, initialConfig, numFramesPool, numShaves);

}  // namespace dai
