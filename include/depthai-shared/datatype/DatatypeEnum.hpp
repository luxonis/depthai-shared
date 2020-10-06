#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>
#include <vector>

namespace dai {

enum class DatatypeEnum : std::int32_t { RawBuffer, ImgFrame, NNTensor };
extern const std::unordered_map<DatatypeEnum, std::vector<DatatypeEnum>> hierarchy;
bool isDatatypeSubclassOf(DatatypeEnum parent, DatatypeEnum children);

}  // namespace dai
