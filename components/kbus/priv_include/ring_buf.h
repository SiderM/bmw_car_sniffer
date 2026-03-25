#ifndef RING_BUF_H
#define RING_BUF_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define RING_BUF_SIZE 512 // должен быть степенью 2

typedef struct
{
    uint8_t buf[RING_BUF_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
} ring_buf_t;

void ring_buf_init(ring_buf_t *rb);
bool ring_buf_push(ring_buf_t *rb, uint8_t byte);
bool ring_buf_pop(ring_buf_t *rb, uint8_t *byte);
bool ring_buf_peek(ring_buf_t *rb, uint16_t offset, uint8_t *byte);
uint16_t ring_buf_size(ring_buf_t *rb);
bool ring_buf_read(ring_buf_t *rb, uint8_t *dst, uint16_t len);

#endif