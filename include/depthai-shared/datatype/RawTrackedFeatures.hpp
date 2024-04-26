#pragma once
#include <cstdint>
#include <vector>
#include <array>

#include "RawFeatureTrackerConfig.hpp"
#include "depthai-shared/common/Point2f.hpp"
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/**
 * TrackedFeature structure
 *
 */
struct TrackedFeature {
    /**
     *  x, y position of the detected feature
     */
    Point2f position;

    /**
     *  Feature ID. Persistent between frames if motion estimation is enabled.
     */
    uint32_t id = 0;

    /**
     *  Feature age in frames
     */
    uint32_t age = 0;

    /**
     *  Feature harris score
     */
    float harrisScore = 0.f;

    /**
     *  Feature tracking error
     */
    float trackingError = 0.f;

    /**
     *  Feature descriptor
     */
    std::array<uint8_t, 32> descriptor = {0};
};
DEPTHAI_SERIALIZE_EXT(TrackedFeature, position, id, age, harrisScore, trackingError, descriptor);

/// RawTrackedFeatures structure
struct RawTrackedFeatures : public RawBuffer {
    std::vector<TrackedFeature> trackedFeatures;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::TrackedFeatures;
    };

    DEPTHAI_SERIALIZE(RawTrackedFeatures, trackedFeatures, RawBuffer::sequenceNum, RawBuffer::ts, RawBuffer::tsDevice);
};

}  // namespace dai
