#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"
#include "RawImgFrame.hpp"

namespace dai {

struct RawImageManipConfig : public RawBuffer {
    // NNData data is in PoBuf
    struct CropRect {
        // Normalized range 0-1
        float xmin = 0.0f, ymin = 0.0f, xmax = 0.0f, ymax = 0.0f;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CropRect, xmin, ymin, xmax, ymax);
    };

    // Point2f, Size2f, RotatedRect are defined similar to OpenCV types
    struct Point2f {
        float x;
        float y;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Point2f, x, y);
    };

    struct Size2f {
        float width;
        float height;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Size2f, width, height);
    };

    struct RotatedRect {
        Point2f center;
        Size2f size;
        // degrees, increasing clockwise
        float angle;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(RotatedRect, center, size, angle);
    };

    struct CropConfig {
        CropRect cropRect;
        RotatedRect cropRotatedRect;

        bool enableCenterCropRectangle = false;
        // if enableCenterCropRectangle -> automatically calculated crop parameters
        float cropRatio = 1.0f, widthHeightAspectRatio = 1.0f;

        bool enableRotatedRect = false;

        // Range 0..1 by default. Set 'false' to specify in pixels
        bool normalizedCoords = true;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CropConfig,
                                       cropRect,
                                       cropRotatedRect,
                                       enableCenterCropRectangle,
                                       cropRatio,
                                       widthHeightAspectRatio,
                                       enableRotatedRect,
                                       normalizedCoords);
    };

    struct ResizeConfig {
        int width = 0, height = 0;
        bool lockAspectRatioFill = false;
        char bgRed = 0, bgGreen = 0, bgBlue = 0;

        //  clockwise order, pt[0] is mapped to the top-left output corner
        std::vector<Point2f> warpFourPoints;
        bool normalizedCoords = true;
        bool enableWarp4pt = false;

        std::vector<float> warpMatrix3x3;
        bool enableWarpMatrix = false;

        // clockwise
        float rotationAngle;
        // false -> degrees
        bool angleInRadians = false;
        bool enableRotation = false;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ResizeConfig,
                                       width,
                                       height,
                                       lockAspectRatioFill,
                                       bgRed,
                                       bgGreen,
                                       bgBlue,
                                       warpFourPoints,
                                       normalizedCoords,
                                       enableWarp4pt,
                                       warpMatrix3x3,
                                       enableWarpMatrix,
                                       rotationAngle,
                                       angleInRadians,
                                       enableRotation);
    };

    struct FormatConfig {
        RawImgFrame::Type type = RawImgFrame::Type::RGB888p;
        bool flipHorizontal = false;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(FormatConfig, type, flipHorizontal);
    };

    CropConfig cropConfig;
    ResizeConfig resizeConfig;
    FormatConfig formatConfig;

    bool enableCrop = false;
    bool enableResize = false;
    bool enableFormat = false;

    // Usable with runtime config only,
    // when ImageManipProperties.inputConfigSync is set
    bool reusePreviousImage = false;
    bool skipCurrentImage = false;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::ImageManipConfig;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawImageManipConfig,
                                   cropConfig,
                                   resizeConfig,
                                   formatConfig,
                                   enableCrop,
                                   enableResize,
                                   enableFormat,
                                   reusePreviousImage,
                                   skipCurrentImage);
};

}  // namespace dai
