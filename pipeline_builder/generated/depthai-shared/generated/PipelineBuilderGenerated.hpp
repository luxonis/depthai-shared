//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     PipelineBuilderGenerated.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

#include "ColorOrderInsidePixel.hpp"
#include "CameraSensorResolution.hpp"
#include "ColorCameraProperties.hpp"
#include "ProcessorType.hpp"
#include "MyConsumerProperties.hpp"
#include "MyProducerProperties.hpp"
#include "NeuralNetworkProperties.hpp"
#include "VideoEncoderProfile.hpp"
#include "RateControlMode.hpp"
#include "VideoEncoderProperties.hpp"
#include "XLinkInProperties.hpp"
#include "XLinkOutProperties.hpp"
#include "NodeConnectionSchema.hpp"
#include "GlobalProperties.hpp"
#include "NodeObjInfo.hpp"
#include "PipelineSchema.hpp"
namespace dai {
namespace gen {
}
}
