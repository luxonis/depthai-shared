#pragma once

#include <depthai-shared/pb/common/optional.hpp>
#include <nlohmann/json.hpp>

namespace dai {

/**
 * Properties for XLinkOut which define stream name
 */
struct CommonObjDetProperties {
    /**
     * Set a limit to how many packets will be sent further to host
     */
    std::string streamName;
    /**
     * Uri which points to blob
     */
    std::string nnConfig;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CommonObjDetProperties, streamName, nnConfig)

}  // namespace dai