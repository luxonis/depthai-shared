#pragma once

// std
#include <vector>

// libraries
#include <nlohmann/json.hpp>

// project
#include "DetectionNetworkProperties.hpp"
#include "depthai-shared/common/DetectionNetworkType.hpp"
#include "depthai-shared/common/optional.hpp"

namespace dai {

/**
 * Properties for DetectionNetworkDepth
 */
struct DetectionNetworkDepthProperties : DetectionNetworkProperties {

    float detectedBBScaleFactor = 1.0;
    uint32_t lower_threshold = 100;
    uint32_t upper_threshold = 10000;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DetectionNetworkDepthProperties,
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
                                   detectedBBScaleFactor)

}  // namespace dai
