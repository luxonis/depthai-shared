#pragma once

#include <nlohmann/json.hpp>

namespace dai {

/**
 * Specify ColorCamera options such as camera ID, ...
 */
struct ColorCameraProperties {
    /**
     * Select the camera sensor resolution
     */
    enum class SensorResolution : int32_t { THE_1080_P, THE_4_K, THE_12_MP };

    /**
     * For 24 bit color these can be either RGB or BGR
     */
    enum class ColorOrder : int32_t { BGR, RGB };

    /**
     * Which color camera the node will use
     */
    int32_t camId = 0;
    /**
     * For 24 bit color these can be either RGB or BGR
     */
    ColorOrder colorOrder = ColorOrder::BGR;
    /**
     * Are colors interleaved (R1G1B1, R2G2B2, ...) or planar (R1R2..., G1G2..., B1B2)
     */
    bool interleaved = true;
    /**
     * Are values FP16 type (0.0 - 255.0)
     */
    bool fp16 = false;
    /**
     * Preview frame output height
     */
    uint32_t previewHeight = 300;
    /**
     * Preview frame output width
     */
    uint32_t previewWidth = 300;
    /**
     * Select the camera sensor resolution
     */
    SensorResolution resolution = SensorResolution::THE_1080_P;
    /**
     * Camera sensor FPS
     */
    float fps = 30.0;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ColorCameraProperties, camId, colorOrder, interleaved, fp16, previewHeight, previewWidth, resolution, fps);

}  // namespace dai
