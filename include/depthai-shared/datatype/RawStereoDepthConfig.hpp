#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"

namespace dai {

/**
 * BilateralFilter configuration
 *
 * Contains configuration for sigma value.
 */

/// BilateralFilter configuration data structure
struct StereoDepthConfigData {
    /**
     * Median filter config for disparity post-processing
     */
    enum class MedianFilter : int32_t { MEDIAN_OFF = 0, KERNEL_3x3 = 3, KERNEL_5x5 = 5, KERNEL_7x7 = 7 };
    /**
     * Set kernel size for disparity/depth median filtering, or disable
     */
    MedianFilter median = MedianFilter::KERNEL_5x5;
    /**
     * Confidence threshold for disparity calculation, 0..255
     */
    std::int32_t confidenceThreshold = 200;

    /**
     * Sigma value for bilateral filter. 0 means disabled
     */
    int16_t bilateralSigmaValue = 0;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(StereoDepthConfigData, median, confidenceThreshold, bilateralSigmaValue);

/// RawBilateralFilter configuration structure
struct RawStereoDepthConfig : public RawBuffer {
    StereoDepthConfigData config;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::StereoDepthConfig;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawStereoDepthConfig, config);
};

}  // namespace dai