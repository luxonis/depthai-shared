#include "depthai-shared/json_helper.hpp"

#include <string>

bool getJSONFromString(const std::string& str, nlohmann::json& json_obj) {
    json_obj = nlohmann::json::parse(str);
    return true;
}
