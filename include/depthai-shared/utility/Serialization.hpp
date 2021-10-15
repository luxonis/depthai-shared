#pragma once

// std
#include <cstddef>
#include <cstdint>
#include <vector>

// libraries
#include <nlohmann/json.hpp>

namespace dai {
namespace utility {

// Json-Msgpack serialization
template<typename T>
inline void serialize(const T& obj, std::vector<std::uint8_t>& data){
    nlohmann::json j = obj;
    data = nlohmann::json::to_msgpack(j);
}
template<typename T>
inline std::vector<std::uint8_t> serialize(const T& obj){
    std::vector<std::uint8_t> data;
    serialize(obj, data);
    return data;
}

// Json-Msgpack deserialization
template<typename T>
inline void deserialize(const std::uint8_t* data, std::size_t size, T& obj){
    nlohmann::from_json(nlohmann::json::from_msgpack(data, data + size), obj);
}
template<typename T>
inline void deserialize(const std::vector<std::uint8_t>& data, T& obj){
    deserialize(data.data(), data.size(), obj);
}


}
}