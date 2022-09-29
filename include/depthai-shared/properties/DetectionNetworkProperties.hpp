#pragma once

// std
#include <vector>

// project
#include "NeuralNetworkProperties.hpp"
#include "depthai-shared/common/DetectionParserOptions.hpp"
#include "depthai-shared/common/optional.hpp"

namespace dai {

/**
 *  Specify properties for DetectionNetwork
 */
struct DetectionNetworkProperties : PropertiesSerializable<NeuralNetworkProperties, DetectionNetworkProperties> {
    DetectionParserOptions parser;
};

DEPTHAI_SERIALIZE_EXT(
    DetectionNetworkProperties, modelSource, blobSize, blobUri, xmlUri, binUri, numFrames, numThreads, numNCEPerThread, numShavesPerThread, backend, parser);

}  // namespace dai
