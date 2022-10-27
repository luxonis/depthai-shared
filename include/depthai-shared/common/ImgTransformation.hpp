#pragma once

#include "depthai-shared/common/Rect.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {
struct ImgTransformation {
    float rotationAngle = 0;  // degrees
    dai::Rect crop = {0, 0, 0, 0};
    int topPadding = 0, bottomPadding = 0, leftPadding = 0, rightPadding = 0;
    float scaleFactorX = 1, scaleFactorY = 1;
    bool horizontalFlip = false;
    bool verticalFlip = false;
    bool warpEnabled = false;

    ImgTransformation(int width, int height) {
        this->crop.width = width;
        this->crop.height = height;
    }

    ImgTransformation() {}

    void setSize(int width, int height) {
        crop.x = 0;
        crop.y = 0;
        crop.width = width;
        crop.height = height;
    }

    void setPadding(ImgTransformation sourceFrame, dai::Rect iRoiRect, int topPadding, int bottomPadding, int leftPadding, int rightPadding) {
        int sourceTopPadding = sourceFrame.topPadding;
        int sourceLeftPadding = sourceFrame.leftPadding;
        int sourceBottomPadding = sourceFrame.bottomPadding;
        int sourceRightPadding = sourceFrame.rightPadding;

        int topPaddingIntersection = 0;
        int leftPaddingIntersection = 0;
        int bottomPaddingIntersection = 0;
        int rightPaddingIntersection = 0;

        if((int)iRoiRect.y < sourceTopPadding) topPaddingIntersection = sourceTopPadding - iRoiRect.y;
        if((int)iRoiRect.x < sourceLeftPadding) leftPaddingIntersection = sourceLeftPadding - iRoiRect.x;
        if((int)iRoiRect.y + iRoiRect.height < sourceBottomPadding) bottomPaddingIntersection = sourceBottomPadding - iRoiRect.y + iRoiRect.height;
        if((int)iRoiRect.x + iRoiRect.width < sourceRightPadding) rightPaddingIntersection = sourceRightPadding - iRoiRect.x + iRoiRect.width;

        this->leftPadding = leftPadding + leftPaddingIntersection;
        this->topPadding = topPadding + topPaddingIntersection;
        this->rightPadding = rightPadding + rightPaddingIntersection;
        this->bottomPadding = bottomPadding + bottomPaddingIntersection;
    }

    void setCrop(ImgTransformation sourceFrame, dai::Rect crop) {
        this->crop.x = sourceFrame.crop.x + crop.x;
        this->crop.y = sourceFrame.crop.y + crop.y;
        this->crop.width = crop.width;
        this->crop.height = crop.height;
    }

    void setRotation(ImgTransformation sourceFrame, float rotationAngle) {
        this->rotationAngle = sourceFrame.rotationAngle + rotationAngle;
    }

    void setScale(ImgTransformation sourceFrame, float scaleFactorX, float scaleFactorY) {
        this->scaleFactorX = sourceFrame.scaleFactorX * scaleFactorX;
        this->scaleFactorY = sourceFrame.scaleFactorY * scaleFactorY;
    }
};

DEPTHAI_SERIALIZE_EXT(ImgTransformation,
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
