#pragma once

#include <vector>

#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/datatype/RawImgFrame.hpp"
#include "depthai-shared/properties/Properties.hpp"


namespace dai {

/**
 * Specify properties for Cast
 */
struct CastProperties : PropertiesSerializable<Properties, CastProperties> {

    dai::RawImgFrame::Type outputType = dai::RawImgFrame::Type::RAW8;
    tl::optional<float> scale;
    int numFramesPool = 4;
};

DEPTHAI_SERIALIZE_EXT(CastProperties, numFramesPool, outputType, scale);

}  // namespace dai
