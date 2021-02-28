#pragma once

#include <depthai-shared/common/optional.hpp>
#include <depthai-shared/datatype/RawDepthCalculatorConfig.hpp>
#include <nlohmann/json.hpp>
#include <vector>

namespace dai {

/**
 * Specify DepthCalculator options
 */
struct DepthCalculatorProperties {
    RawDepthCalculatorConfig roiConfig;

    /// Whether to wait for config at 'inputConfig' IO
    bool inputConfigSync = false;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DepthCalculatorProperties, roiConfig, inputConfigSync);

}  // namespace dai
