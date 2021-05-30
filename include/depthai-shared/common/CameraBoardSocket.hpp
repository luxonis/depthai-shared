#pragma once

#include <nlohmann/json.hpp>

namespace dai {
/**
 * Which Camera socket to use.
 *
 * AUTO denotes that the decision will be made by device
 */
enum class CameraBoardSocket : int32_t { AUTO = -1, RGB, LEFT, RIGHT };

}  // namespace dai

namespace std {

template <>
struct hash<dai::CameraBoardSocket> {
    std::size_t operator()(const dai::CameraBoardSocket& s) const {
        using Type = typename underlying_type<dai::CameraBoardSocket>::type;
        return std::hash<Type>{}(static_cast<Type>(s));
    }
};
}  // namespace std
