#pragma once

// std
#include <cstdint>

// libraries
#include <chrono>

#include "nlohmann/json.hpp"

namespace dai {

struct Timestamp {
    int64_t sec, nsec;
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> getTimestamp() const {
        using namespace std::chrono;
        return time_point<steady_clock, steady_clock::duration>{seconds(sec) + nanoseconds(nsec)};
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Timestamp, sec, nsec);
};

}  // namespace dai
