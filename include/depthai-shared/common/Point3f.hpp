#pragma once

// std
#include <cstdint>

// libraries
#include "nlohmann/json.hpp"

namespace dai {

struct Point3f {
    float x, y, z;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Point3f, x, y, z);
};

}  // namespace dai
