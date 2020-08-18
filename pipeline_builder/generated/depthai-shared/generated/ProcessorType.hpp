//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     ProcessorType.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace dai {
namespace gen {
    /**
     * On which processor the node will be placed
     *
     * Enum specifying processor
     */

    using nlohmann::json;

    /**
     * On which processor the node will be placed
     *
     * Enum specifying processor
     */
    enum class ProcessorType : int { LOS, LRT };
}
}
