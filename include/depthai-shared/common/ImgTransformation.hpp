#pragma once

#include "depthai-shared/utility/matrixOps.hpp"
#include "depthai-shared/common/Point2f.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {
struct RawImgTransformation {
    enum class Transformation : uint8_t {
        Init,
        Crop,
        Rotation,
        Pad,
        Flip,
        Scale,
    };
    Transformation transformationType = Transformation::Init;

    // Crop parameters in absolute pixel values for the original image
    int topLeftCropX = 0, topLeftCropY = 0, bottomRightCropX = 0, bottomRightCropY = 0;

    // Crop parameters in absolute pixel values
    int topPadding = 0, bottomPadding = 0, leftPadding = 0, rightPadding = 0;

    // Used for flipping scale and rotation
    std::vector<std::vector<float>> transformationMatrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    // Image size after transformation
    int afterTransformWidth = 0, afterTransformHeight = 0;
};

DEPTHAI_SERIALIZE_EXT(RawImgTransformation,
                      transformationType,
                      topLeftCropX,
                      topLeftCropY,
                      bottomRightCropX,
                      bottomRightCropY,
                      topPadding,
                      bottomPadding,
                      leftPadding,
                      rightPadding,
                      transformationMatrix,
                      afterTransformWidth,
                      afterTransformHeight);


class ImgTransformations {
   public:
    std::vector<RawImgTransformation> transformations = {};
    bool warpEnabled = false;

    std::vector<std::vector<float>> getFlipHorizontalMatrix(int width);

    std::vector<std::vector<float>> getFlipVerticalMatrix(int height);

    std::vector<std::vector<float>> getRotationMatrix(int px, int py, float theta);

    std::vector<std::vector<float>> getScaleMatrix(float scaleX, float scaleY);

    void setPadding(float topPadding, float bottomPadding, float leftPadding, float rightPadding);

    void setCrop(int topLeftCropX = 0, int topLeftCropY = 0, int bottomRightCropX = 0, int bottomRightCropY = 0);

    void setFlipVertical();

    void setFlipHorizontal();

    void setInitTransformation(int width, int height);

    void setRotation(float angle, dai::Point2f rotationPoint, int newWidth = 0, int newHeight = 0);

    // API that is meant for performance reasons - so matrices can be precomputed.
    void setTransformation(std::vector<std::vector<float>> matrix, std::vector<std::vector<float>> invMatrix, RawImgTransformation::Transformation transformationm, int newWidth, int newHeight);

    dai::Point2f clipPoint(dai::Point2f point, int imageWidth, int imageHeight, bool &isClipped);

    dai::Point2f transformPoint(RawImgTransformation transformation, dai::Point2f point);

    dai::Point2f invTransformPoint(RawImgTransformation transformation, dai::Point2f point);
};

DEPTHAI_SERIALIZE_EXT(ImgTransformations,
                      transformations,
                      warpEnabled);

std::vector<std::vector<float>> ImgTransformations::getFlipHorizontalMatrix(int width) {
    auto scale = matrix::createScalingMatrix(-1, 1);
    auto translate = matrix::createTranslationMatrix(width, 0);
    return matrix::matMul(translate, scale);
}

std::vector<std::vector<float>> ImgTransformations::getFlipVerticalMatrix(int height) {
    auto scale = matrix::createScalingMatrix(1, -1);
    auto translate = matrix::createTranslationMatrix(0, height);
    return matrix::matMul(translate, scale);
}

std::vector<std::vector<float>> ImgTransformations::getRotationMatrix(int px, int py, float theta) {
    auto translateToOrigin = matrix::createTranslationMatrix(-px, -py);
    auto rotate = matrix::createRotationMatrix(theta);
    auto translateBack = matrix::createTranslationMatrix(px, py);

    auto temp = matrix::matMul(translateToOrigin, rotate);
    return matrix::matMul(temp, translateBack);
}

std::vector<std::vector<float>> ImgTransformations::getScaleMatrix(float scaleX, float scaleY) {
    return matrix::createScalingMatrix(scaleX, scaleY);
}

void setPadding(float topPadding, float bottomPadding, float leftPadding, float rightPadding) {
    return;
}

void setCrop(int topLeftCropX = 0, int topLeftCropY = 0, int bottomRightCropX = 0, int bottomRightCropY = 0) {
    return;
}

void setFlipVertical() {
    return;
}

void setFlipHorizontal() {
    return;
}

void setInitTransformation(int width, int height) {
    return;
}

void setRotation(float angle, dai::Point2f rotationPoint, int newWidth = 0, int newHeight = 0) {
    return;
}

// API that is meant for performance reasons - so matrices can be precomputed.
void setTransformation(std::vector<std::vector<float>> matrix, std::vector<std::vector<float>> invMatrix, RawImgTransformation::Transformation transformationm, int newWidth, int newHeight) {
    return;
}

dai::Point2f clipPoint(dai::Point2f point, int imageWidth, int imageHeight, bool &isClipped) {
    return point;
}

dai::Point2f transformPoint(RawImgTransformation transformation, dai::Point2f point) {
    dai::Point2f returnPoint(0, 0);
    return point;
}

dai::Point2f invTransformPoint(RawImgTransformation transformation, dai::Point2f point) {
    return point;
}

}  // namespace dai
