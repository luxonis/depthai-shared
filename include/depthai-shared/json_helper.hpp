
#pragma once

#include <string>

#include "nlohmann/json.hpp"

bool getJSONFromString(const std::string& str, nlohmann::json& json_obj);
