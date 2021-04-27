#pragma once

#include <depthai-shared/datatype/RawIMUData.hpp>
#include <nlohmann/json.hpp>

namespace dai {

/**
 * Specify IMU options
 */

/**
 * Available IMU sensors
 */
enum class IMUSensorId : std::int32_t {
    IMU_ACCELEROMETER = 0x01,
    IMU_LINEAR_ACCELERATION = 0x04,
    IMU_GRAVITY = 0x06,
    IMU_GYROSCOPE_CALIBRATED = 0x02,
    IMU_GYROSCOPE_UNCALIBRATED = 0x07,
    IMU_MAGNETIC_FIELD_CALIBRATED = 0x03,
    IMU_MAGNETIC_FIELD_UNCALIBRATED = 0x0f,
    IMU_ROTATION_VECTOR = 0x05,
    IMU_GAME_ROTATION_VECTOR = 0x08,
    IMU_GEOMAGNETIC_ROTATION_VECTOR = 0x09,
    IMU_ARVR_STABILIZED_RV = 0x28,
    IMU_ARVR_STABILIZED_GRV = 0x29,
    IMU_GYRO_INTEGRATED_RV = 0x2A,

    // UPDATE to reflect greatest sensor id
    IMU_MAX_SENSOR_ID = 0x2A,
};

struct IMUSensorConfig {
    /* Sensitivity enabled */
    bool sensitivityEnabled = false;

    /* Change sensitivity - true if relative; false if absolute */
    bool sensitivityRelative = false; /**< @brief Change reports relative (vs absolute) */

    // TODO write utility function to convert float to Q point notation, sensor specific
    /* 16-bit signed fixed point integer.
     * In case of absolute sensitivity represents the value a
     * sensor output must exceed in order to trigger another input
     * report.
     * In case of relative sensitivity represents the the amount
     * by which a sensor output must change from the previous
     * input report in order to trigger another input report
     * A setting of 0 causes all reports to be sent.
     */
    uint16_t changeSensitivity = 0; /**< @brief Report-on-change threshold */

    /* Interval in microseconds between asynchronous input reports.
     * 0 means disabled
     */
    uint32_t reportIntervalUs = 10000; /**< @brief [uS] Report interval */

    IMUSensorId sensorId;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUSensorConfig, sensitivityEnabled, sensitivityRelative, changeSensitivity, reportIntervalUs, sensorId);

struct IMUProperties {
    /* Enabled IMU sensors */
    std::vector<IMUSensorConfig> imuSensors;
    /* Above this packet threshold data will be sent to host, if queue is not blocked */
    std::int32_t batchReportThreshold = 10;
    /* Maximum number of IMU packets in a batch */
    std::int32_t maxBatchReports = 50;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUProperties, imuSensors, batchReportThreshold, maxBatchReports);

}  // namespace dai
