/**
 * @file    drtos_types.h
 * @brief   Fundamental type definitions used across the drone RTOS kernel.
 */

#ifndef DRTOS_TYPES_H
#define DRTOS_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "drtos_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ──────────────────── Return Codes ──────────────────── */

/** Kernel operation result codes. */
typedef enum {
    DRTOS_OK                =  0,   /**< Success.                           */
    DRTOS_ERR_NULL_PTR      = -1,   /**< NULL pointer argument.             */
    DRTOS_ERR_INVALID_PARAM = -2,   /**< Parameter out of range.            */
    DRTOS_ERR_NO_MEMORY     = -3,   /**< Pool / heap exhausted.             */
    DRTOS_ERR_TIMEOUT       = -4,   /**< Blocking call timed out.           */
    DRTOS_ERR_BUSY          = -5,   /**< Resource is already in use.        */
    DRTOS_ERR_NOT_READY     = -6,   /**< Object not initialised.            */
    DRTOS_ERR_OVERFLOW      = -7,   /**< Queue / buffer overflow.           */
    DRTOS_ERR_UNDERFLOW     = -8,   /**< Queue / buffer underflow (empty).  */
    DRTOS_ERR_ISR_CONTEXT   = -9,   /**< Operation not allowed from ISR.    */
    DRTOS_ERR_STATE         = -10,  /**< Invalid state transition.          */
} drtos_status_t;

/* ──────────────────── Time Types ────────────────────── */

/** Tick count (wraps at UINT32_MAX). */
typedef uint32_t drtos_tick_t;

/** Special value: wait forever in a blocking call. */
#define DRTOS_WAIT_FOREVER      UINT32_MAX

/** Special value: do not block — return immediately. */
#define DRTOS_NO_WAIT           0U

/* ──────────────────── Task Types ────────────────────── */

/** Task function signature: void task_func(void *arg); */
typedef void (*drtos_task_func_t)(void *arg);

/** Task priority: 0 is highest, (DRTOS_MAX_PRIORITY_LEVELS - 1) is lowest. */
typedef uint8_t drtos_priority_t;

/** Opaque handle to a task control block. */
typedef struct drtos_tcb *drtos_task_handle_t;

/** Task lifecycle states. */
typedef enum {
    DRTOS_TASK_STATE_READY      = 0, /**< Eligible to run.                  */
    DRTOS_TASK_STATE_RUNNING    = 1, /**< Currently executing on the CPU.   */
    DRTOS_TASK_STATE_BLOCKED    = 2, /**< Waiting on a sync object / delay. */
    DRTOS_TASK_STATE_SUSPENDED  = 3, /**< Manually suspended.               */
    DRTOS_TASK_STATE_TERMINATED = 4, /**< Finished or deleted.              */
} drtos_task_state_t;

/* ──────────────────── Sync Object Handles ───────────── */

/** Opaque handle to a mutex. */
typedef struct drtos_mutex *drtos_mutex_handle_t;

/** Opaque handle to a binary semaphore. */
typedef struct drtos_semaphore *drtos_sem_handle_t;

/* ──────────────────── Data Structure Handles ─────────── */

/** Opaque handle to a message queue. */
typedef struct drtos_queue *drtos_queue_handle_t;

/** Opaque handle to a ring buffer. */
typedef struct drtos_ringbuf *drtos_ringbuf_handle_t;

/* ──────────────────── Timestamp ─────────────────────── */

/** Microsecond timestamp obtained from a HW timer (e.g. TIM2 32-bit). */
typedef uint32_t drtos_timestamp_us_t;

#ifdef __cplusplus
}
#endif

#endif /* DRTOS_TYPES_H */