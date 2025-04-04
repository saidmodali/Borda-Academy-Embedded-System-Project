#include "circular_buffer.h"
#include <stdint.h>


void buffer_init(circular_buffer_t* cb) {
    cb->head = 0;
    cb->count = 0;
}

void buffer_add(circular_buffer_t* cb, float value) {
    cb->buffer[cb->head] = value;
    cb->head = (cb->head + 1) % BUFFER_CAPACITY;

    if (cb->count < BUFFER_CAPACITY)
        cb->count++;
}

uint8_t buffer_get_all(circular_buffer_t* cb, float* out_array) {
    uint8_t i;
    for (i = 0; i < cb->count; i++) {
        uint8_t index = (cb->head + BUFFER_CAPACITY - cb->count + i) % BUFFER_CAPACITY;
        out_array[i] = cb->buffer[index];
    }
    return cb->count;
}

int buffer_get_last(circular_buffer_t* cb, float* last_value) {
    if (cb->count == 0)
        return -1;

    uint8_t last_index = (cb->head + BUFFER_CAPACITY - 1) % BUFFER_CAPACITY;
    *last_value = cb->buffer[last_index];
    return 0;
}
