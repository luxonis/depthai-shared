#pragma once
#include <cstdint>
#include <vector>

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
    uint32_t id;
#if 0
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
#endif
};
DEPTHAI_SERIALIZE_EXT(TrackedFeature, position, id);

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
