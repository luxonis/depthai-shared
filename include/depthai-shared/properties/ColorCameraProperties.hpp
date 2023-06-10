#pragma once

#include "depthai-shared/common/CameraBoardSocket.hpp"
#include "depthai-shared/common/CameraImageOrientation.hpp"
#include "depthai-shared/datatype/RawCameraControl.hpp"
#include "depthai-shared/properties/Properties.hpp"
#include "depthai-shared/datatype/RawImgFrame.hpp"

namespace dai {

/**
 *  Specify properties for ColorCamera such as camera ID, ...
 */
struct ColorCameraProperties : PropertiesSerializable<Properties, ColorCameraProperties> {
    static constexpr int AUTO = -1;

    struct IspScale {
        int32_t horizNumerator = 0;
        int32_t horizDenominator = 0;
        int32_t vertNumerator = 0;
        int32_t vertDenominator = 0;

        DEPTHAI_SERIALIZE(IspScale, horizNumerator, horizDenominator, vertNumerator, vertDenominator);
    };

    /**
     * Select the camera sensor resolution
     */
    enum class SensorResolution : int32_t {
        /// 1920 × 1080
        THE_1080_P,
        /// 3840 × 2160
        THE_4_K,
        /// 4056 × 3040
        THE_12_MP,
        /// 4208 × 3120
        THE_13_MP,
        /// 1280 × 720
        THE_720_P,
        /// 1280 × 800
        THE_800_P,
        /// 1920 × 1200
        THE_1200_P,
        /// 2592 × 1944
        THE_5_MP,
        /// 4000 × 3000
        THE_4000X3000,
        /// 5312 × 6000
        THE_5312X6000,
        /// 8000 × 6000
        THE_48_MP,
        /// 240 x 180
        THE_240X180,
        /// 1280 x 962
        THE_1280X962,
        /// 2000 × 1500
        THE_2000X1500,
        /// 2028 × 1520
        THE_2028X1520,
        /// 2104 × 1560
        THE_2104X1560,
    };

    /**
     * For 24 bit color these can be either RGB or BGR
     */
    enum class ColorOrder : int32_t { BGR, RGB };

    /*
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
     * Frame type
    */
    RawImgFrame::Type previewType = RawImgFrame::Type::BGR888p;
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
    float sensorCropX = AUTO;
    float sensorCropY = AUTO;

    /**
     * Whether to keep aspect ratio of input (video size) or not
     */
    bool previewKeepAspectRatio = true;

    /**
     * Configure scaling for `isp` output.
     */
    IspScale ispScale;

    /**
     * Pool sizes
     */
    int numFramesPoolRaw = 3;
    int numFramesPoolIsp = 3;
    int numFramesPoolVideo = 4;
    int numFramesPoolPreview = 4;
    int numFramesPoolStill = 4;

    /**
     * Warp mesh source
     */
    enum class WarpMeshSource { AUTO = -1, NONE, CALIBRATION, URI };
    WarpMeshSource warpMeshSource = WarpMeshSource::AUTO;
    std::string warpMeshUri = "";
    int warpMeshWidth, warpMeshHeight;
    float calibAlpha = 1.0f;
    int warpMeshStepWidth = 32;
    int warpMeshStepHeight = 32;
};

DEPTHAI_SERIALIZE_EXT(ColorCameraProperties,
                      initialControl,
                      boardSocket,
                      cameraName,
                      imageOrientation,
                      colorOrder,
                      interleaved,
                      previewType,
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
                      previewKeepAspectRatio,
                      ispScale,
                      numFramesPoolRaw,
                      numFramesPoolIsp,
                      numFramesPoolVideo,
                      numFramesPoolPreview,
                      numFramesPoolStill,
                      warpMeshSource,
                      warpMeshUri,
                      warpMeshWidth,
                      warpMeshHeight,
                      calibAlpha,
                      warpMeshStepWidth,
                      warpMeshStepHeight);

}  // namespace dai
