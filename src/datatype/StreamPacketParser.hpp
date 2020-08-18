#pragma once

//standard
#include <memory>

// libraries
#include <nlohmann/json.hpp>
#include <XLinkPublicDefines.h>

// project
#include <DatatypeEnum.hpp>
#include <RawBuffer.hpp>
#include <ImgFrame.h>
#include <NNTensor.hpp>


// StreamPacket structure ->  || imgframepixels... , serialized_object, object_type, serialized_object_size ||
// object_type -> DataType(int), serialized_object_size -> int

namespace dai
{
    

    // Reads int from little endian format
    int readIntLE(uint8_t* data){
        return data[0] + data[1] * 256 + data[2] * 256*256 + data[3] * 256*256*256;
    }

    template<class T>
    std::shared_ptr<T> parseDatatype(nlohmann::json& ser, std::vector<uint8_t> data){
        T tmp;
        nlohmann::json::from_json(ser, tmp);
        tmp.data = data;
        return tmp;
    }

    std::shared_ptr<RawBuffer> parsePacket(streamPacketDesc_t* packet) {
        
        int serializedObjectSize = readIntLE(packet->data + packet->length - 4);
        Datatype objectType = (Datatype) readIntLE(packet->data + packet->length - 8);
        
        if(serializedObjectSize < 0){
            throw std::runtime_error("Bad packet, couldn't parse");
        }
        int bufferLength = packet->length - 8 - serializedObjectSize;
        auto msgpackStart = packet->data + bufferLength;

        nlohmann::json j = nlohmann::json::from_msgpack(msgpackStart, msgpackStart + serializedObjectSize);

        // copy data part
        std::vector<uint8_t> data(packet->data, packet->data + bufferLength);

        switch (objectType)
        {
        case DatatypeEnum::RawBuffer :
            return parseDatatype<RawBuffer>(ser, data);
            break;
        
        case DatatypeEnum::ImgFrame : 
            return parseDatatype<ImgFrame>(ser, data);
            break;

        case DatatypeEnum::NNTensor : 
            return parseDatatype<NNTensor>(ser, data);
            break;

        default:
            throw std::runtime_error("Bad packet, couldn't parse");
            break;
        }

    }


} // namespace dai
