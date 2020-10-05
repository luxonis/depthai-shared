#pragma once

#include <nlohmann/json.hpp>

namespace dai {

struct NodeObjInfo {
    int64_t id = -1;
    std::string name;
    nlohmann::json properties;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(NodeObjInfo, id, name, properties)

}  // namespace dai
