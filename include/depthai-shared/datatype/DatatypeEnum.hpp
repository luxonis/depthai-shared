#pragma once

#include <cstdint>

namespace dai {

enum class DatatypeEnum : std::int32_t {
    Buffer,
    ImgFrame,
    EncodedFrame,
    NNData,
    ImageManipConfig,
    CameraControl,
    ImgDetections,
    SpatialImgDetections,
    SystemInformation,
    SpatialLocationCalculatorConfig,
    SpatialLocationCalculatorData,
    EdgeDetectorConfig,
    AprilTagConfig,
    AprilTags,
    Tracklets,
    IMUData,
    StereoDepthConfig,
    FeatureTrackerConfig,
    ImageAlignConfig,
    ToFConfig,
    PointCloudConfig,
    PointCloudData,
    TrackedFeatures,
    MessageGroup,
};
bool isDatatypeSubclassOf(DatatypeEnum parent, DatatypeEnum children);

}  // namespace dai
