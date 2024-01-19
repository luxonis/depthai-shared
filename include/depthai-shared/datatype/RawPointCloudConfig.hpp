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
    int config = 0;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::PointCloudConfig;
    };

    DatatypeEnum getType() const override {
        return DatatypeEnum::PointCloudConfig;
    }

    DEPTHAI_SERIALIZE(RawPointCloudConfig, config);
};

}  // namespace dai
