//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     PipelineSchema.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include "NodeConnectionSchema.hpp"
#include "NodeObjInfo.hpp"
#include "depthai-shared/properties/GlobalProperties.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/**
 * Specifies whole pipeline, nodes, properties and connections between nodes IOs
 */
struct PipelineSchema {
    std::vector<NodeConnectionSchema> connections;
    GlobalProperties globalProperties;
    std::unordered_map<int64_t, NodeObjInfo> nodes;
};

DEPTHAI_SERIALIZE_EXT(PipelineSchema, connections, globalProperties, nodes);

}  // namespace dai
