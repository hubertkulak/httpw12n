#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include "esp_log.h"
#include "freertos/task.h"
#include <sys/param.h>

void init_pms(void);
void read_pms3003(void * arg);

int rpm25();
int rpm10();
int rpm1();