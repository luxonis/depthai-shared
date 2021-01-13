#pragma once

#include <nlohmann/json.hpp>

namespace dai {

/**
 * Chip temperature information.
 *
 * Multiple temperature measurement points and their average
 */
struct ChipTemperature { 
    float css, mss, upa0, upa1;
    float average;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ChipTemperature, css, mss, upa0, upa1, average);
 
}  // namespace dai