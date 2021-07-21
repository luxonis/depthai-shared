#pragma once

// std
#include <cstdint>

// project
#include "depthai-shared/common/UsbSpeed.hpp"

namespace dai {

constexpr static uint32_t PREBOOT_CONFIG_MAGIC1 = 0x78010000U;
constexpr static uint32_t PREBOOT_CONFIG_MAGIC2 = 0x21ea17e6U;

struct PrebootConfig {
    uint16_t vid = 0x03e7, pid = 0xf63b;
    uint16_t flashBootedVid = 0x03e7, flashBootedPid = 0xf63d;
    UsbSpeed maxUsbSpeed = UsbSpeed::SUPER;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PrebootConfig, vid, pid, flashBootedVid, flashBootedPid, maxUsbSpeed);

}  // namespace dai
