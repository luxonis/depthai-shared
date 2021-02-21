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
    std::vector<DepthCalculatorConfig> roiConfig;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DepthCalculatorProperties, roiConfig);

}  // namespace dai
