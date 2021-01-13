#pragma once

#include <nlohmann/json.hpp>

namespace dai {

/**
 * CpuUsage structure
 *
 * Average usage in percent and time span of the average (since last query)
 */
struct CpuUsage { 
    float average;
    int32_t msTime;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CpuUsage, average, msTime);


}  // namespace dai