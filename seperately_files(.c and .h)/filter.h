#ifndef __FILTER_H__
#define __FILTER_H__

#include <stdint.h>

// Median filter function prototype
float filter_sensor_value(float raw_sensor_value, uint8_t window_size);

#endif // __FILTER_H__
