#pragma once

#include "depthai-shared/datatype/RawAudioInConfig.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Properties for UAC node
 */
struct UACProperties : PropertiesSerializable<Properties, UACProperties> {
    /// Initial AudioIn config
    RawAudioInConfig initialConfig;

    /**
     * Enable speaker over UAC
     */
    bool enableSpeaker = false;

    /**
     * Configure speaker volume, 0..100
     */
    uint8_t speakerVolume = 70;

    /**
     * Front L/R by default
     */
    bool streamBackMic = false;

    /**
     * Experimental, control the gain automatically (digital AGC)
     */
    bool enableAgc = false;

    /**
     * Audio sample rate
     */
    uint32_t sampleRateHz = 48000;

    /**
     * I2S read size [samples]. Set a lower value to reduce latency
     */
    uint32_t i2sReadSizeSamples = 1440;

    /**
     * XLink send size [samples]
     */
    uint32_t xlinkSendSizeSamples = 1440;

    /**
     * XLink send interleaved samples (from all mics), as opposed to "planar"
     */
    bool xlinkSendInterleaved = true;

    /**
     * Apply the configured `micGain` for XLink output as well (not only UAC)
     */
    bool xLinkApplyMicGain = true;

    /**
     * Native MIC data is 24-bit. Optionally change to 16-bit or 32-bit
     */
    uint8_t xlinkSampleSizeBytes = 3;
};

DEPTHAI_SERIALIZE_EXT(UACProperties,
                      enableSpeaker,
                      speakerVolume,
                      initialConfig,
                      streamBackMic,
                      enableAgc,
                      sampleRateHz,
                      i2sReadSizeSamples,
                      xlinkSendSizeSamples,
                      xlinkSendInterleaved,
                      xLinkApplyMicGain,
                      xlinkSampleSizeBytes);

}  // namespace dai
