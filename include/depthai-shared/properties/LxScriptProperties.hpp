#pragma once

#include <depthai-shared/common/ProcessorType.hpp>
#include <depthai-shared/common/optional.hpp>
#include <nlohmann/json.hpp>

namespace dai {

/**
 * Specify LxScriptProperties options such as script uri, script size, ...
 */
struct LxScriptProperties {
    /**
     * Node name. This will be used to identify the node in the LxScript script.
     */
    std::string nodeName = "";

    /**
     * Uri which points to blob
     */
    std::string scriptUri = "";

    /**
     * Map of asset name to uri
     */
    std::map<std::string, std::string> assetUriMap;

    /**
     * Which processor should execute the LxScript script
     */
    ProcessorType processor = ProcessorType::LEON_MSS;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LxScriptProperties, nodeName, scriptUri, assetUriMap, processor);

}  // namespace dai
