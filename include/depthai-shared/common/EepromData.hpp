#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "depthai-shared/common/CameraBoardSocket.hpp"
#include "depthai-shared/common/CameraInfo.hpp"
#include "depthai-shared/common/Extrinsics.hpp"
#include "depthai-shared/common/Point3f.hpp"
#include "depthai-shared/common/StereoRectification.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {
/**
 * EepromData structure
 *
 * Contains the Calibration and Board data stored on device
 */
struct EepromData {
    uint32_t version = 7;
    std::string productName, boardName, boardRev, boardId, hardwareId, batchName;
    uint64_t batchTime;
    std::unordered_map<CameraBoardSocket, CameraInfo> cameraData;
    StereoRectification stereoRectificationData;
    Extrinsics imuExtrinsics;
    std::vector<uint8_t> miscellaneousData;
    DEPTHAI_SERIALIZE(EepromData, version, boardName, boardRev, boardId, hardwareId, batchName, batchTime, cameraData, stereoRectificationData, imuExtrinsics, miscellaneousData);
};

}  // namespace dai
