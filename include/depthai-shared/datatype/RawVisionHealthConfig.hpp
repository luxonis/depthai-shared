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

    std::vector<dai::VisionHealthMetricTypes> visionHealthConfigs;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::VisionHealthConfig;
    };

    DEPTHAI_SERIALIZE(RawVisionHealthConfig,
                      visionHealthConfigs,
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
