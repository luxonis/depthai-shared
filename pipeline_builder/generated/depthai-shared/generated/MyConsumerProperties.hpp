//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     MyConsumerProperties.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace dai {
namespace gen {
    enum class ProcessorType : int;
}
}

namespace dai {
namespace gen {
    /**
     * Specify message and processor placement of MyConsumer node
     */

    using nlohmann::json;

    /**
     * Specify message and processor placement of MyConsumer node
     */
    struct MyConsumerProperties {
        /**
         * On which processor the node will be placed
         */
        ProcessorType processorPlacement;
    };
}
}
