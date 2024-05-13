#pragma once
#include <cstdint>
#include <vector>

#include "RawImgFrame.hpp"
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// RawImageAlignConfig configuration structure
struct RawImageAlignConfig : public RawBuffer {
    /**
     * Optional static depth plane to align to, in depth units, by default millimeters
     */
    uint16_t staticDepthPlane = 0;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::ImageAlignConfig;
    };

    DEPTHAI_SERIALIZE(RawImageAlignConfig, staticDepthPlane);
};

}  // namespace dai