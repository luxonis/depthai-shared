#pragma once

#include "RawBuffer.hpp"
#include "RawImgDetections.hpp"
#include "depthai-shared/common/Point3f.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/**
 * SpatialImgDetection structure
 *
 * Contains image detection results together with spatial location data.
 */
struct SpatialImgDetection : public ImgDetection {
    Point3f spatialCoordinates;
};

DEPTHAI_SERIALIZE_EXT(SpatialImgDetection, label, confidence, xmin, ymin, xmax, ymax, spatialCoordinates);

/// RawSpatialImgDetections structure
struct RawSpatialImgDetections : public RawBuffer {
    std::vector<SpatialImgDetection> detections;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::SpatialImgDetections;
    };

    DEPTHAI_SERIALIZE(RawSpatialImgDetections, detections);
};

}  // namespace dai
