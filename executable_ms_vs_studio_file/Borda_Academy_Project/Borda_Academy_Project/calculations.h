#ifndef __CALCULATIONS_H__
#define __CALCULATIONS_H__

#include <stdint.h>

// Struct to hold calculated statistical values
typedef struct {
    float min;
    float max;
    float median;
    float std_dev;
} calculation_result_t;

// Function to calculate min, max, median, and std deviation
void calculate_statistics(float* data, uint8_t length, calculation_result_t* result);

#endif // __CALCULATIONS_H__
