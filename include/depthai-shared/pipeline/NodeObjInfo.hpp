#pragma once

#include <nlohmann/json.hpp>
#include <tuple>
#include <unordered_map>

#include "NodeIoInfo.hpp"
namespace dai {

/// NodeObj information structure
struct NodeObjInfo {
    int64_t id = -1;
    std::string name;
    nlohmann::json properties;

    struct IoInfoKey {
        std::size_t operator()(const std::tuple<std::string, std::string>& k) const {
            return std::hash<std::string>()(std::get<0>(k) + std::get<1>(k));
        }
    };
    std::unordered_map<std::tuple<std::string, std::string>, NodeIoInfo, IoInfoKey> ioInfo;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(NodeObjInfo, id, name, properties, ioInfo);

}  // namespace dai
