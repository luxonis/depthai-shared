#pragma once
#include <cstdint>
#include <vector>
#include <nlohmann/json.hpp>


namespace dai
{
    
struct RawBuffer {
    virtual ~RawBuffer(){}
    std::vector<uint8_t> data;

    //NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawBuffer);
};

}