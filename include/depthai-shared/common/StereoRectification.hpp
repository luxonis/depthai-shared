#pragma once

#include <vector>

#include "depthai-shared/common/CameraBoardSocket.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// StereoRectification structure
struct StereoRectification {
    std::vector<std::vector<float>> rectifiedRotationLeft, rectifiedRotationRight, rectifiedRotationVertical;
    CameraBoardSocket leftCameraSocket = CameraBoardSocket::AUTO, rightCameraSocket = CameraBoardSocket::AUTO, verticalCameraSocket = CameraBoardSocket::AUTO;
};

DEPTHAI_SERIALIZE_EXT(
    StereoRectification, rectifiedRotationLeft, rectifiedRotationRight, rectifiedRotationVertical, leftCameraSocket, rightCameraSocket, verticalCameraSocket);

}  // namespace dai
