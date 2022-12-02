#pragma once

// std
#include <vector>

// libraries

// project
#include "depthai-shared/properties/Properties.hpp"
#include "depthai-shared/common/DetectionNetworkType.hpp"
#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/RawSpatialLocationCalculatorConfig.hpp"

namespace dai {

/**
 * Specify properties for SpatialDetectionNetwork
 */
struct SpatialDetectionNetworkProperties : PropertiesSerializable<Properties, SpatialDetectionNetworkProperties> {
    float detectedBBScaleFactor = 1.0;
    SpatialLocationCalculatorConfigThresholds depthThresholds;
    SpatialLocationCalculatorAlgorithm calculationAlgorithm = SpatialLocationCalculatorAlgorithm::AVERAGE;
};

DEPTHAI_SERIALIZE_EXT(SpatialDetectionNetworkProperties,
                      detectedBBScaleFactor,
                      depthThresholds,
                      calculationAlgorithm);

}  // namespace dai
