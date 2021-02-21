#pragma once

#include <depthai-shared/pb/common/optional.hpp>
#include <nlohmann/json.hpp>

namespace dai {

/**
 * Specify MicropythonProperties options such as blob path, ...
 */
struct MicropythonProperties {
    /**
     * Blob binary size in bytes
     */
    tl::optional<std::uint32_t> blobSize;
    /**
     * Uri which points to blob
     */
    std::string blobUri;
    /**
     * Number of available output tensors in pool
     */
    std::uint32_t numFrames = 8;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MicropythonProperties, blobSize, blobUri, numFrames);

}  // namespace dai
