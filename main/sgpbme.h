#pragma once 

#include <string.h>
#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bme280.h"
#include "SGP30.h"
#include "i2c_config.h"

void user_delay_ms(uint32_t ms);
int my_bme280_init(void);

void task_bme280_normal_mode();
void main_task_sgp(void *arg);

void init_sgp();
void read_sgp();

//float EquivalentSeaLevelPressure();

float getTemp();
float getHumid();
float getPressure();
int getTvoc();
int getCO2();
