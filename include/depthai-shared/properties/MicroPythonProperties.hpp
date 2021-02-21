#pragma once

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
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MicroPythonProperties, scriptSize, scriptUri);

}  // namespace dai
