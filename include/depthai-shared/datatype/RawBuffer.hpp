#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"

namespace dai {

struct RawBuffer {
    virtual ~RawBuffer() = default;
    std::vector<std::uint8_t> data;

    virtual void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) {
        (void)metadata;
        datatype = DatatypeEnum::Buffer;
    };

    // NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawBuffer);
};

}  // namespace dai