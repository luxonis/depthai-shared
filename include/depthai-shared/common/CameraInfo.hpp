#pragma once
#include "depthai-shared/common/Extrinsics.hpp"

namespace dai {

struct CameraInfo {
    CameraInfo() : width(0), height(0), measuredFovDeg(0) {}
    uint16_t width, height;
    std::vector<std::vector<float>> intrinsicMatrix;
    std::vector<float> distortionCoeff;
    Extrinsics extrinsics;
    double measuredFovDeg;  // fov in deg
    // TODO(sachin): Should I add type of distortion model here ?
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CameraInfo, intrinsicMatrix, width, height, distortionCoeff, extrinsics, measuredFovDeg);
};

}  // namespace dai