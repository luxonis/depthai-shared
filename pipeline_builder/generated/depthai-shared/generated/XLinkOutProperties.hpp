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
#include "helper.hpp"

namespace dai {
namespace gen {
    /**
     * Properties for XLinkOut which define stream name
     */

    using nlohmann::json;

    /**
     * Properties for XLinkOut which define stream name
     */
    struct XLinkOutProperties {
        /**
         * Set a limit to how many packets will be sent further to host
         */
        double maxFpsLimit;
        std::string streamName;
    };
}
}
