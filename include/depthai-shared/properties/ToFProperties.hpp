#pragma once

#include <vector>

#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/RawToFConfig.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for ToF
 */
struct ToFProperties : PropertiesSerializable<Properties, ToFProperties> {
    /**
     * Initial feature tracker config
     */
    RawToFConfig initialConfig;
};

DEPTHAI_SERIALIZE_EXT(ToFProperties, initialConfig);

}  // namespace dai
