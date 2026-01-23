#pragma once

#include "depthai-shared/common/ProcessorType.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

struct MessageDemuxProperties : PropertiesSerializable<Properties, MessageDemuxProperties> {
    /**
     * Which processor should execute the node.
     */
    ProcessorType processor = ProcessorType::LEON_CSS;
};

DEPTHAI_SERIALIZE_EXT(MessageDemuxProperties, processor);

}  // namespace dai
