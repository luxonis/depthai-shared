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

    unsigned int height;
    unsigned int width;
    unsigned int quality;
    Profile profile;

    bool lossless; // jpeg
    FrameType type; // h264

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::EncodedFrame;
    };

    DEPTHAI_SERIALIZE(RawEncodedFrame, height, width, quality, profile, lossless, type, RawBuffer::sequenceNum, RawBuffer::ts, RawBuffer::tsDevice);
};

}