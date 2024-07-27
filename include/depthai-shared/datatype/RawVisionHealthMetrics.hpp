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
 * AbsoluteVisionHealthMetric structure
 *
 */
struct AbsoluteVisionHealthMetric {
    float value;
};
DEPTHAI_SERIALIZE_EXT(AbsoluteVisionHealthMetric, value);

/**
 * RelativeVisionHealthMetric structure
 *
 */
struct RelativeVisionHealthMetric {
    float value;
    float mean;
    float variance;
};
DEPTHAI_SERIALIZE_EXT(RelativeVisionHealthMetric, value, mean, variance);

/// RawVisionHealthMetrics structure
struct RawVisionHealthMetrics : public RawBuffer {
    std::unordered_map<VisionHealthMetricTypes, AbsoluteVisionHealthMetric> absoluteVisionHealthMetrics;
    std::unordered_map<VisionHealthMetricTypes, RelativeVisionHealthMetric> relativeVisionHealthMetrics;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::VisionHealthMetrics;
    };

    DEPTHAI_SERIALIZE(
        RawVisionHealthMetrics, absoluteVisionHealthMetrics, relativeVisionHealthMetrics, RawBuffer::sequenceNum, RawBuffer::ts, RawBuffer::tsDevice);
};

}  // namespace dai
