#pragma once

#include <vector>

#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/properties/Properties.hpp"
#include "depthai-shared/datatype/RawDepthAlignConfig.hpp"
#include "depthai-shared/common/CameraBoardSocket.hpp"

namespace dai {

/**
 * Specify properties for DepthAlign 
 */
struct DepthAlignProperties: PropertiesSerializable<Properties, DepthAlignProperties> {
    RawDepthAlignConfig initialConfig;
    CameraBoardSocket alignTo = CameraBoardSocket::AUTO;
};

DEPTHAI_SERIALIZE_EXT(DepthAlignProperties, initialConfig, alignTo);

}  // namespace dai
