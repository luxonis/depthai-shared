//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     XLinkOutProperties.hpp data = nlohmann::json::parse(jsonString);

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
