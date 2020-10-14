#pragma once

#include <cstdint>

namespace dai {

enum class DatatypeEnum : std::int32_t { RawBuffer, ImgFrame, NNData };
bool isDatatypeSubclassOf(DatatypeEnum parent, DatatypeEnum children);

}  // namespace dai
