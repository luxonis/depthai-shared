#pragma once

#include "depthai-shared/common/CameraBoardSocket.hpp"
#include <vector>

namespace dai {

struct StereoRectification {
    StereoRectification() {
        leftCameraSocket = CameraBoardSocket::AUTO;
        rightCameraSocket = CameraBoardSocket::AUTO;
    }
    std::vector<std::vector<float>> rectifiedRotationLeft, rectifiedRotationRight;
    CameraBoardSocket leftCameraSocket, rightCameraSocket;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(StereoRectification, rectifiedRotationLeft, rectifiedRotationRight, leftCameraSocket, rightCameraSocket);
};

} // namespace dai
