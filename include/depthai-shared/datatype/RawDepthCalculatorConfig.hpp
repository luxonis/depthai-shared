#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"
#include "RawImgFrame.hpp"

namespace dai {

//TODO move to common
struct Rect {
    // Normalized range 0-1
    float xmin = 0.0f, ymin = 0.0f, xmax = 0.0f, ymax = 0.0f;

};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Rect, xmin, ymin, xmax, ymax);

struct DepthCalculatorConfig {
    // Normalized range 0-1
    Rect roi;
    uint32_t lower_threshold = 0;
    uint32_t upper_threshold = 65000;

};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DepthCalculatorConfig, roi, lower_threshold, upper_threshold);

struct RawDepthCalculatorConfig : public RawBuffer {

    DepthCalculatorConfig config;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::DepthCalculatorConfig;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawDepthCalculatorConfig, config);
};

}  // namespace dai