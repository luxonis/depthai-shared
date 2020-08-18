//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     PipelineSchema.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

#include "GlobalProperties.hpp"

namespace dai {
namespace gen {
    struct NodeConnectionSchema;
    struct NodeObjInfo;
}
}

namespace dai {
namespace gen {
    /**
     * Specifies whole pipeline, nodes, properties and connections between nodes IOs
     */

    using nlohmann::json;

    /**
     * Specifies whole pipeline, nodes, properties and connections between nodes IOs
     */
    struct PipelineSchema {
        std::vector<NodeConnectionSchema> connections;
        GlobalProperties globalProperties;
        std::vector<NodeObjInfo> nodes;
    };
}
}
