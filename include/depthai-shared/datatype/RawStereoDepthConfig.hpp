#pragma once
#include <cstdint>
#include <depthai-shared/common/optional.hpp>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"

namespace dai {

/**
 * Median filter config for disparity post-processing
 */
enum class MedianFilter : int32_t { MEDIAN_OFF = 0, KERNEL_3x3 = 3, KERNEL_5x5 = 5, KERNEL_7x7 = 7 };

/// RawStereoDepthConfig configuration structure
struct RawStereoDepthConfig : public RawBuffer {
    using MedianFilter = dai::MedianFilter;

    struct AlgorithmControl {
        /**
         * Computes and combines disparities in both L-R and R-L directions, and combine them.
         * For better occlusion handling
         */
        bool enableLeftRightCheck = false;

        /**
         * Disparity range increased from 95 to 190, combined from full resolution and downscaled images.
         * Suitable for short range objects
         */
        bool enableExtended = false;

        /**
         * Computes disparity with sub-pixel interpolation (5 fractional bits), suitable for long range
         */
        bool enableSubpixel = false;

        /**
         * Left-right check threshold for left-right, right-left disparity map combine, 0..128
         * Used only when left-right check mode is enabled.
         * Defines the maximum difference between the confidence of pixels from left-right and right-left confidence maps
         */
        std::int32_t leftRightCheckThreshold = 4;

        /**
         * Number of fractional bits for subpixel mode.
         * Valid values: 3,4,5.
         * Defines the number of fractional disparities: 2^x.
         * Median filter postprocessing is supported only for 3 fractional bits.
         */
        std::int32_t subpixelFractionalBits = 3;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(AlgorithmControl, enableLeftRightCheck, enableExtended, enableSubpixel, leftRightCheckThreshold, subpixelFractionalBits);
    };

    /**
     * Controls the flow of stereo algorithm: left-right check, subpixel etc.
     */
    AlgorithmControl algorithmControl;

    struct PostProcessing {
        /**
         * Set kernel size for disparity/depth median filtering, or disable
         */
        MedianFilter median = MedianFilter::KERNEL_5x5;

        /**
         * Sigma value for bilateral filter. 0 means disabled
         * A larger value of the parameter means that farther colors within the pixel neighborhood will be mixed together.
         */
        std::int16_t bilateralSigmaValue = 0;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PostProcessing, median, bilateralSigmaValue);
    };

    /**
     * Controls the postprocessing of disparity and/or depth map.
     */
    PostProcessing postProcessing;

    struct CensusTransform {
        /**
         * Census transform kernel size possible values.
         */
        enum class KernelSize : std::int32_t { AUTO = -1, KERNEL_5x5 = 0, KERNEL_7x7, KERNEL_7x9 };

        /**
         * Census transform kernel size.
         */
        KernelSize kernelSize = KernelSize::AUTO;

        /**
         * Census transform mask, default: auto, mask is set based on resolution and kernel size.
         * Disabled for 400p input resolution.
         * Enabled for 720p.
         * 0XA82415 for 5x5 census transform kernel.
         * 0XAA02A8154055 for 7x7 census transform kernel.
         * 0X2AA00AA805540155 for 7x9 census transform kernel.
         * Empirical values.
         */
        uint64_t kernelMask = 0;

        /**
         * If enabled, each pixel in the window is compared with the mean window value instead of the central pixel.
         */
        bool enableMeanMode = false;

        /**
         * Census transform comparation treshold value.
         */
        uint32_t threshold = 0;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CensusTransform, kernelSize, kernelMask, enableMeanMode, threshold);
    };

    /**
     * Census transform settings.
     */
    CensusTransform censusTransform;

    struct CostMatching {
        /**
         * Disparity search range: 64 or 96 pixels are supported by the HW.
         */
        enum class DisparityWidth : std::uint32_t { DISPARITY_64, DISPARITY_96 };

        /**
         * Disparity search range, default 96 pixels.
         */
        DisparityWidth disparityWidth = DisparityWidth::DISPARITY_96;

        /**
         * Disparity companding using sparse matching.
         * Matching pixel by pixel for N disparities.
         * Matching every 2nd pixel for M disparitites.
         * Matching every 4th pixel for T disparities.
         * In case of 96 disparities: N=48, M=32, T=16.
         * This way the search range is extended to 176 disparities, by sparse matching.
         * Note: when enabling this flag only depth map will be affected, disparity map is not.
         */
        bool enableCompanding = false;

        /**
         * Used only for debug purposes, SW postprocessing handled only invalid value of 0 properly.
         */
        uint8_t invalidDisparityValue = 0;

        /**
         * Disparities with confidence value under this threshold are accepted.
         * Higher confidence threshold means disparities with less confidence are accepted too.
         */
        uint8_t confidenceThreshold = 230;

        /**
         * The linear equation applied for computing the cost is:
         * COMB_COST = α*AD + β*(CTC<<3).
         * CLAMP(COMB_COST >> 5, threshold).
         * Where AD is the Absolute Difference between 2 pixels values.
         * CTC is the Census Transform Cost between 2 pixels, based on Hamming distance (xor).
         * The α and β parameters are subject to fine fine tuning by the user.
         */
        struct LinearEquationParameters {
            uint8_t alpha = 8;
            uint8_t beta = 12;
            uint8_t threshold = 127;

            NLOHMANN_DEFINE_TYPE_INTRUSIVE(LinearEquationParameters, alpha, beta, threshold);
        };

        /**
         * Cost calculation linear equation parameters.
         */
        LinearEquationParameters linearEquationParameters;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CostMatching, disparityWidth, enableCompanding, invalidDisparityValue, confidenceThreshold, linearEquationParameters);
    };

    /**
     * Cost matching settings.
     */
    CostMatching costMatching;

    struct CostAggregation {
        static constexpr const std::array<uint16_t, 256> defaultHorizontalPenaltyCosts = {
            0xfffa, 0xfffa, 0xfa7d, 0xa653, 0x7d3e, 0x6432, 0x5329, 0x4723, 0x3e1f, 0x371b, 0x3219, 0x2d16, 0x2914, 0x2613, 0x2311, 0x2110, 0x1f0f, 0x1d0e,
            0x1b0d, 0x1a0d, 0x190c, 0x170b, 0x160b, 0x150a, 0x140a, 0x140a, 0x1309, 0x1209, 0x1108, 0x1108, 0x1008, 0x1008, 0x0f07, 0x0f07, 0x0e07, 0x0e07,
            0x0d06, 0x0d06, 0x0d06, 0x0c06, 0x0c06, 0x0c06, 0x0b05, 0x0b05, 0x0b05, 0x0b05, 0x0a05, 0x0a05, 0x0a05, 0x0a05, 0x0a05, 0x0904, 0x0904, 0x0904,
            0x0904, 0x0904, 0x0804, 0x0804, 0x0804, 0x0804, 0x0804, 0x0804, 0x0804, 0x0703, 0x0703, 0x0703, 0x0703, 0x0703, 0x0703, 0x0703, 0x0703, 0x0703,
            0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502,
            0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402,
            0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402,
            0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301,
            0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301,
            0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201,
            0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201,
            0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201,
            0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201,
            0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0100,
            0x0100, 0x0100, 0x0100, 0x0100,
        };

        static constexpr const std::array<uint16_t, 256> defaultVerticalPenaltyCosts = {
            0xfffa, 0xfffa, 0xfa7d, 0xa653, 0x7d3e, 0x6432, 0x5329, 0x4723, 0x3e1f, 0x371b, 0x3219, 0x2d16, 0x2914, 0x2613, 0x2311, 0x2110, 0x1f0f, 0x1d0e,
            0x1b0d, 0x1a0d, 0x190c, 0x170b, 0x160b, 0x150a, 0x140a, 0x140a, 0x1309, 0x1209, 0x1108, 0x1108, 0x1008, 0x1008, 0x0f07, 0x0f07, 0x0e07, 0x0e07,
            0x0d06, 0x0d06, 0x0d06, 0x0c06, 0x0c06, 0x0c06, 0x0b05, 0x0b05, 0x0b05, 0x0b05, 0x0a05, 0x0a05, 0x0a05, 0x0a05, 0x0a05, 0x0904, 0x0904, 0x0904,
            0x0904, 0x0904, 0x0804, 0x0804, 0x0804, 0x0804, 0x0804, 0x0804, 0x0804, 0x0703, 0x0703, 0x0703, 0x0703, 0x0703, 0x0703, 0x0703, 0x0703, 0x0703,
            0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0603, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502,
            0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0502, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402,
            0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402, 0x0402,
            0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301,
            0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301,
            0x0301, 0x0301, 0x0301, 0x0301, 0x0301, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201,
            0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201,
            0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201,
            0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201,
            0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0100,
            0x0100, 0x0100, 0x0100, 0x0100,
        };

        // TBD
        uint8_t divisionFactor = 1;

        tl::optional<std::array<uint16_t, 256>> horizontalPenaltyCosts;

        tl::optional<std::array<uint16_t, 256>> verticalPenaltyCosts;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CostAggregation, divisionFactor, horizontalPenaltyCosts, verticalPenaltyCosts);
    };

    /**
     * Cost aggregation settings.
     */
    CostAggregation costAggregation;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::StereoDepthConfig;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawStereoDepthConfig, algorithmControl, postProcessing, censusTransform, costMatching, costAggregation);
};

}  // namespace dai
