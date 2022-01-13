#pragma once

#include <depthai-shared/datatype/RawAprilTagConfig.hpp>
#include "depthai-shared/properties/Properties.hpp"
#include <vector>

namespace dai {

/**
 * Specify properties for AprilTag
 */
struct AprilTagProperties : PropertiesSerializable<Properties, AprilTagProperties> {
    RawAprilTagConfig initialConfig;

    /// Whether to wait for config at 'inputConfig' IO
    bool inputConfigSync = false;
};

DEPTHAI_SERIALIZE_EXT(AprilTagProperties, initialConfig, inputConfigSync);

}  // namespace dai
