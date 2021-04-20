#pragma once

#include <depthai-shared/datatype/RawIMUData.hpp>
#include <nlohmann/json.hpp>

namespace dai {

/**
 * Specify IMU options such as camera ID, ...
 */
struct IMUProperties {
    std::int32_t accelerometerRate = 200;
    std::int32_t gyroRate = 200;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUProperties, accelerometerRate, gyroRate);

}  // namespace dai
