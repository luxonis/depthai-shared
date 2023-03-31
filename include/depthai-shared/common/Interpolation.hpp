#pragma once

#include <cstdint>

namespace dai {

/**
 * Interpolation type
 */
enum class Interpolation : std::int32_t { AUTO = -1, BILINEAR = 0, BICUBIC = 1, NEAREST_NEIGHBOR = 2, BYPASS = NEAREST_NEIGHBOR };

/**
 * Default interpolation type
 */
static constexpr const Interpolation DEFAULT_INTERPOLATION = Interpolation::BILINEAR;
/**
 * Default interpolation type for disparity and depth frames. Overrides DEFAULT_INTERPOLATION
 */
static constexpr const Interpolation DEFAULT_DISPARITY_DEPTH_INTERPOLATION = Interpolation::NEAREST_NEIGHBOR;

}  // namespace dai
