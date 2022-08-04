#pragma once
#include <cstdint>
#include <vector>

#include "RawSpatialLocationCalculatorConfig.hpp"
#include "depthai-shared/common/Point3f.hpp"
#include "depthai-shared/common/Rect.hpp"
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/**
 * SpatialLocations structure
 *
 * Contains configuration data, average depth for the calculated ROI on depth map.
 * Together with spatial coordinates: x,y,z relative to the center of depth map.
 * Units are in depth units (millimeter by default).
 */
struct SpatialLocations {
    /**
     *  Configuration for selected ROI
     */
    SpatialLocationCalculatorConfigData config;
    /**
     *  Average of depth values inside the ROI between the specified thresholds in config
     */
    float depthAverage = 0.f;
    /**
     *  Minimum of depth values inside the ROI between the specified thresholds in config
     */
    std::uint16_t depthMin = 0;
    /**
     *  Maximum of depth values inside the ROI between the specified thresholds in config
     */
    std::uint16_t depthMax = 0;
    /**
     *  Number of depth values used to calculate depthAverage based on config
     */
    std::uint32_t depthAveragePixelCount = 0;
    /**
     *  Spatial coordinates - x,y,z; x,y are the relative positions of the center of ROI to the center of depth map
     */
    Point3f spatialCoordinates;
};
DEPTHAI_SERIALIZE_EXT(SpatialLocations, config, depthAverage, depthMin, depthMax, depthAveragePixelCount, spatialCoordinates);

/// RawSpatialLocations structure
struct RawSpatialLocations : public RawBuffer {
    std::vector<SpatialLocations> spatialLocations;

    // Related to input ImgFrame
    int64_t sequenceNum = 0;  // increments for each frame
    Timestamp ts = {};        // generation timestamp, synced to host time
    Timestamp tsDevice = {};  // generation timestamp, direct device monotonic clock

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::SpatialLocationCalculatorData;
    };

    DEPTHAI_SERIALIZE(RawSpatialLocations, spatialLocations, sequenceNum, ts, tsDevice);
};

}  // namespace dai
