#pragma once

#include <nlohmann/json.hpp>
#include <vector>

#include "NodeIoInfo.hpp"
namespace dai {

struct NodeObjInfo {
    int64_t id = -1;
    std::string name;
    nlohmann::json properties;
    std::vector<NodeIoInfo> ioInfo;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(NodeObjInfo, id, name, properties, ioInfo);

}  // namespace dai
