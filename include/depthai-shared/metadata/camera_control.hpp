#pragma once

#include <cstdint>
#include <cstring>

struct CameraControl {

    enum class CamId : uint8_t {
        CAM_RGB = 0,
        CAM_LEFT = 1,
        CAM_RIGHT = 2,
    };

    enum class AutoWhiteBalanceMode : uint8_t {
        AWB_OFF = 0,
        AWB_AUTO,
        AWB_INCANDESCENT,
        AWB_FLUORESCENT,
        AWB_WARM_FLUORESCENT,
        AWB_DAYLIGHT,
        AWB_CLOUDY_DAYLIGHT,
        AWB_TWILIGHT,
        AWB_SHADE,
    };

    enum class AutoFocusMode : uint8_t {
        AF_OFF = 0,
        AF_AUTO,
        AF_MACRO,
        AF_CONTINUOUS_VIDEO,
        AF_CONTINUOUS_PICTURE,
        AF_EDOF,
    };

    enum class SceneMode : uint8_t {
        SCENE_UNSUPPORTED = 0,
        SCENE_FACE_PRIORITY,
        SCENE_ACTION,
        SCENE_PORTRAIT,
        SCENE_LANDSCAPE,
        SCENE_NIGHT,
        SCENE_NIGHT_PORTRAIT,
        SCENE_THEATRE,
        SCENE_BEACH,
        SCENE_SNOW,
        SCENE_SUNSET,
        SCENE_STEADYPHOTO,
        SCENE_FIREWORKS,
        SCENE_SPORTS,
        SCENE_PARTY,
        SCENE_CANDLELIGHT,
        SCENE_BARCODE,
    };

    enum class AntiBandingMode : uint8_t {
        ANTIBANDING_OFF = 0,
        ANTIBANDING_50HZ,
        ANTIBANDING_60HZ,
        ANTIBANDING_AUTO,
    };

    enum class AutoExposureLockMode : uint8_t {
        AE_LOCK_OFF = 0,
        AE_LOCK_ON,
    };

    enum class AutoWhiteBalanceLockMode : uint8_t {
        AWB_LOCK_OFF = 0,
        AWB_LOCK_ON,
    };

    enum class CaptureIntent : uint8_t {
        CAPTURE_INTENT_CUSTOM = 0,
        CAPTURE_INTENT_PREVIEW,
        CAPTURE_INTENT_STILL_CAPTURE,
        CAPTURE_INTENT_VIDEO_RECORD,
        CAPTURE_INTENT_VIDEO_SNAPSHOT,
        CAPTURE_INTENT_ZERO_SHUTTER_LAG,
    };

    enum ControlMode : uint8_t {
        CONTROL_MODE_OFF = 0,
        CONTROL_MODE_AUTO,
        CONTROL_MODE_USE_SCENE_MODE,
    };

    enum EffectMode : uint8_t {
        EFFECT_OFF = 0,
        EFFECT_MONO,
        EFFECT_NEGATIVE,
        EFFECT_SOLARIZE,
        EFFECT_SEPIA,
        EFFECT_POSTERIZE,
        EFFECT_WHITEBOARD,
        EFFECT_BLACKBOARD,
        EFFECT_AQUA,
    };

    // The commands without comments have no extra arguments
    enum class Command : int32_t {
        CMD_START_STREAM             =  0,
        CMD_STOP_STREAM              =  1,
        CMD_REQUEST_STILL            =  2,
        CMD_MOVE_LENS                =  3, /* [1] lens position: 0-255
                                            */
        CMD_FOCUS_TRIGGER            =  4,
        CMD_AE_MANUAL                =  5, /* [1] exposure time [us]
                                            * [2] sensitivity [iso]
                                            * [3] frame duration [us]
                                            */
        CMD_AE_AUTO                  =  6,
        CMD_SET_AWB_MODE             =  7, /* [1] awb_mode: AutoWhiteBalanceMode
                                            */
        CMD_SCENE_MODES              =  8, /* [1] scene_mode: SceneMode
                                            */
        CMD_ANTIBANDING_MODES        =  9, /* [1] antibanding_mode: AntiBandingMode
                                            */
        CMD_EXPOSURE_COMPENSATION    = 10, /* [1] value
                                            */
        CMD_AE_LOCK                  = 12, /* [1] ae_lock_mode: AutoExposureLockMode
                                            */
        CMD_AE_TARGET_FPS_RANGE      = 13, /* [1] min_fps
                                            * [2] max_fps
                                            */
        CMD_AWB_LOCK                 = 15, /* [1] awb_lock_mode: AutoWhiteBalanceLockMode
                                            */
        CMD_CAPTURE_INTENT           = 16, /* [1] capture_intent_mode: CaptureIntent
                                            */
        CMD_CONTROL_MODE             = 17, /* [1] control_mode: ControlMode
                                            */
        CMD_FRAME_DURATION           = 20, /* [1] frame_duration
                                            */
        CMD_SENSITIVITY              = 22, /* [1] iso_val
                                            */
        CMD_EFFECT_MODE              = 23, /* [1] effect_mode: EffectMode
                                            */
        CMD_AF_MODE                  = 25, /* [1] af_mode: AutoFocusMode
                                            */
        CMD_NOISE_REDUCTION_STRENGTH = 26, /* [1] value
                                            */
        CMD_SATURATION               = 27, /* [1] value
                                            */
        CMD_BRIGHTNESS               = 30, /* [1] value
                                            */
        CMD_STREAM_FORMAT            = 32, /* [1] format
                                            */
        CMD_CAM_RESOLUTION           = 33, /* [1] width
                                            * [2] height
                                            */
        CMD_SHARPNESS                = 34, /* [1] value
                                            */
        CMD_CUSTOM_USECASE           = 39, /* [1] value
                                            */
        CMD_CUSTOM_CAPT_MODE         = 40, /* [1] value
                                            */
        CMD_CUSTOM_EXP_BRACKETS      = 41, /* [1] val1
                                            * [2] val2
                                            * [3] val3
                                            */
        CMD_CUSTOM_CAPTURE           = 42, /* [1] value
                                            */
        CMD_CONTRAST                 = 43, /* [1] value
                                            */
        CMD_AE_REGION                = 44, /* [1] x
                                            * [2] y
                                            * [3] width
                                            * [4] height
                                            * [5] priority
                                            */
        CMD_AF_REGION                = 46, /* [1] x
                                            * [2] y
                                            * [3] width
                                            * [4] height
                                            * [5] priority
                                            */
        CMD_LUMA_DENOISE             = 47, /* [1] value
                                            */
        CMD_CHROMA_DENOISE           = 48, /* [1] value
                                            */
    };

    static std::string createCommandStr(CamId camera_id,
            Command command_id,
            std::string extra_args = "") {
        std::string str = std::string("3A")
            + std::string(" ") + std::to_string((int)command_id)
            + std::string(" ") + std::to_string((int)camera_id);
        if (!extra_args.empty())
           str += std::string(" ") + extra_args;
        return str;
    }
};
