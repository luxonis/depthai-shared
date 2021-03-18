#pragma once
#include "depthai-shared/common/Extrinsics.hpp"


struct CameraInfo {
    std::vector<std::vector<float>> intrinsicMatrix;
    std::vector<float> distortionCoeff;
    Extrinsics extrinsics;
    double measuredFovRad; //fov in radians
    // TODO(sachin): Should I add type of distortion model here ?
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CameraInfo, intrinsicMatrix, distortionCoeff, extrinsics, measuredFovRad);
};
