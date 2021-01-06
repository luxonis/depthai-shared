#pragma once

#include <nlohmann/json.hpp>

#include "depthai-shared/pb/common/CameraBoardSocket.hpp"

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
     * Which socket will color camera use
     */
    CameraBoardSocket boardSocket = CameraBoardSocket::AUTO;

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
     * Preview frame output width
     */
    int32_t videoWidth = -1;

    /**
     * Preview frame output height
     */
    int32_t videoHeight = -1;

    /**
     * Preview frame output width
     */
    int32_t stillWidth = -1;

    /**
     * Preview frame output height
     */
    int32_t stillHeight = -1;

    /**
     * Select the camera sensor resolution
     */
    SensorResolution resolution = SensorResolution::THE_1080_P;
    /**
     * Camera sensor FPS
     */
    float fps = 30.0;

    /**
     * Initial sensor crop, -1 signifies center crop
     */
    float sensorCropX = -1;
    float sensorCropY = -1;

    /**
     * Whether to wait for config at 'inputConfig' io
     */
    bool inputConfigSync = false;

    /**
     * Whether to keep aspect ratio of input (video size) or not
     */
    bool previewKeepAspectRatio = true;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ColorCameraProperties,
                                   boardSocket,
                                   colorOrder,
                                   interleaved,
                                   fp16,
                                   previewHeight,
                                   previewWidth,
                                   videoWidth,
                                   videoHeight,
                                   stillWidth,
                                   stillHeight,
                                   resolution,
                                   fps,
                                   sensorCropX,
                                   sensorCropY,
                                   inputConfigSync,
                                   previewKeepAspectRatio);

}  // namespace dai
