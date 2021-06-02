#pragma once

#include <depthai-shared/datatype/RawIMUData.hpp>
#include <nlohmann/json.hpp>

namespace dai {

/**
 * Available IMU sensors
 */
enum class IMUSensor : std::int32_t {
    RAW_ACCELEROMETER = 0x14,
    ACCELEROMETER = 0x01,
    LINEAR_ACCELERATION = 0x04,
    GRAVITY = 0x06,
    RAW_GYROSCOPE = 0x15,
    GYROSCOPE_CALIBRATED = 0x02,
    // GYROSCOPE_UNCALIBRATED = 0x07,
    RAW_MAGNETOMETER = 0x16,
    MAGNETOMETER_CALIBRATED = 0x03,
    // MAGNETOMETER_UNCALIBRATED = 0x0f,
    ROTATION_VECTOR = 0x05,
    GAME_ROTATION_VECTOR = 0x08,
    GEOMAGNETIC_ROTATION_VECTOR = 0x09,
    ARVR_STABILIZED_ROTATION_VECTOR = 0x28,
    ARVR_STABILIZED_GAME_ROTATION_VECTOR = 0x29,
    // GYRO_INTEGRATED_ROTATION_VECTOR = 0x2A,
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

    /* Rate of reports per second. (hertz)
     * 0 means disabled
     */
    uint32_t reportRate = 100;

    IMUSensor sensorId;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUSensorConfig, sensitivityEnabled, sensitivityRelative, changeSensitivity, reportRate, sensorId);

struct IMUProperties {
    /* Enabled IMU sensors */
    std::vector<IMUSensorConfig> imuSensors;
    /* Above this packet threshold data will be sent to host, if queue is not blocked */
    std::int32_t batchReportThreshold = 1;
    /* Maximum number of IMU packets in a batch. Maximum 5. */
    std::int32_t maxBatchReports = 5;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMUProperties, imuSensors, batchReportThreshold, maxBatchReports);

}  // namespace dai
