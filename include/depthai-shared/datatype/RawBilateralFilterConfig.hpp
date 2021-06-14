#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"

namespace dai {

/**
 * BilateralFilter configuration
 *
 * Contains configuration for sigma value.
 */

/// BilateralFilter configuration data structure
struct BilateralFilterConfig {
    int32_t sigmaValue;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BilateralFilterConfig, sigmaValue);

/// RawBilateralFilter configuration structure
struct RawBilateralFilterConfig : public RawBuffer {
    BilateralFilterConfig config;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::BilateralFilterConfig;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawBilateralFilterConfig, config);
};

}  // namespace dai