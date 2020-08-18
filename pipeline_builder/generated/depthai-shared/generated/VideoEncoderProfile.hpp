//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     VideoEncoderProfile.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace dai {
namespace gen {
    /**
     * Encoding profile, H264, H265 or MJPEG
     */

    using nlohmann::json;

    /**
     * Encoding profile, H264, H265 or MJPEG
     */
    enum class VideoEncoderProfile : int { H264_BASELINE, H264_HIGH, H264_MAIN, H265_MAIN, MJPEG };
}
}
