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
    };

    DEPTHAI_SERIALIZE_EXT(ThermalProperties, width);

} // namespace dai
