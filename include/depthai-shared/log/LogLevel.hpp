#pragma once

// std
#include <cstdint>

// libraries
#include <nlohmann/json.hpp>

// project
#include "depthai-shared/common/Timestamp.hpp"

namespace dai {

// Follows spdlog levels
enum class LogLevel : std::int32_t {
    TRACE = 0,
    DEBUG,
    INFO,
    WARN,
    ERR,
    CRITICAL,
    OFF
};

struct LogMsg {

    std::string nodeIdName;
    LogLevel level;
    Timestamp time;
    size_t colorRangeStart{0};
    size_t colorRangeEnd{0};
    std::string payload;

};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LogMsg, nodeIdName, level, time, colorRangeStart, colorRangeEnd, payload);

} // namespace dai
