
#pragma once

#include <string>

#include "nlohmann/json.hpp"


#define GET_JSON(variable, json ) variable = json.get<decltype(variable)>();
#define SET_JSON(variable, json ) json = variable;

bool getJSONFromString(const std::string& str, nlohmann::json& json_obj);
