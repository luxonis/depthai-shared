#pragma once

#include <nlohmann/json.hpp>

#include "depthai-shared/xlink/XLinkConstants.hpp"

namespace dai {

/**
 * Properties for XLinkIn which define stream name
 */
struct XLinkInProperties {
    /**
     * Name of stream
     */
    std::string streamName;

    /**
     * Maximum input data size
     */
    std::uint32_t maxDataSize = dai::XLINK_USB_BUFFER_MAX_SIZE;

    /**
     * Number of frames in pool
     */
    std::uint32_t numFrames = 8;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(XLinkInProperties, streamName, maxDataSize, numFrames);

}  // namespace dai
