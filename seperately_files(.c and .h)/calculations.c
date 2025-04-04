#include "calculations.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>


#define MAX_ARRAY_SIZE 30  // Should match buffer capacity

// Helper: sort array (bubble sort for small arrays)
static void sort_array(float* arr, uint8_t len) {
    for (uint8_t i = 0; i < len - 1; i++) {
        for (uint8_t j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void calculate_statistics(float* data, uint8_t length, calculation_result_t* result)
{
    if (length == 0 || data == NULL || result == NULL)
        return;

    float sum = 0;
    float min = data[0];
    float max = data[0];

    for (uint8_t i = 0; i < length; i++) {
        if (data[i] < min) min = data[i];
        if (data[i] > max) max = data[i];
        sum += data[i];
    }

    // Copy and sort for median
    float sorted[MAX_ARRAY_SIZE];
    for (uint8_t i = 0; i < length; i++) {
        sorted[i] = data[i];
    }
    sort_array(sorted, length);

    float median;
    if (length % 2 == 1) {
        median = sorted[length / 2];
    }
    else {
        median = (sorted[(length - 1) / 2] + sorted[length / 2]) / 2.0f;
    }

    // Standard deviation
    float mean = sum / length;
    float variance = 0;
    for (uint8_t i = 0; i < length; i++) {
        variance += (data[i] - mean) * (data[i] - mean);
    }
    float std_dev = sqrtf(variance / length);

    result->min = min;
    result->max = max;
    result->median = median;
    result->std_dev = std_dev;
}
