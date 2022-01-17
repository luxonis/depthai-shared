#pragma once
#include <cstdint>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"
#include "RawFeatureTrackerConfig.hpp"
#include "depthai-shared/common/Point2f.hpp"
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
    uint32_t id;

    /**
     *  Feature age in frames
     */
    uint32_t age;
    /**
     *  Feature harris score
     */
    float harrisScore;

    /**
     *  Feature tracking error
     */
    float trackingError;

};
DEPTHAI_SERIALIZE_EXT(TrackedFeature, position, id, age, harrisScore, trackingError);

/// RawTrackedFeatures structure
struct RawTrackedFeatures : public RawBuffer {
    std::vector<TrackedFeature> trackedFeatures;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::TrackedFeatures;
    };

    DEPTHAI_SERIALIZE(RawTrackedFeatures, trackedFeatures);
};

}  // namespace dai
