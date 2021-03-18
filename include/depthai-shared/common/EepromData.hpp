#pragma once
#include <vector>

#include "depthai-shared/common/CameraBoardSocket.hpp"
#include "depthai-shared/common/Point3f.hpp"
#include "depthai-shared/common/Extrinsics.hpp"
#include "depthai-shared/common/CameraInfo.hpp"
#include "depthai-shared/common/StereoRectification.hpp"

// libraries
#include "nlohmann/json.hpp"

namespace dai {
struct EepromData {
    uint32_t version;
    bool swapLeftRightCam;
    std::string boardName, boardRev;
    std::unordered_map<CameraBoardSocket, CameraInfo> cameraData;
    StereoRectification stereoRectificationData;
    Extrinsics imuExtrinsics;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(EepromData, version, swapLeftRightCam, boardName, boardRev, cameraData, stereoRectificationData, imuExtrinsics);
};


}  // namespace dai
