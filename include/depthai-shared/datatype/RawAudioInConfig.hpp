#pragma once
#include <cstdint>
#include <vector>


#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// AudioInConfigData configuration data structure
struct AudioInConfigData {
    /**
     * Configurable fixed mic gain (x times)
     */
    float micGain = 1.0;

    /**
     * Don't send packets on node's outputs if set
     */
    bool disableOutput = false;

    /**
     * Pass through input data to output directly
     * (relevant if the node is doing processing)
     */
    bool passThrough = false;
};
DEPTHAI_SERIALIZE_EXT(AudioInConfigData, micGain, disableOutput, passThrough);

/// RawAudioInConfig configuration structure
struct RawAudioInConfig : public RawBuffer {
    AudioInConfigData config;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::AudioInConfig;
    };

    DEPTHAI_SERIALIZE(RawAudioInConfig, config);
};

}  // namespace dai
