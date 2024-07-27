#pragma once
#include <array>
#include <cstdint>
#include <depthai-shared/common/optional.hpp>
#include <string>
#include <vector>

#include "depthai-shared/common/Point2f.hpp"
#include "depthai-shared/common/VisionHealthMetricTypes.hpp"
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/**
 * AbsoluteVisionHealthConfig structure
 *
 */
struct AbsoluteVisionHealthConfig {
    float threshold;
    std::string oper;
};
DEPTHAI_SERIALIZE_EXT(AbsoluteVisionHealthConfig, threshold, oper);

/**
 * RelativeVisionHealthConfig structure
 *
 */
struct RelativeVisionHealthConfig {
    tl::optional<float> threshold;
    std::string oper;
    float sigmas;
};
DEPTHAI_SERIALIZE_EXT(RelativeVisionHealthConfig, threshold, oper, sigmas);

/// RawVisionHealthConfig structure
struct RawVisionHealthConfig : public RawBuffer {
    int depthVarianceRelativeWindowSize = 30;
    int edgeHoleRateRelativeWindowSize = 30;
    float depthHoleRateThreshold = 10.0;
    float edgeStrengthThreshold = 300.0;
    float edgeHoleRateThreshold = 10.0;
    int edgeHoleRateKernelSize = 5;

    // Constant padding value if image is not perfectly divisible by the block size.
    float depthtHoleRateCval = 400;

    std::unordered_map<VisionHealthMetricTypes, AbsoluteVisionHealthConfig> absoluteVisionHealthConfigs;
    std::unordered_map<VisionHealthMetricTypes, RelativeVisionHealthConfig> relativeVisionHealthConfigs;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::VisionHealthConfig;
    };

    DEPTHAI_SERIALIZE(RawVisionHealthConfig,
                      absoluteVisionHealthConfigs,
                      relativeVisionHealthConfigs,
                      depthVarianceRelativeWindowSize,
                      depthHoleRateThreshold,
                      edgeStrengthThreshold,
                      edgeHoleRateThreshold,
                      edgeHoleRateRelativeWindowSize,
                      edgeHoleRateKernelSize,
                      depthtHoleRateCval,
                      RawBuffer::sequenceNum,
                      RawBuffer::ts,
                      RawBuffer::tsDevice);
};

}  // namespace dai
