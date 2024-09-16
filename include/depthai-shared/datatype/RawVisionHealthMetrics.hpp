#pragma once
#include <array>
#include <cstdint>
#include <vector>

#include "depthai-shared/common/VisionHealthMetricTypes.hpp"
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/**
 * VisionHealthMetric structure
 *
 */
struct VisionHealthMetric {
    float value;
};
DEPTHAI_SERIALIZE_EXT(VisionHealthMetric, value);

/// RawVisionHealthMetrics structure
struct RawVisionHealthMetrics : public RawBuffer {
    std::unordered_map<VisionHealthMetricTypes, VisionHealthMetric> visionHealthMetrics;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::VisionHealthMetrics;
    };

    DEPTHAI_SERIALIZE(RawVisionHealthMetrics, visionHealthMetrics, RawBuffer::sequenceNum, RawBuffer::ts, RawBuffer::tsDevice);
};

}  // namespace dai
