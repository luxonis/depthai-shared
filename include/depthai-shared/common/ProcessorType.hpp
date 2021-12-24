#pragma once

#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/**
 * On which processor the node will be placed
 *
 * Enum specifying processor
 */
enum class ProcessorType : int32_t { LEON_CSS, LEON_MSS };

}  // namespace dai