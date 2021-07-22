#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"
#include "RawFeatureTrackerConfig.hpp"
#include "depthai-shared/common/Point2f.hpp"

namespace dai {

/**
 * TrackedFeatures structure
 *
 */
struct TrackedFeatures {
    /**
     *  x, y position of the detected feature
     */
    Point2f position;
    /**
     *  Feature ID
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
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TrackedFeatures, position, id, age, harrisScore, trackingError);

/// RawTrackedFeatures structure
struct RawTrackedFeatures : public RawBuffer {
    std::vector<TrackedFeatures> trackedFeatures;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::FeatureTrackerData;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawTrackedFeatures, trackedFeatures);
};

}  // namespace dai
