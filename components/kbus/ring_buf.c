#include "ring_buf.h"
#include <string.h>

void ring_buf_init(ring_buf_t *rb)
{
    memset(rb, 0, sizeof(ring_buf_t));
}

bool ring_buf_push(ring_buf_t *rb, uint8_t byte)
{
    if (rb->count >= RING_BUF_SIZE)
    {
        return false; // буфер полон
    }
    rb->buf[rb->tail] = byte;
    rb->tail = (rb->tail + 1) & (RING_BUF_SIZE - 1);
    rb->count++;
    return true;
}

bool ring_buf_pop(ring_buf_t *rb, uint8_t *byte)
{
    if (rb->count == 0)
    {
        return false;
    }
    if (byte)
    {
        *byte = rb->buf[rb->head];
    }
    rb->head = (rb->head + 1) & (RING_BUF_SIZE - 1);
    rb->count--;
    return true;
}

// Посмотреть байт по смещению без извлечения
bool ring_buf_peek(ring_buf_t *rb, uint16_t offset, uint8_t *byte)
{
    if (offset >= rb->count)
    {
        return false;
    }
    *byte = rb->buf[(rb->head + offset) & (RING_BUF_SIZE - 1)];
    return true;
}

uint16_t ring_buf_size(ring_buf_t *rb)
{
    return rb->count;
}

// Читает len байт в dst и извлекает их из буфера
bool ring_buf_read(ring_buf_t *rb, uint8_t *dst, uint16_t len)
{
    if (rb->count < len)
    {
        return false;
    }
    for (uint16_t i = 0; i < len; i++)
    {
        ring_buf_pop(rb, &dst[i]);
    }
    return true;
}