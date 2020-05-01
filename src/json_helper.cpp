#include <string>

#include "depthai-shared/json_helper.hpp"

bool getJSONFromString(const std::string& str, nlohmann::json& json_obj)
{
    json_obj = nlohmann::json::parse(str);
    return true;
}
