#pragma once

#include "depthai-shared/common/Timestamp.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai
{

struct RawTraceEvent :public RawBuffer {
    enum Event : std::uint8_t {
        SEND,
        RECEIVE,
        // PULL,
    };
    enum class Status : std::uint8_t {
        START,
        END,
        TIMEOUT,
    };

    Event event;
    Status status;
    uint32_t srcId;
    uint32_t dstId;
    Timestamp timestamp;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::TraceEvent;
    };

    DEPTHAI_SERIALIZE(RawTraceEvent, event, status, srcId, dstId, timestamp);
};




} // namespace dai
