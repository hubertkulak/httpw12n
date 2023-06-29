#include <stdio.h>
#include "driver/gpio.h"


#define CON_LED 26
#define DIS_LED 25
#define TRY_LED 27


void configled(int pin);

void ledstateon(int pin);

void ledstateoff(int pin);

void ledstatetoggle(int pin);
