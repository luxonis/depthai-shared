#pragma once

#include "depthai-shared/properties/Properties.hpp"
#include "depthai-shared/datatype/RawAudioInConfig.hpp"

namespace dai {

/**
 * Specify properties for AudioProc
 */
struct AudioProcProperties : PropertiesSerializable<Properties, AudioProcProperties> {
    /// Initial AudioIn config
    RawAudioInConfig initialConfig;

    /**
     * This options specifies how many frames are available in this node's pool.
     * Helps when receiver is slow at consuming.
     *
     * Value "0" indicates automatic number of frames assignment
     */
    std::uint32_t numFramesPool = 0;

    /**
     * Sample rate to pre-process the incoming data. AudioProc needs the sound
     * data downsampled to 16kHz first, otherwise the performance may be affected.
     * Values different than 16000 are experimental. Allowed for now: 16000, 24000, 48000
     */
    int sampleRate = 16000;
};

DEPTHAI_SERIALIZE_EXT(AudioProcProperties, initialConfig, numFramesPool, sampleRate);

}  // namespace dai
