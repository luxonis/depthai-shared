#pragma once

// std
#include <chrono>
#include <cstdint>

#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// Timestamp structure
struct Timestamp {
    int64_t sec = 0, nsec = 0;
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> get() const {
        using namespace std::chrono;
        return time_point<steady_clock, steady_clock::duration>{seconds(sec) + nanoseconds(nsec)};
    }
};

DEPTHAI_SERIALIZE_EXT(Timestamp, sec, nsec);

struct Duration {
    int64_t sec = 0, nsec = 0;
    std::chrono::duration<int64_t, std::nano> get() const {
        using namespace std::chrono;
        return duration<int64_t, std::nano>{seconds(sec) + nanoseconds(nsec)};
    }
    void set(std::chrono::duration<int64_t, std::nano> dur) {
        using namespace std::chrono;
        sec = duration_cast<seconds>(dur).count();
        nsec = duration_cast<nanoseconds>(dur).count() % 1000000000;
    }

    std::chrono::duration<int64_t, std::nano> get() const {
        using namespace std::chrono;
        return duration<int64_t, std::nano>{seconds(sec) + nanoseconds(nsec)};
    }
};

DEPTHAI_SERIALIZE_EXT(Duration, sec, nsec);

}  // namespace dai
