//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     XLinkInProperties.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>

namespace dai {

    /**
     * Properties for XLinkIn which define stream name
     */
    struct XLinkInProperties {
        std::string streamName;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(XLinkInProperties, streamName)
    
}
