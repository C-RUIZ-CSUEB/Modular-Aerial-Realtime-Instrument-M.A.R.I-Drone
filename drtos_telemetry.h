/**
 * @file    drtos_rc.h
 * @brief   Data types for the RF remote controller receiver.
 *
 * The RC receiver provides pilot commands (throttle, roll, pitch, yaw,
 * and auxiliary switches).  Data arrives as PPM, SBUS, CRSF, etc. and
 * is normalised into a common structure.
 */

#ifndef DRTOS_RC_H
#define DRTOS_RC_H

#include "drtos_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ──────────── Channel Limits ────────────────────────── */

/** Maximum number of RC channels supported. */
#define DRTOS_RC_MAX_CHANNELS   16U

/* ──────────── Channel Data ──────────────────────────── */

/**
 * @brief   Normalised RC channel values.
 *
 * All channels are normalised to [-1.0, +1.0] for stick axes and
 * [0.0, +1.0] for throttle / switches.
 */
typedef struct {
    float                   channels[DRTOS_RC_MAX_CHANNELS];
    uint8_t                 channel_count;  /**< Number of valid channels. */
    drtos_timestamp_us_t    timestamp_us;
} drtos_rc_channels_t;

/* ──────────── Semantic Mapping ──────────────────────── */

/**
 * @brief   Pilot command structure with named fields.
 *
 * Derived from drtos_rc_channels_t by a configurable channel map.
 */
typedef struct {
    float   throttle;   /**< 0.0 (idle) to 1.0 (full).          */
    float   roll;       /**< -1.0 (left) to +1.0 (right).       */
    float   pitch;      /**< -1.0 (nose down) to +1.0 (nose up).*/
    float   yaw;        /**< -1.0 (CCW) to +1.0 (CW).           */
    bool    arm_switch;         /**< true = armed.               */
    uint8_t flight_mode;        /**< Flight-mode selector.       */
    drtos_timestamp_us_t timestamp_us;
} drtos_rc_command_t;

/* ──────────── Link Status ───────────────────────────── */

/**
 * @brief   RC link health.
 */
typedef struct {
    bool        link_active;        /**< Receiving valid frames.         */
    uint32_t    frames_received;    /**< Total valid frames.             */
    uint32_t    frames_lost;        /**< Lost / CRC-failed frames.       */
    int8_t      rssi_dbm;           /**< Received signal strength (dBm). */
    drtos_tick_t last_frame_tick;    /**< Tick count of last good frame.  */
} drtos_rc_link_status_t;

/* ──────────── Failsafe ──────────────────────────────── */

/**
 * @brief   Failsafe policy when RC link is lost.
 */
typedef enum {
    DRTOS_RC_FAILSAFE_HOLD      = 0,  /**< Hold last known commands.     */
    DRTOS_RC_FAILSAFE_LAND      = 1,  /**< Initiate auto-land.           */
    DRTOS_RC_FAILSAFE_DISARM    = 2,  /**< Cut motors immediately.       */
    DRTOS_RC_FAILSAFE_RTH       = 3,  /**< Return to home (if GPS avail).*/
} drtos_rc_failsafe_t;

#ifdef __cplusplus
}
#endif

#endif /* DRTOS_RC_H */