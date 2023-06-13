#include <assert.h>

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
    auto translateToOrigin = matrix::createTranslationMatrix(px, py);
    auto rotate = matrix::createRotationMatrix(theta);
    auto translateBack = matrix::createTranslationMatrix(-px, -py);

    auto temp = matrix::matMul(translateToOrigin, rotate);
    return matrix::matMul(temp, translateBack);
}

std::vector<std::vector<float>> ImgTransformations::getScaleMatrix(float scaleX, float scaleY) {
    return matrix::createScalingMatrix(scaleX, scaleY);
}

int ImgTransformations::getLastHeight() {
    if(transformations.size() < 1) {
        return 0;
    }
    return transformations.back().afterTransformHeight;
}

int ImgTransformations::getLastWidth() {
    if(transformations.size() < 1) {
        return 0;
    }
    return transformations.back().afterTransformWidth;
}

void ImgTransformations::setPadding(int topPadding, int bottomPadding, int leftPadding, int rightPadding) {
    RawImgTransformation paddingTransformation;
    paddingTransformation.transformationType = RawImgTransformation::Transformation::Pad;
    paddingTransformation.afterTransformWidth = getLastWidth() + leftPadding + rightPadding;
    paddingTransformation.afterTransformHeight = getLastHeight() + topPadding + bottomPadding;
    paddingTransformation.beforeTransformWidth = getLastWidth();
    paddingTransformation.beforeTransformHeight = getLastHeight();
    paddingTransformation.topPadding = topPadding;
    paddingTransformation.bottomPadding = bottomPadding;
    paddingTransformation.leftPadding = leftPadding;
    paddingTransformation.rightPadding = rightPadding;
    transformations.push_back(paddingTransformation);
    return;
}

void ImgTransformations::setCrop(int topLeftCropX, int topLeftCropY, int bottomRightCropX, int bottomRightCropY) {
    if(transformations.size() < 1) {
        throw std::runtime_error("Cannot rotate image without first setting an initial transformation");
    }
    RawImgTransformation croppingTransformation;
    croppingTransformation.transformationType = RawImgTransformation::Transformation::Crop;
    croppingTransformation.afterTransformWidth = getLastWidth() - topLeftCropX - bottomRightCropX;
    croppingTransformation.afterTransformHeight = getLastHeight() - topLeftCropX - bottomRightCropY;
    croppingTransformation.beforeTransformWidth = getLastWidth();
    croppingTransformation.beforeTransformHeight = getLastHeight();
    croppingTransformation.topLeftCropX = topLeftCropX;
    croppingTransformation.topLeftCropY = topLeftCropY;
    croppingTransformation.bottomRightCropX = bottomRightCropX;
    croppingTransformation.bottomRightCropY = bottomRightCropY;
    transformations.push_back(croppingTransformation);
    return;
}

void ImgTransformations::setScale(float scaleX, float scaleY) {
    if(transformations.size() < 1) {
        throw std::runtime_error("Cannot rotate image without first setting an initial transformation");
    }
    RawImgTransformation scaleTransformation;
    scaleTransformation.transformationType = RawImgTransformation::Transformation::Scale;
    scaleTransformation.afterTransformWidth = static_cast<int>(getLastWidth() * scaleX);
    scaleTransformation.afterTransformHeight = static_cast<int>(getLastHeight() * scaleY);
    scaleTransformation.beforeTransformWidth = getLastWidth();
    scaleTransformation.beforeTransformHeight = getLastHeight();
    scaleTransformation.transformationMatrix = getScaleMatrix(scaleX, scaleY);
    scaleTransformation.invTransformationMatrix = std::vector<std::vector<float>>();
    bool success = matrix::matInv(scaleTransformation.transformationMatrix, scaleTransformation.invTransformationMatrix);
    if(!success) {
        throw std::runtime_error("Could not invert matrix");
    }
    transformations.push_back(scaleTransformation);
    return;
}

void ImgTransformations::setFlipVertical() {
    if(transformations.size() < 1) {
        throw std::runtime_error("Cannot rotate image without first setting an initial transformation");
    }
    RawImgTransformation flipTransformation;
    flipTransformation.transformationType = RawImgTransformation::Transformation::Flip;
    flipTransformation.beforeTransformWidth = getLastWidth();
    flipTransformation.beforeTransformHeight = getLastHeight();
    flipTransformation.afterTransformWidth = getLastWidth();
    flipTransformation.afterTransformHeight = getLastHeight();
    flipTransformation.transformationMatrix = getFlipVerticalMatrix(getLastHeight());
    flipTransformation.invTransformationMatrix = std::vector<std::vector<float>>();
    bool success = matrix::matInv(flipTransformation.transformationMatrix, flipTransformation.invTransformationMatrix);
    if(!success) {
        throw std::runtime_error("Could not invert matrix");
    }
    transformations.push_back(flipTransformation);
    return;
}

void ImgTransformations::setFlipHorizontal() {
    if(transformations.size() < 1) {
        throw std::runtime_error("Cannot rotate image without first setting an initial transformation");
    }
    RawImgTransformation flipTransformation;
    flipTransformation.transformationType = RawImgTransformation::Transformation::Flip;
    flipTransformation.beforeTransformHeight = getLastHeight();
    flipTransformation.beforeTransformWidth = getLastWidth();
    flipTransformation.afterTransformWidth = getLastWidth();
    flipTransformation.afterTransformHeight = getLastHeight();
    flipTransformation.transformationMatrix = getFlipHorizontalMatrix(getLastWidth());
    flipTransformation.invTransformationMatrix = std::vector<std::vector<float>>();
    bool success = matrix::matInv(flipTransformation.transformationMatrix, flipTransformation.invTransformationMatrix);
    if(!success) {
        throw std::runtime_error("Could not invert matrix");
    }
    transformations.push_back(flipTransformation);
    return;
}

void ImgTransformations::setInitTransformation(int width, int height) {
    if(transformations.size() > 0) {
        throw std::runtime_error("Cannot set initial transformation after other transformations have been set");
    }
    RawImgTransformation initTransformation;
    initTransformation.transformationType = RawImgTransformation::Transformation::Init;
    initTransformation.afterTransformWidth = width;
    initTransformation.afterTransformHeight = height;
    initTransformation.beforeTransformWidth = width;
    initTransformation.beforeTransformHeight = height;
    transformations.push_back(initTransformation);
    return;
}

void ImgTransformations::setRotation(float angle, dai::Point2f rotationPoint, int newWidth, int newHeight) {
    if(transformations.size() < 1) {
        throw std::runtime_error("Cannot rotate image without first setting an initial transformation");
    }
    RawImgTransformation rotationTransformation;
    rotationTransformation.transformationType = RawImgTransformation::Transformation::Rotation;
    rotationTransformation.beforeTransformHeight = getLastHeight();
    rotationTransformation.beforeTransformWidth = getLastWidth();
    rotationTransformation.afterTransformWidth = newWidth;
    rotationTransformation.afterTransformHeight = newHeight;
    rotationTransformation.transformationMatrix = getRotationMatrix(rotationPoint.x, rotationPoint.y, angle);
    rotationTransformation.invTransformationMatrix = getRotationMatrix(rotationPoint.x, rotationPoint.y, -angle);
    transformations.push_back(rotationTransformation);
}

// API that is meant for performance reasons - so matrices can be precomputed.
void ImgTransformations::setTransformation(std::vector<std::vector<float>> matrix,
                                           std::vector<std::vector<float>> invMatrix,
                                           RawImgTransformation::Transformation transformationm,
                                           int newWidth,
                                           int newHeight) {
    return;
}

dai::Point2f ImgTransformations::applyMatrixTransformation(dai::Point2f point, std::vector<std::vector<float>>& matrix) {
    if(point.isNormalized() && point.x != 0.0f && point.y != 0.0f) {
        throw std::runtime_error("Cannot apply matrix transformation to normalized point (x = " + std::to_string(point.x) + ", y = " + std::to_string(point.y)
                                 + ")");
    }
    std::vector<float> homogenousPoint = {point.x, point.y, 1.0f};
    std::vector<float> transformedPoint = {0.0f, 0.0f, 0.0f};

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            transformedPoint[i] += matrix[i][j] * homogenousPoint[j];
        }
    }
    if(transformedPoint[2] == 0) {
        throw std::runtime_error("Homogeneous coordinate is zero");
    }
    return Point2f(std::round(transformedPoint[0] / transformedPoint[2]), std::round(transformedPoint[1] / transformedPoint[2]));
}

dai::Point2f ImgTransformations::clipPoint(dai::Point2f point, int imageWidth, int imageHeight, bool& isClipped) {
    if(imageHeight == 0 && imageWidth == 0) {
        throw std::runtime_error("Image width and height must be greater than zero");
    }
    isClipped = false;
    if(point.x < 0) {
        point.x = 0;
        isClipped = true;
    }
    if(point.y < 0) {
        point.y = 0;
        isClipped = true;
    }
    if(point.x > imageWidth) {
        point.x = imageWidth;
        isClipped = true;
    }
    if(point.y > imageHeight) {
        point.y = imageHeight;
        isClipped = true;
    }
    return point;
}

dai::Point2f ImgTransformations::transformPoint(RawImgTransformation transformation, dai::Point2f point, bool& isClipped) {
    switch(transformation.transformationType) {
        case RawImgTransformation::Transformation::Init:
            break;
        case RawImgTransformation::Transformation::Pad:
            point.x = point.x + transformation.leftPadding;
            point.y = point.y + transformation.topPadding;
            break;
        case RawImgTransformation::Transformation::Crop:
            point.x = point.x - transformation.topLeftCropX;
            point.y = point.y - transformation.topLeftCropY;
            break;
        case RawImgTransformation::Transformation::Rotation:
        case RawImgTransformation::Transformation::Flip:
        case RawImgTransformation::Transformation::Scale:
            point = applyMatrixTransformation(point, transformation.transformationMatrix);
            break;
        default:
            break;
    }
    point = clipPoint(point, transformation.afterTransformWidth, transformation.afterTransformHeight, isClipped);
    return point;
}

dai::Point2f ImgTransformations::invTransformPoint(RawImgTransformation transformation, dai::Point2f point, bool& isClipped) {
    switch(transformation.transformationType) {
        case RawImgTransformation::Transformation::Pad:
            point.x = point.x - transformation.leftPadding;
            point.y = point.y - transformation.topPadding;
            break;
        case RawImgTransformation::Transformation::Init:
            break;
        case RawImgTransformation::Transformation::Crop:
            point.x = point.x + transformation.topLeftCropX;
            point.y = point.y + transformation.topLeftCropY;
            break;
        case RawImgTransformation::Transformation::Rotation:
        case RawImgTransformation::Transformation::Flip:
        case RawImgTransformation::Transformation::Scale:
            point = applyMatrixTransformation(point, transformation.invTransformationMatrix);
            break;
        default:
            break;
    }
    point = clipPoint(point, transformation.beforeTransformWidth, transformation.beforeTransformHeight, isClipped);
    return point;
}

};  // namespace dai