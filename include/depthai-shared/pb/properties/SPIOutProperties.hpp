//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     SPIOutProperties.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>

namespace dai {

    /**
     * Properties for SPIOut which define stream name
     */
    struct SPIOutProperties {
        /**
         * Set a limit to how many packets will be sent further to host
         */
        std::string streamName;
        int busId;

    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SPIOutProperties, streamName, busId)

}
