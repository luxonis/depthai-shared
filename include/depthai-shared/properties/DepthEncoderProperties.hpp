#pragma once

#include <vector>

#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/properties/Properties.hpp"
#include "depthai-shared/datatype/RawImgFrame.hpp"

namespace dai {

/**
 * Specify properties for DepthEncoder node.
 */
struct DepthEncoderProperties : PropertiesSerializable<Properties, DepthEncoderProperties> {
    RawImgFrame::Type outputType = RawImgFrame::Type::NV12;
    std::vector<uint8_t> lutR, lutG, lutB;
    int numFramesPool = 8;
    int numShaves = 1;
};

DEPTHAI_SERIALIZE_EXT(DepthEncoderProperties, outputType, lutR, lutG, lutB, numFramesPool, numShaves);

}  // namespace dai
