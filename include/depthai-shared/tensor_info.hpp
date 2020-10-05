#pragma once
#include <vector>
#include <map>
#include <iostream>
#include "json_helper.hpp"


typedef std::uint16_t float16;

namespace dai {
struct TensorInfo
{
    public:
    using ShapeType = uint32_t;

    enum class TensorDataType : int32_t
    {
        _fp16 = 0,                  ///< Half precision floating point
        _u8f  = 1,                  ///< Unsigned byte
        _int  = 2,                  ///< Signed integer (4 byte)
        _fp32 = 3,                  ///< Single precision floating point
        _i8   = 4,                  ///< Signed byte
    };


    static const std::map<TensorDataType, unsigned int> c_type_size;
    static const std::map<TensorDataType, std::string> type_to_string;

    enum class Dimension : int32_t
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

    static const std::map<Dimension, std::string> dimension_to_string;

    TensorInfo(){}
    
    TensorInfo(nlohmann::json tensor_info)
    {
        deserialize(tensor_info);
    }

    std::string tensor_name;

    std::vector<Dimension> order;
    std::vector<ShapeType> tensor_dimensions;
    std::vector<ShapeType> tensor_strides;

    TensorDataType tensor_data_type;
    size_t tensor_offset;
    size_t tensor_element_size;
    size_t tensor_idx;

    nlohmann::json serialize()
    {
        nlohmann::json tensor_info;
        DEPTHAI_SHARED_SET_JSON(tensor_name,           tensor_info["name"]);
        DEPTHAI_SHARED_SET_JSON(tensor_offset,         tensor_info["offset"]);
        DEPTHAI_SHARED_SET_JSON(tensor_idx,            tensor_info["idx"]);

        DEPTHAI_SHARED_SET_JSON(tensor_data_type,      tensor_info["shape"]["data_type"]);
        DEPTHAI_SHARED_SET_JSON(tensor_element_size,   tensor_info["shape"]["tensor_element_size"]);
        DEPTHAI_SHARED_SET_JSON(order,                 tensor_info["shape"]["order"]);
        DEPTHAI_SHARED_SET_JSON(tensor_dimensions,     tensor_info["shape"]["dimensions"]);
        DEPTHAI_SHARED_SET_JSON(tensor_strides,        tensor_info["shape"]["strides"]);
        return tensor_info;
    }

    ShapeType get_dimension(Dimension dim)
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
        DEPTHAI_SHARED_GET_JSON(tensor_name,       tensor_info["name"]);
        DEPTHAI_SHARED_GET_JSON(tensor_offset,     tensor_info["offset"]);
        DEPTHAI_SHARED_GET_JSON(tensor_idx,        tensor_info["idx"]);

        DEPTHAI_SHARED_GET_JSON(tensor_data_type,  tensor_info["shape"]["data_type"]);
        tensor_element_size = c_type_size.at(tensor_data_type);
        // DEPTHAI_SHARED_GET_JSON(tensor_element_size,  tensor_info["shape"]["tensor_element_size"]);

        DEPTHAI_SHARED_GET_JSON(order,             tensor_info["shape"]["order"]);
        DEPTHAI_SHARED_GET_JSON(tensor_dimensions, tensor_info["shape"]["dimensions"]);
        DEPTHAI_SHARED_GET_JSON(tensor_strides,    tensor_info["shape"]["strides"]);
    }
};
}


inline std::ostream &operator<<(std::ostream &os, dai::TensorInfo const &t_info)
{

    os << "Name: " << t_info.tensor_name << std::endl;
    os << "Index: " << t_info.tensor_idx << std::endl;
    os << "Element type: " << dai::TensorInfo::type_to_string.at(t_info.tensor_data_type) << std::endl;
    os << "Element size: " << " " << t_info.tensor_element_size << ((t_info.tensor_element_size == 1) ? "byte" : " bytes") << std::endl;
    os << "Offset: " << t_info.tensor_offset << " " << ((t_info.tensor_offset <= 1) ? "byte" : " bytes") << std::endl;
    os << "Dimensions: ";
    os << "[";
    for (unsigned int idx = 0; idx < t_info.tensor_dimensions.size(); idx++)
    {
        auto Dimension = t_info.tensor_dimensions[idx];
        if (idx == t_info.tensor_dimensions.size() - 1)
        {
            os << t_info.dimension_to_string.at(t_info.order[idx]) << " : " << Dimension << "]" << std::endl;
        }
        else
        {
            os << t_info.dimension_to_string.at(t_info.order[idx]) << " : " << Dimension << ", ";
        }
    }
    return os;
}
