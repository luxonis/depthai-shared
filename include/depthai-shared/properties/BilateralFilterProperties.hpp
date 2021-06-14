#pragma once

#include <depthai-shared/common/optional.hpp>
#include <depthai-shared/datatype/RawBilateralFilterConfig.hpp>
#include <nlohmann/json.hpp>
#include <vector>

namespace dai {

/**
 * Specify properties for BilateralFilter
 */
struct BilateralFilterProperties {
    RawBilateralFilterConfig config;

    /// Whether to wait for config at 'inputConfig' IO
    bool inputConfigSync = false;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BilateralFilterProperties, config, inputConfigSync);

}  // namespace dai
