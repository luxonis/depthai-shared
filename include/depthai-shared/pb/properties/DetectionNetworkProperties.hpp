#pragma once

#include <depthai-shared/pb/common/optional.hpp>
#include <nlohmann/json.hpp>
#include <vector>

namespace dai {

/**
 * Properties for DetectionNetwork
 */
struct DetectionNetworkProperties {
    /**
     * Set a limit to how many packets will be sent further to host
     */
    std::string streamName;
    /**
     * Uri which points to blob
     */
    std::string nnConfig;

    std::string nnFamily;
    std::string confidenceThreshold;

    // YOLO specific
    int classes;
    int coordinates;
    std::vector<float> anchors;
    std::vector<std::vector<int>> anchor_masks;
    float iouThreshold;

};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DetectionNetworkProperties, streamName, nnConfig, classes, coordinates, anchors, anchor_masks, iouThreshold)

}  // namespace dai
