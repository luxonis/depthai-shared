#include "depthai-shared/tensor_info.hpp"

using TensorInfo = dai::TensorInfo;

const std::map<TensorInfo::TensorDataType, unsigned int> TensorInfo::c_type_size = {
    {TensorDataType::_fp16,     sizeof(float16)},
    {TensorDataType::_u8f,      sizeof(std::uint8_t)},
    {TensorDataType::_int,      sizeof(std::int32_t)},
    {TensorDataType::_fp32,     sizeof(float)},
    {TensorDataType::_i8,       sizeof(std::int8_t)},
};

const std::map<TensorInfo::TensorDataType, std::string> TensorInfo::type_to_string = {
    {TensorDataType::_fp16,     "float16"},
    {TensorDataType::_u8f,      "uint8"},
    {TensorDataType::_int,      "int32"},
    {TensorDataType::_fp32,     "float32"},
    {TensorDataType::_i8,       "int8"},
};

const std::map<TensorInfo::Dimension, std::string> TensorInfo::dimension_to_string = {
    {Dimension::W,     "Width"},
    {Dimension::H,     "Height"},
    {Dimension::C,     "Channel"},
    {Dimension::N,     "Batch"},
};