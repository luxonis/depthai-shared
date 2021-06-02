#pragma once

#include <nlohmann/json.hpp>

namespace dai {
/**
 * Which Camera Model to initialize the calibration with.
 */
enum class CameraModel : int8_t { Perspective = 0, Fisheye = 1, Equirectangular = 2, RadialDivision = 3 };

}  // namespace dai