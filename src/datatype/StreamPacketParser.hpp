#pragma once

//standard
#include <memory>

// libraries
#include <nlohmann/json.hpp>
#include <XLinkPublicDefines.h>

// project
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/datatype/ImgFrame.hpp"
#include "depthai-shared/datatype/NNTensor.hpp"


// StreamPacket structure ->  || imgframepixels... , serialized_object, object_type, serialized_object_size ||
// object_type -> DataType(int), serialized_object_size -> int

namespace dai
{
    

    // Reads int from little endian format
    inline int readIntLE(uint8_t* data){
        return data[0] + data[1] * 256 + data[2] * 256*256 + data[3] * 256*256*256;
    }

    template<class T>
    inline std::shared_ptr<T> parseDatatype(nlohmann::json& ser, std::vector<uint8_t> data){
        auto tmp = std::make_shared<T>();
        nlohmann::from_json(ser, *tmp);
        tmp->data = data;
        return tmp;
    }

    inline std::shared_ptr<RawBuffer> parsePacket(streamPacketDesc_t* packet) {
        
        int serializedObjectSize = readIntLE(packet->data + packet->length - 4);
        DatatypeEnum objectType = (DatatypeEnum) readIntLE(packet->data + packet->length - 8);
        
        if(serializedObjectSize < 0){
            throw std::runtime_error("Bad packet, couldn't parse");
        }
        int bufferLength = packet->length - 8 - serializedObjectSize;
        auto msgpackStart = packet->data + bufferLength;

        nlohmann::json jser = nlohmann::json::from_msgpack(msgpackStart, msgpackStart + serializedObjectSize);

        // copy data part
        std::vector<uint8_t> data(packet->data, packet->data + bufferLength);

        // RawBuffer is special case, no metadata is actually serialized
        if(objectType == DatatypeEnum::RawBuffer){
            auto pBuf = std::make_shared<RawBuffer>();
            pBuf->data = data;
            return pBuf;
        }

        switch (objectType)
        {
       
        case DatatypeEnum::ImgFrame : 
            return parseDatatype<ImgFrame>(jser, data);
            break;

        case DatatypeEnum::NNTensor : 
            return parseDatatype<NNTensor>(jser, data);
            break;

        default:
            throw std::runtime_error("Bad packet, couldn't parse");
            break;
        }

    }


} // namespace dai
