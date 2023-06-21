#pragma once

// std
#include <cstdint>

// project
#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/**
 * Point2f structure
 *
 * x and y coordinates that define a 2D point.
 */
struct Point2f {
    Point2f() = default;
    Point2f(float x, float y, tl::optional<bool> normalized = tl::nullopt) {
        this->x = x;
        this->y = y;
        this->normalized = normalized;
    }
    float x = 0, y = 0;
    tl::optional<bool> normalized = tl::nullopt;

    bool isNormalized() const {
        if(normalized) {
            return *normalized;
        }
        // When ambiguous, default to denormalized
        if((x == 0 || x == 1) && (y == 0 || y == 1)) return false;
        return x >= 0 && x <= 1 && y >= 0 && y <= 1;
    }
};

DEPTHAI_SERIALIZE_EXT(Point2f, x, y);

}  // namespace dai
