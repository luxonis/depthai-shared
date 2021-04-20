#pragma once

#include "RawBuffer.hpp"
#include "depthai-shared/common/Point3f.hpp"
#include "depthai-shared/common/Timestamp.hpp"

namespace dai {

/**
 * IMU output
 *
 * Contains configuration data, average depth for the calculated ROI on depth map.
 * Together with spatial coordinates: x,y,z relative to the center of depth map.
 * Units are in millimeters.
 */
struct IMUDatas {
    Timestamp ts;
    Point3f accelerometer;
    Point3f gyro;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUDatas, ts, accelerometer, gyro);

struct RawIMUData : public RawBuffer {
    std::vector<IMUDatas> imuDatas;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::IMUDatas;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawIMUData, imuDatas);
};

}  // namespace dai
