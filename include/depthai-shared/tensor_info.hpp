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

enum dimension : int32_t
{   
    W = 1,
    H = 2,
    C = 3, 
    N = 4,
    B = N,
    WIDTH = W,
    HEIGHT = H,
    CHANNEL = C,
    NUMBER = N,
    BATCH = N,
};

const std::map<dimension, std::string> dimension_to_string = {
    {dimension::W,     "Width"},
    {dimension::H,     "Height"},
    {dimension::C,     "Channel"},
    {dimension::N,     "Batch"},
};

using ShapeType = uint32_t;

struct TensorInfo
{
    TensorInfo(){}
    
    TensorInfo(nlohmann::json tensor_info)
    {
        deserialize(tensor_info);
        tensor_element_size = c_type_size.at(tensor_data_type);
    }

    std::string tensor_name;

    std::vector<dimension> order;
    std::vector<ShapeType> tensor_dimensions;
    std::vector<ShapeType> tensor_strides;

    TensorDataType tensor_data_type;
    size_t tensor_offset;
    size_t tensor_element_size;
    size_t tensor_idx;

    nlohmann::json serialize()
    {
        nlohmann::json tensor_info;
        SET_JSON(tensor_name,       tensor_info["name"]);
        SET_JSON(tensor_offset,     tensor_info["offset"]);
        SET_JSON(tensor_idx,        tensor_info["idx"]);

        SET_JSON(tensor_data_type,  tensor_info["shape"]["data_type"]);
        SET_JSON(order,             tensor_info["shape"]["order"]);
        SET_JSON(tensor_dimensions, tensor_info["shape"]["dimensions"]);
        SET_JSON(tensor_strides,    tensor_info["shape"]["strides"]);
        return tensor_info;
    }

    ShapeType get_dimension(dimension dim)
    {
        unsigned int i = 0;
        for(i = 0; i < order.size(); i++)
        {
            if(order[i] == dim) break;
        }
        if(i == order.size()) assert(0);
        return tensor_dimensions[i];
    }

    private:
    void deserialize(nlohmann::json tensor_info)
    {
        GET_JSON(tensor_name,       tensor_info["name"]);
        GET_JSON(tensor_offset,     tensor_info["offset"]);
        GET_JSON(tensor_idx,        tensor_info["idx"]);

        GET_JSON(tensor_data_type,  tensor_info["shape"]["data_type"]);
        GET_JSON(order,             tensor_info["shape"]["order"]);
        GET_JSON(tensor_dimensions, tensor_info["shape"]["dimensions"]);
        GET_JSON(tensor_strides,    tensor_info["shape"]["strides"]);
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
    for (unsigned int idx = 0; idx < t_info.tensor_dimensions.size(); idx++)
    {
        auto dimension = t_info.tensor_dimensions[idx];
        if (idx == t_info.tensor_dimensions.size() - 1)
        {
            os << dimension_to_string.at(t_info.order[idx]) << " : " << dimension << "]" << std::endl;
        }
        else
        {
            os << dimension_to_string.at(t_info.order[idx]) << " : " << dimension << ", ";
        }
    }
    return os;
}