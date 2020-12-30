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

    struct CropQuadrilateral {
        // pt[0] is mapped to the top-left output corner, clockwise order
        std::vector<Point2f> pt;
        Size2f outSize;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CropQuadrilateral, pt, outSize);
    };

    struct CropConfig {
        CropRect cropRect;
        RotatedRect cropRotatedRect;
        CropQuadrilateral cropQuadrilateral;

        bool enableCenterCropRectangle = false;
        // if enableCenterCropRectangle -> automatically calculated crop parameters
        float cropRatio = 1.0f, widthHeightAspectRatio = 1.0f;

        bool enableRotatedRect = false;
        bool enableCropQuadrilateral = false;

        // Range 0..1 by default. Set 'false' to specify in pixels
        bool normalizedCoords = true;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CropConfig,
                                       cropRect,
                                       cropRotatedRect,
                                       cropQuadrilateral,
                                       enableCenterCropRectangle,
                                       cropRatio,
                                       widthHeightAspectRatio,
                                       enableRotatedRect,
                                       enableCropQuadrilateral,
                                       normalizedCoords);
    };

    struct ResizeConfig {
        int width = 0, height = 0;
        bool lockAspectRatioFill = false;
        char bgRed = 0, bgGreen = 0, bgBlue = 0;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ResizeConfig, width, height, lockAspectRatioFill, bgRed, bgGreen, bgBlue);
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

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::ImageManipConfig;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawImageManipConfig, cropConfig, resizeConfig, formatConfig, enableCrop, enableResize, enableFormat);
};

}  // namespace dai