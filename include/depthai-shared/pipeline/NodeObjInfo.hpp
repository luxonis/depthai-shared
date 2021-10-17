#pragma once

#include <unordered_map>

#include "NodeIoInfo.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// NodeObj information structure
struct NodeObjInfo {
    int64_t id = -1;
    std::string name;
    std::unordered_map<std::string, NodeIoInfo> ioInfo;
    std::vector<std::uint8_t> properties;
};

DEPTHAI_SERIALIZE_EXT(NodeObjInfo, id, name, properties, ioInfo);

}  // namespace dai
