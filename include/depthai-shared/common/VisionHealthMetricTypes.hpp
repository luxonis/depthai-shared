#pragma once
#include <cstdint>
#include <iostream>

namespace dai {

/**
 * Get USB Speed
 */

enum class VisionHealthMetricTypes : uint32_t { DepthVariance, FillRate, EdgeHoleRate, Laplacian };

inline std::string toString(const VisionHealthMetricTypes& m) {
    switch(m) {
        case VisionHealthMetricTypes::DepthVariance:
            return "DepthVariance";
        case VisionHealthMetricTypes::FillRate:
            return "FillRate";
        case VisionHealthMetricTypes::EdgeHoleRate:
            return "EdgeHoleRate";
        case VisionHealthMetricTypes::Laplacian:
            return "Laplacian";
        default:
            return "Unknown";
    }
}

inline std::ostream& operator<<(std::ostream& os, const VisionHealthMetricTypes& m) {
    os << dai::toString(m);
    return os;
}

}  // namespace dai