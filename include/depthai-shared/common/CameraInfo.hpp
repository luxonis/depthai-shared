#pragma once

#include "depthai-shared/common/CameraModel.hpp"
#include "depthai-shared/common/Extrinsics.hpp"

namespace dai {

struct CameraInfo {
    CameraInfo() : width(0), height(0), measuredFovDeg(0) {
        cameraType = CameraModel::Perspective;
    }
    uint16_t width, height;
    std::vector<std::vector<float>> intrinsicMatrix;
    std::vector<float> distortionCoeff;
    Extrinsics extrinsics;
    float measuredFovDeg;  // fov in deg
    CameraModel cameraType;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CameraInfo, cameraType, width, height, measuredFovDeg, intrinsicMatrix, distortionCoeff, extrinsics);
};

}  // namespace dai