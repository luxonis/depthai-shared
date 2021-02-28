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
        setRect(xmin, ymin, xmax, ymax);
    };
    Rect(){};

    void setRect(float xmin, float ymin, float xmax, float ymax) {
#ifdef __cpp_exceptions
        if(xmin < 0 || xmin > 1) throw std::out_of_range("xmin out of range [0,1]");
        if(xmax < 0 || xmax > 1) throw std::out_of_range("xmax out of range [0,1]");
        if(ymin < 0 || ymin > 1) throw std::out_of_range("ymin out of range [0,1]");
        if(ymax < 0 || ymax > 1) throw std::out_of_range("ymax out of range [0,1]");
        if(xmin >= xmax) throw std::out_of_range("xmin should be less than xmax");
        if(ymin >= ymax) throw std::out_of_range("ymin should be less than ymax");
#endif
        this->xmin = xmin;
        this->xmax = xmax;
        this->ymin = ymin;
        this->ymax = ymax;
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