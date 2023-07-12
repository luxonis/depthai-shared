#pragma once

#include "depthai-shared/common/Point2f.hpp"
#include "depthai-shared/utility/Serialization.hpp"
#include "depthai-shared/utility/matrixOps.hpp"

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

    // Precomput the inverse matrix for performance reasons
    std::vector<std::vector<float>> invTransformationMatrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    // Image size after transformation
    unsigned int afterTransformWidth = 0, afterTransformHeight = 0;

    // Image size before the transformation
    unsigned int beforeTransformWidth = 0, beforeTransformHeight = 0;
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
                      afterTransformHeight,
                      beforeTransformWidth,
                      beforeTransformHeight);

class ImgTransformations {
   public:
    std::vector<RawImgTransformation> transformations = {};

    bool invalidFlag = false;

    void invalidateTransformations();

    bool isInvalid() const;

    unsigned int getLastWidth() const;

    unsigned int getLastHeight() const;

    void setPadding(int topPadding, int bottomPadding, int leftPadding, int rightPadding);

    void setCrop(int topLeftCropX = 0, int topLeftCropY = 0, int bottomRightCropX = 0, int bottomRightCropY = 0);

    void setFlipVertical();

    void setFlipHorizontal();

    void setInitTransformation(int width, int height);

    void setRotation(float angle, dai::Point2f rotationPoint, int newWidth = 0, int newHeight = 0);

    void setScale(float scaleX, float scaleY);

    bool validateTransformationSizes() const;

    // API that is meant for performance reasons - so matrices can be precomputed.
    void setTransformation(std::vector<std::vector<float>> matrix,
                           std::vector<std::vector<float>> invMatrix,
                           RawImgTransformation::Transformation transformation,
                           int newWidth,
                           int newHeight);

    static dai::Point2f transformPoint(RawImgTransformation transformation, dai::Point2f point, bool& isClipped);

    static dai::Point2f invTransformPoint(RawImgTransformation transformation, dai::Point2f point, bool& isClipped);

    static dai::Point2f clipPoint(dai::Point2f point, int imageWidth, int imageHeight, bool& isClipped);

   private:
    RawImgTransformation getNewTransformation() const;

    static dai::Point2f applyMatrixTransformation(dai::Point2f point, std::vector<std::vector<float>>& matrix);

    static std::vector<std::vector<float>> getFlipHorizontalMatrix(int width);

    static std::vector<std::vector<float>> getFlipVerticalMatrix(int height);

    static std::vector<std::vector<float>> getRotationMatrix(int px, int py, float theta);

    static std::vector<std::vector<float>> getScaleMatrix(float scaleX, float scaleY);
};

DEPTHAI_SERIALIZE_EXT(ImgTransformations, transformations, invalidFlag);

}  // namespace dai
