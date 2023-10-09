#pragma once

#include <cstdint>

#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/RawSerializationHelpers.hpp"

namespace dai {

struct RawGroupMessage {
    dai::DatatypeEnum datatype;
    std::shared_ptr<RawBuffer> buffer;
    uint64_t offset = 0;
    uint64_t size = 0;
};

}  // namespace dai

// tl::optional serialization for nlohmann json
// partial specialization (full specialization works too)
namespace nlohmann {

template <>
struct adl_serializer<dai::RawGroupMessage> {
    static void to_json(json& j, const dai::RawGroupMessage& msg) {  // NOLINT this is a specialization, naming conventions don't apply
        j["datatype"] = msg.datatype;
        j["offset"] = msg.offset;
        j["size"] = msg.size;
        j["buffer"] = dai::serializeRawToJson(msg.buffer, msg.datatype);
    }

    static void from_json(const json& j, dai::RawGroupMessage& msg) {  // NOLINT this is a specialization, naming conventions don't apply
        auto datatype = j["datatype"].get<dai::DatatypeEnum>();
        auto offset = j["offset"].get<uint64_t>();
        auto size = j["size"].get<uint64_t>();
        auto buffer = dai::deserializeJsonToRaw(j["buffer"], datatype);
        msg = {datatype, buffer, offset, size};
    }
};

}  // namespace nlohmann

// tl::optional serialization for libnop
namespace nop {

static const SizeType numMembers = 4;

template <>
struct Encoding<dai::RawGroupMessage> : EncodingIO<dai::RawGroupMessage> {
    using Type = dai::RawGroupMessage;

    static constexpr EncodingByte Prefix(__attribute__((unused)) const Type& value) {
        return EncodingByte::Structure;
    }
    static std::size_t Size(const Type& value) {
        return BaseEncodingSize(EncodingByte::Structure) + Encoding<std::uint64_t>::Size(numMembers) + Encoding<dai::DatatypeEnum>::Size(value.datatype)
               + Encoding<uint64_t>::Size(value.offset) + Encoding<uint64_t>::Size(value.size) + dai::getNopSize(value.buffer, value.datatype);
    }

    static constexpr bool Match(EncodingByte prefix) {
        return prefix == EncodingByte::Structure;
    }

    template <typename Writer>
    static Status<void> WritePayload(__attribute__((unused)) EncodingByte prefix, const Type& value, Writer* writer) {
        auto status1 = Encoding<SizeType>::Write(numMembers, writer);
        if(!status1) return status1.error();
        auto status2 = Encoding<dai::DatatypeEnum>::Write(value.datatype, writer);
        if(!status2) return status2.error();
        auto status3 = Encoding<uint64_t>::Write(value.offset, writer);
        if(!status3) return status3.error();
        auto status4 = Encoding<uint64_t>::Write(value.size, writer);
        if(!status4) return status4.error();
        auto status5 = dai::serializeRawToNop(value.datatype, value.buffer, writer);
        if(!status5) return status5.error();
        return {};
    }

    template <typename Reader>
    static Status<void> ReadPayload(__attribute__((unused)) EncodingByte prefix, Type* value, Reader* reader) {
        SizeType numMembersRead;
        auto status1 = Encoding<std::uint64_t>::Read(&numMembersRead, reader);
        if(!status1) return status1.error();
        if(numMembersRead != numMembers) return ErrorStatus::InvalidMemberCount;
        dai::DatatypeEnum type;
        auto status2 = Encoding<dai::DatatypeEnum>::Read(&type, reader);
        if(!status2) return status2.error();
        uint64_t offset;
        auto status3 = Encoding<uint64_t>::Read(&offset, reader);
        if(!status3) return status3.error();
        uint64_t size;
        auto status4 = Encoding<uint64_t>::Read(&size, reader);
        if(!status4) return status4.error();
        auto status5 = dai::deserializeNopToRaw(type, reader);
        if(!status5) return status5.error();
        value->datatype = type;
        value->offset = offset;
        value->size = size;
        value->buffer = status5.get();
        return {};
    }
};

}  // namespace nop

namespace dai {

struct RawMessageGroup : public RawBuffer {
    std::unordered_map<std::string, RawGroupMessage> group;

   public:
    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::MessageGroup;
    };

    void updateOffsets() {
        uint64_t offset = 0;
        for(auto& entry : group) {
            entry.second.offset = offset;
            entry.second.size = entry.second.buffer->data.size();
            offset += entry.second.size;
        }
    }

    DEPTHAI_SERIALIZE(RawMessageGroup, group, RawBuffer::ts, RawBuffer::tsDevice);
};

}  // namespace dai
