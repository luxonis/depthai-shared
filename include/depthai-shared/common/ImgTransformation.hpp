#pragma once

#include "depthai-shared/common/Rect.hpp"
#include "depthai-shared/utility/Serialization.hpp"

// All widths, heights, xs, ys are relative - from 0 -> 1
namespace dai {
struct RawImgTransformation {
    float rotationAngle = 0;                      // degrees
    dai::Point2f rotationTurnPoint = {0.5, 0.5};  // TODO naming

    enum class Transformation : uint8_t {
        Crop,
        Rotation,
        Pad,
        Flip,
        Scale,
    };

    Transformation transformationType;

    // Crop relative to the uncropped image
    dai::Rect crop = {0, 0, 0, 0};

    // Paddings are relative (0.0 - 1.0) to the padded image.
    float topPadding = 0, bottomPadding = 0, leftPadding = 0, rightPadding = 0;

    // Relative to the unscaled image
    float scaleFactorX = 1, scaleFactorY = 1;


    bool horizontalFlip = false;
    bool verticalFlip = false;

    bool warpEnabled = false;
};

DEPTHAI_SERIALIZE_EXT(RawImgTransformation,
                      rotationAngle,
                      rotationTurnPoint,
                      transformationType,
                      crop,
                      topPadding,
                      bottomPadding,
                      leftPadding,
                      rightPadding,
                      scaleFactorX,
                      scaleFactorY,
                      horizontalFlip,
                      verticalFlip,
                      warpEnabled);
}  // namespace dai
