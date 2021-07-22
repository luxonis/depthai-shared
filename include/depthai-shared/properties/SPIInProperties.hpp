//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     SPIInProperties.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>

namespace dai {

/**
 * Properties for SPIIn node
 */
struct SPIInProperties {
    /**
     * Name of stream
     */
    std::string streamName;

    /**
     * SPI bus to use
     */
    int busId;

    /**
     * Maximum input data size
     */
    std::uint32_t maxDataSize = dai::XLINK_USB_BUFFER_MAX_SIZE;

    /**
     * Number of frames in pool
     */
    std::uint32_t numFrames = 4;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SPIInProperties, streamName, busId);

}  // namespace dai
