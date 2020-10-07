#pragma once

#include <cstdint>
#include <cstring>

struct CameraControl {

    enum class CamId : uint8_t {
        RGB = 0,
        LEFT = 1,
        RIGHT = 2,
    };

    enum class AutoWhiteBalanceMode : uint8_t {
        OFF = 0,
        AUTO,
        INCANDESCENT,
        FLUORESCENT,
        WARM_FLUORESCENT,
        DAYLIGHT,
        CLOUDY_DAYLIGHT,
        TWILIGHT,
        SHADE,
    };

    enum class AutoFocusMode : uint8_t {
        OFF = 0,
        AUTO,
        MACRO,
        CONTINUOUS_VIDEO,
        CONTINUOUS_PICTURE,
        EDOF,
    };

    enum class SceneMode : uint8_t {
        UNSUPPORTED = 0,
        FACE_PRIORITY,
        ACTION,
        PORTRAIT,
        LANDSCAPE,
        NIGHT,
        NIGHT_PORTRAIT,
        THEATRE,
        BEACH,
        SNOW,
        SUNSET,
        STEADYPHOTO,
        FIREWORKS,
        SPORTS,
        PARTY,
        CANDLELIGHT,
        BARCODE,
    };

    enum class AntiBandingMode : uint8_t {
        OFF = 0,
        _50HZ,
        _60HZ,
        AUTO,
    };

    enum class AutoExposureLockMode : uint8_t {
        OFF = 0,
        ON,
    };

    enum class AutoWhiteBalanceLockMode : uint8_t {
        OFF = 0,
        ON,
    };

    enum class CaptureIntent : uint8_t {
        CUSTOM = 0,
        PREVIEW,
        STILL_CAPTURE,
        VIDEO_RECORD,
        VIDEO_SNAPSHOT,
        ZERO_SHUTTER_LAG,
    };

    enum class ControlMode : uint8_t {
        OFF = 0,
        AUTO,
        USE_SCENE_MODE,
    };

    enum class EffectMode : uint8_t {
        OFF = 0,
        MONO,
        NEGATIVE,
        SOLARIZE,
        SEPIA,
        POSTERIZE,
        WHITEBOARD,
        BLACKBOARD,
        AQUA,
    };

    // The commands without comments have no extra arguments
    enum class Command : int32_t {
        START_STREAM             =  0,
        STOP_STREAM              =  1,
        REQUEST_STILL            =  2,
        MOVE_LENS                =  3, /* [1] lens position: 0-255
                                        */
        FOCUS_TRIGGER            =  4,
        AE_MANUAL                =  5, /* [1] exposure time [us]
                                        * [2] sensitivity [iso]
                                        * [3] frame duration [us]
                                        */
        AE_AUTO                  =  6,
        SET_AWB_MODE             =  7, /* [1] awb_mode: AutoWhiteBalanceMode
                                        */
        SCENE_MODES              =  8, /* [1] scene_mode: SceneMode
                                        */
        ANTIBANDING_MODES        =  9, /* [1] antibanding_mode: AntiBandingMode
                                        */
        EXPOSURE_COMPENSATION    = 10, /* [1] value
                                        */
        AE_LOCK                  = 12, /* [1] ae_lock_mode: AutoExposureLockMode
                                        */
        AE_TARGET_FPS_RANGE      = 13, /* [1] min_fps
                                        * [2] max_fps
                                        */
        AWB_LOCK                 = 15, /* [1] awb_lock_mode: AutoWhiteBalanceLockMode
                                        */
        CAPTURE_INTENT           = 16, /* [1] capture_intent_mode: CaptureIntent
                                        */
        CONTROL_MODE             = 17, /* [1] control_mode: ControlMode
                                        */
        FRAME_DURATION           = 20, /* [1] frame_duration
                                        */
        SENSITIVITY              = 22, /* [1] iso_val
                                        */
        EFFECT_MODE              = 23, /* [1] effect_mode: EffectMode
                                        */
        AF_MODE                  = 25, /* [1] af_mode: AutoFocusMode
                                        */
        NOISE_REDUCTION_STRENGTH = 26, /* [1] value
                                        */
        SATURATION               = 27, /* [1] value
                                        */
        BRIGHTNESS               = 30, /* [1] value
                                        */
        STREAM_FORMAT            = 32, /* [1] format
                                        */
        CAM_RESOLUTION           = 33, /* [1] width
                                        * [2] height
                                        */
        SHARPNESS                = 34, /* [1] value
                                        */
        CUSTOM_USECASE           = 39, /* [1] value
                                        */
        CUSTOM_CAPT_MODE         = 40, /* [1] value
                                        */
        CUSTOM_EXP_BRACKETS      = 41, /* [1] val1
                                        * [2] val2
                                        * [3] val3
                                        */
        CUSTOM_CAPTURE           = 42, /* [1] value
                                        */
        CONTRAST                 = 43, /* [1] value
                                        */
        AE_REGION                = 44, /* [1] x
                                        * [2] y
                                        * [3] width
                                        * [4] height
                                        * [5] priority
                                        */
        AF_REGION                = 46, /* [1] x
                                        * [2] y
                                        * [3] width
                                        * [4] height
                                        * [5] priority
                                        */
        LUMA_DENOISE             = 47, /* [1] value
                                        */
        CHROMA_DENOISE           = 48, /* [1] value
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
