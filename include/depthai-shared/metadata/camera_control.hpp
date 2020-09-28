#pragma once

enum Isp3A_CamId : int {
    CAM_RGB = 0,
    CAM_LEFT = 1,
    CAM_RIGHT = 2,
};

// The commands without comments have no extra arguments
enum Isp3A_Commands : int {
    CMD_START_STREAM             =  0,
    CMD_STOP_STREAM              =  1,
    CMD_REQ_STILL                =  2,
    CMD_MOV_LENS                 =  3, /* [1] lens position: 0-255
                                        */
    CMD_FOCUS_TRIGGER            =  4,
    CMD_AE_MANUAL                =  5, /* [1] exposure time [us]
                                        * [2] sensitivity [iso]
                                        * [3] frame duration [us]
                                        */
    CMD_AE_AUTO                  =  6,
    CMD_SET_AWB_MODE             =  7, /* [1] awb_mode
                                        */
    CMD_SCENE_MODES              =  8, /* [1] scene_mode
                                        */
    CMD_ANTIBANDING_MODES        =  9, /* [1] antibanding_mode
                                        */
    CMD_EXPOSURE_COMPENSATION    = 10, /* [1] value
                                        */
    CMD_AE_LOCK                  = 12, /* [1] ae_lock_mode
                                        */
    CMD_AE_TARGET_FPS_RANGE      = 13, /* [1] min_fps
                                        * [2] max_fps
                                        */
    CMD_AWB_LOCK                 = 15, /* [1] awb_lock_control
                                        */
    CMD_CAPTURE_INTENT           = 16, /* [1] capture_intent_mode
                                        */
    CMD_CONTROL_MODE             = 17, /* [1] control_mode
                                        */
    CMD_FRAME_DURATION           = 20, /* [1] frame_duration
                                        */
    CMD_SENSITIVITY              = 22, /* [1] iso_val
                                        */
    CMD_EFFECT_MODE              = 23, /* [1] effect_mode
                                        */
    CMD_AF_MODE                  = 25, /* [1] af_mode
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
    CMD_CUST_USECASE             = 39, /* [1] value
                                        */
    CMD_CUST_CAPT_MODE           = 40, /* [1] value
                                        */
    CMD_CUST_EXP_BRACKETS        = 41, /* [1] val1
                                        * [2] val2
                                        * [3] val3
                                        */
    CMD_CUST_CAPTURE             = 42, /* [1] value
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
