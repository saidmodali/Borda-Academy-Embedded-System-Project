#ifndef __I2C_SENSOR_H__
#define __I2C_SENSOR_H__

#include <stdint.h>

// Simulated I2C addresses (not used in simulation, but required for interface consistency)
#define TMP117_ADDR   (0x48 << 1)
#define HTU21D_ADDR   (0x40 << 1)
#define SCD30_ADDR    (0x61 << 1)

// Sensor type enumeration
typedef enum {
    SENSOR_TMP117,
    SENSOR_HTU21D,
    SENSOR_SCD30
} sensor_t;

// Function prototype for reading simulated sensor data
float i2c_sensor_read(uint8_t device_address, sensor_t sensor_type);

#endif // __I2C_SENSOR_H__
