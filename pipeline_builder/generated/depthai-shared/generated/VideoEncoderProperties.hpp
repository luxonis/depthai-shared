//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     VideoEncoderProperties.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace dai {
namespace gen {
    enum class VideoEncoderProfile : int;
    enum class RateControlMode : int;
}
}

namespace dai {
namespace gen {
    /**
     * Specify VideoEncoder options such as profile, bitrate, ...
     */

    using nlohmann::json;

    /**
     * Specify VideoEncoder options such as profile, bitrate, ...
     */
    struct VideoEncoderProperties {
        /**
         * Specifies prefered bitrate of compressed output bitstream
         */
        std::shared_ptr<int64_t> bitrate;
        /**
         * Input and compressed output frame height
         */
        int64_t height;
        /**
         * Every x number of frames a keyframe will be inserted
         */
        std::shared_ptr<int64_t> keyframeFrequency;
        /**
         * Specifies maximum bitrate of compressed output bitstream
         */
        std::shared_ptr<int64_t> maxBitrate;
        /**
         * Specifies number of B frames to be inserted
         */
        std::shared_ptr<int64_t> numBFrames;
        /**
         * This options specifies how many frames are available in this nodes pool (can help if
         * receiver node is slow at consuming
         */
        std::shared_ptr<int64_t> numFramesPool;
        /**
         * Encoding profile, H264, H265 or MJPEG
         */
        VideoEncoderProfile profile;
        /**
         * Value between 0-100% (approximates quality)
         */
        std::shared_ptr<int64_t> quality;
        /**
         * Rate control mode specifies if constant or variable bitrate should be used (H264 / H265)
         */
        std::shared_ptr<RateControlMode> rateCtrlMode;
        /**
         * Input and compressed output frame width
         */
        int64_t width;
    };
}
}
