#pragma once
#include <cstdint>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// RawAprilTags configuration structure
struct RawAprilTagConfig : public RawBuffer {
    enum class Type : std::int32_t { TAG_36H11 = 0, TAG_25H9, TAG_16H5, TAG_CIR21H7, TAG_CIR49H12, TAG_CUST48H12, TAG_STAND41H12, TAG_STAND52H13 };

    Type type = Type::TAG_36H11;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::AprilTagConfig;
    };

    DEPTHAI_SERIALIZE(RawAprilTagConfig, type);
};

}  // namespace dai
