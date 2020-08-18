//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     GlobalProperties.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace dai {
namespace gen {
    /**
     * Specify properties which apply for whole pipeline
     */

    using nlohmann::json;

    /**
     * Specify properties which apply for whole pipeline
     */
    struct GlobalProperties {
        /**
         * Set frequency of Leon OS - Incresing can improve performance, at the cost of higher power
         * draw
         */
        double leonOsFrequencyKhz;
        /**
         * Set frequency of Leon RT - Incresing can improve performance, at the cost of higher power
         * draw
         */
        double leonRtFrequencyKhz;
        std::shared_ptr<std::string> pipelineName;
        std::shared_ptr<std::string> pipelineVersion;
    };
}
}
