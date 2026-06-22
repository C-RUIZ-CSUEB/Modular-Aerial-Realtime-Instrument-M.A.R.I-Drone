/**
 * @file    drtos_imu.h
 * @brief   Data types for the Inertial Measurement Unit (accelerometer +
 *          gyroscope).
 *
 * The IMU is typically read at 1 kHz via SPI/I2C and produces 6-axis
 * raw + calibrated data used by the attitude estimator.
 */

#ifndef DRTOS_IMU_H
#define DRTOS_IMU_H

#include "drtos_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ──────────── Raw Sensor Reading ────────────────────── */

/**
 * @brief   3-axis signed 16-bit raw reading straight from the sensor
 *          registers.
 */
typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} drtos_imu_raw_axis_t;

/**
 * @brief   Full raw IMU sample (accelerometer + gyroscope + temperature).
 */
typedef struct {
    drtos_imu_raw_axis_t    accel;          /**< Accelerometer raw counts.  */
    drtos_imu_raw_axis_t    gyro;           /**< Gyroscope raw counts.      */
    int16_t                 temperature_raw;/**< On-die temperature counts. */
    drtos_timestamp_us_t    timestamp_us;   /**< Capture timestamp.         */
} drtos_imu_raw_sample_t;

/* ──────────── Calibrated / Scaled Reading ───────────── */

/**
 * @brief   3-axis floating-point vector in physical units.
 */
typedef struct {
    float x;
    float y;
    float z;
} drtos_vec3f_t;

/**
 * @brief   Calibrated IMU sample in SI units.
 */
typedef struct {
    drtos_vec3f_t           accel_mps2;     /**< m/s².                      */
    drtos_vec3f_t           gyro_rads;      /**< rad/s.                     */
    float                   temperature_c;  /**< Degrees Celsius.           */
    drtos_timestamp_us_t    timestamp_us;
} drtos_imu_calibrated_sample_t;

/* ──────────── Calibration Parameters ────────────────── */

/**
 * @brief   Per-axis offset + scale calibration.
 */
typedef struct {
    drtos_vec3f_t   accel_offset;   /**< Bias to subtract from raw.         */
    drtos_vec3f_t   accel_scale;    /**< Scale factor per axis.             */
    drtos_vec3f_t   gyro_offset;
    drtos_vec3f_t   gyro_scale;
} drtos_imu_calibration_t;

/* ──────────── IMU Status ────────────────────────────── */

/**
 * @brief   IMU health / status flags.
 */
typedef struct {
    bool    data_ready;             /**< New sample available.              */
    bool    sensor_ok;              /**< Communication with sensor OK.      */
    uint32_t sample_count;          /**< Total samples acquired.            */
    uint32_t error_count;           /**< Cumulative read errors.            */
} drtos_imu_status_t;

#ifdef __cplusplus
}
#endif

#endif /* DRTOS_IMU_H */