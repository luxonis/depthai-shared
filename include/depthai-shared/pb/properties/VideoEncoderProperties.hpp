#pragma once

#include <nlohmann/json.hpp>
#include <common/optional.hpp>

namespace dai {

    /**
     * Specify VideoEncoder options such as profile, bitrate, ...
     */
    struct VideoEncoderProperties {

        /**
         * Rate control mode specifies if constant or variable bitrate should be used (H264 / H265)
         */
        enum class RateControlMode : int { CBR, VBR };

        /**
         * Encoding profile, H264, H265 or MJPEG
         */
        enum class VideoEncoderProfile : int { H264_BASELINE, H264_HIGH, H264_MAIN, H265_MAIN, MJPEG };

        /**
         * Specifies prefered bitrate of compressed output bitstream
         */
        tl::optional<int32_t> bitrate;
        /**
         * Every x number of frames a keyframe will be inserted
         */
        tl::optional<int32_t> keyframeFrequency;
        /**
         * Specifies maximum bitrate of compressed output bitstream
         */
        tl::optional<int32_t> maxBitrate;
        /**
         * Specifies number of B frames to be inserted
         */
        tl::optional<int32_t> numBFrames;
        /**
         * This options specifies how many frames are available in this nodes pool (can help if
         * receiver node is slow at consuming
         */
        tl::optional<int32_t> numFramesPool;
        /**
         * Encoding profile, H264, H265 or MJPEG
         */
        VideoEncoderProfile profile;
        /**
         * Value between 0-100% (approximates quality)
         */
        tl::optional<int32_t> quality;
        /**
         * Rate control mode specifies if constant or variable bitrate should be used (H264 / H265)
         */
        tl::optional<RateControlMode> rateCtrlMode;
        /**
         * Input and compressed output frame width
         */
        int32_t width;
        /**
         * Input and compressed output frame height
         */
        int32_t height;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(VideoEncoderProperties, bitrate, keyframeFrequency, maxBitrate, numBFrames, numFramesPool, profile, quality, rateCtrlMode, width, height)

}
