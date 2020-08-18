//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     NodeObjInfo.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace dai {
namespace gen {
    using nlohmann::json;

    struct NodeObjInfo {
        int64_t id;
        std::string name;
        nlohmann::json properties;
    };
}
}
