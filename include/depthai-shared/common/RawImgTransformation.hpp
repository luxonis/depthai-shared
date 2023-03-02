#pragma once

#include "depthai-shared/common/Rect.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {
struct RawImgTransformation {
    float rotationAngle = 0;  // degrees
    dai::Rect crop = {0, 0, 0, 0};
    int topPadding = 0, bottomPadding = 0, leftPadding = 0, rightPadding = 0;
    float scaleFactorX = 1, scaleFactorY = 1;
    bool horizontalFlip = false;
    bool verticalFlip = false;

    bool warpEnabled = false;
    RawImgTransformation(int width, int height) {
        this->crop.width = width;
        this->crop.height = height;
    }
    RawImgTransformation() {}
};

DEPTHAI_SERIALIZE_EXT(RawImgTransformation,
                      rotationAngle,
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
