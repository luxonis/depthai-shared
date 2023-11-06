#pragma once

#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * TODO
 */
struct MessageDemuxProperties : PropertiesSerializable<Properties, MessageDemuxProperties> {
    bool demuxOnlyOnSuccessful = false;
};

DEPTHAI_SERIALIZE_EXT(MessageDemuxProperties, demuxOnlyOnSuccessful);

}  // namespace dai
