#include "depthai-shared/datatype/DatatypeEnum.hpp"

namespace dai
{
    
   const std::unordered_map<DatatypeEnum, std::vector<DatatypeEnum>> hierarchy = {
        {DatatypeEnum::RawBuffer, {DatatypeEnum::ImgFrame, DatatypeEnum::NNTensor}},
        {DatatypeEnum::ImgFrame, {}},
        {DatatypeEnum::NNTensor, {}}
    };

    bool isDatatypeSubclassOf(DatatypeEnum parent, DatatypeEnum children){
        for(auto& d : hierarchy.at(parent)){
            if(d == children) return true;
            if(isDatatypeSubclassOf(d, children)) return true;
        }
        return false;
    }

} // namespace dai


    