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
    CameraBoardSocket alignFrom = CameraBoardSocket::AUTO;
    CameraBoardSocket alignTo = CameraBoardSocket::AUTO;
    int alignWidth = 1280;
    int alignHeight = 720;

    bool downscaleSource = true;
};

DEPTHAI_SERIALIZE_EXT(DepthAlignProperties, initialConfig, alignFrom, alignTo, alignWidth, alignHeight, downscaleSource);

}  // namespace dai
