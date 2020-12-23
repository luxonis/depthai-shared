#pragma once

#include <depthai-shared/pb/common/optional.hpp>
#include <nlohmann/json.hpp>

namespace dai {

/**
 * Specify properties which apply for whole pipeline
 */
struct GlobalProperties {
    /**
     * Set frequency of Leon OS - Incresing can improve performance, at the cost of higher power
     * draw
     */
    double leonOsFrequencyHz = 600 * 1000 * 1000;
    /**
     * Set frequency of Leon RT - Incresing can improve performance, at the cost of higher power
     * draw
     */
    double leonRtFrequencyHz = 600 * 1000 * 1000;
    tl::optional<std::string> pipelineName;
    tl::optional<std::string> pipelineVersion;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GlobalProperties, leonOsFrequencyHz, leonRtFrequencyHz, pipelineName, pipelineVersion);

}  // namespace dai
