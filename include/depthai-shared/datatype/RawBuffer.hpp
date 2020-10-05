#pragma once
#include <cstdint>
#include <vector>
#include <nlohmann/json.hpp>
#include "DatatypeEnum.hpp"

namespace dai
{
    
struct RawBuffer {
    virtual ~RawBuffer() = default;
    std::vector<uint8_t> data;

    virtual void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype){
        (void) metadata;
        datatype = DatatypeEnum::RawBuffer;
    };

    //NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawBuffer);
};

}