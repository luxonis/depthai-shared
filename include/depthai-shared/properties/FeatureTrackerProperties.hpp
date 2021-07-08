#pragma once

#include <depthai-shared/common/optional.hpp>
#include <depthai-shared/datatype/RawFeatureTrackerConfig.hpp>
#include <nlohmann/json.hpp>
#include <vector>

namespace dai {

/**
 * Specify properties for FeatureTracker
 */
struct FeatureTrackerProperties {
    RawFeatureTrackerConfig initialConfig;

    /// Whether to wait for config at 'inputConfig' IO
    bool inputConfigSync = false;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FeatureTrackerProperties, initialConfig, inputConfigSync);

}  // namespace dai
