/**
 * @file    drtos_ringbuffer.h
 * @brief   Single-producer / single-consumer lock-free byte ring buffer.
 *
 * Ideal for UART DMA paths (e.g. LoRa telemetry TX/RX) where one
 * context produces bytes and another consumes them without any
 * kernel lock overhead.
 */

#ifndef DRTOS_RINGBUFFER_H
#define DRTOS_RINGBUFFER_H

#include "drtos_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ──────────── Configuration ─────────────────────────── */

/**
 * @brief   Ring buffer creation descriptor.
 */
typedef struct {
    uint8_t *buffer;    /**< Pre-allocated byte array.              */
    uint32_t capacity;  /**< Size in bytes (must be power of 2).    */
} drtos_ringbuf_config_t;

/* ──────────── API ───────────────────────────────────── */

/**
 * @brief   Initialise a ring buffer.
 *
 * @param[in]  config  Descriptor.
 * @param[out] handle  Receives the ring buffer handle.
 *
 * @retval DRTOS_OK
 * @retval DRTOS_ERR_INVALID_PARAM  Capacity not a power of 2.
 */
drtos_status_t drtos_ringbuf_create(const drtos_ringbuf_config_t *config,
                                    drtos_ringbuf_handle_t       *handle);

/**
 * @brief   Destroy a ring buffer.
 */
drtos_status_t drtos_ringbuf_destroy(drtos_ringbuf_handle_t handle);

/**
 * @brief   Write bytes into the ring buffer (producer side).
 *
 * @param[in]  handle  Ring buffer handle.
 * @param[in]  data    Source bytes.
 * @param[in]  len     Number of bytes to write.
 * @param[out] written Receives the number of bytes actually written
 *                     (may be < len if the buffer is full).
 *
 * @retval DRTOS_OK
 * @retval DRTOS_ERR_OVERFLOW  No room at all.
 */
drtos_status_t drtos_ringbuf_write(drtos_ringbuf_handle_t handle,
                                   const uint8_t         *data,
                                   uint32_t               len,
                                   uint32_t              *written);

/**
 * @brief   Read bytes from the ring buffer (consumer side).
 *
 * @param[in]  handle  Ring buffer handle.
 * @param[out] data    Destination buffer.
 * @param[in]  len     Maximum bytes to read.
 * @param[out] read    Receives the number of bytes actually read.
 *
 * @retval DRTOS_OK
 * @retval DRTOS_ERR_UNDERFLOW  Buffer was empty.
 */
drtos_status_t drtos_ringbuf_read(drtos_ringbuf_handle_t handle,
                                  uint8_t               *data,
                                  uint32_t               len,
                                  uint32_t              *read);

/**
 * @brief   Return the number of bytes available for reading.
 */
uint32_t drtos_ringbuf_count(drtos_ringbuf_handle_t handle);

/**
 * @brief   Return the number of free bytes available for writing.
 */
uint32_t drtos_ringbuf_free(drtos_ringbuf_handle_t handle);

/**
 * @brief   Discard all data in the ring buffer.
 */
drtos_status_t drtos_ringbuf_flush(drtos_ringbuf_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* DRTOS_RINGBUFFER_H */