#pragma once

#include "RawBuffer.hpp"

namespace dai {

struct ImgDetection {
    
    uint32_t label;
    float confidence;
    float xmin;
    float ymin;
    float xmax;
    float ymax;
    float xdepth;
    float ydepth;
    float zdepth;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ImgDetection, label, confidence, xmin, ymin, xmax, ymax, xdepth, ydepth, zdepth);
};

struct RawImgDetections : public RawBuffer {
    
    std::vector<ImgDetection> detections;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::ImgDetections;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawImgDetections, detections);
};

}  // namespace dai
