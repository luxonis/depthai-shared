#pragma once

#include <nlohmann/json.hpp>

namespace dai {

/// Camera sensor type
enum class CameraSensorType : int32_t { COLOR, MONO, TOF, THERMAL };

}  // namespace dai
