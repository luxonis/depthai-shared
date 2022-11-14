#pragma once

#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify PoolProperties options such as pool uri, pool name, ...
 */
struct PoolProperties : PropertiesSerializable<Properties, PoolProperties> {
    /**
     * Number of messages in pool
     */
    int numMessages = 0;

    /**
     * Size of data allocated for each message
     */
    std::int64_t maxMessageSize = 0;
};

DEPTHAI_SERIALIZE_EXT(PoolProperties, numMessages, maxMessageSize);

}  // namespace dai
