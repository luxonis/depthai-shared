#pragma once

#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for RTSP such as stream name, ...
 */
struct RTSPProperties : PropertiesSerializable<Properties, RTSPProperties> {
    int dummy;
};

DEPTHAI_SERIALIZE_EXT(RTSPProperties, dummy);

}  // namespace dai
