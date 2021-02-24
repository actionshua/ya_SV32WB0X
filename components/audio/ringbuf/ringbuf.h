
#ifndef _RING_BUF_H_
#define _RING_BUF_H_

#include "osal.h"
#include <stdint.h>

typedef struct RingBuf {
    uint8_t* p_o;        /**< Original pointer */
    uint8_t* volatile p_r;   /**< Read pointer */
    uint8_t* volatile p_w;   /**< Write pointer */
    volatile int32_t fill_cnt;  /**< Number of filled slots */
    int32_t size;       /**< Buffer size */
    OsMutex can_read;
    OsMutex can_write;
    OsMutex mux;
    size_t total_sz;
    int abort;
} RingBuf;

struct RingBuf *rb_init(int32_t size);
void rb_abort(struct RingBuf *rb, int val);
int  rb_read(struct RingBuf *r, uint8_t *buf, int len, TickType_t ticks_to_wait, int debug);
int rb_write(struct RingBuf *r, uint8_t *buf, int len, TickType_t ticks_to_wait, int debug);
int32_t rb_isFull(struct RingBuf *rb);
void rb_unint(RingBuf *rb);
#endif
