#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"

namespace dai {

/// FeatureTracker configuration data structure
struct FeatureTrackerConfigData {
    enum class AlgorithmType : std::int32_t {
        /// Performs only corner detection
        CORNER_DETECTION,
        /// Performs corner detection + optical flow
        CORNER_DETECTION_WITH_OPTICAL_FLOW
    };

    enum class CornerDetector : std::int32_t {
        /// Harris corner detector
        HARRIS,
        /// Shi-Thomasi corner detector
        SHI_THOMASI
    };

    AlgorithmType algorithmType = AlgorithmType::CORNER_DETECTION_WITH_OPTICAL_FLOW;

    /// Corner detection algorithm type
    CornerDetector cornerDetector = CornerDetector::HARRIS;

    /**
     * Target number of features to detect
     * maximum number of features is determined at runtime based on algorithm type
     */
    std::int32_t targetNrFeatures = 320;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FeatureTrackerConfigData, algorithmType, cornerDetector, targetNrFeatures);

/// RawSpatialLocation configuration structure
struct RawFeatureTrackerConfig : public RawBuffer {
    FeatureTrackerConfigData config;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::FeatureTrackerConfig;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawFeatureTrackerConfig, config);
};

}  // namespace dai
