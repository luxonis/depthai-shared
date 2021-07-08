#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"

namespace dai {

/// FeatureTracker configuration data structure
struct FeatureTrackerConfigData {
    int dummy;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FeatureTrackerConfigData, dummy);

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
