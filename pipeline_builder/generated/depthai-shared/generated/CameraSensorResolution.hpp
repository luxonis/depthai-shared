//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     CameraSensorResolution.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace dai {
namespace gen {
    /**
     * Select the camera sensor resolution
     */

    using nlohmann::json;

    /**
     * Select the camera sensor resolution
     */
    enum class CameraSensorResolution : int { THE_1080_P, THE_4_K };
}
}
