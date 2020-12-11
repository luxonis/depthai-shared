#pragma once

#include <depthai-shared/datatype/RawImageManipConfig.hpp>
#include <depthai-shared/pb/common/optional.hpp>
#include <nlohmann/json.hpp>

namespace dai {

/**
 * Specify ImageManip options
 */
struct ImageManipProperties {
    RawImageManipConfig initialConfig;

    // Whether to wait for config at 'inputConfig' io
    bool inputConfigSync = false;

    // Maximum output frame size in bytes (eg: 300x300 BGR image -> 300*300*3 bytes)
    int outputFrameSize = 1 * 1024 * 1024;

    // Num frames in pool
    int numFramesPool = 4;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImageManipProperties, initialConfig, inputConfigSync, outputFrameSize, numFramesPool);

}  // namespace dai
