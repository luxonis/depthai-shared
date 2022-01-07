#pragma once

// std
#include <cstdint>
#include <unordered_map>

// project
#include "depthai-shared/common/UsbSpeed.hpp"
#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/utility/Serialization.hpp"
#include "depthai-shared/xlink/XLinkConstants.hpp"
#include "depthai-shared/device/BoardConfig.hpp"

namespace dai {

constexpr static uint32_t BOARD_CONFIG_MAGIC1 = 0x78010000U;
constexpr static uint32_t BOARD_CONFIG_MAGIC2 = 0x21ea17e6U;

struct BoardConfig {
    // USB related config
    struct USB {
        uint16_t vid = 0x03e7, pid = 0xf63b;
        uint16_t flashBootedVid = 0x03e7, flashBootedPid = 0xf63d;
        UsbSpeed maxSpeed = UsbSpeed::SUPER;
    };

    USB usb;

    // Watchdog config
    tl::optional<uint32_t> watchdogTimeoutMs;
    tl::optional<uint32_t> watchdogInitialDelayMs;

    // GPIO config
    struct GPIO {
        std::int8_t mode = 7;
        bool output = false;
        bool level = false;
        std::int8_t pull = 0;
        std::int8_t voltage = 0;
        /// Drive strenght in mA
        std::int8_t drive = 0;
        bool schmitt = false, slewFast = false;
    };
    std::unordered_map<std::int8_t, GPIO> gpio;

    // Uart config

    /// UART instance config
    struct UART {
        // TBD
        // std::int8_t tx, rx;
        std::int8_t tmp;
    };
    /// UART instance map
    std::unordered_map<std::int8_t, UART> uart;

};

DEPTHAI_SERIALIZE_EXT(BoardConfig::USB, vid, pid, flashBootedVid, flashBootedPid, maxSpeed);
DEPTHAI_SERIALIZE_EXT(BoardConfig::GPIO, mode, output, level, pull, voltage, drive, schmitt, slewFast);
DEPTHAI_SERIALIZE_EXT(BoardConfig::UART, tmp);
DEPTHAI_SERIALIZE_EXT(BoardConfig, usb, watchdogTimeoutMs, watchdogInitialDelayMs, gpio, uart);

}  // namespace dai
