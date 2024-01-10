#pragma once

#include <cstdint>

#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"

namespace dai {

struct RawPointCloudData : public RawBuffer {
    unsigned int width;        // width in pixels
    unsigned int height;       // height in pixels
    uint32_t instanceNum = 0;  // Which source created this frame (color, mono, ...)
    float minx, miny, minz;
    float maxx, maxy, maxz;

   public:
    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::PointCloudData;
    };

    DatatypeEnum getType() const override {
        return DatatypeEnum::PointCloudData;
    }

    DEPTHAI_SERIALIZE(
        RawPointCloudData, width, height, minx, miny, minz, maxx, maxy, maxz, instanceNum, RawBuffer::ts, RawBuffer::tsDevice, RawBuffer::sequenceNum);
};

}  // namespace dai
