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
     * Maximum phase unwrapping level.
     */
    int maxPhaseUnwrappingLevel = 4;

    tl::optional<bool> enableFPPNCorrection;
    tl::optional<bool> enableOpticalCorrection;
    tl::optional<bool> enableTemperatureCorrection;
    tl::optional<bool> enableWiggleCorrection;
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
                      enableFPPNCorrection,
                      enableOpticalCorrection,
                      enableTemperatureCorrection,
                      enableWiggleCorrection,
                      enablePhaseUnwrapping,
                      maxPhaseUnwrappingLevel);
};

}  // namespace dai
