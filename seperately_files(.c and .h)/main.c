// This project was prepared as part of the Borda Academy Summer Internship & New Graduating Training Program. All rights reserved.
// Author: Said Modali
// Email: smodalim@gmail.com   


#include "i2c.h"
#include "filter.h"
#include "circular_buffer.h"
#include "calculations.h"
#include <stdio.h>
#include <windows.h>
#include <time.h>  // required for srand()

circular_buffer_t temp_buffer;
circular_buffer_t hum_buffer;
circular_buffer_t co2_buffer;

void simulate_sensor_loop(void);

int main(void)
{
    buffer_init(&temp_buffer);
    buffer_init(&hum_buffer);
    buffer_init(&co2_buffer);

    // Continuous simulation loop
    while (1)
    {
        simulate_sensor_loop();
        Sleep(500);  // wait 500 milliseconds
        srand(time(NULL));  // update random seed to ensure value change
        Sleep(500);  // wait another 500 milliseconds
    }
}

void simulate_sensor_loop(void)
{
    // 1. Read simulated sensor data
    float raw_temp = i2c_sensor_read(0x00, SENSOR_TMP117);
    float raw_hum = i2c_sensor_read(0x00, SENSOR_HTU21D);
    float raw_co2 = i2c_sensor_read(0x00, SENSOR_SCD30);

    // 2. Apply median filtering
    float filt_temp = filter_sensor_value(raw_temp, 5);
    float filt_hum = filter_sensor_value(raw_hum, 5);
    float filt_co2 = filter_sensor_value(raw_co2, 5);

    // 3. Store filtered values into circular buffer
    buffer_add(&temp_buffer, filt_temp);
    buffer_add(&hum_buffer, filt_hum);
    buffer_add(&co2_buffer, filt_co2);

    // 4. Retrieve all values from buffer and compute statistics
    float temp_arr[BUFFER_CAPACITY];
    float hum_arr[BUFFER_CAPACITY];
    float co2_arr[BUFFER_CAPACITY];

    uint8_t len_temp = buffer_get_all(&temp_buffer, temp_arr);
    uint8_t len_hum = buffer_get_all(&hum_buffer, hum_arr);
    uint8_t len_co2 = buffer_get_all(&co2_buffer, co2_arr);

    calculation_result_t t_stat, h_stat, c_stat;
    calculate_statistics(temp_arr, len_temp, &t_stat);
    calculate_statistics(hum_arr, len_hum, &h_stat);
    calculate_statistics(co2_arr, len_co2, &c_stat);

    // 5. Print results to terminal (simulating BLE/UART output)
    printf("TEMP => Min: %.2f | Max: %.2f | Median: %.2f | Std: %.2f\n",
        t_stat.min, t_stat.max, t_stat.median, t_stat.std_dev);
    printf("HUM  => Min: %.2f | Max: %.2f | Median: %.2f | Std: %.2f\n",
        h_stat.min, h_stat.max, h_stat.median, h_stat.std_dev);
    printf("CO2  => Min: %.2f | Max: %.2f | Median: %.2f | Std: %.2f\n\n",
        c_stat.min, c_stat.max, c_stat.median, c_stat.std_dev);
}
