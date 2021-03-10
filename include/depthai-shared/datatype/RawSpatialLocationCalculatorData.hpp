#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"
#include "RawImgFrame.hpp"
#include "RawSpatialLocationCalculatorConfig.hpp"
#include "depthai-shared/common/Point3f.hpp"
#include "depthai-shared/common/Rect.hpp"

namespace dai {

struct SpatialLocationCalculatorDataOut {
    SpatialLocationCalculatorConfigData config;
    float depthAverage;
    Point3f spatialCoordinates;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SpatialLocationCalculatorDataOut, config, depthAverage, spatialCoordinates);

struct RawSpatialLocationCalculatorData : public RawBuffer {
    std::vector<SpatialLocationCalculatorDataOut> depth;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::SpatialLocationCalculatorData;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawSpatialLocationCalculatorData, depth);
};

}  // namespace dai