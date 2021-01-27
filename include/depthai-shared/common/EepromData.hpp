#pragma once

// std
#include <cstdint>

// libraries
#include "nlohmann/json.hpp"

namespace dai {

struct EEPROMData {
    // int64_t sec, nsec;
    bool SwapLeftRightCam;
    double MonoFovRad, RGBFovRad; // Can we change this to radians? most of the standard api's prefer radian. would make things easier to integrate
    double LeftRightDistanceMtrs, LeftRGBDistanceMtrs; // since gen2 is more flexible can we move these to setting during pipeline creation or can be used from calibration
    std::string name, revision; // board name. do we need this ? it might help in debugging which device the user is using.
    /** 
     * While helping OPAL I realized this can also be produced rectification from the other information we get during calibration.
     * we might need to add that function on the host side if the users want to use rgb camera like OPAL did
    **/
    std::vector<std::vector<double>> RectifiedRotationLeft, RectifiedRotationRight;
    // Intriniscs of the cameras
    std::vector<std::vector<double>> IntrinsicMatrixLeft, IntrinsicMatrixRight, IntrinsicMatrixRGB;
    // Relative rotation between cameras
    std::vector<std::vector<double>> RotationMatrixLeftRight, RotationMatrixRightRGB; // need to add IMU extrinsics later
    // Relative translation between cameras
    std::vector<double> TranslationLeftRight, TranslationRightRGB;
    // Distortion Coefficients
    std::vector<double> DistortionCoeffLeft, DistortionCoeffRight, DistortionCoeffRGB;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(EEPROMData, SwapLeftRightCam, MonoFovRad, RGBFovRad, LeftRightDistanceMtrs, \
                                    LeftRGBDistanceMtrs, name, revision, RectifiedRotationLeft, RectifiedRotationRight,\
                                    IntrinsicMatrixLeft, IntrinsicMatrixRight, IntrinsicMatrixRGB, \
                                    RotationMatrixLeftRight, RotationMatrixRightRGB, TranslationLeftRight,\
                                    TranslationRightRGB, DistortionCoeffLeft, DistortionCoeffRight, DistortionCoeffRGB);
};

} // namespace dai
