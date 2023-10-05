#pragma once

#include <cstdint>

#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/RawSerializationHelpers.hpp"

namespace dai {

struct RawGroupMessage {
    dai::DatatypeEnum datatype;
    std::shared_ptr<RawBuffer> buffer;
};

}  // namespace dai

// tl::optional serialization for nlohmann json
// partial specialization (full specialization works too)
namespace nlohmann {

template <>
struct adl_serializer<dai::RawGroupMessage> {
    static void to_json(json& j, const dai::RawGroupMessage& msg) {  // NOLINT this is a specialization, naming conventions don't apply
        j["datatype"] = msg.datatype;
        j["buffer"] = dai::serializeRawToJson(msg.buffer, msg.datatype);
    }

    static void from_json(const json& j, dai::RawGroupMessage& msg) {  // NOLINT this is a specialization, naming conventions don't apply
        auto datatype = j["datatype"].get<dai::DatatypeEnum>();
        auto buffer = dai::deserializeJsonToRaw(j["buffer"], datatype);
        msg = {datatype, buffer};
    }
};

}  // namespace nlohmann

// tl::optional serialization for libnop
namespace nop {

template <>
struct Encoding<dai::RawGroupMessage> : EncodingIO<dai::RawGroupMessage> {
    using Type = dai::RawGroupMessage;

    inline static const SizeType numMembers = 2;

    static constexpr EncodingByte Prefix(__attribute__((unused)) const Type& value) {
        return EncodingByte::Structure;
    }
    static std::size_t Size(const Type& value) {
        return BaseEncodingSize(EncodingByte::Structure) + Encoding<std::uint64_t>::Size(numMembers) + Encoding<dai::DatatypeEnum>::Size(value.datatype)
               + dai::getNopSize(value.buffer, value.datatype);
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
        auto status3 = dai::serializeRawToNop(value.datatype, value.buffer, writer);
        if(!status3) return status3.error();
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
        auto status3 = dai::deserializeNopToRaw(type, reader);
        if(!status3) return status3.error();
        value->datatype = type;
        value->buffer = status3.get();
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
        datatype = DatatypeEnum::AprilTags;
    };

    DEPTHAI_SERIALIZE(RawMessageGroup, group, RawBuffer::ts, RawBuffer::tsDevice);
};

}  // namespace dai
