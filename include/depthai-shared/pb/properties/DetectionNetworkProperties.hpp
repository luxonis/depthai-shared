#pragma once

#include <depthai-shared/pb/common/optional.hpp>
#include <nlohmann/json.hpp>
#include <vector>
#include "depthai-shared/datatype/DetectionNetworkTypeEnum.hpp"

namespace dai {

/**
 * Properties for DetectionNetwork
 */
struct DetectionNetworkProperties {
    std::string streamName;
    std::string blobUri;
    tl::optional<std::uint32_t> blobSize;

    // Generic Neural Network Info
    DetectionNetworkTypeEnum nnFamily;
    float confidenceThreshold;

    // YOLO specific
    int classes;
    int coordinates;
    std::vector<float> anchors;
    std::map<std::string, std::vector<int>> anchorMasks;
    float iouThreshold;

    // Misc Stuff
    std::uint32_t numFrames = 8;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DetectionNetworkProperties,
                                   streamName,
                                   nnFamily,
                                   blobUri,
                                   blobSize,
                                   confidenceThreshold,
                                   classes,
                                   coordinates,
                                   anchors,
                                   anchorMasks,
                                   iouThreshold,
                                   numFrames)

}  // namespace dai
