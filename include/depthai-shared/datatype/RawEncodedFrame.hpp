#pragma once

#include "depthai-shared/common/Timestamp.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

struct RawEncodedFrame : public RawBuffer {
    enum class Profile : std::uint8_t {
        JPEG,
        AVC,
        HEVC
    };
    enum class FrameType : std::uint8_t {
        I,
        P,
        B,
        Unknown
    };

    unsigned int quality;
    Profile profile;

    bool lossless; // jpeg
    FrameType type; // h264

    unsigned int frameOffset = 0;
    unsigned int frameSize = 0;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::EncodedFrame;
    };

    DEPTHAI_SERIALIZE(RawEncodedFrame, quality, profile, lossless, type, frameOffset, frameSize, RawBuffer::sequenceNum, RawBuffer::ts, RawBuffer::tsDevice);
};

}