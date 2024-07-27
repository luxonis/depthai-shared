#pragma once

#include <vector>

#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/RawVisionHealthConfig.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for VisionHealth
 */
struct VisionHealthProperties : PropertiesSerializable<Properties, VisionHealthProperties> {
    RawVisionHealthConfig initialConfig;
    int memory = 20;
    int bootThreshold = 10;
    int checkThreshold = 50;
};

DEPTHAI_SERIALIZE_EXT(VisionHealthProperties, initialConfig, memory, bootThreshold, checkThreshold);

}  // namespace dai
