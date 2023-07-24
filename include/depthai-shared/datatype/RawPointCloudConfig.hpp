#pragma once
#include <cstdint>
#include <vector>

#include "RawImgFrame.hpp"
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// RawPointCloudConfig configuration structure
struct RawPointCloudConfig : public RawBuffer {

    float minDist = 1000;
    float maxDist = 5000;
    float minAngle = -4500;
    float maxAngle = 4500;
    float minHeight = -100;
    float maxHeight = 500;
    uint32_t numRings = 8;
    uint32_t numSectors = 6;
    uint32_t occupancyThreshold = 1;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::PointCloudConfig;
    };

    DEPTHAI_SERIALIZE(RawPointCloudConfig, minDist, maxDist, minAngle, maxAngle, minHeight, maxHeight, numRings, numSectors, occupancyThreshold);
};

}  // namespace dai
