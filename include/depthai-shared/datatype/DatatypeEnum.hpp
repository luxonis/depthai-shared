#pragma once

#include <cstdint>

namespace dai {

enum class DatatypeEnum : std::int32_t { RawBuffer, ImgFrame, NNTensor };
bool isDatatypeSubclassOf(DatatypeEnum parent, DatatypeEnum children);

}  // namespace dai
