#pragma once

#include <cstdint>
#include <vector>

#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// RawNNConfig configuration structure
struct RawNNConfig : public RawBuffer {
    /**
     * Whether to process inputs or not
     */
    bool processInputs = true;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::NNConfig;
    };

    DEPTHAI_SERIALIZE(RawNNConfig, processInputs);
};

}  // namespace dai
