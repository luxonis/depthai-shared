#pragma once

#include "RawBuffer.hpp"
#include "depthai-shared/common/Point3f.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// ImgDetection structure
struct ImgDetection {
    uint32_t label;
    float confidence;
    float xmin;
    float ymin;
    float xmax;
    float ymax;
};

DEPTHAI_SERIALIZE_EXT(ImgDetection, label, confidence, xmin, ymin, xmax, ymax);

/// RawImgDetections structure
struct RawImgDetections : public RawBuffer {
    std::vector<ImgDetection> detections;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::ImgDetections;
    };

    DEPTHAI_SERIALIZE(RawImgDetections, detections);
};

}  // namespace dai
