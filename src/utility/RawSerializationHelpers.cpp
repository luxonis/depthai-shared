#include "depthai-shared/utility/RawSerializationHelpers.hpp"

namespace dai {

nlohmann::json serializeRawToJson(const std::shared_ptr<RawBuffer>& object, DatatypeEnum type) {
    switch(type) {
        case DatatypeEnum::Buffer:
            return *object;
        case DatatypeEnum::ImgFrame:
            return *std::dynamic_pointer_cast<RawImgFrame>(object);
        case DatatypeEnum::NNData:
            return *std::dynamic_pointer_cast<RawNNData>(object);
        case DatatypeEnum::ImageManipConfig:
            return *std::dynamic_pointer_cast<RawImageManipConfig>(object);
        case DatatypeEnum::CameraControl:
            return *std::dynamic_pointer_cast<RawCameraControl>(object);
        case DatatypeEnum::ImgDetections:
            return *std::dynamic_pointer_cast<RawImgDetections>(object);
        case DatatypeEnum::SpatialImgDetections:
            return *std::dynamic_pointer_cast<RawSpatialImgDetections>(object);
        case DatatypeEnum::SystemInformation:
            return *std::dynamic_pointer_cast<RawSystemInformation>(object);
        case DatatypeEnum::SpatialLocationCalculatorConfig:
            return *std::dynamic_pointer_cast<RawSpatialLocationCalculatorConfig>(object);
        case DatatypeEnum::SpatialLocationCalculatorData:
            return *std::dynamic_pointer_cast<RawSpatialLocations>(object);
        case DatatypeEnum::EdgeDetectorConfig:
            return *std::dynamic_pointer_cast<RawEdgeDetectorConfig>(object);
        case DatatypeEnum::AprilTagConfig:
            return *std::dynamic_pointer_cast<RawAprilTagConfig>(object);
        case DatatypeEnum::AprilTags:
            return *std::dynamic_pointer_cast<RawAprilTags>(object);
        case DatatypeEnum::Tracklets:
            return *std::dynamic_pointer_cast<RawTracklets>(object);
        case DatatypeEnum::IMUData:
            return *std::dynamic_pointer_cast<RawIMUData>(object);
        case DatatypeEnum::StereoDepthConfig:
            return *std::dynamic_pointer_cast<RawStereoDepthConfig>(object);
        case DatatypeEnum::FeatureTrackerConfig:
            return *std::dynamic_pointer_cast<RawFeatureTrackerConfig>(object);
        case DatatypeEnum::ToFConfig:
            return *std::dynamic_pointer_cast<RawToFConfig>(object);
        case DatatypeEnum::TrackedFeatures:
            return *std::dynamic_pointer_cast<RawTrackedFeatures>(object);
        case DatatypeEnum::MessageGroup:
            return {};
    }
    return {};
}

std::shared_ptr<RawBuffer> deserializeJsonToRaw(const nlohmann::json& json, DatatypeEnum type) {
    switch(type) {
        case DatatypeEnum::Buffer: {
            auto buffer = std::make_shared<RawBuffer>();
            from_json(json, *buffer);
            return buffer;
        }
        case DatatypeEnum::ImgFrame: {
            auto buffer = std::make_shared<RawImgFrame>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::NNData: {
            auto buffer = std::make_shared<RawNNData>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::ImageManipConfig: {
            auto buffer = std::make_shared<RawImageManipConfig>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::CameraControl: {
            auto buffer = std::make_shared<RawCameraControl>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::ImgDetections: {
            auto buffer = std::make_shared<RawImgDetections>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::SpatialImgDetections: {
            auto buffer = std::make_shared<RawSpatialImgDetections>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::SystemInformation: {
            auto buffer = std::make_shared<RawSystemInformation>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::SpatialLocationCalculatorConfig: {
            auto buffer = std::make_shared<RawSpatialLocationCalculatorConfig>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::SpatialLocationCalculatorData: {
            auto buffer = std::make_shared<RawSpatialLocations>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::EdgeDetectorConfig: {
            auto buffer = std::make_shared<RawEdgeDetectorConfig>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::AprilTagConfig: {
            auto buffer = std::make_shared<RawAprilTagConfig>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::AprilTags: {
            auto buffer = std::make_shared<RawAprilTags>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::Tracklets: {
            auto buffer = std::make_shared<RawTracklets>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::IMUData: {
            auto buffer = std::make_shared<RawIMUData>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::StereoDepthConfig: {
            auto buffer = std::make_shared<RawStereoDepthConfig>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::FeatureTrackerConfig: {
            auto buffer = std::make_shared<RawFeatureTrackerConfig>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::ToFConfig: {
            auto buffer = std::make_shared<RawToFConfig>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::TrackedFeatures: {
            auto buffer = std::make_shared<RawTrackedFeatures>();
            from_json(json, *buffer);
            return std::static_pointer_cast<RawBuffer>(buffer);
        }
        case DatatypeEnum::MessageGroup: {
            return {};
        }
    }
    return {};
}

std::size_t getNopSize(const std::shared_ptr<RawBuffer>& object, DatatypeEnum type) {
    switch(type) {
        case DatatypeEnum::Buffer:
            return nop::Encoding<RawBuffer>::Size(*object);
        case DatatypeEnum::ImgFrame:
            return nop::Encoding<RawImgFrame>::Size(*std::dynamic_pointer_cast<RawImgFrame>(object));
        case DatatypeEnum::NNData:
            return nop::Encoding<RawNNData>::Size(*std::dynamic_pointer_cast<RawNNData>(object));
        case DatatypeEnum::ImageManipConfig:
            return nop::Encoding<RawImageManipConfig>::Size(*std::dynamic_pointer_cast<RawImageManipConfig>(object));
        case DatatypeEnum::CameraControl:
            return nop::Encoding<RawCameraControl>::Size(*std::dynamic_pointer_cast<RawCameraControl>(object));
        case DatatypeEnum::ImgDetections:
            return nop::Encoding<RawImgDetections>::Size(*std::dynamic_pointer_cast<RawImgDetections>(object));
        case DatatypeEnum::SpatialImgDetections:
            return nop::Encoding<RawSpatialImgDetections>::Size(*std::dynamic_pointer_cast<RawSpatialImgDetections>(object));
        case DatatypeEnum::SystemInformation:
            return nop::Encoding<RawSystemInformation>::Size(*std::dynamic_pointer_cast<RawSystemInformation>(object));
        case DatatypeEnum::SpatialLocationCalculatorConfig:
            return nop::Encoding<RawSpatialLocationCalculatorConfig>::Size(*std::dynamic_pointer_cast<RawSpatialLocationCalculatorConfig>(object));
        case DatatypeEnum::SpatialLocationCalculatorData:
            return nop::Encoding<RawSpatialLocations>::Size(*std::dynamic_pointer_cast<RawSpatialLocations>(object));
        case DatatypeEnum::EdgeDetectorConfig:
            return nop::Encoding<RawEdgeDetectorConfig>::Size(*std::dynamic_pointer_cast<RawEdgeDetectorConfig>(object));
        case DatatypeEnum::AprilTagConfig:
            return nop::Encoding<RawAprilTagConfig>::Size(*std::dynamic_pointer_cast<RawAprilTagConfig>(object));
        case DatatypeEnum::AprilTags:
            return nop::Encoding<RawAprilTags>::Size(*std::dynamic_pointer_cast<RawAprilTags>(object));
        case DatatypeEnum::Tracklets:
            return nop::Encoding<RawTracklets>::Size(*std::dynamic_pointer_cast<RawTracklets>(object));
        case DatatypeEnum::IMUData:
            return nop::Encoding<RawIMUData>::Size(*std::dynamic_pointer_cast<RawIMUData>(object));
        case DatatypeEnum::StereoDepthConfig:
            return nop::Encoding<RawStereoDepthConfig>::Size(*std::dynamic_pointer_cast<RawStereoDepthConfig>(object));
        case DatatypeEnum::FeatureTrackerConfig:
            return nop::Encoding<RawFeatureTrackerConfig>::Size(*std::dynamic_pointer_cast<RawFeatureTrackerConfig>(object));
        case DatatypeEnum::ToFConfig:
            return nop::Encoding<RawToFConfig>::Size(*std::dynamic_pointer_cast<RawToFConfig>(object));
        case DatatypeEnum::TrackedFeatures:
            return nop::Encoding<RawTrackedFeatures>::Size(*std::dynamic_pointer_cast<RawTrackedFeatures>(object));
        case DatatypeEnum::MessageGroup:
            return 0;
    }
    return 0;
}

}  // namespace dai
