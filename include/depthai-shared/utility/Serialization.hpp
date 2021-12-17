#pragma once

// std
#include <cstddef>
#include <cstdint>
#include <vector>

// libraries
#include <nop/serializer.h>
#include <nop/structure.h>
#include <nop/utility/buffer_reader.h>
#include <nop/utility/stream_writer.h>

#include <nlohmann/json.hpp>

// To not require exceptions for embedded usecases.
#ifndef __has_feature           // Optional of course.
    #define __has_feature(x) 0  // Compatibility with non-clang compilers.
#endif
#if __has_feature(cxx_exceptions) || defined(__cpp_exceptions) || (defined(_MSC_VER) && defined(_CPPUNWIND)) || defined(__EXCEPTIONS)
    #define DEPTHAI_EXCEPTIONS
#endif

namespace dai {
namespace utility {

// // Json-Msgpack serialization
// template<typename T>
// inline void serialize(const T& obj, std::vector<std::uint8_t>& data){
//     nlohmann::json j = obj;
//     data = nlohmann::json::to_msgpack(j);
// }
// template<typename T>
// inline std::vector<std::uint8_t> serialize(const T& obj){
//     std::vector<std::uint8_t> data;
//     serialize(obj, data);
//     return data;
// }
//
// // Json-Msgpack deserialization
// template<typename T>
// inline void deserialize(const std::uint8_t* data, std::size_t size, T& obj){
//     nlohmann::from_json(nlohmann::json::from_msgpack(data, data + size), obj);
// }
// template<typename T>
// inline void deserialize(const std::vector<std::uint8_t>& data, T& obj){
//     deserialize(data.data(), data.size(), obj);
// }

class VectorWriter {
   public:
    template <typename... Args>
    VectorWriter(Args&&... args) : vector{std::forward<Args>(args)...} {}
    VectorWriter(const VectorWriter&) = default;
    VectorWriter& operator=(const VectorWriter&) = default;

    nop::Status<void> Prepare(std::size_t /*size*/) {
        return {};
    }

    nop::Status<void> Write(std::uint8_t byte) {
        vector.push_back(byte);
        return ReturnStatus();
    }

    nop::Status<void> Write(const void* begin, const void* end) {
        vector.insert(vector.end(), static_cast<const std::uint8_t*>(begin), static_cast<const std::uint8_t*>(end));
        return ReturnStatus();
    }

    nop::Status<void> Skip(std::size_t padding_bytes, std::uint8_t padding_value = 0x00) {
        for(std::size_t i = 0; i < padding_bytes; i++) {
            vector.push_back(padding_value);
            auto status = ReturnStatus();
            if(!status) return status;
        }

        return {};
    }

    const std::vector<std::uint8_t>& ref() const {
        return vector;
    }
    std::vector<std::uint8_t>& ref() {
        return vector;
    }
    std::vector<std::uint8_t>&& take() {
        return std::move(vector);
    }

   private:
    nop::Status<void> ReturnStatus() {
        return {};
    }

    std::vector<std::uint8_t> vector;
};

// libnop serialization
// If exceptions are available it throws in error cases
// Otherwise return value can be checked
template <typename T>
inline bool serialize(const T& obj, std::vector<std::uint8_t>& data) {
    nop::Serializer<VectorWriter> serializer{std::move(data)};
    auto status = serializer.Write(obj);
    if(!status) {
#ifdef DEPTHAI_EXCEPTIONS
        throw std::runtime_error(status.GetErrorMessage());
#else
        return false;
#endif
    }
    data = std::move(serializer.writer().take());
    return true;
}
template <typename T>
inline std::vector<std::uint8_t> serialize(const T& obj) {
    std::vector<std::uint8_t> data;
    if(serialize(obj, data)) {
        return data;
    } else {
        return {};
    }
}

// libnop deserialization
template <typename T>
inline bool deserialize(const std::uint8_t* data, std::size_t size, T& obj) {
    nop::Deserializer<nop::BufferReader> deserializer{data, size};
    auto status = deserializer.Read(&obj);
    if(!status) {
#ifdef DEPTHAI_EXCEPTIONS
        throw std::runtime_error(status.GetErrorMessage());
#else
        return false;
#endif
    }
    return true;
}
template <typename T>
inline bool deserialize(const std::vector<std::uint8_t>& data, T& obj) {
    return deserialize(data.data(), data.size(), obj);
}

}  // namespace utility

// // In dai scope
// template<typename Base, typename Derived>
// struct Serializable : Base {
//     virtual void serialize(std::vector<std::uint8_t>& data) {
//         utility::serialize(static_cast<const Derived&>(*this), data);
//     }
// };

}  // namespace dai

// Macros
#define DEPTHAI_SERIALIZE_EXT(...)                  \
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(__VA_ARGS__) \
    NOP_EXTERNAL_STRUCTURE(__VA_ARGS__)

#define DEPTHAI_SERIALIZE(...)                  \
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(__VA_ARGS__) \
    NOP_STRUCTURE(__VA_ARGS__)
