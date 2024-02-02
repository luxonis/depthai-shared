#pragma once

#include "depthai-shared/common/CameraBoardSocket.hpp"
#include "depthai-shared/common/CameraImageOrientation.hpp"
#include "depthai-shared/common/CameraSensorType.hpp"
#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/RawCameraControl.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 *  Specify properties for ColorCamera such as camera ID, ...
 */
struct CameraProperties : PropertiesSerializable<Properties, CameraProperties> {
    static constexpr int AUTO = -1;

    struct IspScale {
        int32_t horizNumerator = 0;
        int32_t horizDenominator = 0;
        int32_t vertNumerator = 0;
        int32_t vertDenominator = 0;

        DEPTHAI_SERIALIZE(IspScale, horizNumerator, horizDenominator, vertNumerator, vertDenominator);
    };

    enum class SensorResolution : int32_t {
        AUTO = -1,
        /// 1920 × 1080
        THE_1080_P,
        /// 3840 × 2160
        THE_4_K,
        /// 4056 × 3040
        THE_12_MP,
        /// 4208 × 3120
        THE_13_MP,
        /// 640 x 400
        THE_400_P,
        /// 640 x 480
        THE_480_P,
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
        /// 4224 x 3136
        THE_4224X3136,
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
        /// 1440 × 1080
        THE_1440X1080,
    };

    // class SensorResolution {
    //    public:
    //     enum Resolution : int32_t {
    //         AUTO = -1,
    //         /// 1920 × 1080
    //         THE_1080_P,
    //         /// 3840 × 2160
    //         THE_4_K,
    //         /// 4056 × 3040
    //         THE_12_MP,
    //         /// 4208 × 3120
    //         THE_13_MP,
    //         /// 640 x 400
    //         THE_400_P,
    //         /// 640 x 480
    //         THE_480_P,
    //         /// 1280 × 720
    //         THE_720_P,
    //         /// 1280 × 800
    //         THE_800_P,
    //         /// 1920 × 1200
    //         THE_1200_P,
    //         /// 2592 × 1944
    //         THE_5_MP,
    //         /// 4000 × 3000
    //         THE_4000X3000,
    //         /// 4224 x 3136
    //         THE_4224X3136,
    //         /// 5312 × 6000
    //         THE_5312X6000,
    //         /// 8000 × 6000
    //         THE_48_MP,
    //         /// 240 x 180
    //         THE_240X180,
    //         /// 1280 x 962
    //         THE_1280X962,
    //         /// 2000 × 1500
    //         THE_2000X1500,
    //         /// 2028 × 1520
    //         THE_2028X1520,
    //         /// 2104 × 1560
    //         THE_2104X1560,
    //         /// 1440 × 1080
    //         THE_1440X1080,
    //     };
    //     SensorResolution() = default;
    //     constexpr SensorResolution(Resolution aResolution) : resolution(aResolution) {}

    //     // Allow switch and comparisons.
    //     constexpr operator Resolution() const {
    //         return resolution;
    //     }
    //     explicit operator bool() const = delete;
    //     constexpr bool operator==(SensorResolution a) const {
    //         return resolution == a.resolution;
    //     }
    //     constexpr bool operator!=(SensorResolution a) const {
    //         return resolution != a.resolution;
    //     }

    //     static std::pair<int32_t, int32_t> toSize(SensorResolution resolution) {
    //         switch(resolution) {
    //             case THE_1080_P:
    //                 return {1920, 1080};
    //             case THE_4_K:
    //                 return {3840, 2160};
    //             case THE_12_MP:
    //                 return {4056, 3040};
    //             case THE_13_MP:
    //                 return {4208, 3120};
    //             case THE_400_P:
    //                 return {640, 400};
    //             case THE_480_P:
    //                 return {640, 480};
    //             case THE_720_P:
    //                 return {1280, 720};
    //             case THE_800_P:
    //                 return {1280, 800};
    //             case THE_1200_P:
    //                 return {1920, 1200};
    //             case THE_5_MP:
    //                 return {2592, 1944};
    //             case THE_4000X3000:
    //                 return {4000, 3000};
    //             case THE_4224X3136:
    //                 return {4224, 3136};
    //             case THE_5312X6000:
    //                 return {5312, 6000};
    //             case THE_48_MP:
    //                 return {8000, 6000};
    //             case THE_240X180:
    //                 return {240, 180};
    //             case THE_1280X962:
    //                 return {1280, 962};
    //             case THE_2000X1500:
    //                 return {2000, 1500};
    //             case THE_2028X1520:
    //                 return {2028, 1520};
    //             case THE_2104X1560:
    //                 return {2104, 1560};
    //             case THE_1440X1080:
    //                 return {1440, 1080};
    //             case AUTO:
    //                 return {-1, -1};
    //             default:
    //                 throw std::invalid_argument("Invalid resolution supplied to CameraProperties::SensorResolution::toSize");
    //         }
    //     }

    //     static SensorResolution fromSize(int32_t width, int32_t height) {
    //         if(width == 1920 && height == 1080) {
    //             return THE_1080_P;
    //         } else if(width == 3840 && height == 2160) {
    //             return THE_4_K;
    //         } else if(width == 4056 && height == 3040) {
    //             return THE_12_MP;
    //         } else if(width == 4208 && height == 3120) {
    //             return THE_13_MP;
    //         } else if(width == 640 && height == 400) {
    //             return THE_400_P;
    //         } else if(width == 640 && height == 480) {
    //             return THE_480_P;
    //         } else if(width == 1280 && height == 720) {
    //             return THE_720_P;
    //         } else if(width == 1280 && height == 800) {
    //             return THE_800_P;
    //         } else if(width == 1920 && height == 1200) {
    //             return THE_1200_P;
    //         } else if(width == 2592 && height == 1944) {
    //             return THE_5_MP;
    //         } else if(width == 4000 && height == 3000) {
    //             return THE_4000X3000;
    //         } else if(width == 4224 && height == 3136) {
    //             return THE_4224X3136;
    //         } else if(width == 5312 && height == 6000) {
    //             return THE_5312X6000;
    //         } else if(width == 8000 && height == 6000) {
    //             return THE_48_MP;
    //         } else if(width == 240 && height == 180) {
    //             return THE_240X180;
    //         } else if(width == 1280 && height == 962) {
    //             return THE_1280X962;
    //         } else if(width == 2000 && height == 1500) {
    //             return THE_2000X1500;
    //         } else if(width == 2028 && height == 1520) {
    //             return THE_2028X1520;
    //         } else if(width == 2104 && height == 1560) {
    //             return THE_2104X1560;
    //         } else if(width == 1440 && height == 1080) {
    //             return THE_1440X1080;
    //         } else {
    //             return AUTO;
    //         }
    //     }

    //     DEPTHAI_SERIALIZE(Resolution, resolution);
    //    private:
    //     Resolution resolution;
    // };

    SensorResolution resolution = SensorResolution::AUTO;

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
     * Preview frame output height
     */
    uint32_t previewHeight = 300;
    /**
     * Preview frame output width
     */
    uint32_t previewWidth = 300;

    static constexpr auto DEFAULT_PREVIEW_TYPE = ImgFrame::Type::RGB888i;

    /**
     * Preview output frame type.
     */
    ImgFrame::Type previewType = DEFAULT_PREVIEW_TYPE;

    /**
     * Preview frame output width
     */
    int32_t videoWidth = AUTO;

    /**
     * Preview frame output height
     */
    int32_t videoHeight = AUTO;

    static constexpr auto DEFAULT_VIDEO_TYPE = ImgFrame::Type::NV12;
    /**
     * video output frame type.
     */
    ImgFrame::Type videoType = DEFAULT_VIDEO_TYPE;

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
     * Isp 3A rate (auto focus, auto exposure, auto white balance, camera controls etc.).
     * Default (0) matches the camera FPS, meaning that 3A is running on each frame.
     * Reducing the rate of 3A reduces the CPU usage on CSS, but also increases the convergence rate of 3A.
     * Note that camera controls will be processed at this rate. E.g. if camera is running at 30 fps, and camera control is sent at every frame,
     * but 3A fps is set to 15, the camera control messages will be processed at 15 fps rate, which will lead to queueing.

     */
    int isp3aFps = 0;

    /**
     * Initial sensor crop, -1 signifies center crop
     */
    float sensorCropX = AUTO;
    float sensorCropY = AUTO;

    /**
     * Whether to keep aspect ratio of input (video/preview size) or not
     */
    bool previewKeepAspectRatio = false;

    /**
     * Configure scaling for `isp` output.
     */
    IspScale ispScale;

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

    /**
     * Configures whether the camera `raw` frames are saved as MIPI-packed to memory.
     * The packed format is more efficient, consuming less memory on device, and less data
     * to send to host: RAW10: 4 pixels saved on 5 bytes, RAW12: 2 pixels saved on 3 bytes.
     * When packing is disabled (`false`), data is saved lsb-aligned, e.g. a RAW10 pixel
     * will be stored as uint16, on bits 9..0: 0b0000'00pp'pppp'pppp.
     * Default is auto: enabled for standard color/monochrome cameras where ISP can work
     * with both packed/unpacked, but disabled for other cameras like ToF.
     */
    tl::optional<bool> rawPacked;
};

DEPTHAI_SERIALIZE_EXT(CameraProperties,
                      initialControl,
                      boardSocket,
                      cameraName,
                      imageOrientation,
                      previewHeight,
                      previewWidth,
                      previewType,
                      videoWidth,
                      videoHeight,
                      videoType,
                      stillWidth,
                      stillHeight,
                      resolutionWidth,
                      resolutionHeight,
                      resolution,
                      fps,
                      isp3aFps,
                      sensorCropX,
                      sensorCropY,
                      previewKeepAspectRatio,
                      ispScale,
                      sensorType,
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
                      warpMeshStepHeight,
                      rawPacked);

inline CameraProperties::SensorResolution sensorResolutionFromSize(int32_t width, int32_t height) {
    if(width == 1920 && height == 1080) {
        return CameraProperties::SensorResolution::THE_1080_P;
    } else if(width == 3840 && height == 2160) {
        return CameraProperties::SensorResolution::THE_4_K;
    } else if(width == 4056 && height == 3040) {
        return CameraProperties::SensorResolution::THE_12_MP;
    } else if(width == 4208 && height == 3120) {
        return CameraProperties::SensorResolution::THE_13_MP;
    } else if(width == 640 && height == 400) {
        return CameraProperties::SensorResolution::THE_400_P;
    } else if(width == 640 && height == 480) {
        return CameraProperties::SensorResolution::THE_480_P;
    } else if(width == 1280 && height == 720) {
        return CameraProperties::SensorResolution::THE_720_P;
    } else if(width == 1280 && height == 800) {
        return CameraProperties::SensorResolution::THE_800_P;
    } else if(width == 1920 && height == 1200) {
        return CameraProperties::SensorResolution::THE_1200_P;
    } else if(width == 2592 && height == 1944) {
        return CameraProperties::SensorResolution::THE_5_MP;
    } else if(width == 4000 && height == 3000) {
        return CameraProperties::SensorResolution::THE_4000X3000;
    } else if(width == 4224 && height == 3136) {
        return CameraProperties::SensorResolution::THE_4224X3136;
    } else if(width == 5312 && height == 6000) {
        return CameraProperties::SensorResolution::THE_5312X6000;
    } else if(width == 8000 && height == 6000) {
        return CameraProperties::SensorResolution::THE_48_MP;
    } else if(width == 240 && height == 180) {
        return CameraProperties::SensorResolution::THE_240X180;
    } else if(width == 1280 && height == 962) {
        return CameraProperties::SensorResolution::THE_1280X962;
    } else if(width == 2000 && height == 1500) {
        return CameraProperties::SensorResolution::THE_2000X1500;
    } else if(width == 2028 && height == 1520) {
        return CameraProperties::SensorResolution::THE_2028X1520;
    } else if(width == 2104 && height == 1560) {
        return CameraProperties::SensorResolution::THE_2104X1560;
    } else if(width == 1440 && height == 1080) {
        return CameraProperties::SensorResolution::THE_1440X1080;
    } else {
        return CameraProperties::SensorResolution::AUTO;
    }
}

inline std::pair<int32_t, int32_t> sensorResolutionToSize(CameraProperties::SensorResolution resolution) {
    switch(resolution) {
        case CameraProperties::SensorResolution::THE_1080_P:
            return {1920, 1080};
        case CameraProperties::SensorResolution::THE_4_K:
            return {3840, 2160};
        case CameraProperties::SensorResolution::THE_12_MP:
            return {4056, 3040};
        case CameraProperties::SensorResolution::THE_13_MP:
            return {4208, 3120};
        case CameraProperties::SensorResolution::THE_400_P:
            return {640, 400};
        case CameraProperties::SensorResolution::THE_480_P:
            return {640, 480};
        case CameraProperties::SensorResolution::THE_720_P:
            return {1280, 720};
        case CameraProperties::SensorResolution::THE_800_P:
            return {1280, 800};
        case CameraProperties::SensorResolution::THE_1200_P:
            return {1920, 1200};
        case CameraProperties::SensorResolution::THE_5_MP:
            return {2592, 1944};
        case CameraProperties::SensorResolution::THE_4000X3000:
            return {4000, 3000};
        case CameraProperties::SensorResolution::THE_4224X3136:
            return {4224, 3136};
        case CameraProperties::SensorResolution::THE_5312X6000:
            return {5312, 6000};
        case CameraProperties::SensorResolution::THE_48_MP:
            return {8000, 6000};
        case CameraProperties::SensorResolution::THE_240X180:
            return {240, 180};
        case CameraProperties::SensorResolution::THE_1280X962:
            return {1280, 962};
        case CameraProperties::SensorResolution::THE_2000X1500:
            return {2000, 1500};
        case CameraProperties::SensorResolution::THE_2028X1520:
            return {2028, 1520};
        case CameraProperties::SensorResolution::THE_2104X1560:
            return {2104, 1560};
        case CameraProperties::SensorResolution::THE_1440X1080:
            return {1440, 1080};
        case CameraProperties::SensorResolution::AUTO:
            return {-1, -1};
        default:
            throw std::invalid_argument("Invalid resolution supplied to CameraProperties::SensorResolution::toSize");
    }
}
}  // namespace dai
