#pragma once

#include <nlohmann/json.hpp>

namespace dai {

    /**
     * Properties for XLinkOut which define stream name
     */
    struct XLinkOutProperties {
        /**
         * Set a limit to how many packets will be sent further to host
         */
        float maxFpsLimit;
        std::string streamName;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(XLinkOutProperties, maxFpsLimit, streamName)

}
