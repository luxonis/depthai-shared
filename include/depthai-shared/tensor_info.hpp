#pragma once
#include <vector>
#include <map>
#include <iostream>
#include "json_helper.hpp"


//create a new dummy type, 2 bytes
struct float16
{
    std::uint16_t _dummy;
};

namespace dai {
struct TensorInfo
{
    public:
    using ShapeType = uint32_t;

    enum class DataType : int32_t
    {
        _fp16 = 0,                  ///< Half precision floating point
        _u8f  = 1,                  ///< Unsigned byte
        _int  = 2,                  ///< Signed integer (4 byte)
        _fp32 = 3,                  ///< Single precision floating point
        _i8   = 4,                  ///< Signed byte
    };


    static const std::map<DataType, unsigned int> c_type_size;
    static const std::map<DataType, std::string> type_to_string;

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

    std::string name;

    std::vector<Dimension> order;
    std::vector<ShapeType> dimensions;
    std::vector<ShapeType> strides;

    DataType data_type;
    size_t offset;
    size_t element_size;
    size_t index;

    nlohmann::json serialize()
    {
        nlohmann::json tensor_info;
        DEPTHAI_SHARED_SET_JSON(name,           tensor_info["name"]);
        DEPTHAI_SHARED_SET_JSON(offset,         tensor_info["offset"]);
        DEPTHAI_SHARED_SET_JSON(index,          tensor_info["idx"]);

        DEPTHAI_SHARED_SET_JSON(data_type,      tensor_info["shape"]["data_type"]);
        DEPTHAI_SHARED_SET_JSON(element_size,   tensor_info["shape"]["element_size"]);
        DEPTHAI_SHARED_SET_JSON(order,          tensor_info["shape"]["order"]);
        DEPTHAI_SHARED_SET_JSON(dimensions,     tensor_info["shape"]["dimensions"]);
        DEPTHAI_SHARED_SET_JSON(strides,        tensor_info["shape"]["strides"]);
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
        return dimensions[i];
    }

    private:
    void deserialize(nlohmann::json tensor_info)
    {
        DEPTHAI_SHARED_GET_JSON(name,       tensor_info["name"]);
        DEPTHAI_SHARED_GET_JSON(offset,     tensor_info["offset"]);
        DEPTHAI_SHARED_GET_JSON(index,      tensor_info["idx"]);

        DEPTHAI_SHARED_GET_JSON(data_type,  tensor_info["shape"]["data_type"]);
        element_size = c_type_size.at(data_type);
        // DEPTHAI_SHARED_GET_JSON(element_size,  tensor_info["shape"]["element_size"]);

        DEPTHAI_SHARED_GET_JSON(order,      tensor_info["shape"]["order"]);
        DEPTHAI_SHARED_GET_JSON(dimensions, tensor_info["shape"]["dimensions"]);
        DEPTHAI_SHARED_GET_JSON(strides,    tensor_info["shape"]["strides"]);
    }
};
}


inline std::ostream &operator<<(std::ostream &os, dai::TensorInfo const &t_info)
{

    os << "Name: " << t_info.name << std::endl;
    os << "Index: " << t_info.index << std::endl;
    os << "Element type: " << dai::TensorInfo::type_to_string.at(t_info.data_type) << std::endl;
    os << "Element size: " << " " << t_info.element_size << ((t_info.element_size == 1) ? "byte" : " bytes") << std::endl;
    os << "Offset: " << t_info.offset << " " << ((t_info.offset <= 1) ? "byte" : " bytes") << std::endl;
    os << "Dimensions: ";
    os << "[";
    for (unsigned int idx = 0; idx < t_info.dimensions.size(); idx++)
    {
        auto Dimension = t_info.dimensions[idx];
        if (idx == t_info.dimensions.size() - 1)
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
