//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     NeuralNetworkProperties.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace dai {
namespace gen {
    /**
     * Specify NeuralNetwork options such as blob path, ...
     */

    using nlohmann::json;

    /**
     * Specify NeuralNetwork options such as blob path, ...
     */
    struct NeuralNetworkProperties {
        /**
         * Blob binary size in bytes
         */
        std::shared_ptr<int64_t> blobSize;
        /**
         * Uri which points to blob
         */
        std::string blobUri;
        /**
         * Number of available output tensors in pool
         */
        std::shared_ptr<int64_t> numFrames;
    };
}
}
