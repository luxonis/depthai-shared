
#pragma once

#include <string>

#include "nlohmann/json.hpp"



// TODO
// doesn't build on MacOS (clang), falling back to good old macros
// template <typename T>
// constexpr void DEPTHAI_SHARED_GET_JSON(T& variable, const nlohmann::json json)
// {
//     variable = json.get<T>();
// }

// template <typename T>
// constexpr void DEPTHAI_SHARED_SET_JSON(const T variable, nlohmann::json& json)
// {
//     json = variable;
// }

#define DEPTHAI_SHARED_GET_JSON(variable, json) variable = json.get<decltype(variable)>()
#define DEPTHAI_SHARED_SET_JSON(variable, json) json = variable


bool getJSONFromString(const std::string& str, nlohmann::json& json_obj);
