#pragma once

#include <nlohmann/json.hpp>

namespace dai {

/// NodeIo informations such as name, type, ...
struct NodeIoInfo {
    enum class Type { MSender, SSender, MReceiver, SReceiver };

    std::string group;
    std::string name;
    Type type = Type::SReceiver;
    bool blocking = true;
    int queueSize = 8;

    struct Options {
        bool waitForMessage = false;
    } options;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(NodeIoInfo::Options, waitForMessage);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(NodeIoInfo, group, name, type, blocking, queueSize, options);

}  // namespace dai
