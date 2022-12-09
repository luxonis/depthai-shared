#pragma once

#include "depthai-shared/common/CameraBoardSocket.hpp"
#include "depthai-shared/common/CameraImageOrientation.hpp"
#include "depthai-shared/datatype/RawCameraControl.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 *  Specify properties for ColorCamera such as camera ID, ...
 */
struct CameraProperties : PropertiesSerializable<Properties, CameraProperties> {
    static constexpr int AUTO = -1;

    /**
     * For 24 bit color these can be either RGB or BGR
     */
    enum class ColorOrder : int32_t { BGR, RGB };

    /**
     * Initial controls applied to ColorCamera node
     */
    RawCameraControl initialControl;

    /**
     * Which socket will color camera use
     */
    CameraBoardSocket boardSocket = CameraBoardSocket::AUTO;

    /**
     * Which camera name will color camera use
     */
    std::string cameraName = "";

    /**
     * Camera sensor image orientation / pixel readout
     */
    CameraImageOrientation imageOrientation = CameraImageOrientation::AUTO;

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
    int32_t videoWidth = AUTO;

    /**
     * Preview frame output height
     */
    int32_t videoHeight = AUTO;

    /**
     * Preview frame output width
     */
    int32_t stillWidth = AUTO;

    /**
     * Preview frame output height
     */
    int32_t stillHeight = AUTO;

    /**
     * Select the camera sensor width
     */
    int32_t resolutionWidth = AUTO;
    /**
     * Select the camera sensor height
     */
    int32_t resolutionHeight = AUTO;

    /**
     * Camera sensor FPS
     */
    float fps = 30.0;

    /**
     * Initial sensor crop, -1 signifies center crop
     */
    float sensorCropX = AUTO;
    float sensorCropY = AUTO;

    /**
     * Whether to keep aspect ratio of input (video size) or not
     */
    bool previewKeepAspectRatio = true;

    // /**
    //  * Configure scaling for `isp` output.
    //  */
    // IspScale ispScale;

    /// Type of sensor, specifies what kind of postprocessing is performed
    CameraSensorType sensorType = CameraSensorType::AUTO;

    /**
     * Pool sizes
     */
    int numFramesPoolRaw = 3;
    int numFramesPoolIsp = 3;
    int numFramesPoolVideo = 4;
    int numFramesPoolPreview = 4;
    int numFramesPoolStill = 4;
};

DEPTHAI_SERIALIZE_EXT(CameraProperties,
                      initialControl,
                      boardSocket,
                      cameraName,
                      imageOrientation,
                      colorOrder,
                      interleaved,
                      fp16,
                      previewHeight,
                      previewWidth,
                      videoWidth,
                      videoHeight,
                      stillWidth,
                      stillHeight,
                      resolutionWidth,
                      resolutionHeight,
                      fps,
                      sensorCropX,
                      sensorCropY,
                      previewKeepAspectRatio,
                      ispScale,
                      sensorType,
                      numFramesPoolRaw,
                      numFramesPoolIsp,
                      numFramesPoolVideo,
                      numFramesPoolPreview,
                      numFramesPoolStill);

}  // namespace dai
