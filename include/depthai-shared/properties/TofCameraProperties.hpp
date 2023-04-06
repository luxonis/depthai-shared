#pragma once

#include <vector>

#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/RawTofCameraConfig.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for TofCamera
 */
struct TofCameraProperties : PropertiesSerializable<Properties, TofCameraProperties> {
    /**
     * Initial feature tracker config
     */
    RawTofCameraConfig initialConfig;

};

DEPTHAI_SERIALIZE_EXT(TofCameraProperties, initialConfig);

}  // namespace dai
