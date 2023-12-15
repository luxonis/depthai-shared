#pragma once
#include "depthai-shared/properties/Properties.hpp"

namespace dai
{

    /**
     * Specify properties for ToF
     */
    struct ThermalProperties : PropertiesSerializable<Properties, ThermalProperties>
    {
        uint32_t width;
        uint32_t baudrate;
    };

    DEPTHAI_SERIALIZE_EXT(ThermalProperties, width, baudrate);

} // namespace dai
