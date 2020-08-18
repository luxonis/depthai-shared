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
#include "helper.hpp"

namespace dai {
namespace gen {
    /**
     * Properties for XLinkIn which define stream name
     */

    using nlohmann::json;

    /**
     * Properties for XLinkIn which define stream name
     */
    struct XLinkInProperties {
        std::string streamName;
    };
}
}
