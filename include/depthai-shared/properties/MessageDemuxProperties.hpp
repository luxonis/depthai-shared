#pragma once

#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * TODO
 */
struct MessageDemuxProperties : PropertiesSerializable<Properties, MessageDemuxProperties> {
    char dummy = 0;
};

DEPTHAI_SERIALIZE_EXT(MessageDemuxProperties, dummy);

}  // namespace dai
