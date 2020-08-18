#pragma once

#include <unordered_map>
#include <vector>

namespace dai
{

    enum class DatatypeEnum : int32_t {
        RawBuffer,
        ImgFrame,
        NNTensor
    };
    extern const std::unordered_map<DatatypeEnum, std::vector<DatatypeEnum>> hierarchy;
    bool isDatatypeSubclassOf(DatatypeEnum parent, DatatypeEnum children);

    
} // namespace dai

