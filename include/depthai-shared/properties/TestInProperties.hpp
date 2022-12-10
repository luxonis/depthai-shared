#pragma once

#include "depthai-shared/common/ProcessorType.hpp"
#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify PoolProperties options such as pool uri, pool name, ...
 */
struct TestInProperties : PropertiesSerializable<Properties, TestInProperties> {
    /**
     * Number of messages to send
     */
    int numMessagesToSend = 50;
};

DEPTHAI_SERIALIZE_EXT(TestInProperties, numMessagesToSend);

}  // namespace dai
