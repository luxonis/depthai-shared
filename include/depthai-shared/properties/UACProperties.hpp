#pragma once

#include <nlohmann/json.hpp>

namespace dai {

/**
 * Properties for UAC node
 */
struct UACProperties {

    /**
     * Front L/R by default
     */
    bool streamBackMic = false;

    /**
     * Experimental, control the gain automatically (digital AGC)
     */
    bool enableAgc = false;

    /**
     * Configurable fixed mic gain (x times)
     */
    float micGain = 1.0;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UACProperties, streamBackMic, enableAgc, micGain);

}  // namespace dai
