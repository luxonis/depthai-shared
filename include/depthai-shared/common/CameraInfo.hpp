#pragma once
#include "depthai-shared/common/Extrinsics.hpp"


struct CameraInfo {
    int width, height;
    std::vector<std::vector<float>> intrinsicMatrix;
    std::vector<float> distortionCoeff;
    Extrinsics extrinsics;
    double measuredFovDeg; //fov in deg
    // TODO(sachin): Should I add type of distortion model here ?
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CameraInfo, intrinsicMatrix, distortionCoeff, extrinsics, measuredFovDeg);
};
