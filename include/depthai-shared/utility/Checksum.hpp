#pragma once

// std
#include <cstddef>
#include <cstdint>

namespace dai {
namespace utility {

std::uint32_t checksum(const void* buffer, std::size_t size, uint32_t prevChecksum);
std::uint32_t checksum(const void* buffer, std::size_t size);

}  // namespace utility
}  // namespace dai
