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
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UACProperties, streamBackMic);

}  // namespace dai
