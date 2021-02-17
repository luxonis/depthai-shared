#pragma once

// std
#include <cstdint>

// libraries
#include "nlohmann/json.hpp"

namespace dai {

struct Point2f {
    float x, y;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Point2f, x, y);
};

}  // namespace dai
