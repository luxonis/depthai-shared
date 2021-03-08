#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"
#include "RawImgFrame.hpp"
#include "depthai-shared/common/Rect.hpp"

namespace dai {

struct DepthCalculatorConfigThresholds {
    uint32_t lowerThreshold = 0;
    uint32_t upperThreshold = 65000;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DepthCalculatorConfigThresholds, lowerThreshold, upperThreshold);

struct DepthCalculatorConfigData {
    // Normalized range 0-1
    Rect roi;
    DepthCalculatorConfigThresholds depthThresholds;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DepthCalculatorConfigData, roi, depthThresholds);

struct RawDepthCalculatorConfig : public RawBuffer {
    std::vector<DepthCalculatorConfigData> config;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::DepthCalculatorConfig;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawDepthCalculatorConfig, config);
};

}  // namespace dai