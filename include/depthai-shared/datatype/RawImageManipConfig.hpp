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

    struct CropConfig {
        CropRect cropRect;
        bool enableCenterCropRectangle = false;
        // if enableCenterCropRectangle -> automatically calculated crop parameters
        float cropRatio = 1.0f, widthHeightAspectRatio = 1.0f;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CropConfig, cropRect, enableCenterCropRectangle, cropRatio, widthHeightAspectRatio);
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