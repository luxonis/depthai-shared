#pragma once

#include <depthai-shared/common/ProcessorType.hpp>
#include <depthai-shared/common/optional.hpp>
#include <nlohmann/json.hpp>

namespace dai {

/**
 * Specify MicropythonProperties options such as script uri, script size, ...
 */
struct MicroPythonProperties {
    /**
     * Uri which points to blob
     */
    std::string scriptUri = "";

    /**
     * Map of asset name to uri
     */
    std::map<std::string, std::string> assetUriMap;

    /**
     * Which processor should execute the MicroPython script
     */
    ProcessorType processor = ProcessorType::LEON_MSS;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MicroPythonProperties, scriptUri, assetUriMap, processor);

}  // namespace dai