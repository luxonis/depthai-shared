#pragma once

#include <nop/base/encoding_byte.h>

#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawAprilTagConfig.hpp"
#include "depthai-shared/datatype/RawAprilTags.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/datatype/RawCameraControl.hpp"
#include "depthai-shared/datatype/RawEdgeDetectorConfig.hpp"
#include "depthai-shared/datatype/RawFeatureTrackerConfig.hpp"
#include "depthai-shared/datatype/RawIMUData.hpp"
#include "depthai-shared/datatype/RawImageManipConfig.hpp"
#include "depthai-shared/datatype/RawImgDetections.hpp"
#include "depthai-shared/datatype/RawImgFrame.hpp"
#include "depthai-shared/datatype/RawNNData.hpp"
#include "depthai-shared/datatype/RawSpatialImgDetections.hpp"
#include "depthai-shared/datatype/RawSpatialLocationCalculatorConfig.hpp"
#include "depthai-shared/datatype/RawSpatialLocations.hpp"
#include "depthai-shared/datatype/RawStereoDepthConfig.hpp"
#include "depthai-shared/datatype/RawSystemInformation.hpp"
#include "depthai-shared/datatype/RawToFConfig.hpp"
#include "depthai-shared/datatype/RawTrackedFeatures.hpp"
#include "depthai-shared/datatype/RawTracklets.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

nlohmann::json serializeRawToJson(const std::shared_ptr<RawBuffer>& object, DatatypeEnum type);

std::shared_ptr<RawBuffer> deserializeJsonToRaw(const nlohmann::json& json, DatatypeEnum type);

std::size_t getNopSize(const std::shared_ptr<RawBuffer>& object, DatatypeEnum type);

template <typename Writer>
nop::Status<void> serializeRawToNop(DatatypeEnum type, const std::shared_ptr<RawBuffer>& buffer, Writer* writer) {
    switch(type) {
        case DatatypeEnum::Buffer:
            return nop::Encoding<RawBuffer>::Write(*buffer, writer);
        case DatatypeEnum::ImgFrame:
            return nop::Encoding<RawImgFrame>::Write(*std::dynamic_pointer_cast<RawImgFrame>(buffer), writer);
        case DatatypeEnum::NNData:
            return nop::Encoding<RawNNData>::Write(*std::dynamic_pointer_cast<RawNNData>(buffer), writer);
        case DatatypeEnum::ImageManipConfig:
            return nop::Encoding<RawImageManipConfig>::Write(*std::dynamic_pointer_cast<RawImageManipConfig>(buffer), writer);
        case DatatypeEnum::CameraControl:
            return nop::Encoding<RawCameraControl>::Write(*std::dynamic_pointer_cast<RawCameraControl>(buffer), writer);
        case DatatypeEnum::ImgDetections:
            return nop::Encoding<RawImgDetections>::Write(*std::dynamic_pointer_cast<RawImgDetections>(buffer), writer);
        case DatatypeEnum::SpatialImgDetections:
            return nop::Encoding<RawSpatialImgDetections>::Write(*std::dynamic_pointer_cast<RawSpatialImgDetections>(buffer), writer);
        case DatatypeEnum::SystemInformation:
            return nop::Encoding<RawSystemInformation>::Write(*std::dynamic_pointer_cast<RawSystemInformation>(buffer), writer);
        case DatatypeEnum::SpatialLocationCalculatorConfig:
            return nop::Encoding<RawSpatialLocationCalculatorConfig>::Write(*std::dynamic_pointer_cast<RawSpatialLocationCalculatorConfig>(buffer), writer);
        case DatatypeEnum::SpatialLocationCalculatorData:
            return nop::Encoding<RawSpatialLocations>::Write(*std::dynamic_pointer_cast<RawSpatialLocations>(buffer), writer);
        case DatatypeEnum::EdgeDetectorConfig:
            return nop::Encoding<RawEdgeDetectorConfig>::Write(*std::dynamic_pointer_cast<RawEdgeDetectorConfig>(buffer), writer);
        case DatatypeEnum::AprilTagConfig:
            return nop::Encoding<RawAprilTagConfig>::Write(*std::dynamic_pointer_cast<RawAprilTagConfig>(buffer), writer);
        case DatatypeEnum::AprilTags:
            return nop::Encoding<RawAprilTags>::Write(*std::dynamic_pointer_cast<RawAprilTags>(buffer), writer);
        case DatatypeEnum::Tracklets:
            return nop::Encoding<RawTracklets>::Write(*std::dynamic_pointer_cast<RawTracklets>(buffer), writer);
        case DatatypeEnum::IMUData:
            return nop::Encoding<RawIMUData>::Write(*std::dynamic_pointer_cast<RawIMUData>(buffer), writer);
        case DatatypeEnum::StereoDepthConfig:
            return nop::Encoding<RawStereoDepthConfig>::Write(*std::dynamic_pointer_cast<RawStereoDepthConfig>(buffer), writer);
        case DatatypeEnum::FeatureTrackerConfig:
            return nop::Encoding<RawFeatureTrackerConfig>::Write(*std::dynamic_pointer_cast<RawFeatureTrackerConfig>(buffer), writer);
        case DatatypeEnum::ToFConfig:
            return nop::Encoding<RawToFConfig>::Write(*std::dynamic_pointer_cast<RawToFConfig>(buffer), writer);
        case DatatypeEnum::TrackedFeatures:
            return nop::Encoding<RawTrackedFeatures>::Write(*std::dynamic_pointer_cast<RawTrackedFeatures>(buffer), writer);
        case DatatypeEnum::MessageGroup:
            return {};
    }
    return {};
}

template <typename Reader>
nop::Status<std::shared_ptr<RawBuffer>> deserializeNopToRaw(DatatypeEnum type, Reader* reader) {
    switch(type) {
        case DatatypeEnum::Buffer: {
            RawBuffer buf;
            auto status = nop::Encoding<RawBuffer>::Read(&buf, reader);
            if(!status) return status.error();
            return std::make_shared<RawBuffer>(std::move(buf));
        }
        case DatatypeEnum::ImgFrame: {
            RawImgFrame buf;
            auto status = nop::Encoding<RawImgFrame>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawImgFrame>(std::move(buf)));
        }
        case DatatypeEnum::NNData: {
            RawNNData buf;
            auto status = nop::Encoding<RawNNData>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawNNData>(std::move(buf)));
        }
        case DatatypeEnum::ImageManipConfig: {
            RawImageManipConfig buf;
            auto status = nop::Encoding<RawImageManipConfig>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawImageManipConfig>(std::move(buf)));
        }
        case DatatypeEnum::CameraControl: {
            RawCameraControl buf;
            auto status = nop::Encoding<RawCameraControl>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawCameraControl>(std::move(buf)));
        }
        case DatatypeEnum::ImgDetections: {
            RawImgDetections buf;
            auto status = nop::Encoding<RawImgDetections>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawImgDetections>(std::move(buf)));
        }
        case DatatypeEnum::SpatialImgDetections: {
            RawSpatialImgDetections buf;
            auto status = nop::Encoding<RawSpatialImgDetections>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawSpatialImgDetections>(std::move(buf)));
        }
        case DatatypeEnum::SystemInformation: {
            RawSystemInformation buf;
            auto status = nop::Encoding<RawSystemInformation>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawSystemInformation>(std::move(buf)));
        }
        case DatatypeEnum::SpatialLocationCalculatorConfig: {
            RawSpatialLocationCalculatorConfig buf;
            auto status = nop::Encoding<RawSpatialLocationCalculatorConfig>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawSpatialLocationCalculatorConfig>(std::move(buf)));
        }
        case DatatypeEnum::SpatialLocationCalculatorData: {
            RawSpatialLocations buf;
            auto status = nop::Encoding<RawSpatialLocations>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawSpatialLocations>(std::move(buf)));
        }
        case DatatypeEnum::EdgeDetectorConfig: {
            RawEdgeDetectorConfig buf;
            auto status = nop::Encoding<RawEdgeDetectorConfig>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawEdgeDetectorConfig>(std::move(buf)));
        }
        case DatatypeEnum::AprilTagConfig: {
            RawAprilTagConfig buf;
            auto status = nop::Encoding<RawAprilTagConfig>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawAprilTagConfig>(std::move(buf)));
        }
        case DatatypeEnum::AprilTags: {
            RawAprilTags buf;
            auto status = nop::Encoding<RawAprilTags>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawAprilTags>(std::move(buf)));
        }
        case DatatypeEnum::Tracklets: {
            RawTracklets buf;
            auto status = nop::Encoding<RawTracklets>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawTracklets>(std::move(buf)));
        }
        case DatatypeEnum::IMUData: {
            RawIMUData buf;
            auto status = nop::Encoding<RawIMUData>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawIMUData>(std::move(buf)));
        }
        case DatatypeEnum::StereoDepthConfig: {
            RawStereoDepthConfig buf;
            auto status = nop::Encoding<RawStereoDepthConfig>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawStereoDepthConfig>(std::move(buf)));
        }
        case DatatypeEnum::FeatureTrackerConfig: {
            RawFeatureTrackerConfig buf;
            auto status = nop::Encoding<RawFeatureTrackerConfig>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawFeatureTrackerConfig>(std::move(buf)));
        }
        case DatatypeEnum::ToFConfig: {
            RawToFConfig buf;
            auto status = nop::Encoding<RawToFConfig>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawToFConfig>(std::move(buf)));
        }
        case DatatypeEnum::TrackedFeatures: {
            RawTrackedFeatures buf;
            auto status = nop::Encoding<RawTrackedFeatures>::Read(&buf, reader);
            if(!status) return status.error();
            return std::static_pointer_cast<RawBuffer>(std::make_shared<RawTrackedFeatures>(std::move(buf)));
        }
        case DatatypeEnum::MessageGroup: {
            return {};
        }
    }
    return {};
}
}  // namespace dai
