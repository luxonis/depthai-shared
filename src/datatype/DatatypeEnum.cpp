#include "depthai-shared/datatype/DatatypeEnum.hpp"

#include <functional>
#include <type_traits>
#include <unordered_map>
#include <vector>

// DatatypeEnum hash specialization
namespace std {

template <>
struct hash<dai::DatatypeEnum> {
    std::size_t operator()(const dai::DatatypeEnum& s) const {
        using Type = typename underlying_type<dai::DatatypeEnum>::type;
        return std::hash<Type>{}(static_cast<Type>(s));
    }
};

}  // namespace std

namespace dai {

const std::unordered_map<DatatypeEnum, std::vector<DatatypeEnum>> hierarchy = {
    {DatatypeEnum::RawBuffer, {DatatypeEnum::ImgFrame, DatatypeEnum::NNData}}, {DatatypeEnum::ImgFrame, {}}, {DatatypeEnum::NNData, {}}};

bool isDatatypeSubclassOf(DatatypeEnum parent, DatatypeEnum children) {
    for(const auto& d : hierarchy.at(parent)) {
        if(d == children) return true;
        if(isDatatypeSubclassOf(d, children)) return true;
    }
    return false;
}

}  // namespace dai
