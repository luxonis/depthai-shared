#pragma once

// std
#include <cstdint>
#include <vector>

#include "depthai-shared/common/CameraBoardSocket.hpp"

// libraries
#include "nlohmann/json.hpp"

namespace dai {

struct point {
    float x, y, z;
    point();
    point(float _x, float _y, float _z):x(_x),y(_y),z(_z){}
};

struct Extrinsics {
    std::vector<std::vector<float>> rotationMatrix;
    // (x, y, z) pose of destCameraSocket w.r.t currentCameraSocket obtained through calibration
    point translation;
    // (x, y, z) pose of destCameraSocket w.r.t currentCameraSocket measured through CAD design
    point measuredTranslation;
    CameraBoardSocket toCameraSocket;
    // FIXME(sachin): Why does fromCameraSocket needs to be vector?
    std::vector<CameraBoardSocket> fromCameraSockets;
};

struct StereoRectification {
    std::vector<std::vector<float>> rectifiedRotationLeft, rectifiedRotationRight;
    CameraBoardSocket leftCameraSocket, rightCameraSocket;
    float baseline; // distance between left and right camera in cm
};

struct CameraInfo {
    std::vector<std::vector<float>> intrinsicMatrix;
    std::vector<float> distortionCoeff;
    Extrinsics extrinsics;
    double measuredFovRad; //fov in radians
    // TODO(sachin): Should I add type of distortion model here ?
};

struct EepromData {
    uint32_t version;
    bool swapLeftRightCam;
    std::string boardName, boardRev;
    std::unordered_map<CameraBoardSocket, CameraInfo> cameraData;
    StereoRectification stereoRectificationData;
    Extrinsics imuExtrinsics;
};


}  // namespace dai
