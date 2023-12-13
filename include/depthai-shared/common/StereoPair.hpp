

#pragma once

#include "depthai-shared/common/CameraBoardSocket.hpp"
namespace dai {
/**
 * Describes which camera sockets can be used for stereo and their baseline.
 *
 */
struct StereoPair {
    CameraBoardSocket left;
    CameraBoardSocket right;
    /**
     * Baseline in centimeters.
     */
    float baseline = -1;
    bool isVertical = false;
    DEPTHAI_SERIALIZE(StereoPair, left, right, baseline);
};
}  // namespace dai
