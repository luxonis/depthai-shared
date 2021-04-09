#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"
#include "RawSpatialLocationCalculatorConfig.hpp"
#include "depthai-shared/common/Point3f.hpp"
#include "depthai-shared/common/Rect.hpp"

namespace dai {

/**
 * Spatial location information structure
 *
 * Contains configuration data, average depth for the calculated ROI on depth map.
 * Together with spatial coordinates: x,y,z relative to the center of depth map.
 * Units are in millimeters.
 */
struct SpatialLocations {
    // Configuration for selected ROI
    SpatialLocationCalculatorConfigData config;
    // Average of depth values inside the ROI between the specified thresholds in config
    float depthAverage;
    // Number of depth values used to calculate depthAverage based on config
    std::uint32_t depthAveragePixelCount;
    // Spatial coordinates: x,y,z; x,y are the relative positions of the center of ROI to the center of depth map
    Point3f spatialCoordinates;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SpatialLocations, config, depthAverage, depthAveragePixelCount, spatialCoordinates);

struct RawSpatialLocations : public RawBuffer {
    std::vector<SpatialLocations> spatialLocations;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::SpatialLocationCalculatorData;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawSpatialLocations, spatialLocations);
};

}  // namespace dai