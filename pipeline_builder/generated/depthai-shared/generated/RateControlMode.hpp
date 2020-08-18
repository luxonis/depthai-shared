//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     RateControlMode.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace dai {
namespace gen {
    /**
     * Rate control mode specifies if constant or variable bitrate should be used (H264 / H265)
     */

    using nlohmann::json;

    /**
     * Rate control mode specifies if constant or variable bitrate should be used (H264 / H265)
     */
    enum class RateControlMode : int { CBR, VBR };
}
}
