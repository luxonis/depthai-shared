#pragma once

#include <vector>

#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/RawImageAlignConfig.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for ImageAlign
 */
struct ImageAlignProperties : PropertiesSerializable<Properties, ImageAlignProperties> {
    RawImageAlignConfig initialConfig;
    int alignWidth = 0;
    int alignHeight = 0;
};

DEPTHAI_SERIALIZE_EXT(ImageAlignProperties, initialConfig, alignWidth, alignHeight);

}  // namespace dai
