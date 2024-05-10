#pragma once

#include <vector>

#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/RawDepthAlignConfig.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for DepthAlign
 */
struct DepthAlignProperties : PropertiesSerializable<Properties, DepthAlignProperties> {
    RawDepthAlignConfig initialConfig;
    int alignWidth = 0;
    int alignHeight = 0;
};

DEPTHAI_SERIALIZE_EXT(DepthAlignProperties, initialConfig, alignWidth, alignHeight);

}  // namespace dai
