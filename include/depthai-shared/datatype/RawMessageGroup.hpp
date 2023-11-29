#pragma once

#include <cstdint>

#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"

namespace dai {

struct RawGroupMessage {
    std::shared_ptr<RawBuffer> buffer;
    uint32_t index = 0;

    DEPTHAI_SERIALIZE(RawGroupMessage, index);
};

}  // namespace dai

namespace dai {

struct RawMessageGroup : public RawBuffer {
    std::unordered_map<std::string, RawGroupMessage> group;

   public:
    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::MessageGroup;
    };

    DatatypeEnum getType() const override {
        return DatatypeEnum::MessageGroup;
    }

    DEPTHAI_SERIALIZE(RawMessageGroup, group, RawBuffer::ts, RawBuffer::tsDevice, RawBuffer::sequenceNum);
};

}  // namespace dai
