//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     ColorOrderInsidePixel.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace dai {
namespace gen {
    /**
     * For 24 bit color these can be either RGB or BGR
     */

    using nlohmann::json;

    /**
     * For 24 bit color these can be either RGB or BGR
     */
    enum class ColorOrderInsidePixel : int { BGR, RGB };
}
}
