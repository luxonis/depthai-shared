#pragma once
#include <vector>
#include <map>
#include "half.hpp"
#include "json_helper.hpp"

using float16 = half_float::half;


enum TensorDataType : int32_t
{
    _fp16 = 0,                  ///< Half precision floating point
    _u8f  = 1,                  ///< Unsigned byte
    _int  = 2,                  ///< Signed integer (4 byte)
    _fp32 = 3,                  ///< Single precision floating point
    _i8   = 4,                  ///< Signed byte
};


const std::map<TensorDataType, unsigned int> c_type_size = {
    {TensorDataType::_fp16,     sizeof(float16)},
    {TensorDataType::_u8f,      sizeof(std::uint8_t)},
    {TensorDataType::_int,      sizeof(std::int32_t)},
    {TensorDataType::_fp32,     sizeof(float)},
    {TensorDataType::_i8,       sizeof(std::int8_t)},
};


const std::map<TensorDataType, std::string> type_to_string = {
    {TensorDataType::_fp16,     "float16"},
    {TensorDataType::_u8f,      "uint8"},
    {TensorDataType::_int,      "int32"},
    {TensorDataType::_fp32,     "float32"},
    {TensorDataType::_i8,       "int8"},
};



struct TensorInfo
{
    TensorInfo(){}
    
    TensorInfo(nlohmann::json tensor_info)
    {
        deserialize(tensor_info);
        tensor_element_size = c_type_size.at(tensor_data_type);
    }

    std::string tensor_name;

    std::vector<uint32_t> order;
    std::vector<uint32_t> tensor_dimensions;
    std::vector<uint32_t> tensor_strides;

    TensorDataType tensor_data_type;
    size_t tensor_offset;
    size_t tensor_element_size;
    size_t tensor_idx;

    nlohmann::json serialize()
    {
        nlohmann::json tensor_info;
        tensor_info["name"] = tensor_name;
        tensor_info["shape"]["data_type"] = tensor_data_type;
        tensor_info["offset"] = tensor_offset;
        tensor_info["idx"] = tensor_idx;
        tensor_info["shape"]["order"] = order;
        tensor_info["shape"]["dimensions"] = tensor_dimensions;
        tensor_info["shape"]["strides"] = tensor_strides;
        return tensor_info;
    }

    private:
    void deserialize(nlohmann::json tensor_info)
    {
        tensor_name = tensor_info["name"];
        tensor_data_type = tensor_info["shape"]["data_type"];
        tensor_offset = tensor_info["offset"];
        tensor_idx = tensor_info["idx"];
        order = tensor_info["shape"]["order"].get<std::vector<uint32_t>>();
        tensor_dimensions = tensor_info["shape"]["dimensions"].get<std::vector<uint32_t>>();
        tensor_strides = tensor_info["shape"]["strides"].get<std::vector<uint32_t>>();
    }
};

inline std::ostream &operator<<(std::ostream &os, TensorInfo const &t_info)
{
    os << "Name: " << t_info.tensor_name << std::endl;
    os << "Index: " << t_info.tensor_idx << std::endl;
    os << "Element type: " << type_to_string.at(t_info.tensor_data_type) << std::endl;
    os << "Element size: " << " " << t_info.tensor_element_size << ((t_info.tensor_element_size == 1) ? "byte" : " bytes") << std::endl;
    os << "Offset: " << t_info.tensor_offset << " " << ((t_info.tensor_offset <= 1) ? "byte" : " bytes") << std::endl;
    os << "Dimensions: ";
    os << "[";
    for (int idx = 0; idx < t_info.tensor_dimensions.size(); idx++)
    {
        auto dimension = t_info.tensor_dimensions[idx];
        if (idx == t_info.tensor_dimensions.size() - 1)
        {
            os << dimension << "]" << std::endl;
        }
        else
        {
            os << dimension << ", ";
        }
    }
    return os;
}