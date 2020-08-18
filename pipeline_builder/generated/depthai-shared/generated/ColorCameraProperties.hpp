//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     ColorCameraProperties.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace dai {
namespace gen {
    enum class ColorOrderInsidePixel : int;
    enum class CameraSensorResolution : int;
}
}

namespace dai {
namespace gen {
    /**
     * Specify ColorCamera options such as camera ID, ...
     */

    using nlohmann::json;

    /**
     * Specify ColorCamera options such as camera ID, ...
     */
    struct ColorCameraProperties {
        /**
         * Which color camera the node will use
         */
        int64_t camId;
        /**
         * For 24 bit color these can be either RGB or BGR
         */
        ColorOrderInsidePixel colorOrder;
        /**
         * Are colors interleaved (R1G1B1, R2G2B2, ...) or planar (R1R2..., G1G2..., B1B2)
         */
        bool interleaved;
        /**
         * Preview frame output height
         */
        double previewHeight;
        /**
         * Preview frame output width
         */
        double previewWidth;
        /**
         * Select the camera sensor resolution
         */
        CameraSensorResolution resolution;
    };
}
}
