#pragma once

// std
#include <cstdint>

// project
#include "depthai-shared/common/UsbSpeed.hpp"
#include "depthai-shared/xlink/XLinkConstants.hpp"

namespace dai {

constexpr static uint32_t PREBOOT_CONFIG_MAGIC1 = 0x78010000U;
constexpr static uint32_t PREBOOT_CONFIG_MAGIC2 = 0x21ea17e6U;

struct PrebootConfig {
    // USB related config
    struct USB {
        uint16_t vid = 0x03e7, pid = 0xf63b;
        uint16_t flashBootedVid = 0x03e7, flashBootedPid = 0xf63d;
        UsbSpeed maxSpeed = UsbSpeed::SUPER;
    };

    USB usb;
    uint32_t watchdogTimeoutMs = device::XLINK_WATCHDOG_TIMEOUT.count();
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PrebootConfig::USB, vid, pid, flashBootedVid, flashBootedPid, maxSpeed);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PrebootConfig, usb, watchdogTimeoutMs);

}  // namespace dai
