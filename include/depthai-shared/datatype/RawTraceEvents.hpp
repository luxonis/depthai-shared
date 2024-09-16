#pragma once

#include "depthai-shared/common/Timestamp.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

struct RawQueueTraceEvent : public RawBuffer {
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
    uint32_t queueSize;
    Timestamp timestamp;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::QueueTraceEvent;
    };

    DEPTHAI_SERIALIZE(RawQueueTraceEvent, event, status, srcId, dstId, queueSize, timestamp);
};

struct RawNodeTraceEvent : public RawBuffer {
    uint32_t nodeId;
    Timestamp timeLoopStart;
    Timestamp timeProcStart;  // Time after the node got all the messages needed to process
    Timestamp timeProcEnd;
    Timestamp timeLoopEnd;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::NodeTraceEvent;
    };

    DEPTHAI_SERIALIZE(RawNodeTraceEvent, nodeId, timeLoopStart, timeProcStart, timeProcEnd, timeLoopEnd);
};

}  // namespace dai
