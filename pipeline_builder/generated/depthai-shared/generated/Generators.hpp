//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Generators.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

#include "PipelineSchema.hpp"
#include "NodeObjInfo.hpp"
#include "GlobalProperties.hpp"
#include "NodeConnectionSchema.hpp"
#include "XLinkOutProperties.hpp"
#include "XLinkInProperties.hpp"
#include "VideoEncoderProperties.hpp"
#include "RateControlMode.hpp"
#include "VideoEncoderProfile.hpp"
#include "NeuralNetworkProperties.hpp"
#include "MyProducerProperties.hpp"
#include "MyConsumerProperties.hpp"
#include "ProcessorType.hpp"
#include "ColorCameraProperties.hpp"
#include "CameraSensorResolution.hpp"
#include "ColorOrderInsidePixel.hpp"

namespace nlohmann {
    void from_json(const json & j, dai::gen::ColorCameraProperties & x);
    void to_json(json & j, const dai::gen::ColorCameraProperties & x);

    void from_json(const json & j, dai::gen::MyConsumerProperties & x);
    void to_json(json & j, const dai::gen::MyConsumerProperties & x);

    void from_json(const json & j, dai::gen::MyProducerProperties & x);
    void to_json(json & j, const dai::gen::MyProducerProperties & x);

    void from_json(const json & j, dai::gen::NeuralNetworkProperties & x);
    void to_json(json & j, const dai::gen::NeuralNetworkProperties & x);

    void from_json(const json & j, dai::gen::VideoEncoderProperties & x);
    void to_json(json & j, const dai::gen::VideoEncoderProperties & x);

    void from_json(const json & j, dai::gen::XLinkInProperties & x);
    void to_json(json & j, const dai::gen::XLinkInProperties & x);

    void from_json(const json & j, dai::gen::XLinkOutProperties & x);
    void to_json(json & j, const dai::gen::XLinkOutProperties & x);

    void from_json(const json & j, dai::gen::NodeConnectionSchema & x);
    void to_json(json & j, const dai::gen::NodeConnectionSchema & x);

    void from_json(const json & j, dai::gen::GlobalProperties & x);
    void to_json(json & j, const dai::gen::GlobalProperties & x);

    void from_json(const json & j, dai::gen::NodeObjInfo & x);
    void to_json(json & j, const dai::gen::NodeObjInfo & x);

    void from_json(const json & j, dai::gen::PipelineSchema & x);
    void to_json(json & j, const dai::gen::PipelineSchema & x);

    void from_json(const json & j, dai::gen::ColorOrderInsidePixel & x);
    void to_json(json & j, const dai::gen::ColorOrderInsidePixel & x);

    void from_json(const json & j, dai::gen::CameraSensorResolution & x);
    void to_json(json & j, const dai::gen::CameraSensorResolution & x);

    void from_json(const json & j, dai::gen::ProcessorType & x);
    void to_json(json & j, const dai::gen::ProcessorType & x);

    void from_json(const json & j, dai::gen::VideoEncoderProfile & x);
    void to_json(json & j, const dai::gen::VideoEncoderProfile & x);

    void from_json(const json & j, dai::gen::RateControlMode & x);
    void to_json(json & j, const dai::gen::RateControlMode & x);

    inline void from_json(const json & j, dai::gen::ColorCameraProperties& x) {
        x.camId = j.at("camId").get<int64_t>();
        x.colorOrder = j.at("colorOrder").get<dai::gen::ColorOrderInsidePixel>();
        x.interleaved = j.at("interleaved").get<bool>();
        x.previewHeight = j.at("previewHeight").get<double>();
        x.previewWidth = j.at("previewWidth").get<double>();
        x.resolution = j.at("resolution").get<dai::gen::CameraSensorResolution>();
    }

    inline void to_json(json & j, const dai::gen::ColorCameraProperties & x) {
        j = json::object();
        j["camId"] = x.camId;
        j["colorOrder"] = x.colorOrder;
        j["interleaved"] = x.interleaved;
        j["previewHeight"] = x.previewHeight;
        j["previewWidth"] = x.previewWidth;
        j["resolution"] = x.resolution;
    }

    inline void from_json(const json & j, dai::gen::MyConsumerProperties& x) {
        x.processorPlacement = j.at("processorPlacement").get<dai::gen::ProcessorType>();
    }

    inline void to_json(json & j, const dai::gen::MyConsumerProperties & x) {
        j = json::object();
        j["processorPlacement"] = x.processorPlacement;
    }

    inline void from_json(const json & j, dai::gen::MyProducerProperties& x) {
        x.message = dai::gen::get_optional<std::string>(j, "message");
        x.processorPlacement = j.at("processorPlacement").get<dai::gen::ProcessorType>();
    }

    inline void to_json(json & j, const dai::gen::MyProducerProperties & x) {
        j = json::object();
        j["message"] = x.message;
        j["processorPlacement"] = x.processorPlacement;
    }

    inline void from_json(const json & j, dai::gen::NeuralNetworkProperties& x) {
        x.blobSize = dai::gen::get_optional<int64_t>(j, "blobSize");
        x.blobUri = j.at("blobUri").get<std::string>();
        x.numFrames = dai::gen::get_optional<int64_t>(j, "numFrames");
    }

    inline void to_json(json & j, const dai::gen::NeuralNetworkProperties & x) {
        j = json::object();
        j["blobSize"] = x.blobSize;
        j["blobUri"] = x.blobUri;
        j["numFrames"] = x.numFrames;
    }

    inline void from_json(const json & j, dai::gen::VideoEncoderProperties& x) {
        x.bitrate = dai::gen::get_optional<int64_t>(j, "bitrate");
        x.height = j.at("height").get<int64_t>();
        x.keyframeFrequency = dai::gen::get_optional<int64_t>(j, "keyframeFrequency");
        x.maxBitrate = dai::gen::get_optional<int64_t>(j, "maxBitrate");
        x.numBFrames = dai::gen::get_optional<int64_t>(j, "numBFrames");
        x.numFramesPool = dai::gen::get_optional<int64_t>(j, "numFramesPool");
        x.profile = j.at("profile").get<dai::gen::VideoEncoderProfile>();
        x.quality = dai::gen::get_optional<int64_t>(j, "quality");
        x.rateCtrlMode = dai::gen::get_optional<dai::gen::RateControlMode>(j, "rateCtrlMode");
        x.width = j.at("width").get<int64_t>();
    }

    inline void to_json(json & j, const dai::gen::VideoEncoderProperties & x) {
        j = json::object();
        j["bitrate"] = x.bitrate;
        j["height"] = x.height;
        j["keyframeFrequency"] = x.keyframeFrequency;
        j["maxBitrate"] = x.maxBitrate;
        j["numBFrames"] = x.numBFrames;
        j["numFramesPool"] = x.numFramesPool;
        j["profile"] = x.profile;
        j["quality"] = x.quality;
        j["rateCtrlMode"] = x.rateCtrlMode;
        j["width"] = x.width;
    }

    inline void from_json(const json & j, dai::gen::XLinkInProperties& x) {
        x.streamName = j.at("streamName").get<std::string>();
    }

    inline void to_json(json & j, const dai::gen::XLinkInProperties & x) {
        j = json::object();
        j["streamName"] = x.streamName;
    }

    inline void from_json(const json & j, dai::gen::XLinkOutProperties& x) {
        x.maxFpsLimit = j.at("maxFpsLimit").get<double>();
        x.streamName = j.at("streamName").get<std::string>();
    }

    inline void to_json(json & j, const dai::gen::XLinkOutProperties & x) {
        j = json::object();
        j["maxFpsLimit"] = x.maxFpsLimit;
        j["streamName"] = x.streamName;
    }

    inline void from_json(const json & j, dai::gen::NodeConnectionSchema& x) {
        x.node1Id = j.at("node1Id").get<int64_t>();
        x.node1Output = j.at("node1Output").get<std::string>();
        x.node2Id = j.at("node2Id").get<int64_t>();
        x.node2Input = j.at("node2Input").get<std::string>();
    }

    inline void to_json(json & j, const dai::gen::NodeConnectionSchema & x) {
        j = json::object();
        j["node1Id"] = x.node1Id;
        j["node1Output"] = x.node1Output;
        j["node2Id"] = x.node2Id;
        j["node2Input"] = x.node2Input;
    }

    inline void from_json(const json & j, dai::gen::GlobalProperties& x) {
        x.leonOsFrequencyKhz = j.at("leonOsFrequencyKhz").get<double>();
        x.leonRtFrequencyKhz = j.at("leonRtFrequencyKhz").get<double>();
        x.pipelineName = dai::gen::get_optional<std::string>(j, "pipelineName");
        x.pipelineVersion = dai::gen::get_optional<std::string>(j, "pipelineVersion");
    }

    inline void to_json(json & j, const dai::gen::GlobalProperties & x) {
        j = json::object();
        j["leonOsFrequencyKhz"] = x.leonOsFrequencyKhz;
        j["leonRtFrequencyKhz"] = x.leonRtFrequencyKhz;
        j["pipelineName"] = x.pipelineName;
        j["pipelineVersion"] = x.pipelineVersion;
    }

    inline void from_json(const json & j, dai::gen::NodeObjInfo& x) {
        x.id = j.at("id").get<int64_t>();
        x.name = j.at("name").get<std::string>();
        x.properties = dai::gen::get_untyped(j, "properties");
    }

    inline void to_json(json & j, const dai::gen::NodeObjInfo & x) {
        j = json::object();
        j["id"] = x.id;
        j["name"] = x.name;
        j["properties"] = x.properties;
    }

    inline void from_json(const json & j, dai::gen::PipelineSchema& x) {
        x.connections = j.at("connections").get<std::vector<dai::gen::NodeConnectionSchema>>();
        x.globalProperties = j.at("globalProperties").get<dai::gen::GlobalProperties>();
        x.nodes = j.at("nodes").get<std::vector<dai::gen::NodeObjInfo>>();
    }

    inline void to_json(json & j, const dai::gen::PipelineSchema & x) {
        j = json::object();
        j["connections"] = x.connections;
        j["globalProperties"] = x.globalProperties;
        j["nodes"] = x.nodes;
    }

    inline void from_json(const json & j, dai::gen::ColorOrderInsidePixel & x) {
        if (j == "bgr") x = dai::gen::ColorOrderInsidePixel::BGR;
        else if (j == "rgb") x = dai::gen::ColorOrderInsidePixel::RGB;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const dai::gen::ColorOrderInsidePixel & x) {
        switch (x) {
            case dai::gen::ColorOrderInsidePixel::BGR: j = "bgr"; break;
            case dai::gen::ColorOrderInsidePixel::RGB: j = "rgb"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, dai::gen::CameraSensorResolution & x) {
        if (j == "1080p") x = dai::gen::CameraSensorResolution::THE_1080_P;
        else if (j == "4k") x = dai::gen::CameraSensorResolution::THE_4_K;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const dai::gen::CameraSensorResolution & x) {
        switch (x) {
            case dai::gen::CameraSensorResolution::THE_1080_P: j = "1080p"; break;
            case dai::gen::CameraSensorResolution::THE_4_K: j = "4k"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, dai::gen::ProcessorType & x) {
        if (j == "LOS") x = dai::gen::ProcessorType::LOS;
        else if (j == "LRT") x = dai::gen::ProcessorType::LRT;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const dai::gen::ProcessorType & x) {
        switch (x) {
            case dai::gen::ProcessorType::LOS: j = "LOS"; break;
            case dai::gen::ProcessorType::LRT: j = "LRT"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, dai::gen::VideoEncoderProfile & x) {
        if (j == "H264_BASELINE") x = dai::gen::VideoEncoderProfile::H264_BASELINE;
        else if (j == "H264_HIGH") x = dai::gen::VideoEncoderProfile::H264_HIGH;
        else if (j == "H264_MAIN") x = dai::gen::VideoEncoderProfile::H264_MAIN;
        else if (j == "H265_MAIN") x = dai::gen::VideoEncoderProfile::H265_MAIN;
        else if (j == "MJPEG") x = dai::gen::VideoEncoderProfile::MJPEG;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const dai::gen::VideoEncoderProfile & x) {
        switch (x) {
            case dai::gen::VideoEncoderProfile::H264_BASELINE: j = "H264_BASELINE"; break;
            case dai::gen::VideoEncoderProfile::H264_HIGH: j = "H264_HIGH"; break;
            case dai::gen::VideoEncoderProfile::H264_MAIN: j = "H264_MAIN"; break;
            case dai::gen::VideoEncoderProfile::H265_MAIN: j = "H265_MAIN"; break;
            case dai::gen::VideoEncoderProfile::MJPEG: j = "MJPEG"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, dai::gen::RateControlMode & x) {
        if (j == "CBR") x = dai::gen::RateControlMode::CBR;
        else if (j == "VBR") x = dai::gen::RateControlMode::VBR;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const dai::gen::RateControlMode & x) {
        switch (x) {
            case dai::gen::RateControlMode::CBR: j = "CBR"; break;
            case dai::gen::RateControlMode::VBR: j = "VBR"; break;
            default: throw "This should not happen";
        }
    }
}
