#pragma once

#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for ToF
 */
struct ToFProperties : PropertiesSerializable<Properties, ToFProperties> {
    int dummy;
};

DEPTHAI_SERIALIZE_EXT(ToFProperties, dummy);

}  // namespace dai
