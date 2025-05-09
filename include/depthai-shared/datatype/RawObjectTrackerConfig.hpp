#pragma once
#include <cstdint>
#include <vector>

#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// RawObjectTrackerConfig configuration structure
struct RawObjectTrackerConfig : public RawBuffer {
    /**
     * Tracklet IDs to remove from tracking.
     * Tracklet will transition to REMOVED state.
     */
    std::vector<int32_t> trackletIdsToRemove;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::ObjectTrackerConfig;
    };

    DatatypeEnum getType() const override {
        return DatatypeEnum::ObjectTrackerConfig;
    }

    DEPTHAI_SERIALIZE(RawObjectTrackerConfig, trackletIdsToRemove);
};

}  // namespace dai
