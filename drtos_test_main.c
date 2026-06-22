/**
 * @file    drtos_config.h
 * @brief   RTOS configuration for STM32F756 quadcopter drone.
 *
 * Tune these constants per your hardware and flight-controller requirements.
 * The STM32F756 runs Cortex-M7 at up to 216 MHz with 320 KB SRAM + 64 KB
 * DTCM-RAM, giving ample room for real-time task stacks and kernel objects.
 */

#ifndef DRTOS_CONFIG_H
#define DRTOS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* ──────────────────────── Clock ──────────────────────── */

/** System core clock in Hz (STM32F756 max with over-drive). */
#define DRTOS_CPU_CLOCK_HZ              216000000U

/** SysTick rate — 1 kHz gives 1 ms tick resolution. */
#define DRTOS_TICK_RATE_HZ              1000U

/* ──────────────────────── Tasks ─────────────────────── */

/** Maximum number of concurrent tasks the kernel can manage. */
#define DRTOS_MAX_TASKS                 16U

/** Default stack size in 32-bit words (512 words = 2 KB). */
#define DRTOS_DEFAULT_STACK_SIZE        512U

/** Minimum stack size in 32-bit words. */
#define DRTOS_MIN_STACK_SIZE            128U

/** Number of distinct priority levels (0 = highest). */
#define DRTOS_MAX_PRIORITY_LEVELS       8U

/** Priority assigned to the idle task (lowest). */
#define DRTOS_IDLE_TASK_PRIORITY        (DRTOS_MAX_PRIORITY_LEVELS - 1U)

/* ─────────────────── Synchronisation ────────────────── */

/** Maximum number of mutexes available system-wide. */
#define DRTOS_MAX_MUTEXES               16U

/** Maximum number of binary semaphores available system-wide. */
#define DRTOS_MAX_SEMAPHORES            16U

/* ──────────────────── Data Structures ───────────────── */

/** Default capacity (element count) for message queues. */
#define DRTOS_DEFAULT_QUEUE_CAPACITY    32U

/** Default capacity (byte count) for ring buffers. */
#define DRTOS_DEFAULT_RINGBUF_CAPACITY  256U

/* ──────────────────── Sensor Rates ──────────────────── */

/** IMU sample rate in Hz. */
#define DRTOS_IMU_SAMPLE_RATE_HZ        1000U

/** Barometer sample rate in Hz. */
#define DRTOS_BARO_SAMPLE_RATE_HZ       50U

/** RC receiver update rate in Hz. */
#define DRTOS_RC_UPDATE_RATE_HZ         50U

/** LoRa telemetry transmit rate in Hz. */
#define DRTOS_TELEMETRY_RATE_HZ         10U

#ifdef __cplusplus
}
#endif

#endif /* DRTOS_CONFIG_H */