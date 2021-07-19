#pragma once

#include <nlohmann/json.hpp>

namespace dai {

/**
 * Properties for UVC node
 */
struct UVCProperties {
    /// <gpio_number, value> list for GPIOs to set at init
    std::unordered_map<int, int> gpioInit;

    /// <gpio_number, value> list for GPIOs to set when streaming is enabled
    std::unordered_map<int, int> gpioStreamOn;

    /// <gpio_number, value> list for GPIOs to set when streaming is disabled
    std::unordered_map<int, int> gpioStreamOff;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UVCProperties, gpioInit, gpioStreamOn, gpioStreamOff);

}  // namespace dai
