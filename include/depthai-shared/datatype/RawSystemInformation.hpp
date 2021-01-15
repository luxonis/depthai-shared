#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"
#include "depthai-shared/pb/common/ChipTemperature.hpp"
#include "depthai-shared/pb/common/CpuUsage.hpp"
#include "depthai-shared/pb/common/MemoryInfo.hpp"

namespace dai {

struct RawSystemInformation : public RawBuffer {
    MemoryInfo memoryDdrUsage, memoryLeonOsUsage, memoryLeonRtUsage;
    CpuUsage cpuLeonOsUsage, cpuLeonRtUsage;
    ChipTemperature chipTemperature;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::SystemInformation;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawSystemInformation, memoryDdrUsage, memoryLeonOsUsage, memoryLeonRtUsage, cpuLeonOsUsage, cpuLeonRtUsage, chipTemperature);
};

}  // namespace dai