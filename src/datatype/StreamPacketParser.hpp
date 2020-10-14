#pragma once

// standard
#include <memory>

// libraries
#include <XLinkPublicDefines.h>

#include <nlohmann/json.hpp>

// project
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/ImgFrame.hpp"
#include "depthai-shared/datatype/NNData.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"

// StreamPacket structure ->  || imgframepixels... , serialized_object, object_type, serialized_object_size ||
// object_type -> DataType(int), serialized_object_size -> int

namespace dai {

// Reads int from little endian format
inline int readIntLE(uint8_t* data) {
    return data[0] + data[1] * 256 + data[2] * 256 * 256 + data[3] * 256 * 256 * 256;
}

template <class T>
inline std::shared_ptr<T> parseDatatype(nlohmann::json& ser, const std::vector<uint8_t>& data) {
    auto tmp = std::make_shared<T>();
    nlohmann::from_json(ser, *tmp);
    tmp->data = data;
    return tmp;
}

inline std::shared_ptr<RawBuffer> parsePacket(streamPacketDesc_t* packet) {
    int serializedObjectSize = readIntLE(packet->data + packet->length - 4);
    auto objectType = static_cast<DatatypeEnum>(readIntLE(packet->data + packet->length - 8));

    if(serializedObjectSize < 0) {
        throw std::runtime_error("Bad packet, couldn't parse");
    }
    std::uint32_t bufferLength = packet->length - 8 - serializedObjectSize;
    auto* msgpackStart = packet->data + bufferLength;

    nlohmann::json jser = nlohmann::json::from_msgpack(msgpackStart, msgpackStart + serializedObjectSize);

    // copy data part
    std::vector<uint8_t> data(packet->data, packet->data + bufferLength);

    // RawBuffer is special case, no metadata is actually serialized
    if(objectType == DatatypeEnum::RawBuffer) {
        auto pBuf = std::make_shared<RawBuffer>();
        pBuf->data = data;
        return pBuf;
    }

    switch(objectType) {
        case DatatypeEnum::ImgFrame:
            return parseDatatype<ImgFrame>(jser, data);
            break;

        case DatatypeEnum::NNData:
            return parseDatatype<NNData>(jser, data);
            break;

        default:
            throw std::runtime_error("Bad packet, couldn't parse");
            break;
    }
}

inline std::vector<std::uint8_t> serializeData(const std::shared_ptr<RawBuffer>& data) {
    std::vector<std::uint8_t> ser;
    if(!data) return ser;

    // Serialization:
    // 1. fill vector with bytes from data.data
    // 2. serialize and append metadata
    // 3. append datatype enum (4B LE)
    // 4. append size (4B LE) of serialized metadata

    std::vector<std::uint8_t> metadata;
    DatatypeEnum datatype;
    data->serialize(metadata, datatype);
    uint32_t metadataSize = metadata.size();

    // 4B datatype & 4B metadata size
    std::uint8_t leDatatype[4];
    std::uint8_t leMetadataSize[4];
    for(int i = 0; i < 4; i++) leDatatype[i] = (static_cast<std::int32_t>(datatype) >> (i * 8)) & 0xFF;
    for(int i = 0; i < 4; i++) leMetadataSize[i] = (metadataSize >> i * 8) & 0xFF;

    ser.insert(ser.end(), data->data.begin(), data->data.end());
    ser.insert(ser.end(), metadata.begin(), metadata.end());
    ser.insert(ser.end(), leDatatype, leDatatype + sizeof(leDatatype));
    ser.insert(ser.end(), leMetadataSize, leMetadataSize + sizeof(leMetadataSize));

    return ser;
}

}  // namespace dai
