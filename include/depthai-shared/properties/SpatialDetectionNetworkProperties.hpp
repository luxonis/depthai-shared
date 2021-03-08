#pragma once

// std
#include <vector>

// libraries
#include <nlohmann/json.hpp>

// project
#include "DetectionNetworkProperties.hpp"
#include "depthai-shared/common/DetectionNetworkType.hpp"
#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/RawDepthCalculatorConfig.hpp"

namespace dai {

/**
 * Properties for SpatialDetectionNetwork
 */
struct SpatialDetectionNetworkProperties : DetectionNetworkProperties {
    float detectedBBScaleFactor = 1.0;
    DepthCalculatorConfigThresholds depthThresholds;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SpatialDetectionNetworkProperties,
                                   nnFamily,
                                   blobSize,
                                   blobUri,
                                   numFrames,
                                   numThreads,
                                   numNCEPerThread,
                                   confidenceThreshold,
                                   classes,
                                   coordinates,
                                   anchors,
                                   anchorMasks,
                                   iouThreshold,
                                   detectedBBScaleFactor,
                                   depthThresholds)

}  // namespace dai
