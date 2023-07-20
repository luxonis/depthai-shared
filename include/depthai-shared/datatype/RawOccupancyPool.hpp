#pragma once
#include <cstdint>
#include <vector>

#include "depthai-shared/common/Timestamp.hpp"
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// RawOccupancyPool structure
struct RawOccupancyPool : public RawBuffer {
    std::vector<std::vector<int>> occupancyPool;

    // Related to input ImgFrame
    int64_t sequenceNum = 0;  // increments for each frame
    Timestamp ts = {};        // generation timestamp, synced to host time
    Timestamp tsDevice = {};  // generation timestamp, direct device monotonic clock

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::OccupancyPool;
    };

    DEPTHAI_SERIALIZE(RawOccupancyPool, occupancyPool, sequenceNum, ts, tsDevice);
};

}  // namespace dai
