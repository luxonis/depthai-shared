#pragma once

#include <nlohmann/json.hpp>

namespace dai {

/**
 * Specify MonoCamera options such as camera ID, ...
 */
struct MonoCameraProperties {
    /**
     * Select the camera sensor resolution: 1280×720, 1280×800, 640×400
     */
    enum class SensorResolution : int32_t { THE_720_P, THE_800_P, THE_400_P };

    /**
     * Which mono camera the node will use
     */
    int32_t camId = 1;
    /**
     * Select the camera sensor resolution
     */
    SensorResolution resolution = SensorResolution::THE_720_P;
    /**
     * Camera sensor FPS
     */
    float fps = 30.0;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MonoCameraProperties, camId, resolution, fps)

}  // namespace dai
