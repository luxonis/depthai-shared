#pragma once

#include <nlohmann/json.hpp>
#include <depthai-shared/pb/common/optional.hpp>


namespace dai {

    /**
     * Specify NeuralNetwork options such as blob path, ...
     */
    struct NeuralNetworkProperties {
        /**
         * Blob binary size in bytes
         */
        tl::optional<int64_t> blobSize;
        /**
         * Uri which points to blob
         */
        std::string blobUri;
        /**
         * Number of available output tensors in pool
         */
        tl::optional<int32_t> numFrames;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(NeuralNetworkProperties, blobSize, blobUri, numFrames)

}
