#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"


long map(long x, long in_min, long in_max, long out_min, long out_max);

void water(void *arg);

void init_adc(void);

void adc_calibration_init(void);
