#pragma once

#include "depthai-shared/properties/Properties.hpp"
#include "depthai-shared/datatype/RawAudioInConfig.hpp"

namespace dai {

/**
 * Properties for UAC node
 */
struct UACProperties : PropertiesSerializable<Properties, UACProperties> {
    /// Initial AudioIn config - TODO
    RawAudioInConfig initialConfig;
};

DEPTHAI_SERIALIZE_EXT(UACProperties, initialConfig);

}  // namespace dai
