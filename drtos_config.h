/**
 * @file    drtos_semaphore.h
 * @brief   Binary semaphore for ISR-to-task and task-to-task signalling.
 *
 * Binary semaphores are the primary mechanism for an ISR (e.g. IMU
 * data-ready interrupt) to wake a processing task.  Unlike mutexes they
 * have no ownership and no priority inheritance.
 *
 * The "give" operation is safe to call from ISR context.
 */

#ifndef DRTOS_SEMAPHORE_H
#define DRTOS_SEMAPHORE_H

#include "drtos_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ──────────── Configuration ─────────────────────────── */

/**
 * @brief   Configuration for binary semaphore creation.
 */
typedef struct {
    const char *name;           /**< Optional debug name.            */
    bool        initial_state;  /**< true = given (available),
                                     false = taken (unavailable).    */
} drtos_sem_config_t;

/* ──────────── API ───────────────────────────────────── */

/**
 * @brief   Create a binary semaphore.
 *
 * @param[in]  config  Configuration (NULL gives defaults: taken, unnamed).
 * @param[out] handle  Receives the semaphore handle.
 *
 * @retval DRTOS_OK
 * @retval DRTOS_ERR_NO_MEMORY
 */
drtos_status_t drtos_sem_create(const drtos_sem_config_t *config,
                                drtos_sem_handle_t       *handle);

/**
 * @brief   Destroy a binary semaphore.
 *
 * @param[in] handle  Semaphore to destroy.
 */
drtos_status_t drtos_sem_destroy(drtos_sem_handle_t handle);

/**
 * @brief   Take (wait on) the semaphore.
 *
 * The calling task blocks until the semaphore is given or the timeout
 * expires.  Must NOT be called from ISR context.
 *
 * @param[in] handle   Semaphore handle.
 * @param[in] timeout  Maximum ticks to wait.
 *
 * @retval DRTOS_OK
 * @retval DRTOS_ERR_TIMEOUT
 * @retval DRTOS_ERR_ISR_CONTEXT
 */
drtos_status_t drtos_sem_take(drtos_sem_handle_t handle,
                              drtos_tick_t       timeout);

/**
 * @brief   Give (signal) the semaphore.
 *
 * Safe to call from ISR context.  If a task is blocked on the
 * semaphore it is moved to the READY state.  Multiple gives without
 * an intervening take are idempotent (binary, not counting).
 *
 * @param[in] handle  Semaphore handle.
 *
 * @retval DRTOS_OK
 */
drtos_status_t drtos_sem_give(drtos_sem_handle_t handle);

/**
 * @brief   ISR-specific give that requests a context switch if a
 *          higher-priority task was unblocked.
 *
 * @param[in]  handle               Semaphore handle.
 * @param[out] higher_prio_woken    Set to true if a context switch
 *                                  should be performed on ISR exit.
 *
 * @retval DRTOS_OK
 */
drtos_status_t drtos_sem_give_from_isr(drtos_sem_handle_t handle,
                                       bool              *higher_prio_woken);

#ifdef __cplusplus
}
#endif

#endif /* DRTOS_SEMAPHORE_H */