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
     * Blob binary size in bytes
     */
    tl::optional<std::uint32_t> scriptSize;
    /**
     * Uri which points to blob
     */
    std::string scriptUri = "";
    /**
     * Which processor should execute the MicroPython script
     */
    ProcessorType processor = ProcessorType::LEON_MSS;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MicroPythonProperties, scriptSize, scriptUri, processor);

}  // namespace dai
