#pragma once
#include <cstdint>
#include <vector>
#include <array>

#include "RawImgFrame.hpp"
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// RawPointCloudConfig configuration structure
struct RawPointCloudConfig : public RawBuffer {
    bool sparse = false;

    std::array<std::array<float, 4>, 4> transformationMatrix = {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::PointCloudConfig;
    };

    DatatypeEnum getType() const override {
        return DatatypeEnum::PointCloudConfig;
    }

    DEPTHAI_SERIALIZE(RawPointCloudConfig, sparse, transformationMatrix);
};

}  // namespace dai
