#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"

namespace dai {

struct RawCameraControl : public RawBuffer {
    enum class AutoFocusMode : uint8_t {
        /// Autofocus disabled. Suitable for manual focus
        OFF = 0,
        /// Runs autofocus once at startup, and at subsequent trigger commands
        AUTO,
        /// TODO
        MACRO,
        /// Runs autofocus when the scene is detected as out-of-focus
        CONTINUOUS_VIDEO,
        CONTINUOUS_PICTURE,
        EDOF,
    };

    AutoFocusMode autoFocusMode = AutoFocusMode::CONTINUOUS_VIDEO;

    /**
     * Lens/VCM position, range: 0..255. Used with `autoFocusMode = OFF`.
     * With current IMX378 modules:
     * - max 255: macro focus, at 8cm distance
     * - infinite focus at about 120..130 (may vary from module to module)
     * - lower values lead to out-of-focus (lens too close to the sensor array)
     */
    uint8_t lensPosition = 0;

    // TODO(themarpe/alex) - this is a placeholder for vairous camera control commands
    bool captureStill = false;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::CameraControl;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawCameraControl, captureStill, autoFocusMode, lensPosition);
};

}  // namespace dai