#pragma once

#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// NodeIo informations such as name, type, ...
struct NodeIoInfo {
    enum class Type { MSender, SSender, MReceiver, SReceiver };

    std::string name;
    Type type = Type::SReceiver;
    bool blocking = true;
    int queueSize = 8;
};

DEPTHAI_SERIALIZE_EXT(NodeIoInfo, name, type, blocking, queueSize);

}  // namespace dai
