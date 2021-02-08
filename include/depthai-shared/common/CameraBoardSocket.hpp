#pragma once

#include <nlohmann/json.hpp>

namespace dai {
/**
 * Which Camera socket to use.
 *
 * AUTO denotes that the decision will be made by device
 */
<<<<<<< HEAD
enum class CameraBoardSocket : int32_t { AUTO = -1, RGB, LEFT, RIGHT};
=======
enum class CameraBoardSocket : int32_t { AUTO = -1, RGB, LEFT, RIGHT };
>>>>>>> changed camera data to unordered map

}  // namespace dai