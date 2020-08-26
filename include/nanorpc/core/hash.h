#ifndef __NANO_RPC_CORE_HASH_H__
#define __NANO_RPC_CORE_HASH_H__

// STD
#include <cstdint>
#include <string>

namespace nanorpc::core
{

// Portable 64 bit string hasher
inline constexpr std::int64_t hash(const std::string& str) {
	std::int64_t h = 1125899906842597L; // prime
	for(const auto& c : str) h = 31 * h + c;
	return h;
}

}   // namespace nanorpc::core


#endif  // !__NANO_RPC_CORE_HASH_H__
