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

//void task_bme280_normal_mode(int com_rslt);
void task_bme280_normal_mode();
void main_task_sgp(void *arg);
void init_both();
void read_both();

long int getTemp();
long int getHumid();
long int getPressure();
int getTvoc();
int getCO2();
