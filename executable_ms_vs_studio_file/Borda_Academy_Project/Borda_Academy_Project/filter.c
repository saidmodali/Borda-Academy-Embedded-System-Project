#include "filter.h"
#include <stdlib.h>
#include <stdint.h>


#define MAX_WINDOW_SIZE 10

float filter_sensor_value(float raw_sensor_value, uint8_t window_size)
{
    static float value_buffer[MAX_WINDOW_SIZE] = { 0 };   // circular buffer
    static uint8_t sample_count = 0;                    // number of stored values
    static uint8_t insert_index = 0;                    // current position in circular buffer

    if (window_size > MAX_WINDOW_SIZE) {
        window_size = MAX_WINDOW_SIZE;
    }

    // Insert new value into circular buffer
    value_buffer[insert_index] = raw_sensor_value;
    insert_index = (insert_index + 1) % window_size;

    // Copy current buffer into a temporary array for sorting
    float sorted_values[MAX_WINDOW_SIZE];
    uint8_t valid_size = (sample_count < window_size) ? (sample_count + 1) : window_size;

    for (uint8_t i = 0; i < valid_size; i++) {
        sorted_values[i] = value_buffer[i];
    }

    // Simple bubble sort for small arrays
    for (uint8_t i = 0; i < valid_size - 1; i++) {
        for (uint8_t j = 0; j < valid_size - i - 1; j++) {
            if (sorted_values[j] > sorted_values[j + 1]) {
                float temp = sorted_values[j];
                sorted_values[j] = sorted_values[j + 1];
                sorted_values[j + 1] = temp;
            }
        }
    }

    sample_count++;

    // Return the median value
    if (valid_size % 2 == 1) {
        return sorted_values[valid_size / 2];
    }
    else {
        return (sorted_values[(valid_size - 1) / 2] + sorted_values[valid_size / 2]) / 2.0f;
    }
}
