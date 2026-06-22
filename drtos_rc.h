/**
 * @file    drtos_queue.h
 * @brief   Fixed-size, typed, thread-safe FIFO message queue.
 *
 * Queues carry fixed-size messages between tasks (e.g. sensor samples
 * from the IMU task to the flight-controller task).  Both the send and
 * receive sides support optional blocking with timeout.
 */

#ifndef DRTOS_QUEUE_H
#define DRTOS_QUEUE_H

#include "drtos_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ──────────── Configuration ─────────────────────────── */

/**
 * @brief   Queue creation descriptor.
 *
 * The caller supplies the backing storage so that no dynamic allocation
 * is needed at runtime.
 */
typedef struct {
    const char *name;           /**< Optional debug name.                */
    void       *buffer;         /**< Pre-allocated storage for items.    */
    uint32_t    item_size;      /**< Size of one item in bytes.          */
    uint32_t    capacity;       /**< Maximum number of items.            */
} drtos_queue_config_t;

/* ──────────── API ───────────────────────────────────── */

/**
 * @brief   Create a message queue.
 *
 * @param[in]  config  Queue descriptor.
 * @param[out] handle  Receives the queue handle.
 *
 * @retval DRTOS_OK
 * @retval DRTOS_ERR_NULL_PTR
 * @retval DRTOS_ERR_INVALID_PARAM
 * @retval DRTOS_ERR_NO_MEMORY
 */
drtos_status_t drtos_queue_create(const drtos_queue_config_t *config,
                                  drtos_queue_handle_t       *handle);

/**
 * @brief   Destroy a queue.
 */
drtos_status_t drtos_queue_destroy(drtos_queue_handle_t handle);

/**
 * @brief   Send (enqueue) an item by copy.
 *
 * @param[in] handle   Queue handle.
 * @param[in] item     Pointer to the item to copy into the queue.
 * @param[in] timeout  Maximum ticks to wait if the queue is full.
 *
 * @retval DRTOS_OK
 * @retval DRTOS_ERR_TIMEOUT
 * @retval DRTOS_ERR_OVERFLOW   Queue full and DRTOS_NO_WAIT specified.
 */
drtos_status_t drtos_queue_send(drtos_queue_handle_t handle,
                                const void          *item,
                                drtos_tick_t         timeout);

/**
 * @brief   Send an item from ISR context.
 *
 * @param[in]  handle              Queue handle.
 * @param[in]  item                Item to enqueue.
 * @param[out] higher_prio_woken   Set to true if a receiver was unblocked.
 *
 * @retval DRTOS_OK
 * @retval DRTOS_ERR_OVERFLOW
 */
drtos_status_t drtos_queue_send_from_isr(drtos_queue_handle_t handle,
                                         const void          *item,
                                         bool                *higher_prio_woken);

/**
 * @brief   Receive (dequeue) an item by copy.
 *
 * @param[in]  handle   Queue handle.
 * @param[out] item     Destination buffer (must be ≥ item_size bytes).
 * @param[in]  timeout  Maximum ticks to wait if the queue is empty.
 *
 * @retval DRTOS_OK
 * @retval DRTOS_ERR_TIMEOUT
 * @retval DRTOS_ERR_UNDERFLOW  Queue empty and DRTOS_NO_WAIT specified.
 */
drtos_status_t drtos_queue_receive(drtos_queue_handle_t handle,
                                   void                *item,
                                   drtos_tick_t         timeout);

/**
 * @brief   Peek at the front item without removing it.
 *
 * @param[in]  handle  Queue handle.
 * @param[out] item    Destination buffer.
 *
 * @retval DRTOS_OK
 * @retval DRTOS_ERR_UNDERFLOW  Queue empty.
 */
drtos_status_t drtos_queue_peek(drtos_queue_handle_t handle,
                                void                *item);

/**
 * @brief   Return the number of items currently in the queue.
 */
uint32_t drtos_queue_count(drtos_queue_handle_t handle);

/**
 * @brief   Return the number of free slots in the queue.
 */
uint32_t drtos_queue_spaces_available(drtos_queue_handle_t handle);

/**
 * @brief   Discard all items in the queue.
 */
drtos_status_t drtos_queue_flush(drtos_queue_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* DRTOS_QUEUE_H */