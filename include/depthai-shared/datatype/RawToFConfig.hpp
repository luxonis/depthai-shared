#pragma once
#include <cstdint>
#include <vector>

#include "depthai-shared/common/MedianFilter.hpp"
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// RawToFConfig configuration structure
struct RawToFConfig : public RawBuffer {
    /**
     * DepthParams configuration structure.
     */
    struct DepthParams {
        /**
         * Enable averaging between phases with same modulation frequency(e.g. for ToF cameras with phase shuffle).
         * The depth frame rate will be half if this is enabled
         */
        bool avgPhaseShuffle = false;

        /**
         * Perform depth calculation only for pixels with amplitude greater than provided value
         */
        float minimumAmplitude = 5.0;

        /**
         * Frequency modulation frames used for depth calculation. If the ToF sensor supports multiple modulation frequencies,
         * all will be used for depth calculation.
         */
        enum class TypeFMod : std::int32_t { F_MOD_ALL, F_MOD_MIN, F_MOD_MAX };

        TypeFMod freqModUsed = TypeFMod::F_MOD_MIN;

        /**
         * Set kernel size for depth median filtering, or disable
         */
        MedianFilter median = MedianFilter::KERNEL_5x5;

        /**
         * Temperature coefficient A
         */
        float temperatureCoefficientA = 0.0f;

        /**
         * Temperature coefficient B
         */
        float temperatureCoefficientB = 0.0f;

        DEPTHAI_SERIALIZE(DepthParams, avgPhaseShuffle, minimumAmplitude, freqModUsed, median, temperatureCoefficientA, temperatureCoefficientB);
    };

    /**
     * DepthParams configuration.
     * Used for configuring the ToF.
     */
    DepthParams depthParams;

    bool enableFPPN = true;
    bool enableDistanceToDepth = true;
    bool enableTemperatureCorrection = true;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::ToFConfig;
    };

    DatatypeEnum getType() const override {
        return DatatypeEnum::ToFConfig;
    }

    DEPTHAI_SERIALIZE(RawToFConfig, depthParams, enableFPPN, enableDistanceToDepth, enableTemperatureCorrection);
};

}  // namespace dai
