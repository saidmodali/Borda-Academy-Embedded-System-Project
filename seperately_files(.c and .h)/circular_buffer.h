#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <stdint.h>
#include <stdbool.h>

#define BUFFER_CAPACITY 30  // You can change this based on your needs

typedef struct {
    float buffer[BUFFER_CAPACITY];
    uint8_t head;
    uint8_t count;
} circular_buffer_t;

// Initialize the buffer
void buffer_init(circular_buffer_t* cb);

// Add a new value to the buffer (oldest is overwritten if full)
void buffer_add(circular_buffer_t* cb, float value);

// Get all valid data from buffer
uint8_t buffer_get_all(circular_buffer_t* cb, float* out_array);

// Get the most recent value from the buffer
int buffer_get_last(circular_buffer_t* cb, float* last_value);

#endif // __CIRCULAR_BUFFER_H__
