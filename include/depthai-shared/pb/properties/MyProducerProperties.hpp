#pragma once

#include <nlohmann/json.hpp>
#include "depthai-shared/pb/common/ProcessorType.hpp"
#include <depthai-shared/pb/common/optional.hpp>

namespace dai {

    /**
     * Specify message and processor placement of MyProducer node
     */
    struct MyProducerProperties {
        /**
         * Message to be sent forward
         */
        tl::optional<std::string> message;
        
        /**
         * On which processor the node will be placed
         */
        ProcessorType processorPlacement = ProcessorType::LOS;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MyProducerProperties, message, processorPlacement)

}
