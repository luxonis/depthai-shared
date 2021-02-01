#pragma once

#include <nlohmann/json.hpp>

namespace dai {

struct NodeIoInfo {
    enum class Type { MSender, SSender, MReceiver, SReceiver };

    std::string name;
    Type type = Type::SReceiver;
    bool blocking = true;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(NodeIoInfo, name, type, blocking);

}  // namespace dai
