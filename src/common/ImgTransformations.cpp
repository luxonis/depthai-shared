#include "depthai-shared/common/ImgTransformation.hpp"

namespace dai {

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

void ImgTransformations::setPadding(float topPadding, float bottomPadding, float leftPadding, float rightPadding) {
    return;
}

void ImgTransformations::setCrop(int topLeftCropX, int topLeftCropY, int bottomRightCropX, int bottomRightCropY) {
    return;
}

void ImgTransformations::setScale(float scaleX, float scaleY){
    return;
}

void ImgTransformations::setFlipVertical() {
    return;
}

void ImgTransformations::setFlipHorizontal() {
    return;
}

void ImgTransformations::setInitTransformation(int width, int height) {
    return;
}

void ImgTransformations::setRotation(float angle, dai::Point2f rotationPoint, int newWidth, int newHeight) {
    return;
}

// API that is meant for performance reasons - so matrices can be precomputed.
void ImgTransformations::setTransformation(std::vector<std::vector<float>> matrix, std::vector<std::vector<float>> invMatrix, RawImgTransformation::Transformation transformationm, int newWidth, int newHeight) {
    return;
}

dai::Point2f ImgTransformations::clipPoint(dai::Point2f point, int imageWidth, int imageHeight, bool &isClipped) {
    return point;
}

dai::Point2f ImgTransformations::transformPoint(RawImgTransformation transformation, dai::Point2f point) {
    dai::Point2f returnPoint(0, 0);
    return point;
}

dai::Point2f ImgTransformations::invTransformPoint(RawImgTransformation transformation, dai::Point2f point) {
    return point;
}

}; // namespace dai