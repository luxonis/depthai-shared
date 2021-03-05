#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"
#include "RawImgFrame.hpp"

namespace dai {

// TODO move to common
struct Rect {
   public:
    Rect(float xmin, float ymin, float xmax, float ymax) {
        set(xmin, ymin, xmax, ymax);
    };
    Rect(){};

    void set(float xmin, float ymin, float xmax, float ymax) {
        this->xmin = xmin;
        this->xmax = xmax;
        this->ymin = ymin;
        this->ymax = ymax;
    }

    bool valid() {
        if(xmin < 0 || xmin > 1) return false;
        if(xmax < 0 || xmax > 1) return false;
        if(ymin < 0 || ymin > 1) return false;
        if(ymax < 0 || ymax > 1) return false;
        if(xmin >= xmax) return false;
        if(ymin >= ymax) return false;
        return true;
    }

    // Normalized range 0-1
    float xmin = 0.0f, ymin = 0.0f, xmax = 0.0f, ymax = 0.0f;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Rect, xmin, ymin, xmax, ymax);

struct DepthCalculatorConfigData {
    // Normalized range 0-1
    Rect roi;
    uint32_t lower_threshold = 0;
    uint32_t upper_threshold = 65000;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DepthCalculatorConfigData, roi, lower_threshold, upper_threshold);

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