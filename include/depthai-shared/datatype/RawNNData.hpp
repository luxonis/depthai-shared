#pragma once

#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/common/Timestamp.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// TensorInfo structure
struct TensorInfo {
    enum class StorageOrder : int {
        NHWC = 0x4213,
        NHCW = 0x4231,
        NCHW = 0x4321,
        HWC = 0x213,
        CHW = 0x321,
        WHC = 0x123,
        HCW = 0x231,
        WCH = 0x132,
        CWH = 0x312,
        NC = 0x43,
        CN = 0x34,
        C = 0x3,
        H = 0x2,
        W = 0x1,
    };

    enum class DataType : int {
        FP16 = 0,  // Half precision floating point
        U8F = 1,   // Unsigned byte
        INT = 2,   // Signed integer (4 byte)
        FP32 = 3,  // Single precision floating point
        I8 = 4,    // Signed byte
    };

    StorageOrder order = StorageOrder::NCHW;
    DataType dataType = DataType::FP16;
    unsigned int numDimensions = 0;
    std::vector<unsigned> dims;
    std::vector<unsigned> strides;
    std::string name;
    unsigned int offset = 0;

    DEPTHAI_SERIALIZE(TensorInfo, order, dataType, numDimensions, dims, strides, name, offset);
};

/// RawNNData structure
struct RawNNData : public RawBuffer {
    // NNData data is in PoBuf
    std::vector<TensorInfo> tensors;
    unsigned int batchSize;

    // Related to input ImgFrame
    int sequenceNum;     // increments for each frame
    Timestamp ts;        // generation timestamp, synced to host time
    Timestamp tsDevice;  // generation timestamp, direct device monotonic clock

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::NNData;
    };

    DEPTHAI_SERIALIZE(RawNNData, tensors, batchSize, sequenceNum, ts, tsDevice);
};

}  // namespace dai
