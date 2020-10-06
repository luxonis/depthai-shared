#include "depthai-shared/tensor_info.hpp"

using TensorInfo = dai::TensorInfo;

const std::map<TensorInfo::DataType, unsigned int> TensorInfo::c_type_size = {
    {DataType::_fp16,     sizeof(float16)},
    {DataType::_u8f,      sizeof(std::uint8_t)},
    {DataType::_int,      sizeof(std::int32_t)},
    {DataType::_fp32,     sizeof(float)},
    {DataType::_i8,       sizeof(std::int8_t)},
};

const std::map<TensorInfo::DataType, std::string> TensorInfo::type_to_string = {
    {DataType::_fp16,     "float16"},
    {DataType::_u8f,      "uint8"},
    {DataType::_int,      "int32"},
    {DataType::_fp32,     "float32"},
    {DataType::_i8,       "int8"},
};

const std::map<TensorInfo::Dimension, std::string> TensorInfo::dimension_to_string = {
    {Dimension::W,     "Width"},
    {Dimension::H,     "Height"},
    {Dimension::C,     "Channel"},
    {Dimension::N,     "Batch"},
};