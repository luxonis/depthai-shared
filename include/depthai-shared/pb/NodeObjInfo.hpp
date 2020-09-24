#pragma once

#include <nlohmann/json.hpp>

namespace dai {
    
    struct NodeObjInfo {
        int64_t id;
        std::string name;
        nlohmann::json properties;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(NodeObjInfo, id, name, properties)
    
}
