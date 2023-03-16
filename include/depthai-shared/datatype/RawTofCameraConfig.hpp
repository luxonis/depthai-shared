#pragma once
#include <cstdint>
#include <vector>

#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// RawTofCameraConfig configuration structure
struct RawTofCameraConfig : public RawBuffer {
    
    int dummy;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::TofCameraConfig;
    };

    DEPTHAI_SERIALIZE(RawTofCameraConfig, dummy);
};

}  // namespace dai
