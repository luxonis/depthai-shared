#pragma once

#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// Base Properties structure
struct Properties {
    virtual void serialize(std::vector<std::uint8_t>& data) = 0;
    virtual ~Properties() = default;
};

/// Serializable properties
template <typename Base, typename Derived>
struct PropertiesSerializable : Base {
    virtual void serialize(std::vector<std::uint8_t>& data) override {
        utility::serialize(static_cast<const Derived&>(*this), data);
    }
};

}  // namespace dai