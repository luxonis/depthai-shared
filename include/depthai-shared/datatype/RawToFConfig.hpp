#pragma once
#include <cstdint>
#include <depthai-shared/common/optional.hpp>
#include <vector>

#include "depthai-shared/common/MedianFilter.hpp"
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// RawToFConfig configuration structure
struct RawToFConfig : public RawBuffer {
    /**
     * Set kernel size for depth median filtering, or disable
     */
    MedianFilter median = MedianFilter::MEDIAN_OFF;

    /*
     * Phase unwrapping level.
     */
    int phaseUnwrappingLevel = 4;

    /*
     * Phase unwrapping error threshold.
     */
    uint16_t phaseUnwrapErrorThreshold = 100;

    /*
     * Enable phase shuffle temporal filter.
     * Temporal filter that averages the shuffle and non-shuffle frequencies.
     */
    bool enablePhaseShuffleTemporalFilter = true;

    /*
     * Enable burst mode.
     * Decoding is performed on a series of 4 frames.
     * Outputf fps will be 4 times lower, but reduces motion blur artifacts.
     */
    bool enableBurstMode = false;

    /*
     * Enable FPN correction. Used for debugging.
     */
    tl::optional<bool> enableFPPNCorrection;
    /*
     * Enable optical correction. Used for debugging.
     */
    tl::optional<bool> enableOpticalCorrection;
    /*
     * Enable temperature correction. Used for debugging.
     */
    tl::optional<bool> enableTemperatureCorrection;
    /*
     * Enable wiggle correction. Used for debugging.
     */
    tl::optional<bool> enableWiggleCorrection;
    /*
     * Enable phase unwrapping. Used for debugging.
     */
    tl::optional<bool> enablePhaseUnwrapping;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::ToFConfig;
    };

    DatatypeEnum getType() const override {
        return DatatypeEnum::ToFConfig;
    }

    DEPTHAI_SERIALIZE(RawToFConfig,
                      median,
                      enablePhaseShuffleTemporalFilter,
                      enableBurstMode,
                      enableFPPNCorrection,
                      enableOpticalCorrection,
                      enableTemperatureCorrection,
                      enableWiggleCorrection,
                      enablePhaseUnwrapping,
                      phaseUnwrappingLevel,
                      phaseUnwrapErrorThreshold);
};

}  // namespace dai
