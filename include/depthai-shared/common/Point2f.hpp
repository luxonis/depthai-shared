#pragma once

// std
#include <cstdint>

// project
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/**
 * Point2f structure
 *
 * x and y coordinates that define a 2D point.
 */
struct Point2f {
    Point2f() = default;
    Point2f(float x, float y) {
        this->x = x;
        this->y = y;
    }
    float x = 0, y = 0;

    bool isNormalized() const {
        // When ambiguous, default to denormalized - this is to avoid breaking existing code TODO(refactor)
        if((x == 0 || x == 1) && (y == 0 || y == 1)) return false;
        return x >= 0 && x <= 1 && y >= 0 && y <= 1;
    }
};

DEPTHAI_SERIALIZE_EXT(Point2f, x, y);

}  // namespace dai
