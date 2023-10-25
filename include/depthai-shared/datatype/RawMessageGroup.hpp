#pragma once

#include <cstdint>

#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"

namespace dai {

struct RawGroupMessage {
    dai::DatatypeEnum datatype;
    std::shared_ptr<RawBuffer> buffer;
    uint32_t index = 0;

    DEPTHAI_SERIALIZE(RawGroupMessage, datatype, index);
};

}  // namespace dai

namespace dai {

struct RawMessageGroup : public RawBuffer {
    std::unordered_map<std::string, RawGroupMessage> group;
    bool success = false;

   public:
    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::MessageGroup;
    };

    void updateMeta() {
        uint32_t index = 0;
        for(auto& entry : group) {
            entry.second.index = index++;
        }
    }

    DEPTHAI_SERIALIZE(RawMessageGroup, group, success, RawBuffer::ts, RawBuffer::tsDevice);
};

}  // namespace dai
