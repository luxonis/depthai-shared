//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     MyProducerProperties.hpp data = nlohmann::json::parse(jsonString);

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
     * Specify message and processor placement of MyProducer node
     */

    using nlohmann::json;

    /**
     * Specify message and processor placement of MyProducer node
     */
    struct MyProducerProperties {
        std::shared_ptr<std::string> message;
        /**
         * On which processor the node will be placed
         */
        ProcessorType processorPlacement;
    };
}
}
