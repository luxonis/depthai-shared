//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     NodeConnectionSchema.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace dai {
namespace gen {
    /**
     * Specifies a connection between nodes IOs
     */

    using nlohmann::json;

    /**
     * Specifies a connection between nodes IOs
     */
    struct NodeConnectionSchema {
        int64_t node1Id;
        std::string node1Output;
        int64_t node2Id;
        std::string node2Input;
    };
}
}
