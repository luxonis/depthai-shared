#pragma once

#include <depthai-shared/common/optional.hpp>
#include <depthai-shared/datatype/RawAprilTagConfig.hpp>
#include <nlohmann/json.hpp>
#include <vector>

namespace dai {

/**
 * Specify properties for AprilTag
 */
struct AprilTagProperties {
    RawAprilTagConfig initialConfig;

    /// Whether to wait for config at 'inputConfig' IO
    bool inputConfigSync = false;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AprilTagProperties, initialConfig, inputConfigSync);

}  // namespace dai
