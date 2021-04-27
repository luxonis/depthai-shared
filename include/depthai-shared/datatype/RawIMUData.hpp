#pragma once

#include "RawBuffer.hpp"
#include "depthai-shared/common/Point3f.hpp"
#include "depthai-shared/common/Timestamp.hpp"

namespace dai {

struct IMUReport {
    enum class IMUReportAccuracy : std::uint8_t {
        UNRELIABLE = 0,
        LOW = 1,
        MEDIUM = 2,
        HIGH = 3,
    };
    /** @brief 8-bit unsigned integer used to track reports.
     *
     * The sequence number increments once for each report sent.  Gaps
     * in the sequence numbers indicate missing or dropped reports.
     */
    uint8_t sequence;

    IMUReportAccuracy accuracy;

    Timestamp timestamp; /**< [uS] */

    uint32_t delay; /**< @brief [uS] delay for batch reports, RESERVED for now */
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUReport, sequence, accuracy, timestamp, delay);

/**
 * @brief Accelerometer
 *
 * See the SH-2 Reference Manual for more detail.
 */
struct IMUReportAccelerometer : IMUReport {
    float x;
    float y;
    float z;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUReportAccelerometer, x, y, z, sequence, accuracy, timestamp, delay);

/**
 * @brief Gyroscope
 *
 * See the SH-2 Reference Manual for more detail.
 */
struct IMUReportGyroscope : IMUReport {
    /* Units are rad/s */
    float x;
    float y;
    float z;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUReportGyroscope, x, y, z, sequence, accuracy, timestamp, delay);

/**
 * @brief Uncalibrated gyroscope
 *
 * See the SH-2 Reference Manual for more detail.
 */
struct IMUReportGyroscopeUncalibrated : IMUReport {
    /* Units are rad/s */
    float x;     /**< @brief [rad/s] */
    float y;     /**< @brief [rad/s] */
    float z;     /**< @brief [rad/s] */
    float biasX; /**< @brief [rad/s] */
    float biasY; /**< @brief [rad/s] */
    float biasZ; /**< @brief [rad/s] */
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUReportGyroscopeUncalibrated, x, y, z, biasX, biasY, biasZ, sequence, accuracy, timestamp, delay);

/**
 * @brief Magnetic field
 *
 * See the SH-2 Reference Manual for more detail.
 */
struct IMUReportMagneticField : IMUReport {
    /* Units are uTesla */
    float x; /**< @brief [uTesla] */
    float y; /**< @brief [uTesla] */
    float z; /**< @brief [uTesla] */
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUReportMagneticField, x, y, z, sequence, accuracy, timestamp, delay);

/**
 * @brief Uncalibrated magnetic field
 *
 * See the SH-2 Reference Manual for more detail.
 */
struct IMUReportMagneticFieldUncalibrated : IMUReport {
    /* Units are uTesla */
    float x;     /**< @brief [uTesla] */
    float y;     /**< @brief [uTesla] */
    float z;     /**< @brief [uTesla] */
    float biasX; /**< @brief [uTesla] */
    float biasY; /**< @brief [uTesla] */
    float biasZ; /**< @brief [uTesla] */
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUReportMagneticFieldUncalibrated, x, y, z, biasX, biasY, biasZ, sequence, accuracy, timestamp, delay);

/**
 * @brief Rotation Vector with Accuracy
 *
 * See the SH-2 Reference Manual for more detail.
 */
struct IMUReportRotationVectorWAcc : IMUReport {
    float i;        /**< @brief Quaternion component i */
    float j;        /**< @brief Quaternion component j */
    float k;        /**< @brief Quaternion component k */
    float real;     /**< @brief Quaternion component, real */
    float accuracy; /**< @brief Accuracy estimate [radians] */
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUReportRotationVectorWAcc, i, j, k, real, accuracy, sequence, accuracy, timestamp, delay);

/**
 * @brief Rotation Vector
 *
 * See the SH-2 Reference Manual for more detail.
 */
struct IMUReportRotationVector : IMUReport {
    float i;    /**< @brief Quaternion component i */
    float j;    /**< @brief Quaternion component j */
    float k;    /**< @brief Quaternion component k */
    float real; /**< @brief Quaternion component real */
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUReportRotationVector, i, j, k, real, sequence, accuracy, timestamp, delay);

/**
 * @brief heartRateMonitor
 *
 * See SH-2 Reference Manual for details.
 */
struct IMUReportGyroIntegratedRV : IMUReport {
    float i;       /**< @brief Quaternion component i */
    float j;       /**< @brief Quaternion component j */
    float k;       /**< @brief Quaternion component k */
    float real;    /**< @brief Quaternion component real */
    float angVelX; /**< @brief Angular velocity about x [rad/s] */
    float angVelY; /**< @brief Angular velocity about y [rad/s] */
    float angVelZ; /**< @brief Angular velocity about z [rad/s] */
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUReportGyroIntegratedRV, i, j, k, real, angVelX, angVelY, angVelZ, sequence, accuracy, timestamp, delay);

/**
 * IMU output
 *
 * Contains configuration data, average depth for the calculated ROI on depth map.
 * Together with spatial coordinates: x,y,z relative to the center of depth map.
 * Units are in millimeters.
 */
struct IMUDatas {
    IMUReportAccelerometer acceleroMeter;
    IMUReportAccelerometer linearAcceleroMeter;
    IMUReportAccelerometer gravity;

    IMUReportGyroscope gyroscope;
    IMUReportGyroscopeUncalibrated gyroscopeUncalibrated;

    IMUReportMagneticField magneticField;
    IMUReportMagneticFieldUncalibrated magneticFieldUncalibrated;

    IMUReportRotationVectorWAcc rotationVector;
    IMUReportRotationVector gameRotationVector;
    IMUReportRotationVectorWAcc geoMagRotationVector;

    IMUReportRotationVectorWAcc arvrStabilizedRotationVector;
    IMUReportRotationVector arvrStabilizedGameRotationVector;
    IMUReportGyroIntegratedRV gyroIntegratedRotationVector;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUDatas,
                                   acceleroMeter,
                                   linearAcceleroMeter,
                                   gravity,
                                   gyroscope,
                                   gyroscopeUncalibrated,
                                   magneticField,
                                   magneticFieldUncalibrated,
                                   rotationVector,
                                   gameRotationVector,
                                   geoMagRotationVector,
                                   arvrStabilizedRotationVector,
                                   arvrStabilizedGameRotationVector,
                                   gyroIntegratedRotationVector);

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
