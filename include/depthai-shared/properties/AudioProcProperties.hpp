#pragma once

#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for AudioProc
 */
struct AudioProcProperties : PropertiesSerializable<Properties, AudioProcProperties> {
    /**
     * This options specifies how many frames are available in this node's pool.
     * Helps when receiver is slow at consuming.
     *
     * Value "0" indicates automatic number of frames assignment
     */
    std::uint32_t numFramesPool = 0;
};

DEPTHAI_SERIALIZE_EXT(AudioProcProperties, numFramesPool);

}  // namespace dai
