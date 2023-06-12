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
        /**
     * Whether rectangle is normalized (coordinates in [0,1] range) or not.
     */
    bool isNormalized() const {
        if(x <= 1.f && y <= 1.f) return true;
        return !(x == static_cast<int>(x) && y == static_cast<int>(y));
    }

    /**
     * Denormalize point.
     * @param width Destination frame width.
     * @param height Destination frame height.
     */
    Point2f denormalize(int width, int height) {
        if(isNormalized()) {
            float _x = std::round(this->x * width);
            float _y = std::round(this->y * height);
            return Point2f(_x, _y);
        }
        return *this;
    }

    /**
     * Normalize point.
     * @param width Source frame width.
     * @param height Source frame height.
     */
    Point2f normalize(int width, int height) {
        if(isNormalized()) {
            return *this;
        }
        float _x = this->x / width;
        float _y = this->y / height;
        return Point2f(_x, _y);
    }
};

DEPTHAI_SERIALIZE_EXT(Point2f, x, y);

}  // namespace dai
