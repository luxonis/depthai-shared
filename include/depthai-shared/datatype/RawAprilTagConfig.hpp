#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"
#include "RawImgFrame.hpp"
#include "depthai-shared/common/Rect.hpp"

namespace dai {

/**
 * AprilTag configuration thresholds structure
 *
 * Contains configuration data for lower and upper threshold in millimeters for ROI.
 * Values outside of threshold range will be ignored when calculating spatial coordinates from depth map.
 */
struct AprilTagConfigThresholds {
    uint32_t lowerThreshold = 0;
    uint32_t upperThreshold = 65535;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AprilTagConfigThresholds, lowerThreshold, upperThreshold);

/// AprilTag configuration data structure
struct AprilTagConfigData {
    enum class AprilTagType : std::int32_t { TAG_36H11 = 0, TAG_25H9, TAG_16H5, TAG_CIR21H7, TAG_CIR49H12, TAG_CUST48H12, TAG_STAND41H12, TAG_STAND52H13 };

    AprilTagType type = AprilTagType::TAG_36H11;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AprilTagConfigData, type);

/// RawAprilTags configuration structure
struct RawAprilTagConfig : public RawBuffer {
    AprilTagConfigData config;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::AprilTagConfig;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawAprilTagConfig, config);
};

}  // namespace dai
