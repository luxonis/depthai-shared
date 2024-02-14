#pragma once

#include <tl/optional.hpp>
#include <vector>

#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/RawImgFrame.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

enum class HueEncodingType : int { LINEAR, LOGARITHMIC };
/**
 * Specify properties for DepthEncoder node.
 */
struct DepthEncoderProperties : PropertiesSerializable<Properties, DepthEncoderProperties> {
    RawImgFrame::Type outputType = RawImgFrame::Type::NV12;
    std::vector<uint8_t> lutR, lutG, lutB;
    bool useHueEncoding = false;
    HueEncodingType hueEncodingType = HueEncodingType::LOGARITHMIC;
    int minDepth = 1000;   // In the stereo depth unit
    int maxDepth = 10000;  // In the stereo depth unit
    int numFramesPool = 8;
    int numShaves = 1;
};

DEPTHAI_SERIALIZE_EXT(DepthEncoderProperties, outputType, lutR, lutG, lutB, useHueEncoding, minDepth, maxDepth, hueEncodingType, numShaves);

}  // namespace dai
