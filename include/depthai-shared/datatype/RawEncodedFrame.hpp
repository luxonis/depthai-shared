#pragma once

#include "depthai-shared/common/Timestamp.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

struct RawEncodedFrame : public RawBuffer {
    enum class Profile : std::uint8_t { JPEG, AVC, HEVC };
    enum class FrameType : std::uint8_t { I, P, B, Unknown };

    struct CameraSettings {
        int32_t exposureTimeUs;
        int32_t sensitivityIso;
        int32_t lensPosition;
        int32_t wbColorTemp;

        DEPTHAI_SERIALIZE(CameraSettings, exposureTimeUs, sensitivityIso, lensPosition, wbColorTemp);
    };

    CameraSettings cam;
    uint32_t instanceNum = 0;  // Which source created this frame (color, mono, ...)

    uint32_t quality;
    uint32_t bitrate;
    Profile profile;

    bool lossless;   // jpeg
    FrameType type;  // h264

    uint32_t frameOffset = 0;
    uint32_t frameSize = 0;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::EncodedFrame;
    };

    DatatypeEnum getType() const override {
        return DatatypeEnum::EncodedFrame;
    }

    DEPTHAI_SERIALIZE(RawEncodedFrame,
                      cam,
                      instanceNum,
                      quality,
                      bitrate,
                      profile,
                      lossless,
                      type,
                      frameOffset,
                      frameSize,
                      RawBuffer::sequenceNum,
                      RawBuffer::ts,
                      RawBuffer::tsDevice);
};

}  // namespace dai
