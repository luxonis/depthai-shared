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
    CameraBoardSocket destCameraSocket;
};

struct StereoRectification {
    std::vector<std::vector<float>> rectifiedRotationLeft, rectifiedRotationRight;
    CameraBoardSocket leftCameraSocket, rightCameraSocket;
    int baseline;
};

struct CameraInfo {
    std::vector<std::vector<float>> intrinsicMatrix;
    std::vector<float> distortionCoeff;
    Extrinsics extrinsics;
    double fovRad; //fov in radians
};

struct EepromData {
    uint32_t version;
    bool swapLeftRightCam;
    std::string boardName, boardRev;
    std::unordered_map<CameraBoardSocket, CameraInfo> cameraData;
    StereoRectification stereoRectificationData;
    Extrinsics imuExtrinsics;
};


// struct EepromData {
//     // int64_t sec, nsec;
//     bool swapLeftRightCam;
//     // Can we change this to radians? most of the standard api's prefer radian. would make things easier to integrate
//     float monoFovRad, rgbFovRad;
//     // since gen2 is more flexible can we move distance vars to setting during pipeline creation or can be used from calibration
//     float leftRightDistanceMtrs, leftRGBDistanceMtrs;
//     // board name. do we need this ? it might help in debugging which device the user is using.
//     std::string name, revision;
//     /**
//      * While helping OPAL I realized this can also be produced rectification from the other information we get during calibration.
//      * we might need to add that function on the host side if the users want to use rgb camera like OPAL did
//      **/
//     std::vector<std::vector<float>> rectifiedRotationLeft, rectifiedRotationRight;
//     // Intriniscs of the cameras
//     std::vector<std::vector<float>> intrinsicMatrixLeft, intrinsicMatrixRight, intrinsicMatrixRGB;
//     // Relative rotation between cameras
//     std::vector<std::vector<float>> rotationMatrixLeftRight, rotationMatrixRightRGB;  // need to add IMU extrinsics later
//     // Relative translation between cameras
//     std::vector<float> translationLeftRight, translationRightRGB;
//     // Distortion Coefficients
//     std::vector<float> distortionCoeffLeft, distortionCoeffRight, distortionCoeffRGB;



//     NLOHMANN_DEFINE_TYPE_INTRUSIVE(EepromData,
//                                    swapLeftRightCam,
//                                    monoFovRad,
//                                    rgbFovRad,
//                                    leftRightDistanceMtrs,
//                                    leftRGBDistanceMtrs,
//                                    name,
//                                    revision,
//                                    rectifiedRotationLeft,
//                                    rectifiedRotationRight,
//                                    intrinsicMatrixLeft,
//                                    intrinsicMatrixRight,
//                                    intrinsicMatrixRGB,
//                                    rotationMatrixLeftRight,
//                                    rotationMatrixRightRGB,
//                                    translationLeftRight,
//                                    translationRightRGB,
//                                    distortionCoeffLeft,
//                                    distortionCoeffRight,
//                                    distortionCoeffRGB);
// };

}  // namespace dai
