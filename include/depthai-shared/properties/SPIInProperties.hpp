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
    /// Output stream name
    std::string streamName;
    /// SPI bus to use
    int busId;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SPIInProperties, streamName, busId);

}  // namespace dai
