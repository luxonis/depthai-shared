#pragma once

#include <depthai-shared/pb/common/optional.hpp>
#include <nlohmann/json.hpp>

namespace dai {

/**
 * Specify ImageManip options
 */
struct ImageManipProperties {

    /**
     * Crop rectrangle normalized xmin, ymin (top left point), xmax, ymax (bottom right point)
     */
    struct CropRect {
        // Normalized range 0-1
        float xmin = 0.0f, ymin = 0.0f, xmax = 0.0f, ymax = 0.0f;
    };

    struct CropConfig {
        CropRect cropRect;
        bool enableCenterCropRectangle = false;
        // if enableCenterCropRectangle -> automatically calculated crop parameters
        float cropRatio = 1.0f, widthHeightAspectRatio = 1.0f;
    };

    struct ResizeConfig {
        int width = 0, height = 0;
        bool lockAspectRatioFill = false;
        char bgRed = 0, bgGreen = 0, bgBlue = 0;
    };

    enum class PixelFormat {
        BGR, RGB, GRAY
    };

    struct FormatConfig {
        PixelFormat pixelFormat;
        bool interleave = false;  
        bool normalizeFp16 = false;
        bool flipHorizontal = false;
    };


    // crop stage, crops input image before passing to Resize stage
    CropConfig cropConfig;
    
    // Resize stage, resizes the image before passing to Format stage
    ResizeConfig resizeConfig;

    // Formats the final image
    FormatConfig formatConfig;

    bool enableCrop = false;
    bool enableResize = false;
    bool enableFormat = false;

    // Whether to wait for config at 'inputConfig' io
    bool inputConfigSync = false;

    // Maximum output frame size in bytes (eg: 300x300 BGR image -> 300*300*3 bytes)
    int outputFrameSize = 1*1024*1024;
    
    // Num frames in pool
    int numFramesPool = 4;

};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImageManipProperties::CropRect, xmin, ymin, xmax, ymax)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImageManipProperties::CropConfig, cropRect, enableCenterCropRectangle, cropRatio, widthHeightAspectRatio)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImageManipProperties::ResizeConfig, width, height, lockAspectRatioFill, bgRed, bgGreen, bgBlue)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImageManipProperties::FormatConfig, pixelFormat, interleave, normalizeFp16, flipHorizontal)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImageManipProperties, cropConfig, resizeConfig, formatConfig, enableCrop, enableResize, enableFormat, inputConfigSync, outputFrameSize, numFramesPool)

}  // namespace dai

