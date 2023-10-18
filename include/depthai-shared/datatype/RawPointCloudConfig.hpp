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
    float maxDist = 7000;
    float minAngle = -5500;
    float maxAngle = 5500;
    float minHeight = -500;
    float maxHeight = 500;
    uint32_t numRings = 8;
    uint32_t numSectors = 6;
    uint32_t numVoxels = 16;
    uint32_t occupancyThreshold = 8000;

    std::array<std::array<float, 3>, 3> transformationMatrix = {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};

    float scale = 1.f;

    bool useFastMath = false;

    bool occupancy3d = false;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::PointCloudConfig;
    };

    DEPTHAI_SERIALIZE(RawPointCloudConfig,
                      minDist,
                      maxDist,
                      minAngle,
                      maxAngle,
                      minHeight,
                      maxHeight,
                      numRings,
                      numSectors,
                      numVoxels,
                      occupancyThreshold,
                      transformationMatrix,
                      scale,
                      useFastMath,
                      occupancy3d);
};

}  // namespace dai
