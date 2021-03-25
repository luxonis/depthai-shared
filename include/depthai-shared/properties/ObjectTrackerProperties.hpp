#pragma once

// std
#include <vector>

// libraries
#include <nlohmann/json.hpp>

// project

#include "depthai-shared/common/optional.hpp"

namespace dai {

enum class TrackType : std::int32_t {
    // Ability to track the objects without accessing image data.
    ZERO_TERM_IMAGELESS = 5,
    // Tracking based on histogram.
    ZERO_TERM_COLOR_HISTOGRAM
};

/**
 * Properties for ObjectTracker
 */
struct ObjectTrackerProperties {
    float trackerThreshold = 0.0;
    std::int32_t maxObjectsToTrack = 60;
    std::vector<std::uint32_t> detectionLabelsToTrack;
    TrackType trackType = TrackType::ZERO_TERM_IMAGELESS;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ObjectTrackerProperties, trackerThreshold, maxObjectsToTrack, detectionLabelsToTrack, trackType)

}  // namespace dai
