#pragma once

#include <depthai-shared/common/optional.hpp>
#include <depthai-shared/datatype/RawImageManipConfig.hpp>
#include <nlohmann/json.hpp>

namespace dai {

/**
 * Specify properties for ImageManip
 */
struct ImageManipProperties {
    /// Initial configuration for ImageManip node
    RawImageManipConfig initialConfig;

    /// Whether to wait for config at 'inputConfig' IO
    bool inputConfigSync = false;

    /// Maximum output frame size in bytes (eg: 300x300 BGR image -> 300*300*3 bytes)
    int outputFrameSize = 1 * 1024 * 1024;

    /// Num frames in output pool
    int numFramesPool = 4;

    /// Custom warp mesh width. Set to zero to disable
    int meshWidth = 0;
    /// Custom warp mesh height. Set to zero to disable.
    int meshHeight = 0;
    /// Custom warp mesh uri. Set to empty string to disable.
    std::string meshUri = "";
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImageManipProperties, initialConfig, inputConfigSync, outputFrameSize, numFramesPool, meshWidth, meshHeight, meshUri);

}  // namespace dai
