#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "i2c.h"

// This function simulates sensor readings by generating random values
// instead of using actual I2C communication

float i2c_sensor_read(uint8_t device_address, sensor_t sensor_type)
{
    float result = -1.0f;

    // Initialize the random number generator once (on first call)
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    switch (sensor_type) {
    case SENSOR_TMP117:
        // Simulated temperature: 20°C – 35°C
        result = 20.0f + (rand() % 1500) / 100.0f;
        break;

    case SENSOR_HTU21D:
        // Simulated humidity: 30% – 80%
        result = 30.0f + (rand() % 5000) / 100.0f;
        break;

    case SENSOR_SCD30:
        // Simulated CO2: 400 – 2000 ppm
        result = 400.0f + (rand() % 1601); // integer value
        break;

    default:
        result = -1.0f; // Invalid sensor type
        break;
    }

    return result;
}
