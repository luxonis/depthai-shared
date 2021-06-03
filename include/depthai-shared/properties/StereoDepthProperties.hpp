#pragma once

#include <depthai-shared/common/EepromData.hpp>
#include <depthai-shared/common/optional.hpp>
#include <nlohmann/json.hpp>

#include "depthai-shared/common/CameraBoardSocket.hpp"

namespace dai {

/**
 * Specify properties for StereoDepth
 */
struct StereoDepthProperties {
    /**
     * Median filter config for disparity post-processing
     */
    enum class MedianFilter : int32_t { MEDIAN_OFF = 0, KERNEL_3x3 = 3, KERNEL_5x5 = 5, KERNEL_7x7 = 7 };

    /**
     * Align the disparity/depth to the perspective of a rectified output, or center it
     */
    enum class DepthAlign : int32_t { RECTIFIED_RIGHT, RECTIFIED_LEFT, CENTER };

    /**
     * Calibration data byte array
     */
    std::vector<std::uint8_t> calibration;

    EepromData calibrationData;

    /**
     * Set kernel size for disparity/depth median filtering, or disable
     */
    MedianFilter median = MedianFilter::KERNEL_5x5;
    /**
     * Set the disparity/depth alignment to the perspective of a rectified output, or center it
     */
    DepthAlign depthAlign = DepthAlign::RECTIFIED_RIGHT;
    /**
     * Which camera to align disparity/depth to.
     * When configured (not AUTO), takes precedence over 'depthAlign'
     */
    CameraBoardSocket depthAlignCamera = CameraBoardSocket::AUTO;
    /**
     * Confidence threshold for disparity calculation, 0..255
     */
    std::int32_t confidenceThreshold = 200;

    bool enableRectification = true;
    /**
     * Computes and combines disparities in both L-R and R-L directions, and combine them.
     * For better occlusion handling
     */
    bool enableLeftRightCheck = false;
    /**
     * Computes disparity with sub-pixel interpolation (5 fractional bits), suitable for long range
     */
    bool enableSubpixel = false;
    /**
     * Disparity range increased from 96 to 192, combined from full resolution and downscaled images.
     * Suitable for short range objects
     */
    bool enableExtendedDisparity = false;
    /**
     * Mirror rectified frames: true to have disparity/depth normal (non-mirrored)
     */
    bool rectifyMirrorFrame = true;
    /**
     * Fill color for missing data at frame edges: grayscale 0..255, or -1 to replicate pixels
     */
    std::int32_t rectifyEdgeFillColor = -1;
    /**
     * Input frame width. Optional (taken from MonoCamera nodes if they exist)
     */
    tl::optional<std::int32_t> width;
    /**
     * Input frame height. Optional (taken from MonoCamera nodes if they exist)
     */
    tl::optional<std::int32_t> height;

    // TODO: rectification mesh option for fisheye camera use-cases
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(StereoDepthProperties,
                                   calibration,
                                   calibrationData,
                                   median,
                                   depthAlign,
                                   depthAlignCamera,
                                   confidenceThreshold,
                                   enableRectification,
                                   enableLeftRightCheck,
                                   enableSubpixel,
                                   enableExtendedDisparity,
                                   rectifyMirrorFrame,
                                   rectifyEdgeFillColor,
                                   width,
                                   height);

}  // namespace dai
