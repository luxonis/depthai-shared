#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"
#include "RawDepthCalculatorConfig.hpp"
#include "RawImgFrame.hpp"
#include "depthai-shared/common/Point3f.hpp"
#include "depthai-shared/common/Rect.hpp"

namespace dai {

struct DepthCalculatorDataOut {
    DepthCalculatorConfigData config;
    float depthAverage;
    Point3f spatialCoordinates;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DepthCalculatorDataOut, config, depthAverage, spatialCoordinates);

struct RawDepthCalculatorData : public RawBuffer {
    std::vector<DepthCalculatorDataOut> depth;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::DepthCalculatorData;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawDepthCalculatorData, depth);
};

}  // namespace dai