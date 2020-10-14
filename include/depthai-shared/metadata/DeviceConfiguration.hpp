#pragma once

#include <nlohmann/json.hpp>

// TODO (if necessary)

namespace dai {
/*
struct EEPROM {
    int version;
    std::array<float, 9> calibrationHomography;
    float leftCameraFov;
};
*/

struct DeviceConfiguration {
    std::string version;
    std::string commit;
};

}  // namespace dai
